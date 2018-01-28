///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 24 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "SubjectDialog.h"

///////////////////////////////////////////////////////////////////////////

SubjectDialog::SubjectDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_infoCtrl = new wxInfoBar( this );
	m_infoCtrl->SetShowHideEffects( wxSHOW_EFFECT_NONE, wxSHOW_EFFECT_NONE );
	m_infoCtrl->SetEffectDuration( 500 );
	bSizer1->Add( m_infoCtrl, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Title"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer2->Add( m_staticText5, 0, wxALL, 5 );
	
	m_txtTitle = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !m_txtTitle->HasFlag( wxTE_MULTILINE ) )
	{
	m_txtTitle->SetMaxLength( 60 );
	}
	#else
	m_txtTitle->SetMaxLength( 60 );
	#endif
	m_txtTitle->SetValidator( wxTextValidator( wxFILTER_NONE, &_title ) );
	
	bSizer2->Add( m_txtTitle, 1, wxALL, 5 );
	
	
	bSizer1->Add( bSizer2, 0, wxALL|wxEXPAND, 5 );
	
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
