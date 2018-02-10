#include "AudioPlayerWrapper.h"
#include "NoteAudioPlayer.h"
#include <wx/sizer.h>
#include "MyApp.h"
using boost::wformat;

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
	if (btnPlay != nullptr)
	{
		audioPlayer.SetURL(url);
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

	Play();
}

void AudioPlayerWrapper::Play()
{
	//audioPlayer.SetURL(url);
	if (btnPlay != nullptr)
	{
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
	else
	{
		audioPlayer.SetURLAsync(url);
	}
	
}

void AudioPlayerWrapper::Stop()
{
	audioPlayer.Stop();
}


void AudioPlayerWrapper::OnAudioURL()
{
	if (btnPlay != nullptr)
	{
		wformat formattedDuration = wformat(L"%f seconds");
		double duration = audioPlayer.GetDuration();
		int milliSecondsDuration = duration * ::ONE_MSEC;
		this->m_gauge2->SetRange(milliSecondsDuration);
		std::wstring durationDisplay((formattedDuration % duration).str());
		this->txtDuration->SetLabel(durationDisplay);
		this->btnPlay->Enable();
	}
	else
	{
		audioPlayer.Play();
	}
}

void AudioPlayerWrapper::OnAudioEnd()
{
	if (btnPlay != nullptr)
	{
		this->m_gauge2->SetValue(0);
		timer.Stop();
		if (audioPlayer.GetPlayState() == AudioPlayer::AudioState::loaded)
		{
			this->btnPlay->SetBitmap(*wxGetApp().GetImages().start_icon);
		}
	}
	else
	{
		callingInstance->PlayCompleted();
	}
	
}


void AudioPlayerWrapper::OnClearURL()
{


}
