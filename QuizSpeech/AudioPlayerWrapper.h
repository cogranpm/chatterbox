#pragma once
#include "AudioPlayer.h"
#include "stdafx.h"
#include "AudioPlayerWrapperClient.h"
#include "AudioPlayerPanelTimer.h"
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/gauge.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/event.h>

class NoteAudioPlayer;

class AudioPlayerWrapper : public wxEvtHandler
{
	AudioPlayerWrapperClient* callingInstance;
	std::wstring url;
	AudioPlayer audioPlayer;
	std::queue<std::wstring> audiofiles;
	boost::signals2::connection onUrlConnection;
	boost::signals2::connection onAudioEndConnection;
	boost::signals2::connection onClearUrlConnection;
	void OnAudioURL();
	void OnAudioEnd();
	void OnClearURL();
	wxWindow* parent;
	wxPanel* targetPanel;
	AudioPlayerPanelTimer timer;
	wxGauge* m_gauge2;
	wxStaticText* txtDuration;
	wxButton* btnPlay;
	void PlayOnButtonClick(wxCommandEvent& event);

public:
	AudioPlayerWrapper(AudioPlayerWrapperClient* callingInstance, std::wstring& url);
	AudioPlayerWrapper(AudioPlayerWrapperClient* callingInstance, std::wstring& url, wxPanel* targetPanel, wxWindow* parent);
	~AudioPlayerWrapper();
	void Play();
	void Stop();
	AudioPlayer& GetAudioPlayer() { return audioPlayer; }
	void SetURL(std::wstring url);
	void RenderPanel();
};

