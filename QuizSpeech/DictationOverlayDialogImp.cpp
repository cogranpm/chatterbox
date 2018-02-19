#include "DictationOverlayDialogImp.h"
#include "MyApp.h"
#include <wx/app.h> 
#include <wx/bitmap.h>
#include "GlobalConstants.h"
#include "resource.h"
#include "AudioWorker.h"
#include "AudioPlayerPanel.h"
#include "ApplicationImages.h"
#include "ActionCommandParser.h"

DictationOverlayDialogImp::DictationOverlayDialogImp( wxWindow* parent )
:
	DictationOverlayDialogImp( parent , L"")
{
	
}

DictationOverlayDialogImp::DictationOverlayDialogImp(wxWindow* parent, const std::wstring& fileName)
	:
	OverlayDialog(parent), fileName(fileName), recognitionReceived(false), recordingState(RecordingState::recording), audioPlayerPanel(nullptr)
{
	fullAudioPath = wxGetApp().GetFileHandler().GetFullAudioPathToFile(fileName);
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

	if (dictationStoppedConnection.connected())
	{
		dictationStoppedConnection.disconnect();
	}
	wxGetApp().DisconnectSpeechHandler(wxGetApp().GetCommandReceivedConnection());
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->Disable();
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
	this->dictationStoppedConnection = wxGetApp().GetSpeechListener().GetDictationContext()->onDictationStopped(boost::bind(&DictationOverlayDialogImp::OnDictationStopped, this));


	wxGetApp().GetSpeechListener().StartDictation(fullAudioPath);
}

void DictationOverlayDialogImp::EnableAllRules()
{
	std::vector<std::wstring> ruleNames;
	ruleNames.push_back(L"AUDIO_RECORD_ACTIONS");
	ruleNames.push_back(MyApp::RULE_DIALOG_ACTIONS);
	wxGetApp().DisconnectSpeechHandler(wxGetApp().GetCommandReceivedConnection());
	boost::signals2::connection* commandConnection = wxGetApp().GetCommandReceivedConnection();
	*(commandConnection) = wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->onCommandRecognized(boost::bind(&DictationOverlayDialogImp::OnCommandRecognized, this, _1, _2));
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->EnableRules(ruleNames);

}

void DictationOverlayDialogImp::OnCommandRecognized(std::wstring& phrase, const std::vector<CommandProperty>& commandPropertyList)
{
	std::wstring actionName;
	std::wstring actionTarget;
	std::wstring targetValue;
	std::wstring ruleName;
	ActionCommandParser actionParser;
	actionParser.Parse(commandPropertyList, actionName, actionTarget, targetValue, ruleName);

	if (boost::algorithm::equals(actionName, MyApp::COMMAND_ACTION_OK))
	{
		wxCommandEvent evt(wxEVT_COMMAND_BUTTON_CLICKED, this->m_sdbSizer1OK->GetId());
		this->m_sdbSizer1OK->Command(evt);
		return;
	}
	else if (boost::algorithm::equals(actionName, MyApp::COMMAND_ACTION_CANCEL))
	{
		this->Close();
		return;
	}
	else if (boost::algorithm::equals(actionName, L"start"))
	{
		StartDictation();
	}
	else if (boost::algorithm::equals(actionName, L"play"))
	{
		if (audioPlayerPanel != nullptr)
		{
			audioPlayerPanel->Play();
		}
	}
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

void DictationOverlayDialogImp::OnDictationStopped()
{
	if (recordingState == RecordingState::recording)
	{
		EndDication();
	}
}

void DictationOverlayDialogImp::EndDication()
{
	recordingState = RecordingState::recorded;
	wxGetApp().GetSpeechListener().StopDictation();
	this->btnStop->SetBitmap(*wxGetApp().GetImages().record_icon);
	/* need to make sure the path exists and size greater than 0 */
	player.SetURLAsync(fullAudioPath);
	EnableAllRules();
	//wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->Enable();
}

void DictationOverlayDialogImp::StartDictation()
{
	wxGetApp().DisconnectSpeechHandler(wxGetApp().GetCommandReceivedConnection());
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->Disable();
	this->txtPhrase->Clear();
	recordingState = RecordingState::recording;
	this->btnStop->SetBitmap(*wxGetApp().GetImages().stop_icon);
	if (wxGetApp().GetFileHandler().FileExists(fullAudioPath))
	{
		wxGetApp().GetFileHandler().DeleteFile(fullAudioPath);
	}
	SetFileName(wxGetApp().GetFileHandler().GetNewAudioFileName());
	wxGetApp().GetSpeechListener().StartDictation(fullAudioPath);
}

void DictationOverlayDialogImp::StopOnButtonClick( wxCommandEvent& event )
{
	
	if (recordingState == RecordingState::recording)
	{
		EndDication();
	}
	else
	{
		//re-start the dictation
		StartDictation();
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

void DictationOverlayDialogImp::SetFileName(std::wstring& newFileName)
{ 
	fileName = newFileName; 
	fullAudioPath = wxGetApp().GetFileHandler().GetFullAudioPathToFile(fileName);
}