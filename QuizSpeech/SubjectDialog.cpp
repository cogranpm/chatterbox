///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 23 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "SubjectDialog.h"

///////////////////////////////////////////////////////////////////////////

SubjectDialog::SubjectDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxDialog( parent, id, title, pos, size, style, name )
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
	gbSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Title:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	gbSizer1->Add( m_staticText5, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALIGN_RIGHT|wxALL, 5 );
	
	m_txtTitle = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), 0 );
	#ifdef __WXGTK__
	if ( !m_txtTitle->HasFlag( wxTE_MULTILINE ) )
	{
	m_txtTitle->SetMaxLength( 60 );
	}
	#else
	m_txtTitle->SetMaxLength( 60 );
	#endif
	m_txtTitle->SetValidator( wxTextValidator( wxFILTER_NONE, &_title ) );
	
	gbSizer1->Add( m_txtTitle, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Comments:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	gbSizer1->Add( m_staticText2, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_RIGHT|wxALL, 5 );
	
	txtComments = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	txtComments->SetValidator( wxTextValidator( wxFILTER_NONE, &_comments ) );
	
	gbSizer1->Add( txtComments, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	
	gbSizer1->AddGrowableCol( 1 );
	gbSizer1->AddGrowableRow( 1 );
	
	bSizer1->Add( gbSizer1, 1, wxALL|wxEXPAND, 5 );
	
	btnStd = new wxStdDialogButtonSizer();
	btnStdOK = new wxButton( this, wxID_OK );
	btnStd->AddButton( btnStdOK );
	btnStdCancel = new wxButton( this, wxID_CANCEL );
	btnStd->AddButton( btnStdCancel );
	btnStd->Realize();
	
	bSizer1->Add( btnStd, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( SubjectDialog::OnClose ) );
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( SubjectDialog::OnInitDialog ) );
	btnStdOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SubjectDialog::OnOKButtonClick ), NULL, this );
}

SubjectDialog::~SubjectDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( SubjectDialog::OnClose ) );
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( SubjectDialog::OnInitDialog ) );
	btnStdOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SubjectDialog::OnOKButtonClick ), NULL, this );
	
}
