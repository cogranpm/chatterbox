#include <wx/valtext.h>
#include <wx/app.h> 
#include "MyApp.h"
#include "PublicationPanelImp.h"
#include "PublicationType.h"
#include "TopicDialogImp.h"
#include "NoteViewModel.h"
#include "ExercisePanelImp.h"
#include "ExerciseRunDialogImp.h"

PublicationPanelImp::PublicationPanelImp( wxWindow* parent, Publication* publication)
:
pnlMain( parent ), _viewModel(new PublicationViewModel(publication)), noteListAudioPlayer(), noteAudioPlayer()
{
	this->cboType->SetClientObject(0, new PublicationType(0));
	this->cboType->SetClientObject(1, new PublicationType(1));
	this->cboType->SetClientObject(2, new PublicationType(2));
	this->cboType->SetClientObject(3, new PublicationType(3));
	_title = this->_viewModel->GetPublication()->getTitle();
	this->InitDialog();
}

PublicationPanelImp::~PublicationPanelImp()
{
	if(_viewModel != nullptr)
	{
		delete _viewModel;
		_viewModel = nullptr;
	}


	if(this->_topicModel != nullptr)
	{
		this->_topicModel->DeleteAllItems();
		this->_topicModel = nullptr;
		delete this->_topicModel;
		
	}

	if(this->_noteModel != nullptr)
	{
		this->_noteModel->DeleteAllItems();
		this->_noteModel = nullptr;
		delete this->_noteModel;
		
	}

	if(this->_quizModel != nullptr)
	{
		this->_quizModel->DeleteAllItems();
		this->_quizModel = nullptr;
		delete this->_quizModel;
	}

	if (this->quizRunModel != nullptr)
	{
		this->quizRunModel->DeleteAllItems();
		this->quizRunModel = nullptr;
		delete this->quizRunModel;
	}
}

void PublicationPanelImp::OnInitDialog( wxInitDialogEvent& event )
{

	//icons 


	btnEditTopic->SetBitmap(*wxGetApp().GetImages().edit_icon);
	btnEditNote->SetBitmap(*wxGetApp().GetImages().edit_icon);
	btnEditQuiz->SetBitmap(*wxGetApp().GetImages().edit_icon);

	btnAddTopic->SetBitmap(*wxGetApp().GetImages().add_icon);
	btnAddNote->SetBitmap(*wxGetApp().GetImages().add_icon);
	btnAddQuiz->SetBitmap(*wxGetApp().GetImages().add_icon);

	btnDeleteTopic->SetBitmap(*wxGetApp().GetImages().delete_icon);
	btnDeleteNote->SetBitmap(*wxGetApp().GetImages().delete_icon);
	btnDeleteQuiz->SetBitmap(*wxGetApp().GetImages().delete_icon);
	btnDeleteQuizRun->SetBitmap(*wxGetApp().GetImages().delete_icon);

	btnPlay->SetBitmap(*wxGetApp().GetImages().start_icon);
	btnPlayAll->SetBitmap(*wxGetApp().GetImages().playstep_icon);
	btnStop->SetBitmap(*wxGetApp().GetImages().stop_icon);

	btnRunQuiz->SetBitmap(*wxGetApp().GetImages().start_icon);
	btnViewQuizRun->SetBitmap(*wxGetApp().GetImages().start_icon);

	this->BindModel();
	this->btnApply->Enable(false);
	this->btnCancel->Enable(false);
	this->_viewModel->GetPublication()->setDirty(false);
	_topicModel = new wxDataViewListStore();
	_noteModel = new wxDataViewListStore();
	_quizModel = new wxDataViewListStore();
	quizRunModel = new wxDataViewListStore();
	this->lstTopics->AssociateModel(_topicModel);
	this->lstNotes->AssociateModel(_noteModel);
	this->lstQuiz->AssociateModel(_quizModel);
	lstQuizRun->AssociateModel(quizRunModel);
	_topicModel->DecRef();
	_noteModel->DecRef();
	_quizModel->DecRef();
	quizRunModel->DecRef();
	this->SetupSpeechHandlers();
	wxGetApp().GetProvider()->GetTopicsByPublication(this->_viewModel->GetPublication(), this->_viewModel->GetTopicList());
	wxGetApp().GetProvider()->GetQuizProvider().GetQuizByPublication(this->_viewModel->GetPublication(), this->_viewModel->GetQuizList());
	wxGetApp().GetProvider()->GetQuizProvider().GetQuizRunsByPublication(this->_viewModel->GetPublication(), this->_viewModel->GetQuizRunHeaderList());
	this->RenderTopics(nullptr);
	this->RenderExercises(nullptr);
	this->RenderQuizRuns();
}

void PublicationPanelImp::SetupSpeechHandlers()
{
	wxGetApp().DisconnectSpeechHandler(wxGetApp().GetCommandReceivedConnection());
}

void PublicationPanelImp::BindModel()
{
	this->txtTitle->GetValidator()->TransferToWindow();
	this->cboType->SetSelection(this->_viewModel->GetPublication()->getType());
}


void PublicationPanelImp::TitleOnText( wxCommandEvent& event ) 
{ 
	this->_viewModel->GetPublication()->setDirty(true);
}

void PublicationPanelImp::TypeOnCombobox( wxCommandEvent& event ) 
{ 
	this->_viewModel->GetPublication()->setDirty(true);
}

void PublicationPanelImp::ApplyOnButtonClick( wxCommandEvent& event )
{
	if(this->txtTitle->GetValidator()->Validate(this) && this->txtTitle->GetValidator()->TransferFromWindow())
	{
		this->_viewModel->GetPublication()->setTitle(this->txtTitle->GetValue().ToStdWstring());
		PublicationType* data = dynamic_cast<PublicationType*>(this->cboType->GetClientObject(this->cboType->GetSelection()));
		this->_viewModel->GetPublication()->setType(data->getKey());
		wxGetApp().GetProvider()->Update(this->_viewModel->GetPublication());
		this->_viewModel->GetPublication()->setDirty(false);
	}
	else
	{
		event.Skip();
	}

}


void PublicationPanelImp::ApplyOnUpdateUI( wxUpdateUIEvent& event ) 
{
	if(this->_viewModel->GetPublication()->getDirty() == true)
	{
		this->btnApply->Enable(true);
	}
	else
	{
		this->btnApply->Enable(false);
	}
}

void PublicationPanelImp::CancelOnButtonClick( wxCommandEvent& event ) 
{ 
	this->BindModel();
	this->_viewModel->GetPublication()->setDirty(false);
}


void PublicationPanelImp::CancelOnUpdateUI( wxUpdateUIEvent& event ) 
{ 
	if(this->_viewModel->GetPublication()->getDirty() == true)
	{
		this->btnCancel->Enable(true);
	}
	else
	{
		this->btnCancel->Enable(false);
	}
}
		

void PublicationPanelImp::RenderTopics(Topic* topic)
{
	this->_topicModel->DeleteAllItems();
	wxVector<wxVariant> data;
	boost::ptr_vector<Topic>* list = this->_viewModel->GetTopicList();
	for(int i = 0; i < list->size(); i ++ )
	{
		data.clear();
		data.push_back(list->at(i).getName());
		_topicModel->AppendItem( data, wxUIntPtr(&list->at(i)));
		if(topic != nullptr && list->at(i).getTopicId() == topic->getTopicId())
		{
			this->lstTopics->SelectRow(i);
		}
	}	
}


void PublicationPanelImp::AddTopicOnButtonClick( wxCommandEvent& event ) 
{ 
	TopicDialog dialog(this);
	dialog._title = wxString("");
	if(dialog.ShowModal() == wxID_OK && !(dialog._title.IsEmpty()))
	{
		Topic* newTopic = new Topic(_viewModel->GetPublication()->getPublicationId(), dialog._title.ToStdWstring());
		_viewModel->AddTopic(newTopic);
		wxGetApp().GetProvider()->Insert(_viewModel->GetTopic());
		this->RenderTopics(_viewModel->GetTopic());
	}
}

void PublicationPanelImp::DeleteTopicOnButtonClick( wxCommandEvent& event ) 
{ 
	Topic* topic = this->_viewModel->GetTopic();
	if(topic == nullptr)
	{
		return;
	}
	
	if(wxMessageBox("Delete, are you sure?", "Confirm Delete", wxYES_NO | wxCANCEL, this) == wxYES)
	{
		boost::ptr_vector<Topic>* list = this->_viewModel->GetTopicList();
		wxGetApp().GetProvider()->Delete(topic);
		list->erase(std::find(list->begin(), list->end(), *topic));
		this->RenderTopics(nullptr);
		this->OnSelectTopic(nullptr);
	}
}


void PublicationPanelImp::EditTopicOnButtonClick( wxCommandEvent& event ) 
{
	this->EditTopic(_viewModel->GetTopic());
}

void PublicationPanelImp::EditTopic(Topic* topic)
{
	if(topic == nullptr)
	{
		return;
	}
	TopicDialog dialog(this);
	dialog._title = topic->getName();
	if(dialog.ShowModal() == wxID_OK && !(dialog._title.IsEmpty()))
	{
		wxString currentTitle(topic->getName());
		if(!(currentTitle.IsSameAs(dialog._title)))
		{
			topic->setName(dialog._title.ToStdWstring());
			wxGetApp().GetProvider()->Update(topic);
			this->RenderTopics(topic);
		}
	}
}



void PublicationPanelImp::OnTopicItemActivated( wxDataViewEvent& event )
{
	this->EditTopic(_viewModel->GetTopic());
}

void PublicationPanelImp::OnTopicSelectionChanged( wxDataViewEvent& event )
{
	wxDataViewItem item = event.GetItem();
	if(item == nullptr)
	{
		return;
	}
	Topic* topic = (Topic*)this->lstTopics->GetItemData(item);
	this->OnSelectTopic(topic);
}

void PublicationPanelImp::OnSelectTopic(Topic* topic)
{
	this->_viewModel->SetTopic(topic);
	this->_viewModel->GetNoteList()->clear();
	if(topic != nullptr)
	{
		wxGetApp().GetProvider()->GetNotesByTopic(this->_viewModel->GetTopic(), this->_viewModel->GetNoteList());
	}
	this->RenderNotes(nullptr);
}

void PublicationPanelImp::EditTopicOnUpdateUI( wxUpdateUIEvent& event )
{
	if(this->_viewModel->GetTopic() != nullptr)
	{
		this->btnEditTopic->Enable(true);
	}
	else
	{
		this->btnEditTopic->Enable(false);
	}
}


void PublicationPanelImp::DeleteTopicOnUpdateUI( wxUpdateUIEvent& event )
{
	if(this->_viewModel->GetTopic() != nullptr)
	{
		this->btnDeleteTopic->Enable(true);
	}
	else
	{
		this->btnDeleteTopic->Enable(false);
	}
}


void PublicationPanelImp::RenderNotes(Note* note)
{
	this->_noteModel->DeleteAllItems();
	wxVector<wxVariant> data;
	boost::ptr_vector<Note>* list = this->_viewModel->GetNoteList();
	for(int i = 0; i < list->size(); i ++ )
	{
		Note* currentNote = &(list->at(i));
		data.clear();
		data.push_back(currentNote->GetTitle());
		data.push_back(currentNote->GetDescription());
		int numSegments = wxGetApp().GetProvider()->GetSegmentCount(currentNote);
		std::wstring segmentDisplay(L"");
		wxGetApp().GetProvider()->GetSegmentDisplay(currentNote, segmentDisplay);
		wxString displaySegments;
		displaySegments << numSegments;
		data.push_back(displaySegments); 
		data.push_back(segmentDisplay);
		data.push_back(currentNote->GetCreatedDate().FormatDate());
		_noteModel->AppendItem(data, wxUIntPtr(currentNote));
		if(note != nullptr && currentNote->GetNoteId() == note->GetNoteId())
		{
			this->lstNotes->SelectRow(i);
		}
	}	
	if (list->size() > 0)
	{
		btnPlayAll->Enable();
	}
	else
	{
		btnPlayAll->Disable();
	}
}

void PublicationPanelImp::OnSelectNote(Note* note)
{
	this->_viewModel->SetNote(note);
}

void PublicationPanelImp::AddNoteOnButtonClick( wxCommandEvent& event ) 
{ 
	Note* note = new Note(this->_viewModel->GetTopic()->getTopicId());
	NoteDialogImp dialog(this, note);
	if(dialog.ShowModal() == wxID_OK)
	{
		this->OnAfterNoteDialogClosed(dialog, note);
	}
}


void PublicationPanelImp::AddNoteOnUpdateUI( wxUpdateUIEvent& event ) 
{ 
	if(this->_viewModel->GetTopic() != nullptr)
	{
		this->btnAddNote->Enable(true);
	}
	else
	{
		this->btnAddNote->Enable(false);
	}
}


void PublicationPanelImp::DeleteNoteOnButtonClick( wxCommandEvent& event ) 
{ 
	Note* note = this->_viewModel->GetNote();
	if(note == nullptr)
	{
		return;
	}
	
	if(wxMessageBox("Delete, are you sure?", "Confirm Delete", wxYES_NO | wxCANCEL, this) == wxYES)
	{
		boost::ptr_vector<Note>* list = this->_viewModel->GetNoteList();
		wxGetApp().GetProvider()->Delete(note);
		list->erase(std::find(list->begin(), list->end(), *note));
		this->RenderNotes(nullptr);
		this->OnSelectNote(nullptr);
	}
}

void PublicationPanelImp::DeleteNoteOnUpdateUI( wxUpdateUIEvent& event ) 
{ 
	if(this->_viewModel->GetNote() != nullptr)
	{
		this->btnDeleteNote->Enable(true);
	}
	else
	{
		this->btnDeleteNote->Enable(false);
	}
}


void PublicationPanelImp::EditNoteOnButtonClick( wxCommandEvent& event )
{ 
	this->OnEditNote();
}

void PublicationPanelImp::EditNoteOnUpdateUI( wxUpdateUIEvent& event )
{ 
	if(this->_viewModel->GetNote() != nullptr)
	{
		this->btnEditNote->Enable(true);
	}
	else
	{
		this->btnEditNote->Enable(false);
	}
}

void PublicationPanelImp::NotesOnItemActivated( wxDataViewEvent& event ) 
{ 
	this->OnEditNote();
}

void PublicationPanelImp::NotesOnSelectionChanged( wxDataViewEvent& event ) 
{ 
	wxDataViewItem item = event.GetItem();
	if(item == nullptr)
	{
		return;
	}
	Note* note = (Note*)this->lstNotes->GetItemData(item);
	this->OnSelectNote(note);
}

void PublicationPanelImp::OnEditNote()
{
	NoteDialogImp dialog(this, this->_viewModel->GetNote());
	if(dialog.ShowModal() == wxID_OK)
	{
		this->OnAfterNoteDialogClosed(dialog, this->_viewModel->GetNote());
	}
}

void PublicationPanelImp::OnAfterNoteDialogClosed(NoteDialogImp& dialog, Note* note)
{
	bool noteIsNew = false;
	/* save the note and all the segments from the view model in the dialog */
	NoteViewModel& noteViewModel = dialog.GetViewModel();
	/* for each segment, insert */
	if(noteViewModel.GetNote()->GetNoteId() > 0)
	{
		wxGetApp().GetProvider()->Update(noteViewModel.GetNote());
	}
	else
	{
		wxGetApp().GetProvider()->Insert(noteViewModel.GetNote());
		this->_viewModel->GetNoteList()->push_back(noteViewModel.GetNote());
		noteIsNew = true;
	}

	/* the dialog updates the view model */
	boost::ptr_vector<NoteSegment>* list = noteViewModel.GetNoteSegmentList();
	for(int i = 0; i < list->size(); i ++ )
	{
		NoteSegment* noteSegment = &(list->at(i));
		noteSegment->SetNoteId(noteViewModel.GetNote()->GetNoteId());
		/* process deletes first */
		if(wxString(noteSegment->GetBody()).IsEmpty() 
			&& wxString(noteSegment->GetTitle()).IsEmpty()
			&& noteSegment->GetNoteSegmentId() > 0)
		{
			wxGetApp().GetProvider()->Delete(noteSegment);
		}
		else
		{
			if(noteSegment->GetNoteSegmentId() > 0)
			{
				wxGetApp().GetProvider()->Update(noteSegment);
			}
			else
			{
				wxGetApp().GetProvider()->Insert(noteSegment);
			}
		}
	}	
	if(noteIsNew)
	{
		this->OnSelectNote(note);
	}
	this->RenderNotes(note);
}

void PublicationPanelImp::PlayOnButtonClick(wxCommandEvent& event) 
{ 
	btnStop->Enable();
	noteAudioPlayer.Start(_viewModel->GetNote());
}


void PublicationPanelImp::PlayAllOnButtonClick(wxCommandEvent& event) 
{ 
	btnStop->Enable();
	noteListAudioPlayer.Start(_viewModel->GetNoteList());
}


void PublicationPanelImp::StopOnButtonClick(wxCommandEvent& event) 
{ 
	noteListAudioPlayer.Stop();
	btnStop->Disable();
}

void PublicationPanelImp::PlayOnUpdateUI(wxUpdateUIEvent& event)
{ 
	if (this->_viewModel->GetNote() != nullptr)
	{
		this->btnPlay->Enable(true);
	}
	else
	{
		this->btnPlay->Enable(false);
	}
}


/* excercise stuff */
void PublicationPanelImp::AddQuizOnButtonClick(wxCommandEvent& event)
{ 

	ExercisePanelImp* pnlExercise = new ExercisePanelImp(wxGetApp().GetMainFrame()->GetShelfNotebook(), _viewModel->GetPublication());
	pnlExercise->InitDialog();
	wxGetApp().GetMainFrame()->GetShelfNotebook()->AddPage(pnlExercise, "Exercise - ", true);
//	wxPanel* pnlNewPublication = new PublicationPanelImp(this->m_auiShelf, this->GetCurrentPublication());

}

void PublicationPanelImp::RenderExercises(Quiz* quiz)
{
	this->_quizModel->DeleteAllItems();
	lstQuiz->DeleteAllItems();
	wxVector<wxVariant> data;
	boost::ptr_vector<Quiz>* list = this->_viewModel->GetQuizList();
	for (int i = 0; i < list->size(); i++)
	{
		data.clear();
		data.push_back(list->at(i).GetName());
		_quizModel->AppendItem(data, wxUIntPtr(&list->at(i)));
		if (quiz != nullptr && list->at(i).GetQuizId() == quiz->GetQuizId())
		{
			this->lstQuiz->SelectRow(i);
		}
	}
}

void PublicationPanelImp::OnEditExercise()
{
	ExercisePanelImp* pnlExercise = new ExercisePanelImp(wxGetApp().GetMainFrame()->GetShelfNotebook(), _viewModel->GetPublication(), _viewModel->GetExercise() );
	pnlExercise->InitDialog();
	wxGetApp().GetMainFrame()->GetShelfNotebook()->AddPage(pnlExercise, L"Exercise - " + _viewModel->GetExercise()->GetName(), true);
}

void PublicationPanelImp::OnSelectExercise(Quiz* quiz)
{
	_viewModel->SetExercise(quiz);
}

void PublicationPanelImp::AddQuizOnUpdateUI(wxUpdateUIEvent& event) { event.Skip(); }
void PublicationPanelImp::DeleteQuizOnButtonClick(wxCommandEvent& event) { event.Skip(); }
void PublicationPanelImp::DeleteQuizOnUpdateUI(wxUpdateUIEvent& event) 
{
	if (_viewModel->GetExercise() != nullptr)
	{
		btnDeleteQuiz->Enable();
	}
	else
	{
		btnDeleteQuiz->Disable();
	}
}
void PublicationPanelImp::EditQuizOnButtonClick(wxCommandEvent& event) 
{ 
	OnEditExercise();
}

void PublicationPanelImp::EditQuizOnUpdateUI(wxUpdateUIEvent& event) 
{ 
	if (_viewModel->GetExercise() != nullptr)
	{
		btnEditQuiz->Enable();
	}
	else
	{
		btnEditQuiz->Disable();
	}
}
void PublicationPanelImp::QuizOnItemActivated(wxDataViewEvent& event) 
{ 
	OnEditExercise();
}


void PublicationPanelImp::QuizOnSelectionChanged(wxDataViewEvent& event) 
{ 
	wxDataViewItem item = event.GetItem();
	if (item == nullptr)
	{
		return;
	}
	Quiz* quiz = (Quiz*)this->lstQuiz->GetItemData(item);
	this->OnSelectExercise(quiz);
}

void PublicationPanelImp::RunQuizOnButtonClick(wxCommandEvent& event)
{
	ExerciseRunDialogImp runDialog(this, _viewModel->GetExercise()->GetQuizId());
	runDialog.ShowModal();

}

void PublicationPanelImp::RunQuizOnUpdateUI(wxUpdateUIEvent& event)
{
	if (_viewModel->GetExercise() != nullptr)
	{
		btnRunQuiz->Enable();
	}
	else
	{
		btnRunQuiz->Disable();
	}
}


void PublicationPanelImp::Refresh()
{
	this->_viewModel->GetQuizList()->clear();
	wxGetApp().GetProvider()->GetQuizProvider().GetQuizByPublication(this->_viewModel->GetPublication(), this->_viewModel->GetQuizList());
	this->RenderExercises(nullptr);
}


void PublicationPanelImp::RenderQuizRuns()
{
	this->quizRunModel->DeleteAllItems();
	lstQuizRun->DeleteAllItems();
	wxVector<wxVariant> data;
	boost::ptr_vector<QuizRunHeader>* list = this->_viewModel->GetQuizRunHeaderList();
	for (int i = 0; i < list->size(); i++)
	{
		data.clear();
		data.push_back(list->at(i).GetCreatedDate().FormatISOCombined());
		if (list->at(i).GetIsComplete())
		{
			data.push_back(wxVariant(wxDataViewIconText(L"Yes", *wxGetApp().GetImages().taskCompleteIcon)));
		}
		else
		{
			data.push_back(wxVariant(wxDataViewIconText(L"No", *wxGetApp().GetImages().taskRejectIcon)));
		}
		quizRunModel->AppendItem(data, wxUIntPtr(&list->at(i)));
		/*if (quiz != nullptr && list->at(i).GetQuizId() == quiz->GetQuizId())
		{
			this->lstQuiz->SelectRow(i);
		}*/
	}
}

void PublicationPanelImp::ViewQuizRunOnButtonClick(wxCommandEvent& event)
{

}
void PublicationPanelImp::ViewQuizRunOnUpdateUI(wxUpdateUIEvent& event)
{

}
void PublicationPanelImp::DeleteQuizRunOnButtonClick(wxCommandEvent& event)
{

}
void PublicationPanelImp::DeleteQuizRunOnUpdateUI(wxUpdateUIEvent& event)
{

}
void PublicationPanelImp::QuizRunOnItemActivated(wxDataViewEvent& event)
{

}
void PublicationPanelImp::QuizRunOnSelectionChanged(wxDataViewEvent& event)
{

}
