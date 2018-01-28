#pragma once
#include <wx/timer.h>
#include <wx/gauge.h>

class DictationOverlayUpdateTimer : public wxTimer
{
	wxGauge* gauge;

public:
	DictationOverlayUpdateTimer();
	~DictationOverlayUpdateTimer();
	void Notify();
	void SetGauge(wxGauge* gauge) { this->gauge = gauge; }
};

