#pragma once
#include "AudioPlayerCallback.h"



template <class T> void SafeRelease(T **ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}


class AudioPlayer 
{
	IMFMediaSession* session;
	IMFMediaSource* mediaSource;
	IUnknown* mediaSourceObject;
	IMFSourceResolver* sourceResolver;
	IMFPresentationDescriptor* presentationDescriptor;
	HANDLE m_hCloseEvent;
	
	class SourceCallback : public IMFAsyncCallback
	{
		long m_cRef;
		AudioPlayer* player;

	
	public:
		SourceCallback();
		~SourceCallback();
		void SetPlayer(AudioPlayer* player) { this->player = player; }


		STDMETHODIMP QueryInterface(REFIID riid, void** ppv)
		{
			static const QITAB qit[] =
			{
				QITABENT(SourceCallback, IMFPMediaPlayerCallback),
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

		virtual HRESULT OnSessionEvent(IMFMediaEvent*, MediaEventType)
		{
			return S_OK;
		}

	};

	
	class EventCallback : public IMFAsyncCallback
	{
		long m_cRef;
		AudioPlayer* player;

	protected:
		HRESULT OnTopologyStatus(IMFMediaEvent *pEvent);
		HRESULT OnPresentationEnded(IMFMediaEvent *pEvent);
		HRESULT OnNewPresentation(IMFMediaEvent *pEvent);
	public:
		EventCallback();
		~EventCallback();
		void SetPlayer(AudioPlayer* player) { this->player = player; }


		STDMETHODIMP QueryInterface(REFIID riid, void** ppv)
		{
			static const QITAB qit[] =
			{
				QITABENT(EventCallback, IMFPMediaPlayerCallback),
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

		virtual HRESULT OnSessionEvent(IMFMediaEvent*, MediaEventType)
		{
			return S_OK;
		}

	};

	EventCallback* callback;
	SourceCallback* sourceCallback;
	std::wstring path;

	HRESULT AddBranchToPartialTopology(IMFTopology *pTopology, DWORD iStream);
	HRESULT CreateMediaSinkActivate(IMFStreamDescriptor *pSourceSD, IMFActivate **ppActivate);
	HRESULT AddSourceNode(IMFTopology *pTopology,  IMFStreamDescriptor *pSD, IMFTopologyNode **ppNode);
	HRESULT AddOutputNode(IMFTopology *pTopology, IMFActivate *pActivate, DWORD dwId, IMFTopologyNode **ppNode);
	
	bool ValidatePath();

public:
	enum class AudioState { unloaded, loaded, playing, paused, stopped, invalidfile };
	AudioPlayer();
	~AudioPlayer();
	//AudioPlayer(const AudioPlayer& copy);
	//AudioPlayer& operator=(AudioPlayer const& copy);


	static void Init();
	static void ShutDown();
	double GetDuration();
	void Play();
	void Pause();
	void Resume();
	void Stop();
	void SetURL(const std::wstring& url);
	void SetURLAsync(const std::wstring& url);
	std::wstring& GetURL();
	void Clear();
	AudioState GetPlayState() { return playState; }

	typedef boost::signals2::signal<void()>  type_audio_end;
	typedef boost::signals2::signal<void()>  type_audio_url;
	typedef boost::signals2::signal<void()>  type_clear_url;
	boost::signals2::connection OnAudioEnd(type_audio_end::slot_function_type subscriber);
	boost::signals2::connection OnAudioUrl(type_audio_url::slot_function_type subscriber);
	boost::signals2::connection OnClearUrl(type_clear_url::slot_function_type subscriber);
	type_audio_end m_audioEnd;
	type_audio_url m_audioUrl;
	type_clear_url m_clearUrl;

private:
	AudioState playState;


};

