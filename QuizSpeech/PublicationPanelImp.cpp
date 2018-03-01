#include <wx/valtext.h>
#include <wx/app.h> 
#include "MyApp.h"
#include "PublicationPanelImp.h"
#include "PublicationType.h"
#include "TopicDialogImp.h"
#include "NoteViewModel.h"
#include "ExercisePanelImp.h"
#include "ExerciseRunDialogImp.h"
#include "SAConfirmDialogImp.h"
#include "ActionCommandParser.h"
#include "ShelfDataViewListStore.h"

PublicationPanelImp::PublicationPanelImp( wxWindow* parent, Publication* publication)
:
pnlMain( parent ), _viewModel(new PublicationViewModel(publication)), noteListAudioPlayer(), noteAudioPlayer(), ruleNames()
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
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->Disconnect();

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
	btnViewQuizRun->SetBitmap(*wxGetApp().GetImages().docpreview_bmp);

	//columns
	colTopicTitle->SetWidth(wxCOL_WIDTH_AUTOSIZE);
	colTopicTitle->SetFlag(wxDATAVIEW_COL_SORTABLE);
	colTopicIndex->SetWidth(MyApp::DEFAULT_INDEX_COLUMN_WIDTH);
	colTopicIndex->SetFlag(wxDATAVIEW_COL_SORTABLE);
	colNoteIndex->SetWidth(MyApp::DEFAULT_INDEX_COLUMN_WIDTH);
	colNoteIndex->SetFlag(wxDATAVIEW_COL_SORTABLE);
	colNoteTitle->SetFlag(wxDATAVIEW_COL_SORTABLE);
	colQuizIndex->SetWidth(MyApp::DEFAULT_INDEX_COLUMN_WIDTH);
	colQuizIndex->SetFlag(wxDATAVIEW_COL_SORTABLE);
	colQuizName->SetFlag(wxDATAVIEW_COL_SORTABLE);
	colQuizRunIndex->SetWidth(MyApp::DEFAULT_INDEX_COLUMN_WIDTH);
	colQuizRunIndex->SetFlag(wxDATAVIEW_COL_SORTABLE);
	colQuizRunDate->SetWidth(wxCOL_WIDTH_AUTOSIZE);

	this->BindModel();
	this->btnApply->Enable(false);
	this->btnCancel->Enable(false);
	this->_viewModel->GetPublication()->setDirty(false);
	_topicModel = new ShelfDataViewListStore();
	_noteModel = new ShelfDataViewListStore();
	_quizModel = new ShelfDataViewListStore();
	quizRunModel = new ShelfDataViewListStore();
	this->lstTopics->AssociateModel(_topicModel);
	this->lstNotes->AssociateModel(_noteModel);
	this->lstQuiz->AssociateModel(_quizModel);
	lstQuizRun->AssociateModel(quizRunModel);
	_topicModel->DecRef();
	_noteModel->DecRef();
	_quizModel->DecRef();
	quizRunModel->DecRef();
	wxGetApp().GetProvider()->GetTopicsByPublication(this->_viewModel->GetPublication(), this->_viewModel->GetTopicList());
	wxGetApp().GetProvider()->GetQuizProvider().GetQuizByPublication(this->_viewModel->GetPublication(), this->_viewModel->GetQuizList());
	wxGetApp().GetProvider()->GetQuizProvider().GetQuizRunsByPublication(this->_viewModel->GetPublication(), this->_viewModel->GetQuizRunHeaderList());
	this->RenderTopics(nullptr);
	this->RenderExercises(nullptr);
	this->RenderQuizRuns();

	ruleNames.push_back(MyApp::RULE_PUBLICATION_PANEL);
	ruleNames.push_back(MyApp::RULE_DIALOG_ACTIONS);
	ruleNames.push_back(MyApp::RULE_FILE_MENU);
	SetupSpeechHandlers();
}

void PublicationPanelImp::SetupSpeechHandlers()
{
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->SetupSpeechHandlers(ruleNames, this->GetName().ToStdString(),
		boost::bind(&PublicationPanelImp::OnCommandRecognized, this, _1, _2));
	//if (wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->GetWindowName() == this->GetName())
	//{
	//	if (!wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->IsEnabled())
	//	{
	//		wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->EnableRules();
	//	}
	//}
	//else
	//{
	//	std::vector<std::wstring> ruleNames;
	//	ruleNames.push_back(MyApp::RULE_PUBLICATION_PANEL);
	//	ruleNames.push_back(MyApp::RULE_DIALOG_ACTIONS);
	//	wxGetApp().DisconnectSpeechHandler(wxGetApp().GetCommandReceivedConnection());
	//	boost::signals2::connection* commandConnection = wxGetApp().GetCommandReceivedConnection();
	//	*(commandConnection) = wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->onCommandRecognized(boost::bind(&PublicationPanelImp::OnCommandRecognized, this, _1, _2));
	//	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->EnableRules(ruleNames, this->GetName().ToStdString());
	//}
}


void PublicationPanelImp::OnCommandRecognized(std::wstring& phrase, const std::vector<CommandProperty>& commandPropertyList)
{
	std::wstring actionName;
	std::wstring actionTarget;
	std::wstring targetValue;
	std::wstring ruleName;
	ActionCommandParser actionParser;
	actionParser.Parse(commandPropertyList, actionName, actionTarget, targetValue, ruleName);

	if (boost::algorithm::equals(actionName, L"addquiz"))
	{
		AddQuiz();
		return;
	}
	else if (boost::algorithm::equals(actionName, L"editquiz"))
	{
		OnEditExercise();
		return;
	}
	else if (boost::algorithm::equals(actionName, L"runquiz"))
	{
		RunQuiz();
		return;
	}
	else if (boost::algorithm::equals(actionName, L"addnote"))
	{
		AddNote();
		return;
	}
	else if (boost::algorithm::equals(actionName, L"editnote"))
	{
		OnEditNote();
		return;
	}
	else if (boost::algorithm::equals(actionName, L"deletequiz"))
	{
		DeleteQuiz();
		return;
	}
	else if (boost::algorithm::equals(actionName, L"addtopic"))
	{
		AddTopic();
		return;
	}
	else if (boost::algorithm::equals(actionName, L"edittopic"))
	{
		EditTopic();
		return;
	}
	else if (boost::algorithm::equals(actionName, L"deletetopic"))
	{
		DeleteTopic();
		return;
	}
	else if (boost::algorithm::equals(actionName, L"deletenote"))
	{
		DeleteNote();
		return;
	}
	else if (boost::algorithm::equals(actionName, L"deletequizrun"))
	{
		DeleteQuizRun();
		return;
	}
	else if (boost::algorithm::equals(actionName, L"close") || boost::algorithm::equals(actionName, L"cancel"))
	{
		CloseMe();
		return;
	}
	wxGetApp().OnCommandRecognized(phrase, commandPropertyList);
}


void PublicationPanelImp::CloseMe()
{
	int index = wxGetApp().GetMainFrame()->GetShelfNotebook()->GetPageIndex(this);
	if (index != wxNOT_FOUND)
	{
		wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->Disconnect();
		wxGetApp().GetMainFrame()->GetShelfNotebook()->DeletePage(index);
	}
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
		data.push_back(boost::lexical_cast<std::wstring>(i + 1));
		data.push_back(list->at(i).getName());
		_topicModel->AppendItem( data, wxUIntPtr(&list->at(i)));
		if(topic != nullptr && list->at(i).getTopicId() == topic->getTopicId())
		{
			this->lstTopics->SelectRow(i);
		}
	}	
	_topicModel->Resort();
}

void PublicationPanelImp::AddTopic()
{
	TopicDialogImp dialog(this);
	dialog._title = wxString("");
	if (dialog.ShowModal() == wxID_OK && !(dialog._title.IsEmpty()))
	{
		Topic* newTopic = new Topic(_viewModel->GetPublication()->getPublicationId(), dialog._title.ToStdWstring());
		_viewModel->AddTopic(newTopic);
		wxGetApp().GetProvider()->Insert(_viewModel->GetTopic());
		this->RenderTopics(_viewModel->GetTopic());
	}
	SetupSpeechHandlers();
}

void PublicationPanelImp::AddTopicOnButtonClick( wxCommandEvent& event ) 
{ 
	AddTopic();
}

void PublicationPanelImp::DeleteTopic()
{
	Topic* topic = this->_viewModel->GetTopic();
	if (topic == nullptr)
	{
		return;
	}

	if (wxMessageBox("Delete, are you sure?", "Confirm Delete", wxYES_NO | wxCANCEL, this) == wxYES)
	{
		boost::ptr_vector<Topic>* list = this->_viewModel->GetTopicList();
		wxGetApp().GetProvider()->Delete(topic);
		list->erase(std::find(list->begin(), list->end(), *topic));
		this->RenderTopics(nullptr);
		this->OnSelectTopic(nullptr);
	}
}


void PublicationPanelImp::DeleteTopicOnButtonClick( wxCommandEvent& event ) 
{ 
	DeleteTopic();
}


void PublicationPanelImp::EditTopicOnButtonClick( wxCommandEvent& event ) 
{
	this->EditTopic();
}

void PublicationPanelImp::EditTopic()
{
	Topic* topic = _viewModel->GetTopic();
	if(topic == nullptr)
	{
		return;
	}
	TopicDialogImp dialog(this);
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
	this->EditTopic();
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
		data.push_back(boost::lexical_cast<std::wstring>(i + 1));
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


void PublicationPanelImp::AddNote()
{
	if (this->_viewModel->GetTopic() == nullptr)
	{
		return;
	}
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->Disconnect();
	Note* note = new Note(this->_viewModel->GetTopic()->getTopicId());
	NoteDialogImp dialog(this, note);
	if (dialog.ShowModal() == wxID_OK)
	{
		this->OnAfterNoteDialogClosed(dialog, note);
	}
	SetupSpeechHandlers();
}

void PublicationPanelImp::AddNoteOnButtonClick( wxCommandEvent& event ) 
{ 
	AddNote();
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

void PublicationPanelImp::DeleteNote()
{
	Note* note = this->_viewModel->GetNote();
	if (note == nullptr)
	{
		return;
	}

	//SpeechMessageDialog dialog(this, L"Delete, are you sure?", L"Confirm Delete");
	SAConfirmDialogImp confirmDlg(this);
	if (confirmDlg.ShowModal() == wxYES)
	{
		boost::ptr_vector<Note>* list = this->_viewModel->GetNoteList();
		wxGetApp().GetProvider()->Delete(note);
		list->erase(std::find(list->begin(), list->end(), *note));
		this->RenderNotes(nullptr);
		this->OnSelectNote(nullptr);
	}
	SetupSpeechHandlers();
}

void PublicationPanelImp::DeleteNoteOnButtonClick( wxCommandEvent& event ) 
{ 
	DeleteNote();
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
	if (_viewModel->GetNote() == nullptr)
	{
		return;
	}
	NoteDialogImp dialog(this, this->_viewModel->GetNote());
	if(dialog.ShowModal() == wxID_OK)
	{
		this->OnAfterNoteDialogClosed(dialog, this->_viewModel->GetNote());
	}
	SetupSpeechHandlers();
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

void PublicationPanelImp::AddQuiz()
{
	ExercisePanelImp* pnlExercise = new ExercisePanelImp(wxGetApp().GetMainFrame()->GetShelfNotebook(), _viewModel->GetPublication());
	pnlExercise->InitDialog();
	wxGetApp().GetMainFrame()->GetShelfNotebook()->AddPage(pnlExercise, "Exercise - ", true);
}

void PublicationPanelImp::AddQuizOnButtonClick(wxCommandEvent& event)
{ 
	AddQuiz();
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
		data.push_back(boost::lexical_cast<std::wstring>(i + 1));
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

void PublicationPanelImp::AddQuizOnUpdateUI(wxUpdateUIEvent& event) 
{ 
	event.Skip(); 
}

void PublicationPanelImp::DeleteQuizRun()
{
	if (lstQuizRun->GetSelectedRow() != wxNOT_FOUND)
	{
		SAConfirmDialogImp confirmDlg(this);
		if (confirmDlg.ShowModal() == wxYES)
		{
			QuizRunHeader header = _viewModel->GetQuizRunHeaderList()->at(lstQuizRun->GetSelectedRow());
			wxGetApp().GetProvider()->GetQuizProvider().Delete(header);
			boost::ptr_vector<QuizRunHeader>* list = this->_viewModel->GetQuizRunHeaderList();
			list->erase(std::find(list->begin(), list->end(), header));
			RenderQuizRuns();
		}
		SetupSpeechHandlers();
	}
}


void PublicationPanelImp::DeleteQuiz()
{
	if (_viewModel->GetExercise() == nullptr)
	{
		return;
	}

	SAConfirmDialogImp confirmDlg(this);
	if (confirmDlg.ShowModal() == wxYES)
	{
		wxGetApp().GetProvider()->GetQuizProvider().Delete(_viewModel->GetExercise());
		_viewModel->SetExercise(nullptr);
		RenderExercises(nullptr);
	}
	SetupSpeechHandlers();
}

void PublicationPanelImp::DeleteQuizOnButtonClick(wxCommandEvent& event) 
{ 
	DeleteQuiz();
}

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

void PublicationPanelImp::RunQuiz()
{
	if (_viewModel->GetExercise() == nullptr)
	{
		return;
	}
	ExerciseRunDialogImp runDialog(this, _viewModel->GetExercise()->GetQuizId());
	runDialog.ShowModal();
	this->_viewModel->GetQuizRunHeaderList()->clear();
	wxGetApp().GetProvider()->GetQuizProvider().GetQuizRunsByPublication(this->_viewModel->GetPublication(), this->_viewModel->GetQuizRunHeaderList());
	this->RenderQuizRuns();
}

void PublicationPanelImp::RunQuizOnButtonClick(wxCommandEvent& event)
{
	RunQuiz();
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
	SetupSpeechHandlers();
	//this->_viewModel->GetQuizRunHeaderList()->clear();
	//wxGetApp().GetProvider()->GetQuizProvider().GetQuizRunsByPublication(this->_viewModel->GetPublication(), this->_viewModel->GetQuizRunHeaderList());
	//this->RenderQuizRuns();
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
		wxString createdDate;
		data.push_back(boost::lexical_cast<std::wstring>(i + 1));
		createdDate.Append(list->at(i).GetCreatedDate().FormatDate());
		createdDate.Append(L" ");
		createdDate.Append(list->at(i).GetCreatedDate().FormatTime());
		data.push_back(createdDate);
		if (list->at(i).GetIsComplete())
		{
			data.push_back(wxVariant(wxDataViewIconText(L"Yes", *wxGetApp().GetImages().taskCompleteIcon)));
		}
		else
		{
			data.push_back(wxVariant(wxDataViewIconText(L"No", *wxGetApp().GetImages().taskRejectIcon)));
		}
		data.push_back(wxVariant(wxString(list->at(i).GetQuiz().GetName())));
		quizRunModel->AppendItem(data, wxUIntPtr(&list->at(i)));
		/*if (quiz != nullptr && list->at(i).GetQuizId() == quiz->GetQuizId())
		{
			this->lstQuiz->SelectRow(i);
		}*/
	}
}

void PublicationPanelImp::ViewQuizRun()
{
	if (lstQuizRun->GetSelectedRow() != wxNOT_FOUND)
	{
		QuizRunHeader header = _viewModel->GetQuizRunHeaderList()->at(lstQuizRun->GetSelectedRow());
		ExerciseRunDialogImp runDialog(this, header);
		runDialog.ShowModal();
		SetupSpeechHandlers();
	}
	
}

void PublicationPanelImp::ViewQuizRunOnButtonClick(wxCommandEvent& event)
{
	ViewQuizRun();
}
void PublicationPanelImp::ViewQuizRunOnUpdateUI(wxUpdateUIEvent& event)
{
	if (lstQuizRun->GetSelectedItemsCount() > 0)
	{
		btnViewQuizRun->Enable();
	}
	else
	{
		btnViewQuizRun->Disable();
	}
}
void PublicationPanelImp::DeleteQuizRunOnButtonClick(wxCommandEvent& event)
{
	DeleteQuizRun();
}
void PublicationPanelImp::DeleteQuizRunOnUpdateUI(wxUpdateUIEvent& event)
{
	if (lstQuizRun->GetSelectedItemsCount() > 0)
	{
		btnDeleteQuizRun->Enable();
	}
	else
	{
		btnDeleteQuizRun->Disable();
	}
}
void PublicationPanelImp::QuizRunOnItemActivated(wxDataViewEvent& event)
{
	ViewQuizRun();
}

void PublicationPanelImp::QuizRunOnSelectionChanged(wxDataViewEvent& event)
{

}
