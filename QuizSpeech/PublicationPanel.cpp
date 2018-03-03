///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug  4 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "PublicationPanel.h"

///////////////////////////////////////////////////////////////////////////

pnlMain::pnlMain( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxVERTICAL );
	
	panelPublication = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( panelPublication, wxID_ANY, wxT("Publication") ), wxVERTICAL );
	
	wxGridBagSizer* gbSizer1;
	gbSizer1 = new wxGridBagSizer( 0, 0 );
	gbSizer1->SetFlexibleDirection( wxBOTH );
	gbSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Title"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	gbSizer1->Add( m_staticText1, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	txtTitle = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), 0 );
	#ifdef __WXGTK__
	if ( !txtTitle->HasFlag( wxTE_MULTILINE ) )
	{
	txtTitle->SetMaxLength( 60 );
	}
	#else
	txtTitle->SetMaxLength( 60 );
	#endif
	txtTitle->SetValidator( wxTextValidator( wxFILTER_NONE, &_title ) );
	
	gbSizer1->Add( txtTitle, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_staticText2 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Type"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	gbSizer1->Add( m_staticText2, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	cboType = new wxComboBox( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), 0, NULL, wxCB_READONLY|wxCB_SORT );
	cboType->Append( wxT("Audio Visual") );
	cboType->Append( wxT("Book") );
	cboType->Append( wxT("Lecture") );
	cboType->Append( wxT("Link") );
	cboType->Append( wxT("List") );
	cboType->Append( wxT("Notebook") );
	cboType->SetSelection( 0 );
	gbSizer1->Add( cboType, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	btnApply = new wxButton( sbSizer1->GetStaticBox(), wxID_APPLY, wxT("&Apply"), wxDefaultPosition, wxDefaultSize, 0 );
	btnApply->Enable( false );
	
	gbSizer1->Add( btnApply, wxGBPosition( 1, 3 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	btnCancel = new wxButton( sbSizer1->GetStaticBox(), wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	btnCancel->Enable( false );
	
	gbSizer1->Add( btnCancel, wxGBPosition( 1, 4 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	
	sbSizer1->Add( gbSizer1, 1, wxEXPAND, 5 );
	
	
	bSizer3->Add( sbSizer1, 1, wxEXPAND, 5 );
	
	
	panelPublication->SetSizer( bSizer3 );
	panelPublication->Layout();
	bSizer3->Fit( panelPublication );
	bSizer24->Add( panelPublication, 0, wxEXPAND | wxALL, 5 );
	
	splitterTopic = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	splitterTopic->Connect( wxEVT_IDLE, wxIdleEventHandler( pnlMain::splitterTopicOnIdle ), NULL, this );
	
	panelTopics = new wxPanel( splitterTopic, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText3 = new wxStaticText( panelTopics, wxID_ANY, wxT("Topics"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer5->Add( m_staticText3, 0, wxALL, 5 );
	
	btnAddTopic = new wxButton( panelTopics, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnAddTopic->SetToolTip( wxT("Add Topic") );
	btnAddTopic->SetMaxSize( wxSize( 25,-1 ) );
	
	bSizer5->Add( btnAddTopic, 0, 0, 5 );
	
	btnDeleteTopic = new wxButton( panelTopics, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnDeleteTopic->Enable( false );
	btnDeleteTopic->SetToolTip( wxT("Delete Topic") );
	btnDeleteTopic->SetMaxSize( wxSize( 25,-1 ) );
	
	bSizer5->Add( btnDeleteTopic, 0, 0, 5 );
	
	btnEditTopic = new wxButton( panelTopics, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnEditTopic->Enable( false );
	btnEditTopic->SetToolTip( wxT("Edit Topic") );
	btnEditTopic->SetMaxSize( wxSize( 60,-1 ) );
	
	bSizer5->Add( btnEditTopic, 1, 0, 5 );
	
	
	bSizer4->Add( bSizer5, 0, 0, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	lstTopics = new wxDataViewListCtrl( panelTopics, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	colTopicIndex = lstTopics->AppendTextColumn( wxEmptyString );
	colTopicTitle = lstTopics->AppendTextColumn( wxT("Title") );
	bSizer6->Add( lstTopics, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer4->Add( bSizer6, 1, wxEXPAND, 5 );
	
	
	panelTopics->SetSizer( bSizer4 );
	panelTopics->Layout();
	bSizer4->Fit( panelTopics );
	panelTopicChildren = new wxPanel( splitterTopic, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );
	
	notebookChildren = new wxNotebook( panelTopicChildren, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	panelTopicChildNote = new wxPanel( notebookChildren, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* sizerTopicChildren;
	sizerTopicChildren = new wxBoxSizer( wxHORIZONTAL );
	
	panelNotes = new wxPanel( panelTopicChildNote, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );
	
	btnAddNote = new wxButton( panelNotes, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnAddNote->Enable( false );
	btnAddNote->SetToolTip( wxT("Add Note") );
	btnAddNote->SetMaxSize( wxSize( 25,-1 ) );
	
	bSizer8->Add( btnAddNote, 0, 0, 5 );
	
	btnDeleteNote = new wxButton( panelNotes, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnDeleteNote->Enable( false );
	btnDeleteNote->SetToolTip( wxT("Delete Note") );
	btnDeleteNote->SetMaxSize( wxSize( 25,-1 ) );
	
	bSizer8->Add( btnDeleteNote, 0, 0, 5 );
	
	btnEditNote = new wxButton( panelNotes, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnEditNote->Enable( false );
	btnEditNote->SetToolTip( wxT("Edit Note") );
	btnEditNote->SetMaxSize( wxSize( 60,-1 ) );
	
	bSizer8->Add( btnEditNote, 0, 0, 5 );
	
	btnPlayAll = new wxButton( panelNotes, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnPlayAll->Enable( false );
	btnPlayAll->SetToolTip( wxT("Play All") );
	
	bSizer8->Add( btnPlayAll, 0, 0, 5 );
	
	btnPlay = new wxButton( panelNotes, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnPlay->Enable( false );
	btnPlay->SetToolTip( wxT("Play") );
	
	bSizer8->Add( btnPlay, 0, 0, 5 );
	
	btnStop = new wxButton( panelNotes, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnStop->Enable( false );
	btnStop->SetToolTip( wxT("Stop") );
	
	bSizer8->Add( btnStop, 0, 0, 5 );
	
	
	bSizer7->Add( bSizer8, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	lstNotes = new wxDataViewListCtrl( panelNotes, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	colNoteIndex = lstNotes->AppendTextColumn( wxEmptyString );
	colNoteTitle = lstNotes->AppendTextColumn( wxT("Title") );
	colNoteDescription = lstNotes->AppendTextColumn( wxT("Description") );
	colNoteSegmentCount = lstNotes->AppendTextColumn( wxT("# Segments") );
	colNoteSegmentTitle = lstNotes->AppendTextColumn( wxT("Segment Titles") );
	colNotesCreatedDate = lstNotes->AppendTextColumn( wxT("Created") );
	bSizer9->Add( lstNotes, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer7->Add( bSizer9, 1, wxEXPAND, 5 );
	
	
	panelNotes->SetSizer( bSizer7 );
	panelNotes->Layout();
	bSizer7->Fit( panelNotes );
	sizerTopicChildren->Add( panelNotes, 1, wxEXPAND, 5 );
	
	
	panelTopicChildNote->SetSizer( sizerTopicChildren );
	panelTopicChildNote->Layout();
	sizerTopicChildren->Fit( panelTopicChildNote );
	notebookChildren->AddPage( panelTopicChildNote, wxT("Notes"), true );
	panelTopicChildQuiz = new wxPanel( notebookChildren, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	wxWrapSizer* wSizer2;
	wSizer2 = new wxWrapSizer( wxHORIZONTAL );
	
	btnAddQuiz = new wxButton( panelTopicChildQuiz, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnAddQuiz->SetMaxSize( wxSize( 25,-1 ) );
	
	wSizer2->Add( btnAddQuiz, 0, 0, 5 );
	
	btnDeleteQuiz = new wxButton( panelTopicChildQuiz, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnDeleteQuiz->Enable( false );
	btnDeleteQuiz->SetMaxSize( wxSize( 25,-1 ) );
	
	wSizer2->Add( btnDeleteQuiz, 0, 0, 5 );
	
	btnEditQuiz = new wxButton( panelTopicChildQuiz, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnEditQuiz->Enable( false );
	btnEditQuiz->SetMaxSize( wxSize( 60,-1 ) );
	
	wSizer2->Add( btnEditQuiz, 0, 0, 5 );
	
	btnRunQuiz = new wxButton( panelTopicChildQuiz, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnRunQuiz->Enable( false );
	btnRunQuiz->SetToolTip( wxT("Run Exercise") );
	
	wSizer2->Add( btnRunQuiz, 0, 0, 5 );
	
	
	bSizer10->Add( wSizer2, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	m_splitter2 = new wxSplitterWindow( panelTopicChildQuiz, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter2->Connect( wxEVT_IDLE, wxIdleEventHandler( pnlMain::m_splitter2OnIdle ), NULL, this );
	
	panelExercise = new wxPanel( m_splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );
	
	lstQuiz = new wxDataViewListCtrl( panelExercise, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	colQuizIndex = lstQuiz->AppendTextColumn( wxEmptyString );
	colQuizName = lstQuiz->AppendTextColumn( wxT("Name") );
	bSizer13->Add( lstQuiz, 1, wxEXPAND, 5 );
	
	
	panelExercise->SetSizer( bSizer13 );
	panelExercise->Layout();
	bSizer13->Fit( panelExercise );
	panelRun = new wxPanel( m_splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );
	
	lblExam = new wxStaticText( panelRun, wxID_ANY, wxT("Exercise Results"), wxDefaultPosition, wxDefaultSize, 0 );
	lblExam->Wrap( -1 );
	bSizer14->Add( lblExam, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxHORIZONTAL );
	
	btnViewQuizRun = new wxButton( panelRun, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnViewQuizRun->Enable( false );
	
	bSizer15->Add( btnViewQuizRun, 0, 0, 5 );
	
	btnDeleteQuizRun = new wxButton( panelRun, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnDeleteQuizRun->Enable( false );
	
	bSizer15->Add( btnDeleteQuizRun, 0, 0, 5 );
	
	
	bSizer14->Add( bSizer15, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer161;
	bSizer161 = new wxBoxSizer( wxVERTICAL );
	
	lstQuizRun = new wxDataViewListCtrl( panelRun, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	colQuizRunIndex = lstQuizRun->AppendTextColumn( wxEmptyString );
	colQuizRunDate = lstQuizRun->AppendTextColumn( wxT("Date Started") );
	colQuizRunComplete = lstQuizRun->AppendIconTextColumn( wxT("Complete") );
	colQuizRunName = lstQuizRun->AppendTextColumn( wxT("Name") );
	bSizer161->Add( lstQuizRun, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer14->Add( bSizer161, 1, wxEXPAND, 5 );
	
	
	panelRun->SetSizer( bSizer14 );
	panelRun->Layout();
	bSizer14->Fit( panelRun );
	m_splitter2->SplitHorizontally( panelExercise, panelRun, 0 );
	bSizer11->Add( m_splitter2, 1, wxEXPAND, 5 );
	
	
	bSizer10->Add( bSizer11, 1, wxEXPAND, 5 );
	
	
	panelTopicChildQuiz->SetSizer( bSizer10 );
	panelTopicChildQuiz->Layout();
	bSizer10->Fit( panelTopicChildQuiz );
	notebookChildren->AddPage( panelTopicChildQuiz, wxT("Exercises"), false );
	
	bSizer16->Add( notebookChildren, 1, wxEXPAND, 5 );
	
	
	panelTopicChildren->SetSizer( bSizer16 );
	panelTopicChildren->Layout();
	bSizer16->Fit( panelTopicChildren );
	splitterTopic->SplitVertically( panelTopics, panelTopicChildren, 255 );
	bSizer24->Add( splitterTopic, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer24 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( pnlMain::OnInitDialog ) );
	txtTitle->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( pnlMain::TitleOnText ), NULL, this );
	cboType->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( pnlMain::TypeOnCombobox ), NULL, this );
	btnApply->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::ApplyOnButtonClick ), NULL, this );
	btnApply->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::ApplyOnUpdateUI ), NULL, this );
	btnCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::CancelOnButtonClick ), NULL, this );
	btnCancel->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::CancelOnUpdateUI ), NULL, this );
	btnAddTopic->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::AddTopicOnButtonClick ), NULL, this );
	btnDeleteTopic->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::DeleteTopicOnButtonClick ), NULL, this );
	btnDeleteTopic->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::DeleteTopicOnUpdateUI ), NULL, this );
	btnEditTopic->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::EditTopicOnButtonClick ), NULL, this );
	btnEditTopic->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::EditTopicOnUpdateUI ), NULL, this );
	lstTopics->Connect( wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler( pnlMain::OnTopicItemActivated ), NULL, this );
	lstTopics->Connect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( pnlMain::OnTopicSelectionChanged ), NULL, this );
	btnAddNote->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::AddNoteOnButtonClick ), NULL, this );
	btnAddNote->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::AddNoteOnUpdateUI ), NULL, this );
	btnDeleteNote->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::DeleteNoteOnButtonClick ), NULL, this );
	btnDeleteNote->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::DeleteNoteOnUpdateUI ), NULL, this );
	btnEditNote->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::EditNoteOnButtonClick ), NULL, this );
	btnEditNote->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::EditNoteOnUpdateUI ), NULL, this );
	btnPlayAll->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::PlayAllOnButtonClick ), NULL, this );
	btnPlay->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::PlayOnButtonClick ), NULL, this );
	btnPlay->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::PlayOnUpdateUI ), NULL, this );
	btnStop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::StopOnButtonClick ), NULL, this );
	lstNotes->Connect( wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler( pnlMain::NotesOnItemActivated ), NULL, this );
	lstNotes->Connect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( pnlMain::NotesOnSelectionChanged ), NULL, this );
	btnAddQuiz->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::AddQuizOnButtonClick ), NULL, this );
	btnAddQuiz->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::AddQuizOnUpdateUI ), NULL, this );
	btnDeleteQuiz->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::DeleteQuizOnButtonClick ), NULL, this );
	btnDeleteQuiz->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::DeleteQuizOnUpdateUI ), NULL, this );
	btnEditQuiz->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::EditQuizOnButtonClick ), NULL, this );
	btnEditQuiz->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::EditQuizOnUpdateUI ), NULL, this );
	btnRunQuiz->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::RunQuizOnButtonClick ), NULL, this );
	btnRunQuiz->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::RunQuizOnUpdateUI ), NULL, this );
	lstQuiz->Connect( wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler( pnlMain::QuizOnItemActivated ), NULL, this );
	lstQuiz->Connect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( pnlMain::QuizOnSelectionChanged ), NULL, this );
	btnViewQuizRun->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::ViewQuizRunOnButtonClick ), NULL, this );
	btnViewQuizRun->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::ViewQuizRunOnUpdateUI ), NULL, this );
	btnDeleteQuizRun->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::DeleteQuizRunOnButtonClick ), NULL, this );
	btnDeleteQuizRun->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::DeleteQuizRunOnUpdateUI ), NULL, this );
	lstQuizRun->Connect( wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler( pnlMain::QuizRunOnItemActivated ), NULL, this );
	lstQuizRun->Connect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( pnlMain::QuizRunOnSelectionChanged ), NULL, this );
}

pnlMain::~pnlMain()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( pnlMain::OnInitDialog ) );
	txtTitle->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( pnlMain::TitleOnText ), NULL, this );
	cboType->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( pnlMain::TypeOnCombobox ), NULL, this );
	btnApply->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::ApplyOnButtonClick ), NULL, this );
	btnApply->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::ApplyOnUpdateUI ), NULL, this );
	btnCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::CancelOnButtonClick ), NULL, this );
	btnCancel->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::CancelOnUpdateUI ), NULL, this );
	btnAddTopic->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::AddTopicOnButtonClick ), NULL, this );
	btnDeleteTopic->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::DeleteTopicOnButtonClick ), NULL, this );
	btnDeleteTopic->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::DeleteTopicOnUpdateUI ), NULL, this );
	btnEditTopic->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::EditTopicOnButtonClick ), NULL, this );
	btnEditTopic->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::EditTopicOnUpdateUI ), NULL, this );
	lstTopics->Disconnect( wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler( pnlMain::OnTopicItemActivated ), NULL, this );
	lstTopics->Disconnect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( pnlMain::OnTopicSelectionChanged ), NULL, this );
	btnAddNote->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::AddNoteOnButtonClick ), NULL, this );
	btnAddNote->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::AddNoteOnUpdateUI ), NULL, this );
	btnDeleteNote->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::DeleteNoteOnButtonClick ), NULL, this );
	btnDeleteNote->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::DeleteNoteOnUpdateUI ), NULL, this );
	btnEditNote->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::EditNoteOnButtonClick ), NULL, this );
	btnEditNote->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::EditNoteOnUpdateUI ), NULL, this );
	btnPlayAll->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::PlayAllOnButtonClick ), NULL, this );
	btnPlay->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::PlayOnButtonClick ), NULL, this );
	btnPlay->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::PlayOnUpdateUI ), NULL, this );
	btnStop->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::StopOnButtonClick ), NULL, this );
	lstNotes->Disconnect( wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler( pnlMain::NotesOnItemActivated ), NULL, this );
	lstNotes->Disconnect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( pnlMain::NotesOnSelectionChanged ), NULL, this );
	btnAddQuiz->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::AddQuizOnButtonClick ), NULL, this );
	btnAddQuiz->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::AddQuizOnUpdateUI ), NULL, this );
	btnDeleteQuiz->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::DeleteQuizOnButtonClick ), NULL, this );
	btnDeleteQuiz->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::DeleteQuizOnUpdateUI ), NULL, this );
	btnEditQuiz->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::EditQuizOnButtonClick ), NULL, this );
	btnEditQuiz->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::EditQuizOnUpdateUI ), NULL, this );
	btnRunQuiz->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::RunQuizOnButtonClick ), NULL, this );
	btnRunQuiz->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::RunQuizOnUpdateUI ), NULL, this );
	lstQuiz->Disconnect( wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler( pnlMain::QuizOnItemActivated ), NULL, this );
	lstQuiz->Disconnect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( pnlMain::QuizOnSelectionChanged ), NULL, this );
	btnViewQuizRun->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::ViewQuizRunOnButtonClick ), NULL, this );
	btnViewQuizRun->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::ViewQuizRunOnUpdateUI ), NULL, this );
	btnDeleteQuizRun->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlMain::DeleteQuizRunOnButtonClick ), NULL, this );
	btnDeleteQuizRun->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlMain::DeleteQuizRunOnUpdateUI ), NULL, this );
	lstQuizRun->Disconnect( wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler( pnlMain::QuizRunOnItemActivated ), NULL, this );
	lstQuizRun->Disconnect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( pnlMain::QuizRunOnSelectionChanged ), NULL, this );
	
}
