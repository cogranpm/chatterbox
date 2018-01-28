#include "AudioPlayerWrapper.h"
#include "NoteAudioPlayer.h"


AudioPlayerWrapper::AudioPlayerWrapper(AudioPlayerWrapperClient* callingInstance, std::wstring& url) : callingInstance(callingInstance), url(url)
{
	onUrlConnection = audioPlayer.OnAudioUrl(boost::bind(&AudioPlayerWrapper::OnAudioURL, this));
	onAudioEndConnection = audioPlayer.OnAudioEnd(boost::bind(&AudioPlayerWrapper::OnAudioEnd, this));
	onClearUrlConnection = audioPlayer.OnClearUrl(boost::bind(&AudioPlayerWrapper::OnClearURL, this));
}


AudioPlayerWrapper::~AudioPlayerWrapper()
{
}


void AudioPlayerWrapper::Play()
{
	//audioPlayer.SetURL(url);
	audioPlayer.SetURLAsync(url);
}

void AudioPlayerWrapper::Stop()
{
	audioPlayer.Stop();
}


void AudioPlayerWrapper::OnAudioURL()
{
	audioPlayer.Play();
}

void AudioPlayerWrapper::OnAudioEnd()
{
	callingInstance->PlayCompleted();
}


void AudioPlayerWrapper::OnClearURL()
{


}
