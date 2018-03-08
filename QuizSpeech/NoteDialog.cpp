///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 23 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "NoteDialog.h"

///////////////////////////////////////////////////////////////////////////

NoteDialog::NoteDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxDialog( parent, id, title, pos, size, style, name )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	dialogSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* buttonBar;
	buttonBar = new wxBoxSizer( wxHORIZONTAL );
	
	btnPlayAll = new wxButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnPlayAll->SetToolTip( wxT("Play All") );
	
	buttonBar->Add( btnPlayAll, 0, wxALL, 5 );
	
	btnStopAll = new wxButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnStopAll->SetToolTip( wxT("Stop Playing") );
	
	buttonBar->Add( btnStopAll, 0, wxALL, 5 );
	
	
	dialogSizer->Add( buttonBar, 0, wxEXPAND, 5 );
	
	wxBoxSizer* sizerNoteFields;
	sizerNoteFields = new wxBoxSizer( wxHORIZONTAL );
	
	wxGridBagSizer* gbSizer21;
	gbSizer21 = new wxGridBagSizer( 0, 0 );
	gbSizer21->SetFlexibleDirection( wxBOTH );
	gbSizer21->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_NONE );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Title"), wxDefaultPosition, wxSize( 65,-1 ), 0 );
	m_staticText1->Wrap( -1 );
	m_staticText1->SetMaxSize( wxSize( 65,-1 ) );
	
	gbSizer21->Add( m_staticText1, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	txtTitle = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,20 ), 0 );
	#ifdef __WXGTK__
	if ( !txtTitle->HasFlag( wxTE_MULTILINE ) )
	{
	txtTitle->SetMaxLength( 60 );
	}
	#else
	txtTitle->SetMaxLength( 60 );
	#endif
	txtTitle->Enable( false );
	txtTitle->SetMaxSize( wxSize( -1,20 ) );
	
	gbSizer21->Add( txtTitle, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALIGN_LEFT|wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	btnUnlockTitle = new wxButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnUnlockTitle->SetToolTip( wxT("Unlock") );
	
	bSizer9->Add( btnUnlockTitle, 0, 0, 5 );
	
	btnRecordTitle = new wxButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	bSizer9->Add( btnRecordTitle, 0, 0, 5 );
	
	btnClearTitle = new wxButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	bSizer9->Add( btnClearTitle, 0, 0, 5 );
	
	szTitlePlayer = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer9->Add( szTitlePlayer, 1, wxEXPAND, 5 );
	
	
	gbSizer21->Add( bSizer9, wxGBPosition( 0, 3 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Description"), wxDefaultPosition, wxSize( 65,-1 ), 0 );
	m_staticText2->Wrap( -1 );
	gbSizer21->Add( m_staticText2, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	txtDescription = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	#ifdef __WXGTK__
	if ( !txtDescription->HasFlag( wxTE_MULTILINE ) )
	{
	txtDescription->SetMaxLength( 32000 );
	}
	#else
	txtDescription->SetMaxLength( 32000 );
	#endif
	txtDescription->Enable( false );
	txtDescription->SetMinSize( wxSize( -1,120 ) );
	
	gbSizer21->Add( txtDescription, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALIGN_LEFT|wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	btnUnlockDescription = new wxButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnUnlockDescription->SetToolTip( wxT("Unlock") );
	
	bSizer11->Add( btnUnlockDescription, 0, 0, 5 );
	
	btnRecordDescription = new wxButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	bSizer11->Add( btnRecordDescription, 0, 0, 5 );
	
	btnClearDescription = new wxButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	bSizer11->Add( btnClearDescription, 0, 0, 5 );
	
	szDescriptionPlayer = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer11->Add( szDescriptionPlayer, 1, wxEXPAND, 5 );
	
	
	gbSizer21->Add( bSizer11, wxGBPosition( 1, 3 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );
	
	
	gbSizer21->AddGrowableCol( 1 );
	gbSizer21->AddGrowableRow( 1 );
	
	sizerNoteFields->Add( gbSizer21, 1, wxALL|wxEXPAND, 5 );
	
	
	dialogSizer->Add( sizerNoteFields, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* segmentSelectionSizer;
	segmentSelectionSizer = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Segment Templates") ), wxVERTICAL );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	btnAddSegment = new wxButton( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnAddSegment->SetToolTip( wxT("Append selected segment") );
	
	bSizer13->Add( btnAddSegment, 0, wxALL, 5 );
	
	btnClear = new wxButton( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnClear->SetToolTip( wxT("Remove all segments from Note") );
	
	bSizer13->Add( btnClear, 0, wxALL, 5 );
	
	btnNewSegment = new wxButton( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnNewSegment->SetToolTip( wxT("Create Note Segment Template") );
	
	bSizer13->Add( btnNewSegment, 0, wxALL, 5 );
	
	btnEditSegment = new wxButton( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnEditSegment->SetToolTip( wxT("Edit Segment Template") );
	
	bSizer13->Add( btnEditSegment, 0, wxALL, 5 );
	
	
	sbSizer2->Add( bSizer13, 0, 0, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	lstTypes = new wxListBox( sbSizer2->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxSize( -1,150 ), 0, NULL, 0 ); 
	bSizer4->Add( lstTypes, 0, wxALL|wxEXPAND, 5 );
	
	typeInfo = new wxHtmlWindow( sbSizer2->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_NO_SELECTION|wxHW_SCROLLBAR_NEVER );
	typeInfo->SetMinSize( wxSize( 300,50 ) );
	typeInfo->SetMaxSize( wxSize( -1,50 ) );
	
	bSizer4->Add( typeInfo, 2, wxALL|wxEXPAND, 5 );
	
	
	sbSizer2->Add( bSizer4, 1, wxEXPAND, 5 );
	
	
	segmentSelectionSizer->Add( sbSizer2, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer8->Add( segmentSelectionSizer, 1, 0, 5 );
	
	
	bSizer3->Add( bSizer8, 1, 0, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	segmentContainer = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	segmentContainer->SetScrollRate( 5, 5 );
	panelSizer = new wxBoxSizer( wxVERTICAL );
	
	sbSegments = new wxStaticBoxSizer( new wxStaticBox( segmentContainer, wxID_ANY, wxT("Note Segments") ), wxVERTICAL );
	
	
	panelSizer->Add( sbSegments, 1, wxEXPAND, 5 );
	
	
	segmentContainer->SetSizer( panelSizer );
	segmentContainer->Layout();
	panelSizer->Fit( segmentContainer );
	bSizer6->Add( segmentContainer, 5, wxEXPAND | wxALL, 5 );
	
	
	bSizer3->Add( bSizer6, 5, wxEXPAND, 5 );
	
	
	dialogSizer->Add( bSizer3, 2, wxEXPAND, 5 );
	
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();
	
	dialogSizer->Add( m_sdbSizer1, 0, wxALIGN_RIGHT, 5 );
	
	
	this->SetSizer( dialogSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( NoteDialog::OnClose ) );
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( NoteDialog::OnInitDialog ) );
	btnPlayAll->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::PlayAllOnButtonClick ), NULL, this );
	btnStopAll->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::StopAllOnButtonClick ), NULL, this );
	btnUnlockTitle->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::UnlockTitleOnButtonClick ), NULL, this );
	btnRecordTitle->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::RecordTitleOnButtonClick ), NULL, this );
	btnClearTitle->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::ClearTitleOnButtonClick ), NULL, this );
	btnUnlockDescription->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::UnlockDescriptionOnButtonClick ), NULL, this );
	btnRecordDescription->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::RecordDescriptionOnButtonClick ), NULL, this );
	btnClearDescription->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::ClearDescriptionOnButtonClick ), NULL, this );
	btnAddSegment->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::AddSegmentOnButtonClick ), NULL, this );
	btnClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::ClearSegmentOnButtonClick ), NULL, this );
	btnNewSegment->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::NewSegmentOnButtonClick ), NULL, this );
	btnEditSegment->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::EditSegmentOnButtonClick ), NULL, this );
	lstTypes->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( NoteDialog::TypesOnListBox ), NULL, this );
	lstTypes->Connect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( NoteDialog::TypesOnListBoxDClick ), NULL, this );
	m_sdbSizer1Cancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::OnCancelButtonClick ), NULL, this );
	m_sdbSizer1OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::OnOKButtonClick ), NULL, this );
}

NoteDialog::~NoteDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( NoteDialog::OnClose ) );
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( NoteDialog::OnInitDialog ) );
	btnPlayAll->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::PlayAllOnButtonClick ), NULL, this );
	btnStopAll->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::StopAllOnButtonClick ), NULL, this );
	btnUnlockTitle->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::UnlockTitleOnButtonClick ), NULL, this );
	btnRecordTitle->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::RecordTitleOnButtonClick ), NULL, this );
	btnClearTitle->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::ClearTitleOnButtonClick ), NULL, this );
	btnUnlockDescription->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::UnlockDescriptionOnButtonClick ), NULL, this );
	btnRecordDescription->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::RecordDescriptionOnButtonClick ), NULL, this );
	btnClearDescription->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::ClearDescriptionOnButtonClick ), NULL, this );
	btnAddSegment->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::AddSegmentOnButtonClick ), NULL, this );
	btnClear->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::ClearSegmentOnButtonClick ), NULL, this );
	btnNewSegment->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::NewSegmentOnButtonClick ), NULL, this );
	btnEditSegment->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::EditSegmentOnButtonClick ), NULL, this );
	lstTypes->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( NoteDialog::TypesOnListBox ), NULL, this );
	lstTypes->Disconnect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( NoteDialog::TypesOnListBoxDClick ), NULL, this );
	m_sdbSizer1Cancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::OnCancelButtonClick ), NULL, this );
	m_sdbSizer1OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoteDialog::OnOKButtonClick ), NULL, this );
	
}
