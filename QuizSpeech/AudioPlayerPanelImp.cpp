#include "AudioPlayerPanelImp.h"
#include "GlobalConstants.h"
#include "ApplicationImages.h"
#include "MyApp.h"

using boost::wformat;

AudioPlayerPanelImp::AudioPlayerPanelImp( wxWindow* parent, AudioPlayer* player )
:
pnlPlayer( parent ), player(player)
{
	this->btnPlay->SetBitmap(*wxGetApp().GetImages().start_icon);
	onUrlConnection = player->OnAudioUrl(boost::bind(&AudioPlayerPanelImp::OnAudioURL, this));
	onAudioEndConnection = player->OnAudioEnd(boost::bind(&AudioPlayerPanelImp::OnAudioEnd, this));
	onClearUrlConnection = player->OnClearUrl(boost::bind(&AudioPlayerPanelImp::OnClearURL, this));
	timer.SetGauge(this->m_gauge2);
}

AudioPlayerPanelImp::~AudioPlayerPanelImp()
{
	if (onUrlConnection.connected())
	{
		onUrlConnection.disconnect();
	}
	if (onAudioEndConnection.connected())
	{
		onAudioEndConnection.disconnect();
	}
}


void AudioPlayerPanelImp::PlayOnButtonClick(wxCommandEvent& event)
{ 

	if (player->GetPlayState() == AudioPlayer::AudioState::loaded)
	{
		player->Play();
		this->btnPlay->SetBitmap(*wxGetApp().GetImages().pause_icon);
		timer.Start(AudioPlayerPanelTimer::INTERVAL);
	}
	else if (player->GetPlayState() == AudioPlayer::AudioState::playing)
	{
		this->player->Pause();
		timer.Stop();
		btnPlay->SetBitmap(*wxGetApp().GetImages().start_icon);
	}
	else if (player->GetPlayState() == AudioPlayer::AudioState::paused)
	{
		player->Resume();
		btnPlay->SetBitmap(*wxGetApp().GetImages().pause_icon);
		timer.Start();
	}
}

void AudioPlayerPanelImp::OnAudioURL()
{
	//int hour;
	//int seconds;
	//int minute;
	//int Seconds_To_Convert = player->GetDuration();
	//::Convert(Seconds_To_Convert, hour, minute, seconds);
	wformat formattedDuration = wformat(L"%.2f seconds");
	double duration = player->GetDuration();
	int milliSecondsDuration = duration * ::ONE_MSEC;
	this->m_gauge2->SetRange(milliSecondsDuration);
	std::wstring durationDisplay((formattedDuration % duration).str());
	this->txtDuration->SetLabel(durationDisplay);
	this->btnPlay->Enable();
}

void AudioPlayerPanelImp::OnAudioEnd()
{
	this->m_gauge2->SetValue(0);
	timer.Stop();
	if (player->GetPlayState() == AudioPlayer::AudioState::loaded)
	{
		this->btnPlay->SetBitmap(*wxGetApp().GetImages().start_icon);
	}
}

void AudioPlayerPanelImp::OnClearURL()
{
	btnPlay->Disable();
	m_gauge2->SetValue(0);
	txtDuration->SetLabel(wxString(""));
}
