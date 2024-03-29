///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version May 29 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "NoteDialog.h"

///////////////////////////////////////////////////////////////////////////

pnlNote::pnlNote( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	dialogSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* buttonBar;
	buttonBar = new wxBoxSizer( wxHORIZONTAL );
	
	btnPlayAll = new wxButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnPlayAll->SetToolTip( wxT("Play All") );
	
	buttonBar->Add( btnPlayAll, 0, 0, 5 );
	
	btnStopAll = new wxButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnStopAll->SetToolTip( wxT("Stop Playing") );
	
	buttonBar->Add( btnStopAll, 0, 0, 5 );
	
	
	dialogSizer->Add( buttonBar, 1, 0, 5 );
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxHORIZONTAL );
	
	btnCancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	btnCancel->Enable( false );
	
	bSizer15->Add( btnCancel, 0, wxALL, 5 );
	
	btnApply = new wxButton( this, wxID_ANY, wxT("&Apply"), wxDefaultPosition, wxDefaultSize, 0 );
	btnApply->SetDefault(); 
	btnApply->Enable( false );
	
	bSizer15->Add( btnApply, 0, wxALL, 5 );
	
	
	dialogSizer->Add( bSizer15, 0, wxALIGN_RIGHT, 5 );
	
	wxBoxSizer* sizerBody;
	sizerBody = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* sizerNoteFields;
	sizerNoteFields = new wxBoxSizer( wxHORIZONTAL );
	
	wxGridBagSizer* gbSizer21;
	gbSizer21 = new wxGridBagSizer( 0, 0 );
	gbSizer21->SetFlexibleDirection( wxBOTH );
	gbSizer21->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_NONE );
	
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
	
	
	gbSizer21->Add( bSizer9, wxGBPosition( 0, 0 ), wxGBSpan( 1, 2 ), wxEXPAND, 5 );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Title"), wxDefaultPosition, wxSize( 65,-1 ), 0 );
	m_staticText1->Wrap( -1 );
	m_staticText1->SetMaxSize( wxSize( 65,-1 ) );
	
	gbSizer21->Add( m_staticText1, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), 0, 5 );
	
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
	
	gbSizer21->Add( txtTitle, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALIGN_LEFT|wxALL|wxEXPAND, 5 );
	
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
	
	
	gbSizer21->Add( bSizer11, wxGBPosition( 2, 0 ), wxGBSpan( 1, 2 ), wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Description"), wxDefaultPosition, wxSize( 65,-1 ), 0 );
	m_staticText2->Wrap( -1 );
	gbSizer21->Add( m_staticText2, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), 0, 5 );
	
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
	
	gbSizer21->Add( txtDescription, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxALIGN_LEFT|wxALL|wxEXPAND, 5 );
	
	
	gbSizer21->AddGrowableCol( 1 );
	gbSizer21->AddGrowableRow( 3 );
	
	sizerNoteFields->Add( gbSizer21, 1, wxEXPAND, 5 );
	
	
	bSizer30->Add( sizerNoteFields, 1, wxEXPAND, 5 );
	
	wxBoxSizer* sizerTemplates;
	sizerTemplates = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* segmentSelectionSizer;
	segmentSelectionSizer = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Segment Templates") ), wxHORIZONTAL );
	
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	btnAddSegment = new wxButton( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnAddSegment->SetToolTip( wxT("Append selected segment") );
	
	bSizer13->Add( btnAddSegment, 0, 0, 5 );
	
	btnClear = new wxButton( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnClear->SetToolTip( wxT("Remove all segments from Note") );
	
	bSizer13->Add( btnClear, 0, 0, 5 );
	
	btnNewSegment = new wxButton( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnNewSegment->SetToolTip( wxT("Create Note Segment Template") );
	
	bSizer13->Add( btnNewSegment, 0, 0, 5 );
	
	btnEditSegment = new wxButton( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnEditSegment->SetToolTip( wxT("Edit Segment Template") );
	
	bSizer13->Add( btnEditSegment, 0, 0, 5 );
	
	
	bSizer18->Add( bSizer13, 0, 0, 5 );
	
	lstTypes = new wxListBox( sbSizer2->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxSize( -1,150 ), 0, NULL, 0 ); 
	bSizer18->Add( lstTypes, 0, wxEXPAND, 5 );
	
	
	bSizer17->Add( bSizer18, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	typeInfo = new wxHtmlWindow( sbSizer2->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_NO_SELECTION|wxHW_SCROLLBAR_NEVER );
	typeInfo->SetMinSize( wxSize( 300,50 ) );
	typeInfo->SetMaxSize( wxSize( -1,50 ) );
	
	bSizer4->Add( typeInfo, 2, wxEXPAND, 5 );
	
	
	bSizer17->Add( bSizer4, 2, wxEXPAND, 5 );
	
	
	sbSizer2->Add( bSizer17, 1, wxEXPAND, 5 );
	
	
	segmentSelectionSizer->Add( sbSizer2, 1, wxEXPAND, 5 );
	
	
	bSizer8->Add( segmentSelectionSizer, 1, wxEXPAND, 1 );
	
	
	sizerTemplates->Add( bSizer8, 1, 0, 1 );
	
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
	bSizer6->Add( segmentContainer, 5, wxEXPAND, 5 );
	
	
	sizerTemplates->Add( bSizer6, 5, wxEXPAND, 1 );
	
	
	bSizer30->Add( sizerTemplates, 1, wxEXPAND, 5 );
	
	
	sizerBody->Add( bSizer30, 1, wxEXPAND, 5 );
	
	
	dialogSizer->Add( sizerBody, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( dialogSizer );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( pnlNote::OnInitDialog ) );
	btnPlayAll->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::PlayAllOnButtonClick ), NULL, this );
	btnStopAll->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::StopAllOnButtonClick ), NULL, this );
	btnCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::OnCancelButtonClick ), NULL, this );
	btnCancel->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlNote::CancelOnUpdateUI ), NULL, this );
	btnApply->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::OnOKButtonClick ), NULL, this );
	btnApply->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlNote::ApplyOnUpdateUI ), NULL, this );
	btnUnlockTitle->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::UnlockTitleOnButtonClick ), NULL, this );
	btnRecordTitle->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::RecordTitleOnButtonClick ), NULL, this );
	btnClearTitle->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::ClearTitleOnButtonClick ), NULL, this );
	txtTitle->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( pnlNote::TitleOnText ), NULL, this );
	btnUnlockDescription->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::UnlockDescriptionOnButtonClick ), NULL, this );
	btnRecordDescription->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::RecordDescriptionOnButtonClick ), NULL, this );
	btnClearDescription->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::ClearDescriptionOnButtonClick ), NULL, this );
	txtDescription->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( pnlNote::DescriptionOnText ), NULL, this );
	btnAddSegment->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::AddSegmentOnButtonClick ), NULL, this );
	btnClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::ClearSegmentOnButtonClick ), NULL, this );
	btnNewSegment->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::NewSegmentOnButtonClick ), NULL, this );
	btnEditSegment->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::EditSegmentOnButtonClick ), NULL, this );
	lstTypes->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( pnlNote::TypesOnListBox ), NULL, this );
	lstTypes->Connect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( pnlNote::TypesOnListBoxDClick ), NULL, this );
}

pnlNote::~pnlNote()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( pnlNote::OnInitDialog ) );
	btnPlayAll->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::PlayAllOnButtonClick ), NULL, this );
	btnStopAll->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::StopAllOnButtonClick ), NULL, this );
	btnCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::OnCancelButtonClick ), NULL, this );
	btnCancel->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlNote::CancelOnUpdateUI ), NULL, this );
	btnApply->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::OnOKButtonClick ), NULL, this );
	btnApply->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( pnlNote::ApplyOnUpdateUI ), NULL, this );
	btnUnlockTitle->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::UnlockTitleOnButtonClick ), NULL, this );
	btnRecordTitle->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::RecordTitleOnButtonClick ), NULL, this );
	btnClearTitle->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::ClearTitleOnButtonClick ), NULL, this );
	txtTitle->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( pnlNote::TitleOnText ), NULL, this );
	btnUnlockDescription->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::UnlockDescriptionOnButtonClick ), NULL, this );
	btnRecordDescription->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::RecordDescriptionOnButtonClick ), NULL, this );
	btnClearDescription->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::ClearDescriptionOnButtonClick ), NULL, this );
	txtDescription->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( pnlNote::DescriptionOnText ), NULL, this );
	btnAddSegment->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::AddSegmentOnButtonClick ), NULL, this );
	btnClear->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::ClearSegmentOnButtonClick ), NULL, this );
	btnNewSegment->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::NewSegmentOnButtonClick ), NULL, this );
	btnEditSegment->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pnlNote::EditSegmentOnButtonClick ), NULL, this );
	lstTypes->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( pnlNote::TypesOnListBox ), NULL, this );
	lstTypes->Disconnect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( pnlNote::TypesOnListBoxDClick ), NULL, this );
	
}
