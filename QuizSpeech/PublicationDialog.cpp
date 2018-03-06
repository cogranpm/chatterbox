///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 23 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "PublicationDialog.h"

///////////////////////////////////////////////////////////////////////////

PublicationDialog::PublicationDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxDialog( parent, id, title, pos, size, style, name )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxVERTICAL );
	
	infoCtrl = new wxInfoBar( this );
	infoCtrl->SetShowHideEffects( wxSHOW_EFFECT_NONE, wxSHOW_EFFECT_NONE );
	infoCtrl->SetEffectDuration( 500 );
	bSizer24->Add( infoCtrl, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	lblTitle = new wxStaticText( this, wxID_ANY, wxT("Title"), wxDefaultPosition, wxDefaultSize, 0 );
	lblTitle->Wrap( -1 );
	bSizer2->Add( lblTitle, 0, wxALL, 5 );
	
	txtTitle = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), 0 );
	txtTitle->SetValidator( wxTextValidator( wxFILTER_NONE, &_title ) );
	
	bSizer2->Add( txtTitle, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer24->Add( bSizer2, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	lblType = new wxStaticText( this, wxID_ANY, wxT("Type"), wxDefaultPosition, wxDefaultSize, 0 );
	lblType->Wrap( -1 );
	bSizer3->Add( lblType, 0, wxALL, 5 );
	
	m_cboTypes = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), 0, NULL, wxCB_READONLY|wxCB_SORT );
	m_cboTypes->Append( wxT("Audio Visual") );
	m_cboTypes->Append( wxT("Book") );
	m_cboTypes->Append( wxT("Lecture") );
	m_cboTypes->Append( wxT("Link") );
	m_cboTypes->Append( wxT("List") );
	m_cboTypes->Append( wxT("Notebook") );
	m_cboTypes->SetSelection( 0 );
	bSizer3->Add( m_cboTypes, 0, wxALL, 5 );
	
	
	bSizer24->Add( bSizer3, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Comments"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer4->Add( m_staticText3, 0, wxALL, 5 );
	
	txtComments = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	txtComments->SetValidator( wxTextValidator( wxFILTER_NONE, &_comments ) );
	
	bSizer4->Add( txtComments, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer24->Add( bSizer4, 1, wxEXPAND, 5 );
	
	btnStd = new wxStdDialogButtonSizer();
	btnStdOK = new wxButton( this, wxID_OK );
	btnStd->AddButton( btnStdOK );
	btnStdCancel = new wxButton( this, wxID_CANCEL );
	btnStd->AddButton( btnStdCancel );
	btnStd->Realize();
	
	bSizer24->Add( btnStd, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	
	this->SetSizer( bSizer24 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( PublicationDialog::OnInitDialog ) );
	txtTitle->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( PublicationDialog::TitleOnKillFocus ), NULL, this );
	txtTitle->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( PublicationDialog::TitleOnSetFocus ), NULL, this );
	m_cboTypes->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( PublicationDialog::TypesOnKillFocus ), NULL, this );
	m_cboTypes->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( PublicationDialog::TypesOnSetFocus ), NULL, this );
	btnStdOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PublicationDialog::OnOKButtonClick ), NULL, this );
}

PublicationDialog::~PublicationDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( PublicationDialog::OnInitDialog ) );
	txtTitle->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( PublicationDialog::TitleOnKillFocus ), NULL, this );
	txtTitle->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( PublicationDialog::TitleOnSetFocus ), NULL, this );
	m_cboTypes->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( PublicationDialog::TypesOnKillFocus ), NULL, this );
	m_cboTypes->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( PublicationDialog::TypesOnSetFocus ), NULL, this );
	btnStdOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PublicationDialog::OnOKButtonClick ), NULL, this );
	
}
