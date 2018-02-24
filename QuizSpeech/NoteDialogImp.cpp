#include "MyApp.h"
#include <wx/app.h> 
#include "NoteDialogImp.h"
#include "NoteSegmentPanelImp.h"
#include "ApplicationImages.h"
#include "DictationOverlayDialogImp.h"
#include "DictationOverlayClientHelper.h"
#include "SegmentTemplateDialogImp.h"
#include "ActionCommandParser.h"

struct findSegmentHeader
{
	findSegmentHeader(unsigned long id) : _id(id) {};
	unsigned long _id;

	bool operator () (const NoteSegmentTypeHeader& arg) const
	{
		return (_id == arg.getId());
	}
};

NoteDialogImp::NoteDialogImp( wxWindow* parent, Note* note )
:
NoteDialog( parent ), viewModel(note), noteAudioPlayer(), ruleNames()// viewModel(std::make_unique<NoteViewModel>(note))
{
	
}

NoteDialogImp::~NoteDialogImp()
{
	//wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->Disconnect();
	
	/*lets delete all the panels that were created manually, this does happen normally but something is wrong
	boost::ptr_vector<NoteSegment>* list = viewModel.GetNoteSegmentList();
	for(int i = 0; i < list->size(); i ++ )
	{
		NoteSegmentPanelImp* segmentPanel = list->at(i).GetPanel();
		if(segmentPanel != NULL)
		{
			delete segmentPanel;
		}
	}
	*/
}

void NoteDialogImp::OnInitDialog( wxInitDialogEvent& event ) 
{ 
	this->btnUnlockTitle->SetBitmap(*wxGetApp().GetImages().unlock_icon);
	this->btnRecordTitle->SetBitmap(*wxGetApp().GetImages().record_icon);
	this->btnClearTitle->SetBitmap(*wxGetApp().GetImages().delete_icon);

	this->btnUnlockDescription->SetBitmap(*wxGetApp().GetImages().unlock_icon);
	this->btnRecordDescription->SetBitmap(*wxGetApp().GetImages().record_icon);
	this->btnClearDescription->SetBitmap(*wxGetApp().GetImages().delete_icon);

	this->btnAddSegment->SetBitmap(*wxGetApp().GetImages().assign_icon);
	this->btnClear->SetBitmap(*wxGetApp().GetImages().delete_icon);
	this->btnNewSegment->SetBitmap(*wxGetApp().GetImages().addnewitem_icon);
	this->btnEditSegment->SetBitmap(*wxGetApp().GetImages().edit_icon);
	this->btnPlayAll->SetBitmap(*wxGetApp().GetImages().playstep_icon);
	this->btnStopAll->SetBitmap(*wxGetApp().GetImages().stop_icon);

	this->typeInfo->SetPage(wxString("<html><body><p></p></body></html>"));
	
	/* load all the segments for this note */
	wxGetApp().GetProvider()->GetNoteSegmentsByNote(viewModel.GetNote(), viewModel.GetNoteSegmentList());
	RenderNoteSegmentTypes();
	ruleNames.push_back(MyApp::RULE_NOTE_DIALOG);
	ruleNames.push_back(MyApp::RULE_DIALOG_ACTIONS);
	this->SetupSpeechHandlers();
	this->RenderNote();
	this->lstTypes->SetSelection(0);
	this->ChangeNoteType(0);
	this->Maximize(true);
	this->btnRecordTitle->SetFocus();
}

void NoteDialogImp::RenderNoteSegmentTypes()
{
	lstTypes->Clear();
	viewModel.GetNoteTypeList()->clear();
	wxGetApp().GetProvider()->GetNoteSegmentTypeProvider().GetAllNoteSegmentTypeHeaders(viewModel.GetNoteTypeList());
	for (int i = 0; i < viewModel.GetNoteTypeList()->size(); i++)
	{
		NoteSegmentTypeHeader header = viewModel.GetNoteTypeList()->at(i);
		unsigned long headerId = header.getId();
		this->lstTypes->Append(header.getTitle(), reinterpret_cast<void*>(headerId));
	}
}


void NoteDialogImp::SetupSpeechHandlers()
{
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->SetupSpeechHandlers(ruleNames, this->GetName().ToStdString(),
		boost::bind(&NoteDialogImp::OnCommandRecognized, this, _1, _2));

}

void NoteDialogImp::OnCommandRecognized(std::wstring& phrase, const std::vector<CommandProperty>& commandPropertyList)
{
	std::wstring actionName;
	std::wstring actionTarget;
	std::wstring targetValue;
	std::wstring ruleName;
	ActionCommandParser actionParser;
	actionParser.Parse(commandPropertyList, actionName, actionTarget, targetValue, ruleName);

	if (boost::algorithm::equals(actionName, MyApp::COMMAND_ACTION_CANCEL))
	{
		CloseMe();
		return;
	}
	else if (boost::algorithm::equals(actionName, MyApp::COMMAND_ACTION_OK))
	{
		wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->Disconnect();
		wxCommandEvent evt(wxEVT_COMMAND_BUTTON_CLICKED, this->m_sdbSizer1OK->GetId());
		this->m_sdbSizer1OK->Command(evt);
		return;
	}
	else if (boost::algorithm::equals(actionName, MyApp::CONTROL_ACTION_CLEAR))
	{
		if (this->txtTitle->HasFocus())
		{
			this->txtTitle->Clear();
		}
		else if (this->txtDescription->HasFocus())
		{
			this->txtDescription->Clear();
		}
		return;
	}
	else if (boost::algorithm::equals(actionName, L"recordtitle"))
	{
		RecordTitle();
		return;
	}
	else if (boost::algorithm::equals(actionName, L"playtitle"))
	{
		titlePlayer.Play();
		return;
	}
	else if (boost::algorithm::equals(actionName, L"recorddescription"))
	{
		RecordDescription();
		return;
	}
	else if (boost::algorithm::equals(actionName, L"playdescription"))
	{
		player.Play();
		return;
	}
	else if (boost::algorithm::equals(actionName, L"playall"))
	{
		noteAudioPlayer.Start(&viewModel);
		return;
	}
	else if (boost::algorithm::equals(actionName, L"applytemplate"))
	{
		AddSelectedSegments();
		return;
	}
	else if (boost::algorithm::equals(actionName, L"addtemplate"))
	{
		NewSegment();
		return;
	}
	else if (boost::algorithm::equals(actionName, L"edittemplate"))
	{
		EditSegment();
		return;
	}
	else if (boost::algorithm::equals(actionName, L"deletetemplate"))
	{
		DeleteSegment();
		return;
	}
	else if (boost::algorithm::equals(actionName, L"close"))
	{
		CloseMe();
		return;
	}
}

void NoteDialogImp::CloseMe()
{
	//wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->Disconnect();
	this->Close();
}

void NoteDialogImp::RecordTitle()
{
	std::wstring filePathBuffer(L"");
	int returnValue = DictationOverlayClientHelper::ShowDictationDialog(viewModel.GetNote()->GetTitleAudioFile(), this, txtTitle, &titlePlayer, &filePathBuffer);
	if (returnValue == wxID_OK)
	{
		viewModel.GetNote()->SetTitleAudioFile(filePathBuffer);
	}
	SetupSpeechHandlers();
}

void NoteDialogImp::RecordDescription()
{
	std::wstring filePathBuffer(L"");
	int returnValue = DictationOverlayClientHelper::ShowDictationDialog(viewModel.GetNote()->GetDescriptionAudioFile(), this, txtDescription, &player, &filePathBuffer);
	if (returnValue == wxID_OK)
	{
		viewModel.GetNote()->SetDescriptionAudioFile(filePathBuffer);
	}
	SetupSpeechHandlers();

}

void NoteDialogImp::RecordTitleOnButtonClick(wxCommandEvent& event)
{ 
	RecordTitle();
}

void NoteDialogImp::ClearTitleOnButtonClick(wxCommandEvent& event)
{ 
	DictationOverlayClientHelper::ClearAudio(viewModel.GetNote()->GetTitleAudioFile(), this, txtTitle, &titlePlayer);
	viewModel.GetNote()->SetTitleAudioFile(std::wstring(L""));
}

void NoteDialogImp::RecordDescriptionOnButtonClick(wxCommandEvent& event)
{ 
	RecordDescription();
}

void NoteDialogImp::ClearDescriptionOnButtonClick(wxCommandEvent& event)
{ 
	DictationOverlayClientHelper::ClearAudio(viewModel.GetNote()->GetDescriptionAudioFile(), this, txtDescription, &player);
	viewModel.GetNote()->SetDescriptionAudioFile(std::wstring(L""));
}



void NoteDialogImp::AddSelectedSegments()
{
	//set up rules for creating the note segments, for example
	//if data already entered on a note segment do not remove etc	
	wxArrayInt selectionsContainer;
	int numItems = this->lstTypes->GetSelections(selectionsContainer);
	if (numItems > 0)
	{
		NoteSegment* noteSegment = nullptr;
		for (size_t i = 0; i < selectionsContainer.GetCount(); i++)
		{
			NoteSegmentTypeHeader foundHeader = this->GetSelectedNoteType(selectionsContainer.Item(i));
			boost::ptr_vector<NoteSegmentType>* list = viewModel.GetNoteTypeSegmentsList();
			list->clear();
			wxGetApp().GetProvider()->GetNoteSegmentTypeProvider().GetNoteSegmentTypesByHeader(&foundHeader, list);
			NoteSegmentPanelImp* panel = nullptr;
			for (int i = 0; i < list->size(); i++)
			{
				NoteSegmentType noteSegmentType = list->at(i);
				noteSegment = new NoteSegment(viewModel.GetNote()->GetNoteId());
				viewModel.GetNoteSegmentList()->push_back(noteSegment);
				panel = this->AddSegment(noteSegment, noteSegmentType);
			}
			//set focus to the title box of last segment added
			if (panel != nullptr)
			{
				this->SetSegmentFocus(panel);
			}

		}
		
	}
	else
	{
		NoteSegment* noteSegment = new NoteSegment(viewModel.GetNote()->GetNoteId());
		viewModel.GetNoteSegmentList()->push_back(noteSegment);
		this->AddSegment(noteSegment, this->defaultSegmentType);
		//noteSegment->GetPanel()->GetTitleControl()->SetFocus();
	}
	dialogSizer->Layout();
}

NoteSegmentPanelImp* NoteDialogImp::AddSegment(NoteSegment* noteSegment, NoteSegmentType& noteSegmentType)
{
	/* associate the noteSegment with the noteSegment Type
		so when the noteSegment is reloaded sometime that the 
		formatting in the noteSegmentType can be applied
	*/
	noteSegment->SetNoteSegmentTypeId(noteSegmentType.getId());

	/* create associated ui element */
	NoteSegmentPanelImp* segmentPanel = new NoteSegmentPanelImp(this->segmentContainer, viewModel, noteSegment);
	this->segmentPanelList.push_back(segmentPanel);
//	noteSegment->SetPanel(segmentPanel);
	/* layout the panel */
	sbSegments->Add(segmentPanel, 1, wxALL | wxEXPAND, 0);
	dialogSizer->Layout();
	//wire up the delete button (currently an issue with this)
//	segmentPanel->btnDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialogImp::DeleteOnButtonClick ), (wxObject*)noteSegment, this );
	std::wstring title = noteSegment->GetTitle();
	if (title.empty())
	{
		title = noteSegmentType.getTitle();
	}
	if (boost::algorithm::equals(title, L"[NOW]"))
	{
		title = wxDateTime::Now().Format(L"%c");
	}
	segmentPanel->GetBodyLabelControl()->SetLabel(title);
	if (!noteSegmentType.getFontDesc().empty())
	{
		wxFont font(noteSegmentType.getFontDesc());
		segmentPanel->GetBodyControl()->SetFont(font);
	}

	segmentPanel->GetBodyControl()->SetValue(noteSegment->GetBody());
	return segmentPanel;
}


void NoteDialogImp::AddSegmentOnButtonClick( wxCommandEvent& event ) 
{
	this->AddSelectedSegments();
}


void NoteDialogImp::ClearSegmentOnButtonClick(wxCommandEvent& event) { event.Skip(); }


void NoteDialogImp::NewSegment()
{
	/* open up a dialog to manage a new note segment template
	then it will appear in the list of templates for the user to apply to the note
	*/
	SegmentTypeViewModel viewModel;
	viewModel.SetIsNew(true);
	SegmentTemplateDialogImp dialog(this, &viewModel);
	if (dialog.ShowModal() == wxID_OK)
	{
		wxGetApp().GetProvider()->GetNoteSegmentTypeProvider().Insert(&viewModel.GetModifiedHeader());
		SaveSegmentTypes(viewModel);
		RenderNoteSegmentTypes();
	}
	SetupSpeechHandlers();
}

void NoteDialogImp::NewSegmentOnButtonClick(wxCommandEvent& event) 
{ 
	NewSegment();
}

void NoteDialogImp::EditSegment()
{
	/* open up a dialog to manage an existing note segment template
	then it will appear in the list of templates for the user to apply to the note
	*/
	NoteSegmentTypeHeader foundHeader = this->GetSelectedNoteType(this->lstTypes->GetSelection());
	if (foundHeader.getId() <= 0)
	{
		return;
	}
	int selectedRow = lstTypes->GetSelection();
	SegmentTypeViewModel viewModel(&foundHeader);
	viewModel.SetIsNew(false);
	SegmentTemplateDialogImp dialog(this, &viewModel);
	if (dialog.ShowModal() == wxID_OK)
	{
		NoteSegmentTypeHeader modifiedHeader = dialog.GetViewModel()->GetModifiedHeader();
		foundHeader.setHelpText(modifiedHeader.getHelpText());
		foundHeader.setTitle(modifiedHeader.getTitle());
		if (foundHeader.GetDirty())
		{
			wxGetApp().GetProvider()->GetNoteSegmentTypeProvider().Update(&foundHeader);
		}
		SaveSegmentTypes(viewModel);
		RenderNoteSegmentTypes();
	}
	if (selectedRow != wxNOT_FOUND)
	{
		lstTypes->SetSelection(selectedRow);
	}
	SetupSpeechHandlers();
}

void NoteDialogImp::DeleteSegment()
{

}

void NoteDialogImp::EditSegmentOnButtonClick(wxCommandEvent& event) 
{ 
	EditSegment();
}

void NoteDialogImp::SaveSegmentTypes(SegmentTypeViewModel& viewModel)
{
	for (int i = 0; i < viewModel.getSegmentList()->size(); i++)
	{
		NoteSegmentType segmentType = viewModel.getSegmentList()->at(i);
		segmentType.setNoteSegmentTypeHeaderId(viewModel.GetModifiedHeader().getId());
		if (segmentType.getId() > 0)
		{
			if (segmentType.GetDeleted())
			{
				wxGetApp().GetProvider()->GetNoteSegmentTypeProvider().Delete(&segmentType);
			}
			else if(segmentType.GetDirty())
			{
				wxGetApp().GetProvider()->GetNoteSegmentTypeProvider().Update(&segmentType);
			}
		}
		else
		{
			if (!segmentType.GetDeleted())
			{
				wxGetApp().GetProvider()->GetNoteSegmentTypeProvider().Insert(&segmentType);
			}
		}
	}
}



void NoteDialogImp::RenderNote(void)
{
	/* draw all the dynamic controls for each of the note segments and fill in the data */
	this->txtDescription->SetValue(viewModel.GetNote()->GetDescription());
	this->txtTitle->SetValue(viewModel.GetNote()->GetTitle());

	titlePlayerPanel = new AudioPlayerPanelImp(this, &titlePlayer);
	playerPanel = new AudioPlayerPanelImp(this, &player);
	this->szTitlePlayer->Add(titlePlayerPanel, 1, wxALL | wxEXPAND, 0);
	this->szTitlePlayer->Layout();
	this->szDescriptionPlayer->Add(playerPanel, 1, wxALL | wxEXPAND, 0);
	this->szDescriptionPlayer->Layout();

	if (!viewModel.GetNote()->GetTitleAudioFile().empty())
	{
		titlePlayer.SetURLAsync(wxGetApp().GetFileHandler().GetFullAudioPathToFile(viewModel.GetNote()->GetTitleAudioFile()));
	}
	if (!viewModel.GetNote()->GetDescriptionAudioFile().empty())
	{
		player.SetURLAsync( wxGetApp().GetFileHandler().GetFullAudioPathToFile(viewModel.GetNote()->GetDescriptionAudioFile()));
	}


	boost::ptr_vector<NoteSegment>* list = viewModel.GetNoteSegmentList();
	NoteSegment* noteSegment = nullptr;
	for(int i = 0; i < list->size(); i ++ )
	{
		noteSegment = &(list->at(i));
		//at this point the note segment type associated with the notesegment needs to be loaded
		int noteSegmentTypeId = noteSegment->GetNoteSegmentTypeId();
		/* load the NoteSegmentType from database or pull from list */
		NoteSegmentType noteSegmentType;
		wxGetApp().GetProvider()->GetNoteSegmentTypeProvider().GetNoteSegmentTypeById(noteSegmentTypeId, noteSegmentType);

		NoteSegmentPanelImp* panel = this->AddSegment(noteSegment, noteSegmentType);
		if (i == 0)
		{
			this->SetSegmentFocus(panel);
		}
	}	
	dialogSizer->Layout();

}

void NoteDialogImp::TypesOnListBox(wxCommandEvent& event)
{
	this->ChangeNoteType(event.GetSelection());
}

void NoteDialogImp::TypesOnListBoxDClick(wxCommandEvent& event)
{
	this->AddSelectedSegments();
}

void NoteDialogImp::OnOKButtonClick( wxCommandEvent& event ) 
{ 

	/* move all the data from controls into the model */
	//boost::ptr_vector<NoteSegment>* list = viewModel.GetNoteSegmentList();
	
	for(int i = 0; i < this->segmentPanelList.size(); i ++ )
	{
		NoteSegmentPanelImp* panel = this->segmentPanelList[i];
		NoteSegment* noteSegment = panel->GetNoteSegment();
		noteSegment->SetBody(panel->GetBodyControl()->GetValue().ToStdWstring());
	}	
	viewModel.GetNote()->SetTitle(this->txtTitle->GetValue().ToStdWstring());
	viewModel.GetNote()->SetDescription(this->txtDescription->GetValue().ToStdWstring());
	/* if everything is ok */
	event.Skip(); 
}


NoteSegmentTypeHeader NoteDialogImp::GetSelectedNoteType(int selectedIndex)
{
	void* selectionData = this->lstTypes->GetClientData(selectedIndex);
	unsigned long id;
	if (selectionData != NULL)
	{
		id = reinterpret_cast<unsigned long>(selectionData);
		boost::ptr_vector<NoteSegmentTypeHeader>::iterator it = std::find_if(viewModel.GetNoteTypeList()->begin(),
			viewModel.GetNoteTypeList()->end(),
			findSegmentHeader(id));
		NoteSegmentTypeHeader foundHeader = *it;
		return foundHeader;
	}
	else
	{
		return NoteSegmentTypeHeader();
	}
}

void NoteDialogImp::ChangeNoteType(int selectedIndex)
{
	/* predefined note segments with the title filled in in some cases, ie for a journal entry with the current date
	client data stored in combo box item is the id of a header record
	*/
	//change the help text shown on screen
	NoteSegmentTypeHeader foundHeader = this->GetSelectedNoteType(selectedIndex);
	this->typeInfo->SetPage(foundHeader.getHelpText());

}

void NoteDialogImp::SetSegmentFocus(NoteSegmentPanelImp* panel)
{
	panel->GetBodyControl()->SetFocus();
}

void NoteDialogImp::PlayAllOnButtonClick(wxCommandEvent& event)
{
	noteAudioPlayer.Start(&viewModel);
}

void NoteDialogImp::StopAllOnButtonClick(wxCommandEvent& event)
{
	noteAudioPlayer.Stop();
}

void NoteDialogImp::UnlockTitleOnButtonClick(wxCommandEvent& event)
{
	
	if(txtTitle->IsEnabled())
	{ 
		txtTitle->Disable();
		btnRecordTitle->SetFocus();
		this->btnUnlockTitle->SetBitmap(*wxGetApp().GetImages().unlock_icon);
	}
	else
	{ 
		//give a suitable warning
		txtTitle->Enable();
		txtTitle->SetFocus();
		this->btnUnlockTitle->SetBitmap(*wxGetApp().GetImages().lock_icon);
	}
}


void NoteDialogImp::UnlockDescriptionOnButtonClick(wxCommandEvent& event) 
{ 
	if (txtDescription->IsEnabled())
	{
		//give a suitable warning
		txtDescription->Disable();
		btnRecordDescription->SetFocus();
		this->btnUnlockDescription->SetBitmap(*wxGetApp().GetImages().unlock_icon);
	}
	else
	{
		//give a suitable warning
		txtDescription->Enable();
		txtDescription->SetFocus();
		this->btnUnlockDescription->SetBitmap(*wxGetApp().GetImages().lock_icon);
	}
}

//void NoteDialogImp::DeleteOnButtonClick( wxCommandEvent& event ) 
//{ 
//
//	/* not sure how to handle this, needs to send an event back up to the containing dialog */
//	wxObject* userData = event.GetEventUserData();
//	if(userData != NULL)
//	{
//		NoteSegment* noteSegment = (NoteSegment*)userData;
//		if(noteSegment != NULL)
//		{
//			/* the segment panel control is stored in note segment */
//			NoteSegmentPanelImp* panel = noteSegment->GetPanel();
//			if(panel != NULL)
//			{
//				panel->HideWithEffect(wxSHOW_EFFECT_ROLL_TO_LEFT);
//				dialogSizer->Layout();
//			}
//
//			/* remove the NoteSegment from the list, and delete from database */
//			if(noteSegment->GetNoteSegmentId() > 0)
//			{
//				wxGetApp().getProvider()->Delete(noteSegment);
//			}
//			viewModel.EraseItem(noteSegment);
//		}
//	}
//
//}


