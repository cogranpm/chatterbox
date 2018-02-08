///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 24 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ExerciseRunDialog.h"

///////////////////////////////////////////////////////////////////////////

ExerciseRunDialog::ExerciseRunDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	dialogSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* sizerTop;
	sizerTop = new wxBoxSizer( wxHORIZONTAL );
	
	lblQuizName = new wxStaticText( this, wxID_ANY, wxT("Running Quiz ..."), wxDefaultPosition, wxDefaultSize, 0 );
	lblQuizName->Wrap( -1 );
	sizerTop->Add( lblQuizName, 0, wxALL, 5 );
	
	
	dialogSizer->Add( sizerTop, 0, wxEXPAND, 5 );
	
	wxBoxSizer* sizerMiddle;
	sizerMiddle = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	listSplitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	listSplitter->Connect( wxEVT_IDLE, wxIdleEventHandler( ExerciseRunDialog::listSplitterOnIdle ), NULL, this );
	
	pnlQuestion = new wxPanel( listSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	szInput = new wxBoxSizer( wxVERTICAL );
	
	mainDisplayBook = new wxSimplebook( pnlQuestion, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	pnlEntries = new wxPanel( mainDisplayBook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	szEntries = new wxBoxSizer( wxVERTICAL );
	
	szQuestion = new wxBoxSizer( wxVERTICAL );
	
	szQuestionTool = new wxBoxSizer( wxHORIZONTAL );
	
	lblQuestion = new wxStaticText( pnlEntries, wxID_ANY, wxT("Question"), wxDefaultPosition, wxDefaultSize, 0 );
	lblQuestion->Wrap( -1 );
	szQuestionTool->Add( lblQuestion, 0, wxALIGN_BOTTOM|wxALL, 5 );
	
	btnAudioPlay = new wxButton( pnlEntries, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	szQuestionTool->Add( btnAudioPlay, 0, wxALIGN_CENTER, 5 );
	
	btnSkip = new wxButton( pnlEntries, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnSkip->SetToolTip( wxT("Skip") );
	
	szQuestionTool->Add( btnSkip, 0, wxALIGN_CENTER, 5 );
	
	
	szQuestion->Add( szQuestionTool, 0, wxEXPAND, 5 );
	
	txtQuestion = new wxTextCtrl( pnlEntries, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	txtQuestion->Enable( false );
	txtQuestion->Hide();
	
	szQuestion->Add( txtQuestion, 1, wxALL|wxEXPAND, 5 );
	
	szPlayer = new wxBoxSizer( wxHORIZONTAL );
	
	
	szQuestion->Add( szPlayer, 1, wxEXPAND, 5 );
	
	
	szEntries->Add( szQuestion, 1, wxEXPAND, 5 );
	
	szAnswer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* szAnswerTool;
	szAnswerTool = new wxBoxSizer( wxHORIZONTAL );
	
	lblAnswer = new wxStaticText( pnlEntries, wxID_ANY, wxT("Answer"), wxDefaultPosition, wxDefaultSize, 0 );
	lblAnswer->Wrap( -1 );
	szAnswerTool->Add( lblAnswer, 0, wxALIGN_BOTTOM|wxALL, 5 );
	
	btnRecord = new wxButton( pnlEntries, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	szAnswerTool->Add( btnRecord, 0, wxALIGN_CENTER, 5 );
	
	btnPlayAnswer = new wxButton( pnlEntries, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnPlayAnswer->Enable( false );
	btnPlayAnswer->SetToolTip( wxT("Play Answer") );
	
	szAnswerTool->Add( btnPlayAnswer, 0, wxALIGN_CENTER, 5 );
	
	
	szAnswer->Add( szAnswerTool, 0, wxEXPAND, 5 );
	
	txtAnswer = new wxTextCtrl( pnlEntries, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	txtAnswer->Enable( false );
	txtAnswer->Hide();
	
	szAnswer->Add( txtAnswer, 1, wxALL|wxEXPAND, 5 );
	
	
	szEntries->Add( szAnswer, 0, wxALL|wxEXPAND, 5 );
	
	szEvaluate = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* szEvaluateTool;
	szEvaluateTool = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText6 = new wxStaticText( pnlEntries, wxID_ANY, wxT("Evaluate"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	szEvaluateTool->Add( m_staticText6, 0, wxALIGN_CENTER|wxALL, 5 );
	
	btnPlayCorrectAnswer = new wxButton( pnlEntries, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnPlayCorrectAnswer->Enable( false );
	btnPlayCorrectAnswer->SetToolTip( wxT("Play Correct Answer") );
	
	szEvaluateTool->Add( btnPlayCorrectAnswer, 0, wxALIGN_CENTER, 5 );
	
	wxString rdoEvaluationChoices[] = { wxT("Correct"), wxT("Incorrect") };
	int rdoEvaluationNChoices = sizeof( rdoEvaluationChoices ) / sizeof( wxString );
	rdoEvaluation = new wxRadioBox( pnlEntries, wxID_ANY, wxT("Evaluate"), wxDefaultPosition, wxDefaultSize, rdoEvaluationNChoices, rdoEvaluationChoices, 1, wxRA_SPECIFY_COLS );
	rdoEvaluation->SetSelection( 0 );
	rdoEvaluation->Enable( false );
	
	szEvaluateTool->Add( rdoEvaluation, 0, wxALIGN_CENTER|wxALL, 5 );
	
	btnNext = new wxButton( pnlEntries, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnNext->Enable( false );
	
	szEvaluateTool->Add( btnNext, 0, wxALIGN_CENTER, 5 );
	
	
	szEvaluate->Add( szEvaluateTool, 0, wxEXPAND, 5 );
	
	txtCorrectAnswer = new wxTextCtrl( pnlEntries, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	txtCorrectAnswer->Enable( false );
	txtCorrectAnswer->Hide();
	
	szEvaluate->Add( txtCorrectAnswer, 1, wxALL|wxEXPAND, 5 );
	
	
	szEntries->Add( szEvaluate, 0, wxALL|wxEXPAND, 5 );
	
	
	pnlEntries->SetSizer( szEntries );
	pnlEntries->Layout();
	szEntries->Fit( pnlEntries );
	mainDisplayBook->AddPage( pnlEntries, wxT("a page"), false );
	pnlComplete = new wxPanel( mainDisplayBook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	szComplete = new wxBoxSizer( wxVERTICAL );
	
	lblFinished = new wxStaticText( pnlComplete, wxID_ANY, wxT("Finished"), wxDefaultPosition, wxDefaultSize, 0 );
	lblFinished->Wrap( -1 );
	szComplete->Add( lblFinished, 0, wxALL|wxEXPAND, 5 );
	
	lblScore = new wxStaticText( pnlComplete, wxID_ANY, wxT("score"), wxDefaultPosition, wxDefaultSize, 0 );
	lblScore->Wrap( -1 );
	szComplete->Add( lblScore, 0, wxALL|wxEXPAND, 5 );
	
	
	pnlComplete->SetSizer( szComplete );
	pnlComplete->Layout();
	szComplete->Fit( pnlComplete );
	mainDisplayBook->AddPage( pnlComplete, wxT("a page"), false );
	
	szInput->Add( mainDisplayBook, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* szStatus;
	szStatus = new wxBoxSizer( wxVERTICAL );
	
	lblStatus = new wxStaticText( pnlQuestion, wxID_ANY, wxT("Question x of x"), wxDefaultPosition, wxDefaultSize, 0 );
	lblStatus->Wrap( -1 );
	szStatus->Add( lblStatus, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	
	szInput->Add( szStatus, 1, wxEXPAND, 5 );
	
	
	pnlQuestion->SetSizer( szInput );
	pnlQuestion->Layout();
	szInput->Fit( pnlQuestion );
	pnlList = new wxPanel( listSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText2 = new wxStaticText( pnlList, wxID_ANY, wxT("Questions"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer7->Add( m_staticText2, 0, wxALL, 5 );
	
	
	bSizer5->Add( bSizer7, 0, wxEXPAND, 5 );
	
	lstQuestions = new wxDataViewListCtrl( pnlList, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	colIndex = lstQuestions->AppendTextColumn( wxT("Index") );
	colQuestion = lstQuestions->AppendTextColumn( wxT("Question") );
	colAnswered = lstQuestions->AppendIconTextColumn( wxT("Answered") );
	colResult = lstQuestions->AppendIconTextColumn( wxT("Result") );
	bSizer5->Add( lstQuestions, 1, wxALL|wxEXPAND, 5 );
	
	
	pnlList->SetSizer( bSizer5 );
	pnlList->Layout();
	bSizer5->Fit( pnlList );
	listSplitter->SplitVertically( pnlQuestion, pnlList, 547 );
	bSizer12->Add( listSplitter, 1, wxEXPAND, 5 );
	
	
	sizerMiddle->Add( bSizer12, 1, wxEXPAND, 5 );
	
	
	dialogSizer->Add( sizerMiddle, 1, wxEXPAND, 5 );
	
	wxBoxSizer* sizerBottom;
	sizerBottom = new wxBoxSizer( wxHORIZONTAL );
	
	
	sizerBottom->Add( 0, 0, 1, wxEXPAND, 5 );
	
	btnClose = new wxButton( this, wxID_ANY, wxT("&Close"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerBottom->Add( btnClose, 0, wxALL, 5 );
	
	
	dialogSizer->Add( sizerBottom, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( dialogSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( ExerciseRunDialog::OnInitDialog ) );
	btnAudioPlay->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExerciseRunDialog::AudioPlayOnButtonClick ), NULL, this );
	btnSkip->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExerciseRunDialog::SkipOnButtonClick ), NULL, this );
	btnRecord->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExerciseRunDialog::RecordOnButtonClick ), NULL, this );
	btnPlayAnswer->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExerciseRunDialog::PlayAnswerOnButtonClick ), NULL, this );
	btnPlayCorrectAnswer->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExerciseRunDialog::PlayCorrectAnswerOnButtonClick ), NULL, this );
	rdoEvaluation->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( ExerciseRunDialog::EvaluationOnRadioBox ), NULL, this );
	btnNext->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExerciseRunDialog::NextOnButtonClick ), NULL, this );
	lstQuestions->Connect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( ExerciseRunDialog::QuestionsSelectionChanged ), NULL, this );
	btnClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExerciseRunDialog::CloseOnButtonClick ), NULL, this );
}

ExerciseRunDialog::~ExerciseRunDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( ExerciseRunDialog::OnInitDialog ) );
	btnAudioPlay->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExerciseRunDialog::AudioPlayOnButtonClick ), NULL, this );
	btnSkip->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExerciseRunDialog::SkipOnButtonClick ), NULL, this );
	btnRecord->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExerciseRunDialog::RecordOnButtonClick ), NULL, this );
	btnPlayAnswer->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExerciseRunDialog::PlayAnswerOnButtonClick ), NULL, this );
	btnPlayCorrectAnswer->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExerciseRunDialog::PlayCorrectAnswerOnButtonClick ), NULL, this );
	rdoEvaluation->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( ExerciseRunDialog::EvaluationOnRadioBox ), NULL, this );
	btnNext->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExerciseRunDialog::NextOnButtonClick ), NULL, this );
	lstQuestions->Disconnect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( ExerciseRunDialog::QuestionsSelectionChanged ), NULL, this );
	btnClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExerciseRunDialog::CloseOnButtonClick ), NULL, this );
	
}
