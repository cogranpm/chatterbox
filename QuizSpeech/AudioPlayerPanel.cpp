///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug  4 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "AudioPlayerPanel.h"

///////////////////////////////////////////////////////////////////////////

pnlPlayer::pnlPlayer( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* szPanelPlayer;
	szPanelPlayer = new wxBoxSizer( wxHORIZONTAL );
	
	btnPlay = new wxButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnPlay->Enable( false );
	btnPlay->SetToolTip( wxT("Play") );
	
	szPanelPlayer->Add( btnPlay, 0, 0, 5 );
	
	m_gauge2 = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	m_gauge2->SetValue( 0 ); 
	szPanelPlayer->Add( m_gauge2, 0, wxLEFT|wxTOP, 5 );
	
	txtDuration = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	txtDuration->Wrap( -1 );
	szPanelPlayer->Add( txtDuration, 1, wxEXPAND|wxLEFT, 5 );
	
	
	this->SetSizer( szPanelPlayer );
	this->Layout();
	
	// Connect Events
	btnPlay->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlPlayer::PlayOnButtonClick ), NULL, this );
}

pnlPlayer::~pnlPlayer()
{
	// Disconnect Events
	btnPlay->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlPlayer::PlayOnButtonClick ), NULL, this );
	
}
