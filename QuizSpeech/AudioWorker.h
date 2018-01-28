#ifndef GTKMM_TEST001_AUDIOWORKDER_H__
#define GTKMM_TEST001_AUDIOWORKDER_H__


class AudioWorker
{
public:
	AudioWorker(void);
	~AudioWorker(void);

	void start(const std::wstring& filePath);
	void join();
	void processQueue(const std::wstring& filePath);
	void cancelAudio();
	void playSoundFile(const std::wstring& filePath);
	HRESULT AudioWorker::ReadMMIO();
	HRESULT AudioWorker::ResetFile();
	HRESULT AudioWorker::Read( BYTE* pBuffer, DWORD dwSizeToRead, DWORD* pdwSizeRead );


  
private:

	void playSoundFileAsync(const std::wstring& filePath);

	boost::thread m_thread;
	
	WAVEFORMATEX* m_pwfx;
	HMMIO m_hmmio;       // MM I/O handle for the WAVE
	MMCKINFO m_ck;          // Multimedia RIFF chunk
	MMCKINFO m_ckRiff;      // Use in opening a WAVE file
	DWORD m_dwSize;      // The size of the wave file
	CHAR* m_pResourceBuffer;
	BOOL m_bIsReadingFromMemory;
	DWORD m_dwFlags;
	BYTE* m_pbDataCur;
	BYTE* m_pbData;
	MMIOINFO m_mmioinfoOut;
	ULONG m_ulDataSize;
};

#endif GTKMM_TEST001_AUDIOWORKDER_H__