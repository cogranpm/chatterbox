#pragma once
#include <wx/timer.h>
#include <wx/textctrl.h>

class DictationOverlayDialogHypothesisTimer : public wxTimer
{
	wxTextCtrl* txtControl;

public:
	DictationOverlayDialogHypothesisTimer();
	~DictationOverlayDialogHypothesisTimer();
	void Notify();
	void SetTextControl(wxTextCtrl* txtControl) { this->txtControl = txtControl; }
};

