///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version May 29 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ExercisePanel.h"

///////////////////////////////////////////////////////////////////////////

ExercisePanel::ExercisePanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* sizerExerciseTitle;
	sizerExerciseTitle = new wxBoxSizer( wxVERTICAL );
	
	lblExercise = new wxStaticText( this, wxID_ANY, wxT("Exercise"), wxDefaultPosition, wxDefaultSize, 0 );
	lblExercise->Wrap( -1 );
	sizerExerciseTitle->Add( lblExercise, 0, wxALL, 5 );
	
	quizMessage = new wxInfoBar( this );
	quizMessage->SetShowHideEffects( wxSHOW_EFFECT_NONE, wxSHOW_EFFECT_NONE );
	quizMessage->SetEffectDuration( 500 );
	sizerExerciseTitle->Add( quizMessage, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer2->Add( sizerExerciseTitle, 0, wxEXPAND, 5 );
	
	wxGridBagSizer* gbSizer1;
	gbSizer1 = new wxGridBagSizer( 0, 0 );
	gbSizer1->SetFlexibleDirection( wxHORIZONTAL );
	gbSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_NONE );
	
	lblName = new wxStaticText( this, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	lblName->Wrap( -1 );
	gbSizer1->Add( lblName, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	txtName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !txtName->HasFlag( wxTE_MULTILINE ) )
	{
	txtName->SetMaxLength( 60 );
	}
	#else
	txtName->SetMaxLength( 60 );
	#endif
	txtName->SetValidator( wxTextValidator( wxFILTER_NONE, &dataName ) );
	
	gbSizer1->Add( txtName, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	
	gbSizer1->Add( 0, 0, wxGBPosition( 0, 2 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );
	
	lblTopic = new wxStaticText( this, wxID_ANY, wxT("Topic"), wxDefaultPosition, wxDefaultSize, 0 );
	lblTopic->Wrap( -1 );
	gbSizer1->Add( lblTopic, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	cboTopics = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY|wxCB_SORT ); 
	gbSizer1->Add( cboTopics, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	
	gbSizer1->Add( 0, 0, wxGBPosition( 1, 2 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );
	
	
	gbSizer1->AddGrowableCol( 1 );
	gbSizer1->AddGrowableCol( 2 );
	gbSizer1->AddGrowableRow( 0 );
	gbSizer1->AddGrowableRow( 1 );
	
	bSizer2->Add( gbSizer1, 0, wxEXPAND, 5 );
	
	wxBoxSizer* sizerQuestions;
	sizerQuestions = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	lblQuestions = new wxStaticText( this, wxID_ANY, wxT("Questions"), wxDefaultPosition, wxDefaultSize, 0 );
	lblQuestions->Wrap( -1 );
	bSizer6->Add( lblQuestions, 0, wxALL, 5 );
	
	
	sizerQuestions->Add( bSizer6, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxVERTICAL );
	
	m_splitter1 = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter1->Connect( wxEVT_IDLE, wxIdleEventHandler( ExercisePanel::m_splitter1OnIdle ), NULL, this );
	
	pnlGrid = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* sizerGrid;
	sizerGrid = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* sizerQuestionButtons;
	sizerQuestionButtons = new wxBoxSizer( wxHORIZONTAL );
	
	btnAddQuestion = new wxButton( pnlGrid, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnAddQuestion->SetToolTip( wxT("Add Question") );
	
	sizerQuestionButtons->Add( btnAddQuestion, 0, 0, 5 );
	
	btnDeleteQuestion = new wxButton( pnlGrid, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	sizerQuestionButtons->Add( btnDeleteQuestion, 0, 0, 5 );
	
	
	sizerGrid->Add( sizerQuestionButtons, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	lstQuestions = new wxDataViewListCtrl( pnlGrid, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	colIndex = lstQuestions->AppendTextColumn( wxT("Index") );
	colQuestion = lstQuestions->AppendTextColumn( wxT("Question") );
	colAnswer = lstQuestions->AppendTextColumn( wxT("Answer") );
	bSizer7->Add( lstQuestions, 1, wxALL|wxEXPAND, 5 );
	
	
	sizerGrid->Add( bSizer7, 2, wxEXPAND, 5 );
	
	
	pnlGrid->SetSizer( sizerGrid );
	pnlGrid->Layout();
	sizerGrid->Fit( pnlGrid );
	pnlEdit = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	sizerEdit = new wxBoxSizer( wxVERTICAL );
	
	sizerQuestionHeader = new wxBoxSizer( wxHORIZONTAL );
	
	lblQuestion = new wxStaticText( pnlEdit, wxID_ANY, wxT("Question"), wxDefaultPosition, wxDefaultSize, 0 );
	lblQuestion->Wrap( -1 );
	sizerQuestionHeader->Add( lblQuestion, 0, wxALL, 5 );
	
	btnRecordQuestion = new wxButton( pnlEdit, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnRecordQuestion->SetToolTip( wxT("Record Question") );
	
	sizerQuestionHeader->Add( btnRecordQuestion, 0, 0, 5 );
	
	btnClearQuestion = new wxButton( pnlEdit, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnClearQuestion->SetToolTip( wxT("Clear Question") );
	
	sizerQuestionHeader->Add( btnClearQuestion, 0, 0, 5 );
	
	pnlQuestionAudioPlayer = new wxPanel( pnlEdit, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	szQuestionAudioPlayer = new wxBoxSizer( wxHORIZONTAL );
	
	
	pnlQuestionAudioPlayer->SetSizer( szQuestionAudioPlayer );
	pnlQuestionAudioPlayer->Layout();
	szQuestionAudioPlayer->Fit( pnlQuestionAudioPlayer );
	sizerQuestionHeader->Add( pnlQuestionAudioPlayer, 0, 0, 5 );
	
	
	sizerEdit->Add( sizerQuestionHeader, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	questionMessage = new wxInfoBar( pnlEdit );
	questionMessage->SetShowHideEffects( wxSHOW_EFFECT_NONE, wxSHOW_EFFECT_NONE );
	questionMessage->SetEffectDuration( 500 );
	bSizer10->Add( questionMessage, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	questionText = new wxTextCtrl( pnlEdit, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	bSizer11->Add( questionText, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer10->Add( bSizer11, 1, wxEXPAND, 5 );
	
	
	sizerEdit->Add( bSizer10, 1, wxEXPAND, 5 );
	
	sizerAnswerHeader = new wxBoxSizer( wxHORIZONTAL );
	
	lblAnswer = new wxStaticText( pnlEdit, wxID_ANY, wxT("Answer"), wxDefaultPosition, wxDefaultSize, 0 );
	lblAnswer->Wrap( -1 );
	sizerAnswerHeader->Add( lblAnswer, 0, wxALL, 5 );
	
	btnRecordAnswer = new wxButton( pnlEdit, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnRecordAnswer->SetToolTip( wxT("Record Answer") );
	
	sizerAnswerHeader->Add( btnRecordAnswer, 0, 0, 5 );
	
	btnClearAnswer = new wxButton( pnlEdit, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnClearAnswer->SetToolTip( wxT("Clear Answer") );
	
	sizerAnswerHeader->Add( btnClearAnswer, 0, 0, 5 );
	
	pnlAnswerAudioPlayer = new wxPanel( pnlEdit, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	szAnswerAudioPlayer = new wxBoxSizer( wxHORIZONTAL );
	
	
	pnlAnswerAudioPlayer->SetSizer( szAnswerAudioPlayer );
	pnlAnswerAudioPlayer->Layout();
	szAnswerAudioPlayer->Fit( pnlAnswerAudioPlayer );
	sizerAnswerHeader->Add( pnlAnswerAudioPlayer, 1, 0, 5 );
	
	
	sizerEdit->Add( sizerAnswerHeader, 0, wxEXPAND, 5 );
	
	wxBoxSizer* sizerAnswerbody;
	sizerAnswerbody = new wxBoxSizer( wxVERTICAL );
	
	answerMessage = new wxInfoBar( pnlEdit );
	answerMessage->SetShowHideEffects( wxSHOW_EFFECT_NONE, wxSHOW_EFFECT_NONE );
	answerMessage->SetEffectDuration( 500 );
	sizerAnswerbody->Add( answerMessage, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );
	
	answerText = new wxTextCtrl( pnlEdit, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	bSizer15->Add( answerText, 1, wxALL|wxEXPAND, 5 );
	
	
	sizerAnswerbody->Add( bSizer15, 1, wxEXPAND, 5 );
	
	
	sizerEdit->Add( sizerAnswerbody, 1, wxEXPAND, 5 );
	
	
	pnlEdit->SetSizer( sizerEdit );
	pnlEdit->Layout();
	sizerEdit->Fit( pnlEdit );
	m_splitter1->SplitVertically( pnlGrid, pnlEdit, 350 );
	bSizer20->Add( m_splitter1, 1, wxEXPAND, 5 );
	
	
	sizerQuestions->Add( bSizer20, 1, wxEXPAND, 5 );
	
	
	bSizer2->Add( sizerQuestions, 1, wxEXPAND, 5 );
	
	
	bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );
	
	wxBoxSizer* sizerApply;
	sizerApply = new wxBoxSizer( wxHORIZONTAL );
	
	
	sizerApply->Add( 0, 0, 1, wxEXPAND, 5 );
	
	btnCancel = new wxButton( this, wxID_ANY, wxT("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	btnCancel->Enable( false );
	
	sizerApply->Add( btnCancel, 0, wxALL, 5 );
	
	btnApply = new wxButton( this, wxID_ANY, wxT("&Apply"), wxDefaultPosition, wxDefaultSize, 0 );
	btnApply->SetDefault(); 
	btnApply->Enable( false );
	
	sizerApply->Add( btnApply, 0, wxALL, 5 );
	
	
	bSizer1->Add( sizerApply, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( ExercisePanel::ExercisePanelOnInitDialog ) );
	txtName->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( ExercisePanel::NameOnKillFocus ), NULL, this );
	txtName->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( ExercisePanel::NameOnSetFocus ), NULL, this );
	txtName->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ExercisePanel::NameOnText ), NULL, this );
	cboTopics->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( ExercisePanel::TopicsOnCombobox ), NULL, this );
	btnAddQuestion->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExercisePanel::AddQuestionOnButtonClick ), NULL, this );
	btnDeleteQuestion->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExercisePanel::DeleteQuestionOnButtonClick ), NULL, this );
	btnDeleteQuestion->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( ExercisePanel::DeleteQuestionOnUpdateUI ), NULL, this );
	lstQuestions->Connect( wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler( ExercisePanel::QuestionsItemActivated ), NULL, this );
	lstQuestions->Connect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( ExercisePanel::QuestionsSelectionChanged ), NULL, this );
	btnRecordQuestion->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExercisePanel::RecordQuestionOnButtonClick ), NULL, this );
	btnClearQuestion->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExercisePanel::ClearQuestionOnButtonClick ), NULL, this );
	questionText->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ExercisePanel::QuestionOnText ), NULL, this );
	btnRecordAnswer->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExercisePanel::RecordAnswerOnButtonClick ), NULL, this );
	btnClearAnswer->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExercisePanel::ClearAnswerOnButtonClick ), NULL, this );
	answerText->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ExercisePanel::AnswerOnText ), NULL, this );
	btnCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExercisePanel::CancelOnButtonClick ), NULL, this );
	btnCancel->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( ExercisePanel::CancelOnUpdateUI ), NULL, this );
	btnApply->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExercisePanel::ApplyOnButtonClick ), NULL, this );
	btnApply->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( ExercisePanel::ApplyOnUpdateUI ), NULL, this );
}

ExercisePanel::~ExercisePanel()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( ExercisePanel::ExercisePanelOnInitDialog ) );
	txtName->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( ExercisePanel::NameOnKillFocus ), NULL, this );
	txtName->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( ExercisePanel::NameOnSetFocus ), NULL, this );
	txtName->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ExercisePanel::NameOnText ), NULL, this );
	cboTopics->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( ExercisePanel::TopicsOnCombobox ), NULL, this );
	btnAddQuestion->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExercisePanel::AddQuestionOnButtonClick ), NULL, this );
	btnDeleteQuestion->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExercisePanel::DeleteQuestionOnButtonClick ), NULL, this );
	btnDeleteQuestion->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( ExercisePanel::DeleteQuestionOnUpdateUI ), NULL, this );
	lstQuestions->Disconnect( wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler( ExercisePanel::QuestionsItemActivated ), NULL, this );
	lstQuestions->Disconnect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( ExercisePanel::QuestionsSelectionChanged ), NULL, this );
	btnRecordQuestion->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExercisePanel::RecordQuestionOnButtonClick ), NULL, this );
	btnClearQuestion->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExercisePanel::ClearQuestionOnButtonClick ), NULL, this );
	questionText->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ExercisePanel::QuestionOnText ), NULL, this );
	btnRecordAnswer->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExercisePanel::RecordAnswerOnButtonClick ), NULL, this );
	btnClearAnswer->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExercisePanel::ClearAnswerOnButtonClick ), NULL, this );
	answerText->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ExercisePanel::AnswerOnText ), NULL, this );
	btnCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExercisePanel::CancelOnButtonClick ), NULL, this );
	btnCancel->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( ExercisePanel::CancelOnUpdateUI ), NULL, this );
	btnApply->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExercisePanel::ApplyOnButtonClick ), NULL, this );
	btnApply->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( ExercisePanel::ApplyOnUpdateUI ), NULL, this );
	
}
