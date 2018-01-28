#include "AudioPlayerPanelTimer.h"


const int AudioPlayerPanelTimer::INTERVAL = 100;

AudioPlayerPanelTimer::AudioPlayerPanelTimer() : gauge(nullptr)
{
	
}


AudioPlayerPanelTimer::~AudioPlayerPanelTimer()
{
}

void AudioPlayerPanelTimer::Notify()
{
	int range = this->gauge->GetRange();
	int currentValue = this->gauge->GetValue();
	int remaining = range - currentValue;
	int increment = (range / INTERVAL);
	this->gauge->SetValue(currentValue + increment);
}
