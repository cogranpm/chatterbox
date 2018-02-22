///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug  4 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "NoteSegmentPanel.h"

///////////////////////////////////////////////////////////////////////////

NoteSegmentPanel::NoteSegmentPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bodySizer;
	bodySizer = new wxBoxSizer( wxHORIZONTAL );
	
	lblTitle = new wxStaticText( this, wxID_ANY, wxT("Body"), wxDefaultPosition, wxDefaultSize, 0 );
	lblTitle->Wrap( -1 );
	bodySizer->Add( lblTitle, 0, wxEXPAND|wxLEFT|wxTOP, 5 );
	
	wxBoxSizer* bodyToolbarSizer;
	bodyToolbarSizer = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	btnBodyRecord = new wxButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnBodyRecord->SetToolTip( wxT("Record") );
	
	bSizer11->Add( btnBodyRecord, 0, 0, 5 );
	
	btnBodyClear = new wxButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnBodyClear->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	btnBodyClear->SetToolTip( wxT("Clear") );
	
	bSizer11->Add( btnBodyClear, 0, 0, 5 );
	
	
	bodyToolbarSizer->Add( bSizer11, 1, wxEXPAND, 5 );
	
	szAudioPlayer = new wxBoxSizer( wxHORIZONTAL );
	
	
	bodyToolbarSizer->Add( szAudioPlayer, 0, 0, 5 );
	
	
	bodySizer->Add( bodyToolbarSizer, 0, 0, 5 );
	
	
	bSizer9->Add( bodySizer, 0, wxEXPAND|wxTOP, 5 );
	
	wxBoxSizer* bodyEntrySizer;
	bodyEntrySizer = new wxBoxSizer( wxVERTICAL );
	
	txtValue = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	txtValue->SetMinSize( wxSize( -1,150 ) );
	
	bodyEntrySizer->Add( txtValue, 1, wxEXPAND|wxLEFT, 5 );
	
	
	bSizer9->Add( bodyEntrySizer, 2, wxEXPAND|wxLEFT, 5 );
	
	
	bSizer4->Add( bSizer9, 1, wxEXPAND, 5 );
	
	wxBoxSizer* removeButtonSizer;
	removeButtonSizer = new wxBoxSizer( wxVERTICAL );
	
	btnDelete = new wxButton( this, wxID_ANY, wxT("Remove"), wxDefaultPosition, wxSize( 75,23 ), 0 );
	removeButtonSizer->Add( btnDelete, 0, 0, 5 );
	
	
	bSizer4->Add( removeButtonSizer, 0, wxALIGN_RIGHT, 5 );
	
	
	this->SetSizer( bSizer4 );
	this->Layout();
	
	// Connect Events
	btnBodyRecord->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteSegmentPanel::BodyRecordOnButtonClick ), NULL, this );
	btnBodyClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteSegmentPanel::OnButtonClickClearBody ), NULL, this );
	txtValue->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( NoteSegmentPanel::ValueOnKillFocus ), NULL, this );
	txtValue->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( NoteSegmentPanel::ValueOnSetFocus ), NULL, this );
	btnDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteSegmentPanel::DeleteOnButtonClick ), NULL, this );
}

NoteSegmentPanel::~NoteSegmentPanel()
{
	// Disconnect Events
	btnBodyRecord->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteSegmentPanel::BodyRecordOnButtonClick ), NULL, this );
	btnBodyClear->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteSegmentPanel::OnButtonClickClearBody ), NULL, this );
	txtValue->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( NoteSegmentPanel::ValueOnKillFocus ), NULL, this );
	txtValue->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( NoteSegmentPanel::ValueOnSetFocus ), NULL, this );
	btnDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteSegmentPanel::DeleteOnButtonClick ), NULL, this );
	
}
