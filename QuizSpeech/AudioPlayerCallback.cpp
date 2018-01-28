#include "AudioPlayerCallback.h"


AudioPlayerCallback::AudioPlayerCallback() : m_cRef(1)
{
}


AudioPlayerCallback::~AudioPlayerCallback()
{
}

void AudioPlayerCallback::SetPlayer(IMFPMediaPlayer* player)
{
	this->player = player;
}

HRESULT AudioPlayerCallback::Invoke(IMFAsyncResult* pAsyncResult)
{
	MediaEventType meType = MEUnknown;  // Event type

	IMFMediaEvent *pEvent = NULL;
	return S_OK;

//	// Get the event from the event queue.
//	HRESULT hr = m_pSession->EndGetEvent(pResult, &pEvent);
//	if (FAILED(hr))
//	{
//		goto done;
//	}
//
//	// Get the event type. 
//	hr = pEvent->GetType(&meType);
//	if (FAILED(hr))
//	{
//		goto done;
//	}
//
//	if (meType == MESessionClosed)
//	{
//		// The session was closed. 
//		// The application is waiting on the m_hCloseEvent event handle. 
//		SetEvent(m_hCloseEvent);
//	}
//	else
//	{
//		// For all other events, get the next event in the queue.
//		hr = m_pSession->BeginGetEvent(this, NULL);
//		if (FAILED(hr))
//		{
//			goto done;
//		}
//	}
//
//	// Check the application state. 
//
//	// If a call to IMFMediaSession::Close is pending, it means the 
//	// application is waiting on the m_hCloseEvent event and
//	// the application's message loop is blocked. 
//
//	// Otherwise, post a private window message to the application. 
//
//	if (m_state != Closing)
//	{
//		// Leave a reference count on the event.
//		pEvent->AddRef();
//
//		PostMessage(m_hwndEvent, WM_APP_PLAYER_EVENT,
//			(WPARAM)pEvent, (LPARAM)meType);
//	}
//
//done:
//	SafeRelease(&pEvent);
//	return S_OK;
	
}

/*
void STDMETHODCALLTYPE AudioPlayerCallback::OnMediaPlayerEvent(MFP_EVENT_HEADER *pEventHeader)
{


	HRESULT hr;
	if (FAILED(pEventHeader->hrEvent))
	{
		//ShowErrorMessage(L"Playback error", pEventHeader->hrEvent);
		return;
	}
	MFP_MEDIAITEM_CREATED_EVENT *pEvent = MFP_GET_MEDIAITEM_CREATED_EVENT(pEventHeader);

	switch (pEventHeader->eEventType)
	{
	case MFP_EVENT_TYPE_MEDIAITEM_CREATED:
		//OnMediaItemCreated(MFP_GET_MEDIAITEM_CREATED_EVENT(pEventHeader));
		
		hr = player->SetMediaItem(pEvent->pMediaItem);
		break;

	case MFP_EVENT_TYPE_MEDIAITEM_SET:
		//OnMediaItemSet(MFP_GET_MEDIAITEM_SET_EVENT(pEventHeader));
		hr = player->Play();
		break;
	}
}
*/