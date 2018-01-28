#include "DictationOverlayDialogHypothesisTimer.h"



DictationOverlayDialogHypothesisTimer::DictationOverlayDialogHypothesisTimer()
{
}


DictationOverlayDialogHypothesisTimer::~DictationOverlayDialogHypothesisTimer()
{
}

void DictationOverlayDialogHypothesisTimer::Notify()
{
	this->txtControl->SetValue(wxString());
}
