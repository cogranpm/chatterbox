///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 28 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MainFrame.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar1 = new wxMenuBar( 0 );
	menuFile = new wxMenu();
	wxMenuItem* menuFileQuit;
	menuFileQuit = new wxMenuItem( menuFile, wxID_QUIT, wxString( wxT("&Quit") ) + wxT('\t') + wxT("CTRL-Q"), wxEmptyString, wxITEM_NORMAL );
	menuFile->Append( menuFileQuit );
	
	m_menubar1->Append( menuFile, wxT("&File") ); 
	
	this->SetMenuBar( m_menubar1 );
	
	m_statusBar1 = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizerNotebookMain;
	bSizerNotebookMain = new wxBoxSizer( wxVERTICAL );
	
	m_auiShelf = new wxAuiNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panelNotes = new wxPanel( m_auiShelf, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panelNotes->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	
	wxBoxSizer* splitterSizer;
	splitterSizer = new wxBoxSizer( wxVERTICAL );
	
	m_splitter1 = new wxSplitterWindow( m_panelNotes, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter1->Connect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::m_splitter1OnIdle ), NULL, this );
	
	pnlShelf = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	pnlShelfHeader = new wxPanel( pnlShelf, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText5 = new wxStaticText( pnlShelfHeader, wxID_ANY, wxT("Shelves"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer6->Add( m_staticText5, 0, wxALL, 5 );
	
	m_btnAddShelf = new wxButton( pnlShelfHeader, wxID_ADD_SHELF, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	m_btnAddShelf->SetMaxSize( wxSize( 25,-1 ) );
	
	bSizer6->Add( m_btnAddShelf, 0, wxALIGN_LEFT, 5 );
	
	m_btnDeleteShelf = new wxButton( pnlShelfHeader, wxID_DELETE_SHELF, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	m_btnDeleteShelf->Enable( false );
	m_btnDeleteShelf->SetMaxSize( wxSize( 25,-1 ) );
	
	bSizer6->Add( m_btnDeleteShelf, 0, 0, 5 );
	
	m_btnEditShelf = new wxButton( pnlShelfHeader, wxID_EDIT_SHELF, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	m_btnEditShelf->Enable( false );
	m_btnEditShelf->SetMaxSize( wxSize( 60,-1 ) );
	
	bSizer6->Add( m_btnEditShelf, 0, 0, 5 );
	
	
	pnlShelfHeader->SetSizer( bSizer6 );
	pnlShelfHeader->Layout();
	bSizer6->Fit( pnlShelfHeader );
	bSizer5->Add( pnlShelfHeader, 0, 0, 5 );
	
	pnlShelfList = new wxPanel( pnlShelf, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	m_dvlShelf = new wxDataViewListCtrl( pnlShelfList, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_SINGLE );
	m_dvlcShelfName = m_dvlShelf->AppendTextColumn( wxT("Title") );
	bSizer7->Add( m_dvlShelf, 1, wxEXPAND, 5 );
	
	
	pnlShelfList->SetSizer( bSizer7 );
	pnlShelfList->Layout();
	bSizer7->Fit( pnlShelfList );
	bSizer5->Add( pnlShelfList, 1, wxEXPAND, 5 );
	
	
	pnlShelf->SetSizer( bSizer5 );
	pnlShelf->Layout();
	bSizer5->Fit( pnlShelf );
	pnlShelfChildren = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	m_splitter2 = new wxSplitterWindow( pnlShelfChildren, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter2->Connect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::m_splitter2OnIdle ), NULL, this );
	
	pnlSubject = new wxPanel( m_splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );
	
	pnlSubjectHeader = new wxPanel( pnlSubject, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText7 = new wxStaticText( pnlSubjectHeader, wxID_ANY, wxT("Subjects"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	bSizer13->Add( m_staticText7, 0, wxALL, 5 );
	
	btnAddSubject = new wxButton( pnlSubjectHeader, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnAddSubject->Enable( false );
	btnAddSubject->SetMaxSize( wxSize( 25,-1 ) );
	
	bSizer13->Add( btnAddSubject, 0, 0, 5 );
	
	btnDeleteSubject = new wxButton( pnlSubjectHeader, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnDeleteSubject->Enable( false );
	btnDeleteSubject->SetMaxSize( wxSize( 25,-1 ) );
	
	bSizer13->Add( btnDeleteSubject, 0, 0, 5 );
	
	btnEditSubject = new wxButton( pnlSubjectHeader, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnEditSubject->Enable( false );
	btnEditSubject->SetMaxSize( wxSize( 60,-1 ) );
	
	bSizer13->Add( btnEditSubject, 0, 0, 5 );
	
	
	pnlSubjectHeader->SetSizer( bSizer13 );
	pnlSubjectHeader->Layout();
	bSizer13->Fit( pnlSubjectHeader );
	bSizer12->Add( pnlSubjectHeader, 0, wxEXPAND, 5 );
	
	pnlSubjectList = new wxPanel( pnlSubject, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );
	
	m_lstSubject = new wxDataViewListCtrl( pnlSubjectList, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_lstSubjectColTitle = m_lstSubject->AppendTextColumn( wxT("Title") );
	bSizer14->Add( m_lstSubject, 1, wxALL|wxEXPAND, 5 );
	
	
	pnlSubjectList->SetSizer( bSizer14 );
	pnlSubjectList->Layout();
	bSizer14->Fit( pnlSubjectList );
	bSizer12->Add( pnlSubjectList, 1, wxEXPAND, 5 );
	
	
	pnlSubject->SetSizer( bSizer12 );
	pnlSubject->Layout();
	bSizer12->Fit( pnlSubject );
	pnlPublication = new wxPanel( m_splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	pnlPublicationHeader = new wxPanel( pnlPublication, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText6 = new wxStaticText( pnlPublicationHeader, wxID_ANY, wxT("Publications"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	bSizer10->Add( m_staticText6, 0, wxALL, 5 );
	
	btnAddPublication = new wxButton( pnlPublicationHeader, wxID_ADDPUBLICATION, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnAddPublication->Enable( false );
	btnAddPublication->SetMaxSize( wxSize( 25,-1 ) );
	
	bSizer10->Add( btnAddPublication, 0, 0, 5 );
	
	btnDeletePublication = new wxButton( pnlPublicationHeader, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnDeletePublication->Enable( false );
	btnDeletePublication->SetMaxSize( wxSize( 25,-1 ) );
	
	bSizer10->Add( btnDeletePublication, 0, 0, 5 );
	
	btnEditPublication = new wxButton( pnlPublicationHeader, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 20,20 ), 0 );
	btnEditPublication->Enable( false );
	btnEditPublication->SetMaxSize( wxSize( 60,-1 ) );
	
	bSizer10->Add( btnEditPublication, 0, 0, 5 );
	
	
	pnlPublicationHeader->SetSizer( bSizer10 );
	pnlPublicationHeader->Layout();
	bSizer10->Fit( pnlPublicationHeader );
	bSizer9->Add( pnlPublicationHeader, 0, wxEXPAND, 5 );
	
	pnlPublicationList = new wxPanel( pnlPublication, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	lstPublication = new wxDataViewListCtrl( pnlPublicationList, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	lstPublicationColTitle = lstPublication->AppendTextColumn( wxT("Title") );
	bSizer11->Add( lstPublication, 1, wxALL|wxEXPAND, 5 );
	
	
	pnlPublicationList->SetSizer( bSizer11 );
	pnlPublicationList->Layout();
	bSizer11->Fit( pnlPublicationList );
	bSizer9->Add( pnlPublicationList, 5, wxEXPAND, 5 );
	
	
	pnlPublication->SetSizer( bSizer9 );
	pnlPublication->Layout();
	bSizer9->Fit( pnlPublication );
	m_splitter2->SplitHorizontally( pnlSubject, pnlPublication, 0 );
	bSizer8->Add( m_splitter2, 1, wxEXPAND, 5 );
	
	
	pnlShelfChildren->SetSizer( bSizer8 );
	pnlShelfChildren->Layout();
	bSizer8->Fit( pnlShelfChildren );
	m_splitter1->SplitVertically( pnlShelf, pnlShelfChildren, 248 );
	splitterSizer->Add( m_splitter1, 1, wxEXPAND, 5 );
	
	
	m_panelNotes->SetSizer( splitterSizer );
	m_panelNotes->Layout();
	splitterSizer->Fit( m_panelNotes );
	m_auiShelf->AddPage( m_panelNotes, wxT("Home"), false, wxNullBitmap );
	
	bSizerNotebookMain->Add( m_auiShelf, 1, wxEXPAND | wxALL, 5 );
	
	
	bSizer1->Add( bSizerNotebookMain, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( menuFileQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::menuFileQuitOnMenuSelection ) );
	m_auiShelf->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( MainFrame::OnNotebookPageChanged ), NULL, this );
	m_auiShelf->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSE, wxAuiNotebookEventHandler( MainFrame::OnNotebookPageClose ), NULL, this );
	m_btnAddShelf->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::AddShelfOnButtonClick ), NULL, this );
	m_btnDeleteShelf->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::DeleteShelfOnButtonClick ), NULL, this );
	m_btnEditShelf->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::EditShelfOnButtonClick ), NULL, this );
	m_dvlShelf->Connect( wxEVT_COMMAND_DATAVIEW_COLUMN_SORTED, wxDataViewEventHandler( MainFrame::OnShelfColumnSort ), NULL, this );
	m_dvlShelf->Connect( wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler( MainFrame::OnShelfItemActivated ), NULL, this );
	m_dvlShelf->Connect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( MainFrame::OnShelfSelectionChanged ), NULL, this );
	btnAddSubject->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::AddSubjectOnButtonClick ), NULL, this );
	btnDeleteSubject->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::DeleteSubjectOnButtonClick ), NULL, this );
	btnEditSubject->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::EditSubjectOnButtonClick ), NULL, this );
	m_lstSubject->Connect( wxEVT_COMMAND_DATAVIEW_COLUMN_SORTED, wxDataViewEventHandler( MainFrame::OnSubjectColumnSort ), NULL, this );
	m_lstSubject->Connect( wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler( MainFrame::OnSubjectItemActivated ), NULL, this );
	m_lstSubject->Connect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( MainFrame::SubjectOnSelectionChanged ), NULL, this );
	btnAddPublication->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::AddPublicationOnButtonClick ), NULL, this );
	btnAddPublication->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrame::AddPublicationOnUpdateUI ), NULL, this );
	btnDeletePublication->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::DeletePublicationOnButtonClick ), NULL, this );
	btnDeletePublication->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrame::DeletePublicationOnUpdateUI ), NULL, this );
	btnEditPublication->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::EditPublicationOnButtonClick ), NULL, this );
	btnEditPublication->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrame::EditPublicationOnUpdateUI ), NULL, this );
	lstPublication->Connect( wxEVT_COMMAND_DATAVIEW_COLUMN_SORTED, wxDataViewEventHandler( MainFrame::OnPublicationColumnSort ), NULL, this );
	lstPublication->Connect( wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler( MainFrame::OnPublicationItemActivated ), NULL, this );
	lstPublication->Connect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( MainFrame::PublicationSelectionChanged ), NULL, this );
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	this->Disconnect( wxID_QUIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::menuFileQuitOnMenuSelection ) );
	m_auiShelf->Disconnect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( MainFrame::OnNotebookPageChanged ), NULL, this );
	m_auiShelf->Disconnect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSE, wxAuiNotebookEventHandler( MainFrame::OnNotebookPageClose ), NULL, this );
	m_btnAddShelf->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::AddShelfOnButtonClick ), NULL, this );
	m_btnDeleteShelf->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::DeleteShelfOnButtonClick ), NULL, this );
	m_btnEditShelf->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::EditShelfOnButtonClick ), NULL, this );
	m_dvlShelf->Disconnect( wxEVT_COMMAND_DATAVIEW_COLUMN_SORTED, wxDataViewEventHandler( MainFrame::OnShelfColumnSort ), NULL, this );
	m_dvlShelf->Disconnect( wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler( MainFrame::OnShelfItemActivated ), NULL, this );
	m_dvlShelf->Disconnect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( MainFrame::OnShelfSelectionChanged ), NULL, this );
	btnAddSubject->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::AddSubjectOnButtonClick ), NULL, this );
	btnDeleteSubject->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::DeleteSubjectOnButtonClick ), NULL, this );
	btnEditSubject->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::EditSubjectOnButtonClick ), NULL, this );
	m_lstSubject->Disconnect( wxEVT_COMMAND_DATAVIEW_COLUMN_SORTED, wxDataViewEventHandler( MainFrame::OnSubjectColumnSort ), NULL, this );
	m_lstSubject->Disconnect( wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler( MainFrame::OnSubjectItemActivated ), NULL, this );
	m_lstSubject->Disconnect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( MainFrame::SubjectOnSelectionChanged ), NULL, this );
	btnAddPublication->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::AddPublicationOnButtonClick ), NULL, this );
	btnAddPublication->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrame::AddPublicationOnUpdateUI ), NULL, this );
	btnDeletePublication->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::DeletePublicationOnButtonClick ), NULL, this );
	btnDeletePublication->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrame::DeletePublicationOnUpdateUI ), NULL, this );
	btnEditPublication->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::EditPublicationOnButtonClick ), NULL, this );
	btnEditPublication->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrame::EditPublicationOnUpdateUI ), NULL, this );
	lstPublication->Disconnect( wxEVT_COMMAND_DATAVIEW_COLUMN_SORTED, wxDataViewEventHandler( MainFrame::OnPublicationColumnSort ), NULL, this );
	lstPublication->Disconnect( wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler( MainFrame::OnPublicationItemActivated ), NULL, this );
	lstPublication->Disconnect( wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( MainFrame::PublicationSelectionChanged ), NULL, this );
	
}
