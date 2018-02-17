#include "AudioPlayer.h"
#include "GlobalConstants.h"
#include <wx/log.h>



AudioPlayer::AudioPlayer() :
	playState(AudioState::unloaded),
	mediaSource(nullptr), 
	session(nullptr),
	mediaSourceObject(NULL), 
	presentationDescriptor(NULL),
	sourceResolver(NULL),
	callback(new AudioPlayer::EventCallback()),
	sourceCallback(new AudioPlayer::SourceCallback())
{

	
	
}


AudioPlayer::~AudioPlayer()
{
	HRESULT hr = S_OK;
	DWORD dwWaitResult = 0;

	SafeRelease(&presentationDescriptor);
	SafeRelease(&sourceResolver);
	SafeRelease(&mediaSourceObject);
	//presentationDescriptor->Release();
	//sourceResolver->Release();
	//mediaSourceObject->Release();

	if (session != nullptr)
	{
		hr = session->Close();
		if (SUCCEEDED(hr))
		{
			dwWaitResult = WaitForSingleObject(m_hCloseEvent, 5000);
			if (dwWaitResult == WAIT_TIMEOUT)
			{
				assert(FALSE);
			}
			// Now there will be no more events from this session.
		}
		session->Shutdown();
		SafeRelease(&session);
		session = nullptr;
	}
	
	//(void)(mediaSourceObject)->Shutdown();

	if (callback != nullptr)
	{
		callback->Release();
		callback = nullptr;
	}

	if (sourceCallback != nullptr)
	{
		sourceCallback->Release();
		sourceCallback = nullptr;
	}
}

//AudioPlayer::AudioPlayer(const AudioPlayer &copy)
//{
//	/* for dynamically allocated memory, reallocate and copy value
//	ptr = new int;
//   *ptr = *obj.ptr; // copy the value
//	*/
//	callback = new AudioPlayer::EventCallback();
//	*callback = *copy.callback;
//	path = copy.path;
//	playState = copy.playState;
//	*session = *copy.session;
//	*mediaSource = *copy.mediaSource;
//	*sourceResolver = *copy.sourceResolver;
//	*presentationDescriptor = *copy.presentationDescriptor;
//
//}
//
//AudioPlayer& AudioPlayer::operator=(AudioPlayer const& copy)
//{
//	if (this != &copy) // protect against invalid self-assignment
//	{
//		callback = new AudioPlayer::EventCallback();
//		*callback = *copy.callback;
//		path = copy.path;
//		playState = copy.playState;
//		*session = *copy.session;
//		*mediaSource = *copy.mediaSource;
//		*sourceResolver = *copy.sourceResolver;
//		*presentationDescriptor = *copy.presentationDescriptor;
//	}
//	// by convention, always return *this
//	return *this;
//}


void AudioPlayer::Init()
{
	HRESULT hr = MFStartup(MF_VERSION);
	if (FAILED(hr))
	{
		/*
		MF_E_BAD_STARTUP_VERSION
		MF_E_DISABLED_IN_SAFEMODE
		E_NOTIMPL
		*/
	}
}

void AudioPlayer::ShutDown()
{
	MFShutdown();
}


void AudioPlayer::Pause()
{
	HRESULT hr = S_OK;
	hr = this->session->Pause();
	if (FAILED(hr))
	{
		::PrintError(std::wstring(L"Pause failed"), hr);
		return;
	}
	this->playState = AudioState::paused;
}

void AudioPlayer::Resume()
{
	HRESULT hr = S_OK;
	PROPVARIANT varResume;
	PropVariantInit(&varResume);
	hr = this->session->Start(NULL, &varResume);
	if (FAILED(hr))
	{
		::PrintError(std::wstring(L"Resume failed"), hr);
		goto done;
	}
	this->playState = AudioState::playing;

done:
	PropVariantClear(&varResume);
}

void AudioPlayer::Stop()
{
	HRESULT hr = this->session->Stop();
	if (FAILED(hr))
	{
		::PrintError(std::wstring(L"Stop failed"), hr);
	}
	this->playState = AudioState::stopped;
}

void AudioPlayer::Clear()
{
	path = std::wstring(L"");
	SafeRelease(&presentationDescriptor);
	SafeRelease(&sourceResolver);
	SafeRelease(&mediaSourceObject);

	HRESULT hr = S_OK;
	DWORD dwWaitResult;
	if (session != nullptr)
	{
		hr = session->ClearTopologies();
		hr = session->Close();
		if (SUCCEEDED(hr))
		{
			dwWaitResult = WaitForSingleObject(m_hCloseEvent, 5000);
			if (dwWaitResult == WAIT_TIMEOUT)
			{
				assert(FALSE);
			}
			// Now there will be no more events from this session.
		}
		session->Shutdown();
		SafeRelease(&session);
		session = nullptr;
	}
	playState = AudioState::unloaded;
	m_clearUrl();
}


void AudioPlayer::SetURL(const std::wstring& url)
{
	path = url;

	HRESULT hr = S_OK;

	hr = MFCreateMediaSession(NULL, &session);
	if (FAILED(hr))
	{
		::PrintError(std::wstring(L"MFCreateMediaSession failed"), hr);
		return;
	}
	callback->SetPlayer(this);
	hr = session->BeginGetEvent(callback, NULL);
	if (FAILED(hr))
	{
		::PrintError(std::wstring(L"BeginGetEvent failed"), hr);
		return;
	}

	MF_OBJECT_TYPE ObjectType = MF_OBJECT_INVALID;
	hr = MFCreateSourceResolver(&sourceResolver);
	if (FAILED(hr))
	{
		::PrintError(std::wstring(L"MFCreateSourceResolver failed"), hr);
		return;
	}


	hr = sourceResolver->CreateObjectFromURL(
		path.c_str(),                       // URL of the source.
		MF_RESOLUTION_MEDIASOURCE,  // Create a source object.
		NULL,                       // Optional property store.
		&ObjectType,        // Receives the created object type. 
		&mediaSourceObject            // Receives a pointer to the media source.
	);

	if (FAILED(hr))
	{
		::PrintError(std::wstring(L"CreateObjectFromURL failed"), hr);
		return;
	}
	hr = mediaSourceObject->QueryInterface(IID_PPV_ARGS(&mediaSource));
	if (FAILED(hr))
	{
		::PrintError(std::wstring(L"QueryInterface failed"), hr);
		return;
	}
	hr = mediaSource->CreatePresentationDescriptor(&presentationDescriptor);
	if (FAILED(hr))
	{
		::PrintError(std::wstring(L"CreatePresentationDescriptor failed"), hr);
		return;
	}
	playState = AudioState::loaded;
	m_audioUrl();

}

void AudioPlayer::SetURLAsync(const std::wstring& url)
{
	path = url;
	HRESULT hr = S_OK;
	hr = MFCreateMediaSession(NULL, &session);
	if (FAILED(hr))
	{
		::PrintError(std::wstring(L"MFCreateMediaSession failed"), hr);
		return;
	}
	callback->SetPlayer(this);
	hr = session->BeginGetEvent(callback, NULL);
	if (FAILED(hr))
	{
		::PrintError(std::wstring(L"BeginGetEvent failed"), hr);
		return;
	}

	
	hr = MFCreateSourceResolver(&sourceResolver);
	if (FAILED(hr))
	{
		::PrintError(std::wstring(L"MFCreateSourceResolver failed"), hr);
		return;
	}
	
	sourceCallback->SetPlayer(this);
	hr = sourceResolver->BeginCreateObjectFromURL(
		path.c_str(),
		MF_RESOLUTION_MEDIASOURCE,
		NULL,
		NULL,
		sourceCallback,
		NULL
	);


	if (FAILED(hr))
	{
		::PrintError(std::wstring(L"CreateObjectFromURL failed"), hr);
		return;
	}

}

std::wstring& AudioPlayer::GetURL()
{
	return path;
}

double AudioPlayer::GetDuration()
{
	MFTIME pDuration = 0;
	HRESULT hr = presentationDescriptor->GetUINT64(MF_PD_DURATION, (UINT64*)&pDuration);
	if (FAILED(hr))
	{
		::PrintError(std::wstring(L"GetUINT64 failed"), hr);
		return 0.0;
	}
	return (double)(pDuration / (double)ONE_SECOND);
}

void AudioPlayer::Play()
{
	HRESULT hr = S_OK;
	IMFTopology *pTopology = NULL;
	DWORD cSourceStreams = 0;

	// Create a new topology.
	hr = MFCreateTopology(&pTopology);
	if (FAILED(hr))
	{
		::PrintError(std::wstring(L"MFCreateTopology failed"), hr);
		return;
	}

	hr = presentationDescriptor->GetStreamDescriptorCount(&cSourceStreams);
	if (FAILED(hr))
	{
		::PrintError(std::wstring(L"GetStreamDescriptorCount failed"), hr);
		return;
	}

	// For each stream, create the topology nodes and add them to the topology.
	for (DWORD i = 0; i < cSourceStreams; i++)
	{
		hr = AddBranchToPartialTopology(pTopology, i);
		if (FAILED(hr))
		{
			goto done;
		}
	}

	hr = session->SetTopology(0, pTopology);
	if (FAILED(hr))
	{
		::PrintError(std::wstring(L"SetTopology failed"), hr);
		goto done;
	}

done:
	SafeRelease(&pTopology);
}


HRESULT AudioPlayer::AddBranchToPartialTopology(IMFTopology* pTopology, DWORD iStream)
{
	IMFStreamDescriptor *pSD = NULL;
	IMFActivate         *pSinkActivate = NULL;
	IMFTopologyNode     *pSourceNode = NULL;
	IMFTopologyNode     *pOutputNode = NULL;
	BOOL fSelected = FALSE;

	HRESULT hr = presentationDescriptor->GetStreamDescriptorByIndex(iStream, &fSelected, &pSD);
	if (FAILED(hr))
	{
		::PrintError(std::wstring(L"GetStreamDescriptorByIndex failed"), hr);
		goto done;
	}
	if (fSelected)
	{
		// Create the media sink activation object.
		hr = CreateMediaSinkActivate(pSD, &pSinkActivate);
		if (FAILED(hr))
		{
			::PrintError(std::wstring(L"CreateMediaSinkActivate failed"), hr);
			goto done;
		}

		// Add a source node for this stream.
		hr = AddSourceNode(pTopology, pSD, &pSourceNode);
		if (FAILED(hr))
		{
			goto done;
		}

		// Create the output node for the renderer.
		hr = AddOutputNode(pTopology, pSinkActivate, 0, &pOutputNode);
		if (FAILED(hr))
		{
			goto done;
		}

		// Connect the source node to the output node.
		hr = pSourceNode->ConnectOutput(0, pOutputNode, 0);
	}

done:
	SafeRelease(&pSD);
	SafeRelease(&pSinkActivate);
	SafeRelease(&pSourceNode);
	SafeRelease(&pOutputNode);
	return hr;
}


HRESULT AudioPlayer::CreateMediaSinkActivate(IMFStreamDescriptor *pSourceSD, IMFActivate **ppActivate)
{
	IMFMediaTypeHandler *pHandler = NULL;
	IMFActivate *pActivate = NULL;

	// Get the media type handler for the stream.
	HRESULT hr = pSourceSD->GetMediaTypeHandler(&pHandler);
	if (FAILED(hr))
	{
		::PrintError(std::wstring(L"GetMediaTypeHandler failed"), hr);
		goto done;
	}

	// Get the major media type.
	GUID guidMajorType;
	hr = pHandler->GetMajorType(&guidMajorType);
	if (FAILED(hr))
	{
		::PrintError(std::wstring(L"GetMajorType failed"), hr);
		goto done;
	}

	// Create an IMFActivate object for the renderer, based on the media type.
	if (MFMediaType_Audio == guidMajorType)
	{
		// Create the audio renderer.
		hr = MFCreateAudioRendererActivate(&pActivate);
	}
	else
	{
		// Unknown stream type. 
		hr = E_FAIL;
		// Optionally, you could deselect this stream instead of failing.
	}
	if (FAILED(hr))
	{
		goto done;
	}

	// Return IMFActivate pointer to caller.
	*ppActivate = pActivate;
	(*ppActivate)->AddRef();

done:
	SafeRelease(&pHandler);
	SafeRelease(&pActivate);
	return hr;
}

HRESULT AudioPlayer::AddSourceNode(IMFTopology *pTopology, IMFStreamDescriptor *pSD, IMFTopologyNode **ppNode)
{
	IMFTopologyNode *pNode = NULL;

	// Create the node.
	HRESULT hr = MFCreateTopologyNode(MF_TOPOLOGY_SOURCESTREAM_NODE, &pNode);
	if (FAILED(hr))
	{
		goto done;
	}

	// Set the attributes.
	hr = pNode->SetUnknown(MF_TOPONODE_SOURCE, mediaSource);
	if (FAILED(hr))
	{
		goto done;
	}

	hr = pNode->SetUnknown(MF_TOPONODE_PRESENTATION_DESCRIPTOR, presentationDescriptor);
	if (FAILED(hr))
	{
		goto done;
	}

	hr = pNode->SetUnknown(MF_TOPONODE_STREAM_DESCRIPTOR, pSD);
	if (FAILED(hr))
	{
		goto done;
	}

	// Add the node to the topology.
	hr = pTopology->AddNode(pNode);
	if (FAILED(hr))
	{
		goto done;
	}

	// Return the pointer to the caller.
	*ppNode = pNode;
	(*ppNode)->AddRef();

done:
	SafeRelease(&pNode);
	return hr;
}

HRESULT AudioPlayer::AddOutputNode(IMFTopology *pTopology, IMFActivate *pActivate, DWORD dwId, IMFTopologyNode **ppNode)
{
	IMFTopologyNode *pNode = NULL;

	// Create the node.
	HRESULT hr = MFCreateTopologyNode(MF_TOPOLOGY_OUTPUT_NODE, &pNode);
	if (FAILED(hr))
	{
		goto done;
	}

	// Set the object pointer.
	hr = pNode->SetObject(pActivate);
	if (FAILED(hr))
	{
		goto done;
	}

	// Set the stream sink ID attribute.
	hr = pNode->SetUINT32(MF_TOPONODE_STREAMID, dwId);
	if (FAILED(hr))
	{
		goto done;
	}

	hr = pNode->SetUINT32(MF_TOPONODE_NOSHUTDOWN_ON_REMOVE, FALSE);
	if (FAILED(hr))
	{
		goto done;
	}

	// Add the node to the topology.
	hr = pTopology->AddNode(pNode);
	if (FAILED(hr))
	{
		goto done;
	}

	// Return the pointer to the caller.
	*ppNode = pNode;
	(*ppNode)->AddRef();

done:
	SafeRelease(&pNode);
	return hr;
}


AudioPlayer::SourceCallback::SourceCallback()
{

}

AudioPlayer::SourceCallback::~SourceCallback()
{

}

HRESULT AudioPlayer::SourceCallback::Invoke(IMFAsyncResult* pAsyncResult)
{
	MF_OBJECT_TYPE ObjectType = MF_OBJECT_INVALID;
	player->sourceResolver->EndCreateObjectFromURL(pAsyncResult, &ObjectType, &player->mediaSourceObject);
	HRESULT hr = player->mediaSourceObject->QueryInterface(IID_PPV_ARGS(&player->mediaSource));
	if (FAILED(hr))
	{
		::PrintError(std::wstring(L"QueryInterface failed"), hr);
		return hr;
	}
	hr = player->mediaSource->CreatePresentationDescriptor(&player->presentationDescriptor);
	if (FAILED(hr))
	{
		::PrintError(std::wstring(L"CreatePresentationDescriptor failed"), hr);
		return hr;
	}
	player->playState = AudioState::loaded;
	player->m_audioUrl();


	return S_OK;
}

AudioPlayer::EventCallback::EventCallback() 
{

}

AudioPlayer::EventCallback::~EventCallback()
{

}

HRESULT AudioPlayer::EventCallback::Invoke(IMFAsyncResult* pAsyncResult)
{
	MediaEventType meType = MEUnknown;  // Event type
	IMFMediaEvent *pEvent = NULL;
	HRESULT hr = player->session->EndGetEvent(pAsyncResult, &pEvent);
	if (FAILED(hr))
	{
		goto done;
	}

	hr = pEvent->GetType(&meType);
	if (FAILED(hr))
	{
		goto done;
	}

	HRESULT hrStatus = S_OK;
	hr = pEvent->GetStatus(&hrStatus);
	if (SUCCEEDED(hr) && FAILED(hrStatus))
	{
		hr = hrStatus;
	}
	if (FAILED(hr))
	{
		goto done;
	}
	switch (meType)
	{
	case MESessionTopologyStatus:
		hr = OnTopologyStatus(pEvent);
		break;

	case MEEndOfPresentation:
		hr = OnPresentationEnded(pEvent);
		break;

	case MENewPresentation:
		hr = OnNewPresentation(pEvent);
		break;

	default:
		hr = OnSessionEvent(pEvent, meType);
		break;
	}


	/* there may be another event */
	if (meType != MESessionClosed && meType != MEEndOfPresentation)
	{
		hr = player->session->BeginGetEvent(this, NULL);
		if (FAILED(hr))
		{
			goto done;
		}
	}

done:
	SafeRelease(&pEvent);
	return S_OK;

}

HRESULT AudioPlayer::EventCallback::OnTopologyStatus(IMFMediaEvent *pEvent)
{
	UINT32 status;
	HRESULT hr = pEvent->GetUINT32(MF_EVENT_TOPOLOGY_STATUS, &status);
	if (SUCCEEDED(hr) && (status == MF_TOPOSTATUS_READY))
	{
		assert(this->player->session != NULL);
		PROPVARIANT varStart;
		PropVariantInit(&varStart);
		HRESULT hr = this->player->session->Start(&GUID_NULL, &varStart);
		if (SUCCEEDED(hr))
		{
			this->player->playState = AudioState::playing;
			// Note: Start is an asynchronous operation. However, we
			// can treat our state as being already started. If Start
			// fails later, we'll get an MESessionStarted event with
			// an error code, and we will update our state then.
			//m_state = Started;
		}
		PropVariantClear(&varStart);
		return hr;
	}
	return hr;
}

HRESULT AudioPlayer::EventCallback::OnPresentationEnded(IMFMediaEvent *pEvent)
{
	this->player->playState = AudioState::loaded;
	this->player->m_audioEnd();
	return S_OK;
}


HRESULT AudioPlayer::EventCallback::OnNewPresentation(IMFMediaEvent *pEvent)
{
	return S_OK;
}


/* signals and slots for interested observers */
boost::signals2::connection AudioPlayer::OnAudioEnd(type_audio_end::slot_function_type subscriber)
{
	return m_audioEnd.connect(subscriber);
}


boost::signals2::connection AudioPlayer::OnAudioUrl(type_audio_url::slot_function_type subscriber)
{
	return m_audioUrl.connect(subscriber);
}

boost::signals2::connection AudioPlayer::OnClearUrl(type_clear_url::slot_function_type subscriber)
{
	return m_clearUrl.connect(subscriber);
}