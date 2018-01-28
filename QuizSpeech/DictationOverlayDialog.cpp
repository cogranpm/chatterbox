///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug  4 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "DictationOverlayDialog.h"

///////////////////////////////////////////////////////////////////////////

OverlayDialog::OverlayDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	btnStop = new wxButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnStop->SetDefault(); 
	btnStop->SetToolTip( wxT("Stop") );
	
	bSizer2->Add( btnStop, 0, 0, 5 );
	
	szAudioPlayer = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer2->Add( szAudioPlayer, 0, 0, 5 );
	
	
	bSizer1->Add( bSizer2, 0, wxALL, 5 );
	
	playbackGauge = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	playbackGauge->SetValue( 0 ); 
	bSizer1->Add( playbackGauge, 0, wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	lblHypothesis = new wxStaticText( this, wxID_ANY, wxT("Hypothesis"), wxDefaultPosition, wxDefaultSize, 0 );
	lblHypothesis->Wrap( -1 );
	bSizer4->Add( lblHypothesis, 0, wxLEFT|wxRIGHT|wxTOP, 5 );
	
	txtHypothesis = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_LEFT|wxTE_NO_VSCROLL|wxTE_READONLY );
	bSizer4->Add( txtHypothesis, 0, wxEXPAND, 5 );
	
	
	bSizer1->Add( bSizer4, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	lblSpeech = new wxStaticText( this, wxID_ANY, wxT("Speech"), wxDefaultPosition, wxDefaultSize, 0 );
	lblSpeech->Wrap( -1 );
	bSizer5->Add( lblSpeech, 0, wxLEFT|wxRIGHT|wxTOP, 5 );
	
	txtPhrase = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_LEFT|wxTE_MULTILINE|wxTE_READONLY );
	txtPhrase->SetValidator( wxTextValidator( wxFILTER_NONE, &recognizedText ) );
	
	bSizer5->Add( txtPhrase, 3, wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	
	bSizer1->Add( bSizer5, 2, wxEXPAND, 5 );
	
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();
	
	bSizer1->Add( m_sdbSizer1, 0, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( OverlayDialog::OnInitDialog ) );
	btnStop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OverlayDialog::StopOnButtonClick ), NULL, this );
	m_sdbSizer1Cancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OverlayDialog::OnCancelButtonClick ), NULL, this );
	m_sdbSizer1OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OverlayDialog::OnOKButtonClick ), NULL, this );
}

OverlayDialog::~OverlayDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( OverlayDialog::OnInitDialog ) );
	btnStop->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OverlayDialog::StopOnButtonClick ), NULL, this );
	m_sdbSizer1Cancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OverlayDialog::OnCancelButtonClick ), NULL, this );
	m_sdbSizer1OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( OverlayDialog::OnOKButtonClick ), NULL, this );
	
}
