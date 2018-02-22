///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug  4 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "TopicDialog.h"

///////////////////////////////////////////////////////////////////////////

TopicDialog::TopicDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxDialog( parent, id, title, pos, size, style, name )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );
	
	m_infoCtrl1 = new wxInfoBar( this );
	m_infoCtrl1->SetShowHideEffects( wxSHOW_EFFECT_NONE, wxSHOW_EFFECT_NONE );
	m_infoCtrl1->SetEffectDuration( 500 );
	bSizer12->Add( m_infoCtrl1, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, wxT("Title"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_staticText6->Wrap( -1 );
	bSizer2->Add( m_staticText6, 0, wxALL, 5 );
	
	txtTitle = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !txtTitle->HasFlag( wxTE_MULTILINE ) )
	{
	txtTitle->SetMaxLength( 60 );
	}
	#else
	txtTitle->SetMaxLength( 60 );
	#endif
	txtTitle->SetMinSize( wxSize( 250,-1 ) );
	
	txtTitle->SetValidator( wxTextValidator( wxFILTER_NONE, &_title ) );
	
	bSizer2->Add( txtTitle, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer12->Add( bSizer2, 0, wxALL|wxEXPAND, 5 );
	
	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2OK = new wxButton( this, wxID_OK );
	m_sdbSizer2->AddButton( m_sdbSizer2OK );
	m_sdbSizer2Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer2->AddButton( m_sdbSizer2Cancel );
	m_sdbSizer2->Realize();
	
	bSizer12->Add( m_sdbSizer2, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	
	this->SetSizer( bSizer12 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_sdbSizer2Cancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TopicDialog::OnCancelButtonClick ), NULL, this );
	m_sdbSizer2OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TopicDialog::OnOKButtonClick ), NULL, this );
}

TopicDialog::~TopicDialog()
{
	// Disconnect Events
	m_sdbSizer2Cancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TopicDialog::OnCancelButtonClick ), NULL, this );
	m_sdbSizer2OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TopicDialog::OnOKButtonClick ), NULL, this );
	
}
