#include "DictationOverlayDialogImp.h"
#include "MyApp.h"
#include <wx/app.h> 
#include <wx/bitmap.h>
#include "GlobalConstants.h"
#include "resource.h"
#include "AudioWorker.h"
#include "AudioPlayerPanel.h"
#include "ApplicationImages.h"

DictationOverlayDialogImp::DictationOverlayDialogImp( wxWindow* parent )
:
	DictationOverlayDialogImp( parent , L"")
{
	
}

DictationOverlayDialogImp::DictationOverlayDialogImp(wxWindow* parent, const std::wstring& fileName)
	:
	OverlayDialog(parent), fileName(fileName), recognitionReceived(false), recordingState(RecordingState::recording)
{
	
}

DictationOverlayDialogImp::~DictationOverlayDialogImp()
{
	if (phraseReceivedConnection.connected())
	{
		phraseReceivedConnection.disconnect();
	}
	if (hypothesisReceivedConnection.connected())
	{
		hypothesisReceivedConnection.disconnect();
	}
	if (soundEndConnection.connected())
	{
		soundEndConnection.disconnect();
	}
	if (soundStartConnection.connected())
	{
		soundStartConnection.disconnect();
	}
}

void DictationOverlayDialogImp::OnInitDialog(wxInitDialogEvent& event) 
{ 
	this->btnStop->SetBitmap(*wxGetApp().GetImages().stop_icon);
	audioPlayerPanel = new AudioPlayerPanelImp(this, &player);
	this->szAudioPlayer->Add(audioPlayerPanel, 1, wxALL | wxEXPAND, 0);
	this->szAudioPlayer->Layout();
	

	timer.SetGauge(this->playbackGauge);
	hypothesisTimer.SetTextControl(this->txtHypothesis);
	this->phraseReceivedConnection = wxGetApp().GetSpeechListener().GetDictationContext()->onSpeechRecognized(boost::bind(&DictationOverlayDialogImp::OnSpeechRecognized, this, _1));
	this->hypothesisReceivedConnection = wxGetApp().GetSpeechListener().GetDictationContext()->onHypothesisRecognized(boost::bind(&DictationOverlayDialogImp::OnHypothesisRecognized, this, _1));
	this->soundStartConnection = wxGetApp().GetSpeechListener().GetDictationContext()->onSoundStart(boost::bind(&DictationOverlayDialogImp::OnSoundStart, this));
	this->soundEndConnection = wxGetApp().GetSpeechListener().GetDictationContext()->onSoundStart(boost::bind(&DictationOverlayDialogImp::OnSoundEnd, this));
	wxGetApp().GetSpeechListener().StartDictation(fileName);
}

void DictationOverlayDialogImp::OnSpeechRecognized(const std::wstring& text)
{
	this->txtPhrase->AppendText(text);
	hypothesisTimer.Start(1000);
}

void DictationOverlayDialogImp::OnHypothesisRecognized(const std::wstring& text)
{
	this->txtHypothesis->AppendText(text);
}

void DictationOverlayDialogImp::OnSoundStart()
{
	/* visual indication that sound is being received */
	playbackGauge->Pulse();
}

void DictationOverlayDialogImp::OnSoundEnd()
{
	/* delay the removal of sound indication or it is too quick to see */
	timer.Start(1000);
}



void DictationOverlayDialogImp::StopOnButtonClick( wxCommandEvent& event )
{
	if (recordingState == RecordingState::recording)
	{
		recordingState = RecordingState::recorded;
		wxGetApp().GetSpeechListener().StopDictation();
		this->btnStop->SetBitmap(*wxGetApp().GetImages().record_icon);
		player.SetURL(fileName);
	}
	else
	{
		//re-start the dictation
		this->txtPhrase->Clear();
		recordingState = RecordingState::recording;
		this->btnStop->SetBitmap(*wxGetApp().GetImages().stop_icon);
		if (wxGetApp().GetFileHandler().FileExists(fileName))
		{
			wxGetApp().GetFileHandler().DeleteFile(fileName);
		}
		fileName = wxGetApp().GetFileHandler().GetFullAudioPathToFile(wxGetApp().GetFileHandler().GetNewAudioFileName());
		wxGetApp().GetSpeechListener().StartDictation(fileName);
	}
}


void DictationOverlayDialogImp::OnOKButtonClick( wxCommandEvent& event )
{
	wxGetApp().GetSpeechListener().StopDictation();
	bool result = this->txtPhrase->GetValidator()->TransferFromWindow();
	EndDialog(wxID_OK);
}

void DictationOverlayDialogImp::OnCancelButtonClick(wxCommandEvent& event)
{
	wxGetApp().GetSpeechListener().StopDictation();
	EndDialog(wxID_CANCEL);
}



void DictationOverlayDialogImp::GetRecognizedText(std::wstring& buffer)
{
	buffer = std::wstring(txtPhrase->GetValue());
}