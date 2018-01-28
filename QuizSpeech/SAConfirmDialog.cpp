///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 28 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "SAConfirmDialog.h"

///////////////////////////////////////////////////////////////////////////

SAConfirmDialog::SAConfirmDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	txtMessage = new wxStaticText( this, wxID_ANY, wxT("Delete, are you sure?"), wxDefaultPosition, wxDefaultSize, 0 );
	txtMessage->Wrap( -1 );
	bSizer2->Add( txtMessage, 0, wxALL, 5 );
	
	
	bSizer1->Add( bSizer2, 0, wxALL|wxEXPAND, 5 );
	
	sbSizer = new wxStdDialogButtonSizer();
	sbSizerYes = new wxButton( this, wxID_YES );
	sbSizer->AddButton( sbSizerYes );
	sbSizerNo = new wxButton( this, wxID_NO );
	sbSizer->AddButton( sbSizerNo );
	sbSizer->Realize();
	
	bSizer1->Add( sbSizer, 0, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( SAConfirmDialog::OnInitDialog ) );
	sbSizerNo->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SAConfirmDialog::NoButtonClick ), NULL, this );
	sbSizerYes->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SAConfirmDialog::YesButtonClick ), NULL, this );
}

SAConfirmDialog::~SAConfirmDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( SAConfirmDialog::OnInitDialog ) );
	sbSizerNo->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SAConfirmDialog::NoButtonClick ), NULL, this );
	sbSizerYes->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SAConfirmDialog::YesButtonClick ), NULL, this );
	
}
