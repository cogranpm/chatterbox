#pragma once
#include "stdafx.h"
#include <Shlwapi.h>


class AudioPlayerCallback : public IMFAsyncCallback
{

	long m_cRef; // Reference count
	IMFPMediaPlayer* player;

public:
	AudioPlayerCallback();
	~AudioPlayerCallback();
	void SetPlayer(IMFPMediaPlayer* player);

	STDMETHODIMP QueryInterface(REFIID riid, void** ppv)
	{
		static const QITAB qit[] =
		{
			QITABENT(AudioPlayerCallback, IMFPMediaPlayerCallback),
			{ 0 },
		};
		return QISearch(this, qit, riid, ppv);
	}
	STDMETHODIMP_(ULONG) AddRef()
	{
		return InterlockedIncrement(&m_cRef);
	}
	STDMETHODIMP_(ULONG) Release()
	{
		ULONG count = InterlockedDecrement(&m_cRef);
		if (count == 0)
		{
			delete this;
			return 0;
		}
		return count;
	}

	STDMETHODIMP  GetParameters(DWORD*, DWORD*)
	{
		// Implementation of this method is optional.
		return E_NOTIMPL;
	}

	STDMETHODIMP  Invoke(IMFAsyncResult* pAsyncResult);
	//void STDMETHODCALLTYPE OnMediaPlayerEvent(MFP_EVENT_HEADER *pEventHeader);
};

