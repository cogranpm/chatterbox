#include "AudioPlayerWrapper.h"
#include "NoteAudioPlayer.h"
#include <wx/sizer.h>
#include "MyApp.h"


AudioPlayerWrapper::AudioPlayerWrapper(AudioPlayerWrapperClient* callingInstance, std::wstring& url) :
	AudioPlayerWrapper(callingInstance, url, nullptr, nullptr)
{

}

AudioPlayerWrapper::AudioPlayerWrapper(AudioPlayerWrapperClient* callingInstance, std::wstring& url, wxPanel* targetPanel, wxWindow* parent)
	: callingInstance(callingInstance), url(url), targetPanel(targetPanel), parent(parent), timer(), btnPlay(nullptr)
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
	if (btnPlay != nullptr)
	{
		this->btnPlay->Enable();
	}
}

void AudioPlayerWrapper::RenderPanel()
{
	if (targetPanel == nullptr)
	{
		return;
	}

	

	btnPlay = new wxButton(targetPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(20, 20), 0);
	btnPlay->Enable(false);
	btnPlay->SetToolTip(wxT("Play"));

	targetPanel->GetSizer()->Add(btnPlay, 0, 0, 5);

	m_gauge2 = new wxGauge(targetPanel, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL);
	m_gauge2->SetValue(0);
	targetPanel->GetSizer()->Add(m_gauge2, 0, wxLEFT | wxTOP, 5);

	txtDuration = new wxStaticText(targetPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	txtDuration->Wrap(-1);
	targetPanel->GetSizer()->Add(txtDuration, 1, wxEXPAND, 5);

	//targetPanel->GetSizer()->Layout();
	targetPanel->Layout();
	parent->Layout();

	// Connect Events
	btnPlay->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AudioPlayerWrapper::PlayOnButtonClick), NULL, this);

	//Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AudioPlayerWrapper::PlayOnButtonClick, this, wxID_EXIT);
	//function< void(wxCommandEvent &) > exitHandler(bind(&MyHandler::OnExit, &myHandler, _1));

	this->btnPlay->SetBitmap(*wxGetApp().GetImages().start_icon);
	timer.SetGauge(this->m_gauge2);

}

void AudioPlayerWrapper::PlayOnButtonClick(wxCommandEvent& event)
{ 
//	audioPlayer.SetURLAsync(url);

	if (audioPlayer.GetPlayState() == AudioPlayer::AudioState::loaded)
	{
		audioPlayer.Play();
		this->btnPlay->SetBitmap(*wxGetApp().GetImages().pause_icon);
		timer.Start(AudioPlayerPanelTimer::INTERVAL);
	}
	else if (audioPlayer.GetPlayState() == AudioPlayer::AudioState::playing)
	{
		this->audioPlayer.Pause();
		timer.Stop();
		btnPlay->SetBitmap(*wxGetApp().GetImages().start_icon);
	}
	else if (audioPlayer.GetPlayState() == AudioPlayer::AudioState::paused)
	{
		audioPlayer.Resume();
		btnPlay->SetBitmap(*wxGetApp().GetImages().pause_icon);
		timer.Start();
	}
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
