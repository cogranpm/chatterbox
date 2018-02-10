/*
NOTE: this is at this stage experimental and not required
it was found out how to fix the AudioPlayerPanelImp class instead which is superior
because it allows the ui to be altered in a gui bilder and is more self contained.
a self contained class that plays audio and shows 
a panel of user controls for the user to control playback
client must provide the panel in which to draw the controls 
so as to avoid sizing issues
*/
#pragma once

#include "stdafx.h"
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
#include "AudioPlayer.h"


class AudioPlayerPanelHelper : public wxEvtHandler
{
	AudioPlayer audioPlayer;
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
	void Play();
public:
	AudioPlayerPanelHelper(wxPanel* targetPanel, wxWindow* parent);
	~AudioPlayerPanelHelper();
	AudioPlayer& GetAudioPlayer() { return audioPlayer; }
	void SetURL(std::wstring url);
	void RenderPanel();
};

