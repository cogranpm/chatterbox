#include "AudioPlayerWrapper.h"
#include "NoteAudioPlayer.h"
#include <wx/sizer.h>
#include "MyApp.h"


AudioPlayerWrapper::AudioPlayerWrapper(AudioPlayerWrapperClient* callingInstance, std::wstring& url) :
	AudioPlayerWrapper(callingInstance, url, nullptr, nullptr)
{

}

AudioPlayerWrapper::AudioPlayerWrapper(AudioPlayerWrapperClient* callingInstance, std::wstring& url, wxSizer* targetSizer, wxWindow* parent)
	: callingInstance(callingInstance), url(url), targetSizer(targetSizer), parent(parent), timer()
{
	onUrlConnection = audioPlayer.OnAudioUrl(boost::bind(&AudioPlayerWrapper::OnAudioURL, this));
	onAudioEndConnection = audioPlayer.OnAudioEnd(boost::bind(&AudioPlayerWrapper::OnAudioEnd, this));
	onClearUrlConnection = audioPlayer.OnClearUrl(boost::bind(&AudioPlayerWrapper::OnClearURL, this));
}

AudioPlayerWrapper::~AudioPlayerWrapper()
{
}

void AudioPlayerWrapper::SetURL(std::wstring url)
{
	this->url = url;
}

void AudioPlayerWrapper::RenderPanel()
{
	if (targetSizer == nullptr)
	{
		return;
	}

	btnPlay = new wxButton(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(20, 20), 0);
	btnPlay->Enable(false);
	btnPlay->SetToolTip(wxT("Play"));

	targetSizer->Add(btnPlay, 0, 0, 5);

	m_gauge2 = new wxGauge(parent, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL);
	m_gauge2->SetValue(0);
	targetSizer->Add(m_gauge2, 0, wxLEFT | wxTOP, 5);

	txtDuration = new wxStaticText(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	txtDuration->Wrap(-1);
	targetSizer->Add(txtDuration, 1, wxEXPAND, 5);


	targetSizer->Layout();

	// Connect Events
	//btnPlay->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(pnlPlayer::PlayOnButtonClick), NULL, this);

	
	this->btnPlay->SetBitmap(*wxGetApp().GetImages().start_icon);
	timer.SetGauge(this->m_gauge2);

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
