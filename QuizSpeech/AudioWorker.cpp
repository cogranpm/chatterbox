#include "stdafx.h"
#include "AudioWorker.h"



using namespace boost::filesystem;

AudioWorker::AudioWorker(void)
{
}


AudioWorker::~AudioWorker(void)
{
}

void AudioWorker::cancelAudio()
{
	::PlaySound(NULL, 0, 0);
}


void AudioWorker::playSoundFile(const std::wstring& fileName)
{
	m_thread = boost::thread(&AudioWorker::playSoundFileAsync, this, fileName);
	//m_thread.join();
}

void AudioWorker::playSoundFileAsync(const std::wstring& fileName)
{
	HRESULT hr;
	CoInitializeEx( NULL, COINIT_MULTITHREADED );
	IXAudio2* pXAudio2 = NULL;

    UINT32 flags = 0;
#ifdef _DEBUG
    flags |= XAUDIO2_DEBUG_ENGINE;
#endif

    if( FAILED( hr = XAudio2Create( &pXAudio2, flags ) ) )
    {
        //wprintf( L"Failed to init XAudio2 engine: %#X\n", hr );
        //CoUninitialize();
        return;
    }

    IXAudio2MasteringVoice* pMasteringVoice = NULL;

    if( FAILED( hr = pXAudio2->CreateMasteringVoice( &pMasteringVoice ) ) )
    {
        //wprintf( L"Failed creating mastering voice: %#X\n", hr );
        SAFE_RELEASE( pXAudio2 );
        //CoUninitialize();
        return;
    }

    m_dwFlags = WAVEFILE_READ;
	m_bIsReadingFromMemory = FALSE;
    if( m_dwFlags == WAVEFILE_READ )
    {
        //SAFE_DELETE_ARRAY( m_pwfx );

        m_hmmio = mmioOpen( const_cast<wchar_t *>(fileName.c_str()), NULL, MMIO_ALLOCBUF | MMIO_READ );

        if( NULL == m_hmmio )
        {
            HRSRC hResInfo;
            HGLOBAL hResData;
            DWORD dwSize;
            VOID* pvRes;

			dwSize = 0;
   
            MMIOINFO mmioInfo;
            ZeroMemory( &mmioInfo, sizeof( mmioInfo ) );
            mmioInfo.fccIOProc = FOURCC_MEM;
            mmioInfo.cchBuffer = dwSize;
            mmioInfo.pchBuffer = ( CHAR* )m_pResourceBuffer;

            m_hmmio = mmioOpen( NULL, &mmioInfo, MMIO_ALLOCBUF | MMIO_READ );
        }

        if( FAILED( hr = this->ReadMMIO() ) )
        {
            // ReadMMIO will fail if its an not a wave file
            mmioClose( m_hmmio, 0 );
			return;
            //return DXTRACE_ERR( L"ReadMMIO", hr );
        }

        if( FAILED( hr = this->ResetFile() ) )
		{
			return;
		}
            //return DXTRACE_ERR( L"ResetFile", hr );

        // After the reset, the size of the wav file is m_ck.cksize so store it now
        m_dwSize = m_ck.cksize;
    }


	WAVEFORMATEX* pwfx = m_pwfx;
	// Calculate how many bytes and samples are in the wave
    DWORD cbWaveSize = m_dwSize;
	// Read the sample data into memory
    BYTE* pbWaveData = new BYTE[ cbWaveSize ];

    if( FAILED( hr = this->Read( pbWaveData, cbWaveSize, &cbWaveSize ) ) )
    {
        SAFE_DELETE_ARRAY( pbWaveData );
        return;
    }



    IXAudio2SourceVoice* pSourceVoice;
    if( FAILED( hr = pXAudio2->CreateSourceVoice( &pSourceVoice, pwfx ) ) )
    {
        SAFE_DELETE_ARRAY( pbWaveData );
        return;
    }

    XAUDIO2_BUFFER buffer = {0};
    buffer.pAudioData = pbWaveData;
    buffer.Flags = XAUDIO2_END_OF_STREAM;  // tell the source voice not to expect any data after this buffer
    buffer.AudioBytes = cbWaveSize;

    if( FAILED( hr = pSourceVoice->SubmitSourceBuffer( &buffer ) ) )
    {
        pSourceVoice->DestroyVoice();
        SAFE_DELETE_ARRAY( pbWaveData );
        return;
    }


    hr = pSourceVoice->Start( 0 );

    // Let the sound play
    BOOL isRunning = TRUE;
    while( SUCCEEDED( hr ) && isRunning )
    {
        XAUDIO2_VOICE_STATE state;
        pSourceVoice->GetState( &state );
        isRunning = ( state.BuffersQueued > 0 ) != 0;

        // Wait till the escape key is pressed
        if( GetAsyncKeyState( VK_ESCAPE ) )
            break;

        Sleep( 10 );
    }

    // Wait till the escape key is released
    while( GetAsyncKeyState( VK_ESCAPE ) )
        Sleep( 10 );

    pSourceVoice->DestroyVoice();
    SAFE_DELETE_ARRAY( pbWaveData );

    pMasteringVoice->DestroyVoice();

    SAFE_RELEASE( pXAudio2 );
    CoUninitialize();
}


HRESULT AudioWorker::Read( BYTE* pBuffer, DWORD dwSizeToRead, DWORD* pdwSizeRead )
{
    if( m_bIsReadingFromMemory )
    {
        if( m_pbDataCur == NULL )
            return CO_E_NOTINITIALIZED;
        if( pdwSizeRead != NULL )
            *pdwSizeRead = 0;

        if( ( BYTE* )( m_pbDataCur + dwSizeToRead ) >
            ( BYTE* )( m_pbData + m_ulDataSize ) )
        {
            dwSizeToRead = m_ulDataSize - ( DWORD )( m_pbDataCur - m_pbData );
        }

#pragma warning( disable: 4616 )    // disable warning about warning number '22104' being out of range
#pragma warning( disable: 22104 )   // disable PREfast warning during static code analysis
        CopyMemory( pBuffer, m_pbDataCur, dwSizeToRead );
#pragma warning( default: 22104 )
#pragma warning( default: 4616 )

        if( pdwSizeRead != NULL )
            *pdwSizeRead = dwSizeToRead;

        return S_OK;
    }
    else
    {
        MMIOINFO mmioinfoIn; // current status of m_hmmio

        if( m_hmmio == NULL )
            return CO_E_NOTINITIALIZED;
        if( pBuffer == NULL || pdwSizeRead == NULL )
            return E_INVALIDARG;

        *pdwSizeRead = 0;

        if( 0 != mmioGetInfo( m_hmmio, &mmioinfoIn, 0 ) )
            return E_FAIL;

        UINT cbDataIn = dwSizeToRead;
        if( cbDataIn > m_ck.cksize )
            cbDataIn = m_ck.cksize;

        m_ck.cksize -= cbDataIn;

        for( DWORD cT = 0; cT < cbDataIn; cT++ )
        {
            // Copy the bytes from the io to the buffer.
            if( mmioinfoIn.pchNext == mmioinfoIn.pchEndRead )
            {
                if( 0 != mmioAdvance( m_hmmio, &mmioinfoIn, MMIO_READ ) )
                    return  E_FAIL;

                if( mmioinfoIn.pchNext == mmioinfoIn.pchEndRead )
                    return E_FAIL;
            }

            // Actual copy.
            *( ( BYTE* )pBuffer + cT ) = *( ( BYTE* )mmioinfoIn.pchNext );
            mmioinfoIn.pchNext++;
        }

        if( 0 != mmioSetInfo( m_hmmio, &mmioinfoIn, 0 ) )
            return E_FAIL;

        *pdwSizeRead = cbDataIn;

        return S_OK;
    }
}

HRESULT AudioWorker::ResetFile()
{
    if( m_bIsReadingFromMemory )
    {
        m_pbDataCur = m_pbData;
    }
    else
    {
        if( m_hmmio == NULL )
            return CO_E_NOTINITIALIZED;

        if( m_dwFlags == WAVEFILE_READ )
        {
            // Seek to the data
            if( -1 == mmioSeek( m_hmmio, m_ckRiff.dwDataOffset + sizeof( FOURCC ),
                                SEEK_SET ) )
                //return DXTRACE_ERR( L"mmioSeek", E_FAIL );
				return E_FAIL;

            // Search the input file for the 'data' chunk.
            m_ck.ckid = mmioFOURCC( 'd', 'a', 't', 'a' );
            if( 0 != mmioDescend( m_hmmio, &m_ck, &m_ckRiff, MMIO_FINDCHUNK ) )
                //return DXTRACE_ERR( L"mmioDescend", E_FAIL );
				return E_FAIL;
        }
        else
        {
            // Create the 'data' chunk that holds the waveform samples.
            m_ck.ckid = mmioFOURCC( 'd', 'a', 't', 'a' );
            m_ck.cksize = 0;

            if( 0 != mmioCreateChunk( m_hmmio, &m_ck, 0 ) )
                //return DXTRACE_ERR( L"mmioCreateChunk", E_FAIL );
				return E_FAIL;

            if( 0 != mmioGetInfo( m_hmmio, &m_mmioinfoOut, 0 ) )
                //return DXTRACE_ERR( L"mmioGetInfo", E_FAIL );
				return E_FAIL;
        }
    }

    return S_OK;

}

HRESULT AudioWorker::ReadMMIO()
{
    MMCKINFO ckIn;           // chunk info. for general use.
    PCMWAVEFORMAT pcmWaveFormat;  // Temp PCM structure to load in.

    memset( &ckIn, 0, sizeof(ckIn) );

    m_pwfx = NULL;

    if( ( 0 != mmioDescend( m_hmmio, &m_ckRiff, NULL, 0 ) ) )
        //return DXTRACE_ERR( L"mmioDescend", E_FAIL );
		return 0;

    // Check to make sure this is a valid wave file
    if( ( m_ckRiff.ckid != FOURCC_RIFF ) ||
        ( m_ckRiff.fccType != mmioFOURCC( 'W', 'A', 'V', 'E' ) ) )
        //return DXTRACE_ERR( L"mmioFOURCC", E_FAIL );
		return 0;

    // Search the input file for for the 'fmt ' chunk.
    ckIn.ckid = mmioFOURCC( 'f', 'm', 't', ' ' );
    if( 0 != mmioDescend( m_hmmio, &ckIn, &m_ckRiff, MMIO_FINDCHUNK ) )
        //return DXTRACE_ERR( L"mmioDescend", E_FAIL );
		return 0;

    // Expect the 'fmt' chunk to be at least as large as <PCMWAVEFORMAT>;
    // if there are extra parameters at the end, we'll ignore them
    if( ckIn.cksize < ( LONG )sizeof( PCMWAVEFORMAT ) )
        //return DXTRACE_ERR( L"sizeof(PCMWAVEFORMAT)", E_FAIL );
		return 0;

    // Read the 'fmt ' chunk into <pcmWaveFormat>.
    if( mmioRead( m_hmmio, ( HPSTR )&pcmWaveFormat,
                  sizeof( pcmWaveFormat ) ) != sizeof( pcmWaveFormat ) )
        //return DXTRACE_ERR( L"mmioRead", E_FAIL );
		return 0;

    // Allocate the waveformatex, but if its not pcm format, read the next
    // word, and thats how many extra bytes to allocate.
    if( pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM )
    {
        m_pwfx = ( WAVEFORMATEX* )new CHAR[ sizeof( WAVEFORMATEX ) ];
        if( NULL == m_pwfx )
            //return DXTRACE_ERR( L"m_pwfx", E_FAIL );
			return 0;

        // Copy the bytes from the pcm structure to the waveformatex structure
        memcpy( m_pwfx, &pcmWaveFormat, sizeof( pcmWaveFormat ) );
        m_pwfx->cbSize = 0;
    }
    else
    {
        // Read in length of extra bytes.
        WORD cbExtraBytes = 0L;
        if( mmioRead( m_hmmio, ( CHAR* )&cbExtraBytes, sizeof( WORD ) ) != sizeof( WORD ) )
            //return DXTRACE_ERR( L"mmioRead", E_FAIL );
			return 0;

        m_pwfx = ( WAVEFORMATEX* )new CHAR[ sizeof( WAVEFORMATEX ) + cbExtraBytes ];
        if( NULL == m_pwfx )
            //return DXTRACE_ERR( L"new", E_FAIL );
			return 0;

        // Copy the bytes from the pcm structure to the waveformatex structure
        memcpy( m_pwfx, &pcmWaveFormat, sizeof( pcmWaveFormat ) );
        m_pwfx->cbSize = cbExtraBytes;

        // Now, read those extra bytes into the structure, if cbExtraAlloc != 0.
        if( mmioRead( m_hmmio, ( CHAR* )( ( ( BYTE* )&( m_pwfx->cbSize ) ) + sizeof( WORD ) ),
                      cbExtraBytes ) != cbExtraBytes )
        {
            SAFE_DELETE( m_pwfx );
            //return DXTRACE_ERR( L"mmioRead", E_FAIL );
			return 0;
        }
    }

    // Ascend the input file out of the 'fmt ' chunk.
    if( 0 != mmioAscend( m_hmmio, &ckIn, 0 ) )
    {
        SAFE_DELETE( m_pwfx );
        //return DXTRACE_ERR( L"mmioAscend", E_FAIL );
		return 0;
    }

    return S_OK;
}



void AudioWorker::start(const std::wstring& fileName)
{
	m_thread = boost::thread(&AudioWorker::processQueue, this, fileName);
	//m_thread = boost::thread(&AudioWorker::playSoundFile, this, fileName);
	//processQueue(fileName);
}

void AudioWorker::join(void)
{
	m_thread.join();
}

void AudioWorker::processQueue(const std::wstring& fileName)
{
	
	if (exists(fileName))    // does p actually exist?
	{
		if (is_directory(fileName))      // is p a directory?
		{

			directory_iterator end_iter;
			typedef std::multimap<std::time_t, path> result_set_t;
			result_set_t result_set;

			for( directory_iterator dir_iter(fileName) ; dir_iter != end_iter ; ++dir_iter)
			{
				if (is_regular_file(dir_iter->status()) )
				{
					result_set.insert(result_set_t::value_type(last_write_time(*dir_iter), *dir_iter));
				}
			}

			for (result_set_t::iterator it = result_set.begin(); it != result_set.end();++it)
			{
				path p((*it).second );
				std::wstring fileNamex = p.wstring();
				std::wstring extension = p.extension().wstring();
				if(extension == ".wav")
				{
					//this->PlaySound(p.string());
					//::PlaySound(p.string().c_str(), NULL, SND_SYNC | SND_NOSTOP); 
					playSoundFile(p.wstring().c_str());
					//std::cout << p.string();
				}
			}
		}
		else
		{
			path p(fileName);
			std::wstring extension = p.extension().wstring();
			if(extension == ".wav")
			{
				playSoundFile(p.wstring().c_str());
			}
		}
	}


}
