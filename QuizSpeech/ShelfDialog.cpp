///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 23 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ShelfDialog.h"

///////////////////////////////////////////////////////////////////////////

ShelfDialog::ShelfDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxDialog( parent, id, title, pos, size, style, name )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_infoCtrl = new wxInfoBar( this );
	m_infoCtrl->SetShowHideEffects( wxSHOW_EFFECT_NONE, wxSHOW_EFFECT_NONE );
	m_infoCtrl->SetEffectDuration( 500 );
	bSizer1->Add( m_infoCtrl, 0, wxALL|wxEXPAND, 5 );
	
	wxGridBagSizer* gbSizer1;
	gbSizer1 = new wxGridBagSizer( 0, 0 );
	gbSizer1->SetFlexibleDirection( wxHORIZONTAL );
	gbSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );
	
	wxStaticText* m_lblName;
	m_lblName = new wxStaticText( this, wxID_ANY, wxT("Title:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblName->Wrap( -1 );
	gbSizer1->Add( m_lblName, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALIGN_RIGHT|wxALL, 5 );
	
	m_txtName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 320,-1 ), 0 );
	#ifdef __WXGTK__
	if ( !m_txtName->HasFlag( wxTE_MULTILINE ) )
	{
	m_txtName->SetMaxLength( 60 );
	}
	#else
	m_txtName->SetMaxLength( 60 );
	#endif
	m_txtName->SetValidator( wxTextValidator( wxFILTER_NONE, &_title ) );
	
	gbSizer1->Add( m_txtName, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Comments:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	gbSizer1->Add( m_staticText2, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_RIGHT|wxALL, 5 );
	
	txtComments = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	txtComments->SetValidator( wxTextValidator( wxFILTER_NONE, &_comments ) );
	
	gbSizer1->Add( txtComments, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	
	gbSizer1->AddGrowableCol( 1 );
	gbSizer1->AddGrowableRow( 1 );
	
	bSizer1->Add( gbSizer1, 1, wxALL|wxEXPAND, 5 );
	
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();
	
	bSizer1->Add( m_sdbSizer1, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( ShelfDialog::OnClose ) );
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( ShelfDialog::OnInitDialog ) );
	m_sdbSizer1OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ShelfDialog::OnOKButtonClick ), NULL, this );
}

ShelfDialog::~ShelfDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( ShelfDialog::OnClose ) );
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( ShelfDialog::OnInitDialog ) );
	m_sdbSizer1OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ShelfDialog::OnOKButtonClick ), NULL, this );
	
}
