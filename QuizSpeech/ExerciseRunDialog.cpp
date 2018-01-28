///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 28 2017)
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
	szQuestion = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* szButtons;
	szButtons = new wxBoxSizer( wxHORIZONTAL );
	
	btnRecord = new wxButton( pnlQuestion, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	szButtons->Add( btnRecord, 0, 0, 5 );
	
	btnSkip = new wxButton( pnlQuestion, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnSkip->SetToolTip( wxT("Skip") );
	
	szButtons->Add( btnSkip, 0, 0, 5 );
	
	wxString rdoEvaluationChoices[] = { wxT("Correct"), wxT("Incorrect") };
	int rdoEvaluationNChoices = sizeof( rdoEvaluationChoices ) / sizeof( wxString );
	rdoEvaluation = new wxRadioBox( pnlQuestion, wxID_ANY, wxT("Evaluate"), wxDefaultPosition, wxDefaultSize, rdoEvaluationNChoices, rdoEvaluationChoices, 1, wxRA_SPECIFY_COLS );
	rdoEvaluation->SetSelection( 0 );
	rdoEvaluation->Enable( false );
	
	szButtons->Add( rdoEvaluation, 0, wxALL, 5 );
	
	btnNext = new wxButton( pnlQuestion, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnNext->Enable( false );
	
	szButtons->Add( btnNext, 0, 0, 5 );
	
	
	szQuestion->Add( szButtons, 0, wxEXPAND, 5 );
	
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer1->AddGrowableCol( 0 );
	fgSizer1->AddGrowableCol( 1 );
	fgSizer1->AddGrowableRow( 1 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	lblQuestion = new wxStaticText( pnlQuestion, wxID_ANY, wxT("Question"), wxDefaultPosition, wxDefaultSize, 0 );
	lblQuestion->Wrap( -1 );
	bSizer13->Add( lblQuestion, 0, wxALL, 5 );
	
	szAudioPlayer = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer13->Add( szAudioPlayer, 0, wxEXPAND, 5 );
	
	szPlayer = new wxGridSizer( 1, 0, 0, 0 );
	
	szWrap = new wxWrapSizer( wxHORIZONTAL );
	
	
	szPlayer->Add( szWrap, 1, wxEXPAND, 5 );
	
	
	bSizer13->Add( szPlayer, 0, 0, 5 );
	
	
	fgSizer1->Add( bSizer13, 0, wxEXPAND, 5 );
	
	lblAnswer = new wxStaticText( pnlQuestion, wxID_ANY, wxT("Answer"), wxDefaultPosition, wxDefaultSize, 0 );
	lblAnswer->Wrap( -1 );
	fgSizer1->Add( lblAnswer, 0, wxALL, 5 );
	
	txtQuestion = new wxTextCtrl( pnlQuestion, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	txtQuestion->Enable( false );
	
	fgSizer1->Add( txtQuestion, 1, wxALL|wxEXPAND, 5 );
	
	txtAnswer = new wxTextCtrl( pnlQuestion, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	txtAnswer->Enable( false );
	
	fgSizer1->Add( txtAnswer, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer10->Add( fgSizer1, 1, wxEXPAND, 5 );
	
	
	szQuestion->Add( bSizer10, 1, wxEXPAND, 5 );
	
	wxBoxSizer* szStatus;
	szStatus = new wxBoxSizer( wxVERTICAL );
	
	lblStatus = new wxStaticText( pnlQuestion, wxID_ANY, wxT("Question x of x"), wxDefaultPosition, wxDefaultSize, 0 );
	lblStatus->Wrap( -1 );
	szStatus->Add( lblStatus, 0, wxALL, 5 );
	
	
	szQuestion->Add( szStatus, 1, wxEXPAND, 5 );
	
	
	pnlQuestion->SetSizer( szQuestion );
	pnlQuestion->Layout();
	szQuestion->Fit( pnlQuestion );
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
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( ExerciseRunDialog::OnInitDialog ) );
	btnRecord->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExerciseRunDialog::RecordOnButtonClick ), NULL, this );
	btnSkip->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExerciseRunDialog::SkipOnButtonClick ), NULL, this );
	rdoEvaluation->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( ExerciseRunDialog::EvaluationOnRadioBox ), NULL, this );
	btnNext->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExerciseRunDialog::NextOnButtonClick ), NULL, this );
	btnClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExerciseRunDialog::CloseOnButtonClick ), NULL, this );
}

ExerciseRunDialog::~ExerciseRunDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( ExerciseRunDialog::OnInitDialog ) );
	btnRecord->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExerciseRunDialog::RecordOnButtonClick ), NULL, this );
	btnSkip->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExerciseRunDialog::SkipOnButtonClick ), NULL, this );
	rdoEvaluation->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( ExerciseRunDialog::EvaluationOnRadioBox ), NULL, this );
	btnNext->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExerciseRunDialog::NextOnButtonClick ), NULL, this );
	btnClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ExerciseRunDialog::CloseOnButtonClick ), NULL, this );
	
}
