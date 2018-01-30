#pragma once
#include "AudioPlayer.h"
#include "stdafx.h"
#include "AudioPlayerWrapperClient.h"

class NoteAudioPlayer;

class AudioPlayerWrapper
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

public:
	AudioPlayerWrapper(AudioPlayerWrapperClient* callingInstance, std::wstring& url);
	~AudioPlayerWrapper();
	void Play();
	void Stop();
	AudioPlayer& GetAudioPlayer() { return audioPlayer; }
	void SetURL(std::wstring url);
};

