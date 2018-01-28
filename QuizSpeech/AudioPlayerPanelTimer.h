#pragma once
#include <wx/timer.h>
#include <wx/gauge.h>

class AudioPlayerPanelTimer : public wxTimer
{
	wxGauge* gauge;
	
public:
	AudioPlayerPanelTimer();
	~AudioPlayerPanelTimer();
	void Notify();
	void SetGauge(wxGauge* gauge) { this->gauge = gauge; }
	static const int INTERVAL;
};

