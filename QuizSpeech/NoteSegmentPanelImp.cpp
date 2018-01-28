#include "NoteSegmentPanelImp.h"
#include "MyApp.h"
#include <wx/app.h> 
#include <wx/bitmap.h>
#include "GlobalConstants.h"
#include "resource.h"
#include "DictationOverlayDialogImp.h"
#include "AudioPlayer.h"
#include "ApplicationImages.h"
#include "SpeechMessageDialog.h"
#include "DictationOverlayClientHelper.h"

NoteSegmentPanelImp::NoteSegmentPanelImp( wxWindow* parent, NoteViewModel& noteViewModel, NoteSegment* noteSegment)
:
NoteSegmentPanel( parent ), noteViewModel(noteViewModel), noteSegment(noteSegment)
{

	this->btnBodyRecord->SetBitmap(*wxGetApp().GetImages().record_icon);
	this->btnBodyClear->SetBitmap(*wxGetApp().GetImages().delete_icon);

	playerPanel = new AudioPlayerPanelImp(this, &player);
	this->szAudioPlayer->Add(playerPanel, 1, wxALL | wxEXPAND, 0);
	this->szAudioPlayer->Layout();
	if (!this->noteSegment->GetBodyFile().empty())
	{
		player.SetURL(this->noteSegment->GetBodyFile());
	}


}

NoteSegmentPanelImp::~NoteSegmentPanelImp()
{
	if (playerPanel != nullptr)
	{
		delete playerPanel;
		playerPanel = nullptr;
	}
}

void NoteSegmentPanelImp::DeleteOnButtonClick( wxCommandEvent& event ) 
{ 
	event.Skip(); 
}

wxTextCtrl* NoteSegmentPanelImp::GetBodyControl()
{
	return this->txtValue;
}


wxStaticText* NoteSegmentPanelImp::GetBodyLabelControl()
{
	return this->lblTitle;
}

void NoteSegmentPanelImp::ValueOnKillFocus(wxFocusEvent& event)
{ 
	//wxGetApp().GetSpeechListener().StopDictation();
	NoteSegmentPanel::ValueOnKillFocus(event);
	//switch to command and control mode
	
}

void NoteSegmentPanelImp::ValueOnSetFocus(wxFocusEvent& event)
{ 
	try
	{
		NoteSegmentPanel::ValueOnSetFocus(event);
	}
	catch (std::exception& e)
	{
		wxMessageBox(e.what(), L"Error", wxICON_ERROR);
	}
}

void NoteSegmentPanelImp::BodyRecordOnButtonClick(wxCommandEvent& event)
{ 

	std::wstring filePathBuffer(L"");
	int returnValue = DictationOverlayClientHelper::ShowDictationDialog(noteSegment->GetBodyFile(), this, txtValue, &player, &filePathBuffer);
	if (returnValue == wxID_OK)
	{
		noteSegment->SetBodyFile(filePathBuffer);
	}
}


void NoteSegmentPanelImp::OnButtonClickClearBody(wxCommandEvent& event)
{ 
	ClearBody();
}


void NoteSegmentPanelImp::ClearBody()
{
	DictationOverlayClientHelper::ClearAudio(this->noteSegment->GetBodyFile(), this, txtValue, &player);
	noteSegment->SetBodyFile(std::wstring(L""));
}


void NoteSegmentPanelImp::UpdateUI(bool isRecording)
{
	if (isRecording)
	{
		this->btnBodyClear->Disable();
		this->btnBodyRecord->Disable();
		
	}
	else
	{
		this->btnBodyClear->Enable();
		this->btnBodyRecord->Enable();
	}

}
		