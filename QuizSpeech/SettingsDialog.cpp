///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 23 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "SettingsDialog.h"

///////////////////////////////////////////////////////////////////////////

DlgSettings::DlgSettings( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Data Directory"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer2->Add( m_staticText1, 0, wxALL, 5 );
	
	dataDirPicker = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE|wxDIRP_DIR_MUST_EXIST );
	bSizer2->Add( dataDirPicker, 5, wxALL|wxEXPAND, 5 );
	
	
	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );
	
	stdButtonSizer = new wxStdDialogButtonSizer();
	stdButtonSizerOK = new wxButton( this, wxID_OK );
	stdButtonSizer->AddButton( stdButtonSizerOK );
	stdButtonSizerCancel = new wxButton( this, wxID_CANCEL );
	stdButtonSizer->AddButton( stdButtonSizerCancel );
	stdButtonSizer->Realize();
	
	bSizer1->Add( stdButtonSizer, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( DlgSettings::OnInitDialog ) );
	dataDirPicker->Connect( wxEVT_COMMAND_DIRPICKER_CHANGED, wxFileDirPickerEventHandler( DlgSettings::DataDirectoryOnDirChanged ), NULL, this );
	stdButtonSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DlgSettings::OnOKButtonClick ), NULL, this );
}

DlgSettings::~DlgSettings()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( DlgSettings::OnInitDialog ) );
	dataDirPicker->Disconnect( wxEVT_COMMAND_DIRPICKER_CHANGED, wxFileDirPickerEventHandler( DlgSettings::DataDirectoryOnDirChanged ), NULL, this );
	stdButtonSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DlgSettings::OnOKButtonClick ), NULL, this );
	
}
