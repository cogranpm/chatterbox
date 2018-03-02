#include "AudioPlayerPanelHelper.h"
#include "NoteAudioPlayer.h"
#include <wx/sizer.h>
#include "MyApp.h"
using boost::wformat;

AudioPlayerPanelHelper::AudioPlayerPanelHelper(wxPanel* targetPanel, wxWindow* parent)
	: targetPanel(targetPanel), parent(parent), timer(), btnPlay(nullptr)
{
	onUrlConnection = audioPlayer.OnAudioUrl(boost::bind(&AudioPlayerPanelHelper::OnAudioURL, this));
	onAudioEndConnection = audioPlayer.OnAudioEnd(boost::bind(&AudioPlayerPanelHelper::OnAudioEnd, this));
	onClearUrlConnection = audioPlayer.OnClearUrl(boost::bind(&AudioPlayerPanelHelper::OnClearURL, this));
}


AudioPlayerPanelHelper::~AudioPlayerPanelHelper()
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

	btnPlay->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AudioPlayerPanelHelper::PlayOnButtonClick), NULL, this);
}

void AudioPlayerPanelHelper::SetURL(std::wstring url)
{
	audioPlayer.SetURL(url);
}

void AudioPlayerPanelHelper::RenderPanel()
{

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
	targetPanel->Layout();
	parent->Layout();

	btnPlay->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AudioPlayerPanelHelper::PlayOnButtonClick), NULL, this);

	//Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AudioPlayerWrapper::PlayOnButtonClick, this, wxID_EXIT);
	//function< void(wxCommandEvent &) > exitHandler(bind(&MyHandler::OnExit, &myHandler, _1));

	this->btnPlay->SetBitmap(*wxGetApp().GetImages().start_icon);
	timer.SetGauge(this->m_gauge2);

}

void AudioPlayerPanelHelper::PlayOnButtonClick(wxCommandEvent& event)
{
	//	audioPlayer.SetURLAsync(url);
	Play();
}

void AudioPlayerPanelHelper::Play()
{
	//audioPlayer.SetURL(url);
	
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

void AudioPlayerPanelHelper::OnAudioURL()
{
	wformat formattedDuration = wformat(L"%.2f seconds");
	double duration = audioPlayer.GetDuration();
	int milliSecondsDuration = duration * GlobalConstants::ONE_MSEC;
	this->m_gauge2->SetRange(milliSecondsDuration);
	std::wstring durationDisplay((formattedDuration % duration).str());
	this->txtDuration->SetLabel(durationDisplay);
	this->btnPlay->Enable();
}

void AudioPlayerPanelHelper::OnAudioEnd()
{
	this->m_gauge2->SetValue(0);
	timer.Stop();
	if (audioPlayer.GetPlayState() == AudioPlayer::AudioState::loaded)
	{
		this->btnPlay->SetBitmap(*wxGetApp().GetImages().start_icon);
	}
}


void AudioPlayerPanelHelper::OnClearURL()
{
	btnPlay->Disable();
	m_gauge2->SetValue(0);
	txtDuration->SetLabel(wxString(""));
}
