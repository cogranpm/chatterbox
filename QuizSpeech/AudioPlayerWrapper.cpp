#include "AudioPlayerWrapper.h"
#include "NoteAudioPlayer.h"
#include "MyApp.h"



AudioPlayerWrapper::AudioPlayerWrapper(AudioPlayerWrapperClient* callingInstance, std::wstring& url)
	: callingInstance(callingInstance), url(url)
{
	onUrlConnection = audioPlayer.OnAudioUrl(boost::bind(&AudioPlayerWrapper::OnAudioURL, this));
	onAudioEndConnection = audioPlayer.OnAudioEnd(boost::bind(&AudioPlayerWrapper::OnAudioEnd, this));
	onClearUrlConnection = audioPlayer.OnClearUrl(boost::bind(&AudioPlayerWrapper::OnClearURL, this));
}

AudioPlayerWrapper::~AudioPlayerWrapper()
{
	if (onUrlConnection.connected())
	{
		onUrlConnection.disconnect();
	}
	if (onAudioEndConnection.connected())
	{
		onAudioEndConnection.disconnect();
	}
	if (onClearUrlConnection.connected())
	{
		onClearUrlConnection.disconnect();
	}
}

void AudioPlayerWrapper::SetURL(std::wstring url)
{
	this->url = url;
}


void AudioPlayerWrapper::Play()
{
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
