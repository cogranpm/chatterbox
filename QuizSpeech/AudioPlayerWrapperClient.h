#pragma once
class AudioPlayerWrapperClient
{
public:
	AudioPlayerWrapperClient();
	~AudioPlayerWrapperClient();
	virtual void PlayCompleted() = 0;
};

