#include "DictationOverlayUpdateTimer.h"



DictationOverlayUpdateTimer::DictationOverlayUpdateTimer()
	: wxTimer()
{
}


DictationOverlayUpdateTimer::~DictationOverlayUpdateTimer()
{
}

void DictationOverlayUpdateTimer::Notify()
{
	gauge->SetValue(0);
	this->Stop();
}