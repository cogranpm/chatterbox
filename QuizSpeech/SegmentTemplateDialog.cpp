///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug  4 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "SegmentTemplateDialog.h"

///////////////////////////////////////////////////////////////////////////

SegmentTemplateDialog::SegmentTemplateDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxDialog( parent, id, title, pos, size, style, name )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer131;
	bSizer131 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );
	
	headerInfo = new wxInfoBar( this );
	headerInfo->SetShowHideEffects( wxSHOW_EFFECT_NONE, wxSHOW_EFFECT_NONE );
	headerInfo->SetEffectDuration( 500 );
	bSizer12->Add( headerInfo, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	lblName = new wxStaticText( this, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	lblName->Wrap( -1 );
	bSizer6->Add( lblName, 0, wxALL, 5 );
	
	txtName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !txtName->HasFlag( wxTE_MULTILINE ) )
	{
	txtName->SetMaxLength( 65 );
	}
	#else
	txtName->SetMaxLength( 65 );
	#endif
	txtName->SetValidator( wxTextValidator( wxFILTER_NONE, &templateName ) );
	
	bSizer6->Add( txtName, 1, wxALL, 5 );
	
	
	bSizer12->Add( bSizer6, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer13->Add( m_staticText5, 0, wxALL, 5 );
	
	txtHelp = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	#ifdef __WXGTK__
	if ( !txtHelp->HasFlag( wxTE_MULTILINE ) )
	{
	txtHelp->SetMaxLength( 3200 );
	}
	#else
	txtHelp->SetMaxLength( 3200 );
	#endif
	txtHelp->SetValidator( wxTextValidator( wxFILTER_NONE, &helpText ) );
	
	bSizer13->Add( txtHelp, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer12->Add( bSizer13, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer131->Add( bSizer12, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Segment") ), wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	segmentInfo = new wxInfoBar( sbSizer2->GetStaticBox() );
	segmentInfo->SetShowHideEffects( wxSHOW_EFFECT_NONE, wxSHOW_EFFECT_NONE );
	segmentInfo->SetEffectDuration( 500 );
	bSizer2->Add( segmentInfo, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer101;
	bSizer101 = new wxBoxSizer( wxHORIZONTAL );
	
	lblTitle = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Title"), wxDefaultPosition, wxDefaultSize, 0 );
	lblTitle->Wrap( -1 );
	bSizer101->Add( lblTitle, 0, wxALL, 5 );
	
	txtTitle = new wxTextCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !txtTitle->HasFlag( wxTE_MULTILINE ) )
	{
	txtTitle->SetMaxLength( 256 );
	}
	#else
	txtTitle->SetMaxLength( 256 );
	#endif
	bSizer101->Add( txtTitle, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer2->Add( bSizer101, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	lblFont = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Font"), wxDefaultPosition, wxDefaultSize, 0 );
	lblFont->Wrap( -1 );
	bSizer3->Add( lblFont, 0, wxALL, 5 );
	
	fontPicker = new wxFontPickerCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxNullFont, wxDefaultPosition, wxSize( -1,-1 ), wxFNTP_DEFAULT_STYLE );
	fontPicker->SetMaxPointSize( 100 ); 
	bSizer3->Add( fontPicker, 1, wxALL, 5 );
	
	
	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizer2->Add( bSizer3, 1, wxALL|wxEXPAND, 5 );
	
	btnAddUpdate = new wxButton( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( btnAddUpdate, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	
	sbSizer2->Add( bSizer2, 0, wxEXPAND, 5 );
	
	
	bSizer131->Add( sbSizer2, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer1->Add( bSizer131, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Note Segments") ), wxVERTICAL );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	btnNew = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	bSizer9->Add( btnNew, 0, 0, 5 );
	
	btnRemove = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	bSizer9->Add( btnRemove, 0, 0, 5 );
	
	
	bSizer4->Add( bSizer9, 0, 0, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	lstSegments = new wxDataViewListCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	colTitle = lstSegments->AppendTextColumn( wxT("Title") );
	colFont = lstSegments->AppendTextColumn( wxT("Font") );
	colSize = lstSegments->AppendTextColumn( wxT("Size") );
	bSizer10->Add( lstSegments, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer4->Add( bSizer10, 1, wxEXPAND, 5 );
	
	
	sbSizer1->Add( bSizer4, 1, wxEXPAND, 5 );
	
	
	bSizer7->Add( sbSizer1, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer5->Add( bSizer7, 1, wxEXPAND, 5 );
	
	
	bSizer1->Add( bSizer5, 5, wxEXPAND, 5 );
	
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
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( SegmentTemplateDialog::OnInitDialog ) );
	btnAddUpdate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SegmentTemplateDialog::AddUpdateOnButtonClick ), NULL, this );
	btnNew->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SegmentTemplateDialog::NewOnButtonClick ), NULL, this );
	btnRemove->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SegmentTemplateDialog::RemoveOnButtonClick ), NULL, this );
	btnRemove->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( SegmentTemplateDialog::RemoveOnUpdateUI ), NULL, this );
	lstSegments->Connect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( SegmentTemplateDialog::OnSegmentListSelectionChanged ), NULL, this );
	m_sdbSizer1Cancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SegmentTemplateDialog::OnCancelButtonClick ), NULL, this );
	m_sdbSizer1OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SegmentTemplateDialog::OnOKButtonClick ), NULL, this );
}

SegmentTemplateDialog::~SegmentTemplateDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( SegmentTemplateDialog::OnInitDialog ) );
	btnAddUpdate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SegmentTemplateDialog::AddUpdateOnButtonClick ), NULL, this );
	btnNew->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SegmentTemplateDialog::NewOnButtonClick ), NULL, this );
	btnRemove->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SegmentTemplateDialog::RemoveOnButtonClick ), NULL, this );
	btnRemove->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( SegmentTemplateDialog::RemoveOnUpdateUI ), NULL, this );
	lstSegments->Disconnect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( SegmentTemplateDialog::OnSegmentListSelectionChanged ), NULL, this );
	m_sdbSizer1Cancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SegmentTemplateDialog::OnCancelButtonClick ), NULL, this );
	m_sdbSizer1OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SegmentTemplateDialog::OnOKButtonClick ), NULL, this );
	
}
