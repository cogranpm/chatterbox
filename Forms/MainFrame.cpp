/////////////////////////////////////////////////////////////////////////////
// Name:        mainframe.cpp
// Purpose:     
// Author:      Paul Martin
// Modified by: 
// Created:     03/07/2017 14:24:21
// RCS-ID:      
// Copyright:   Copyright
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// Generated by DialogBlocks (unregistered), 03/07/2017 14:24:21

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
#include "wx/imaglist.h"
////@end includes

#include "mainframe.h"

////@begin XPM images
////@end XPM images


/*
 * MainFrame type definition
 */

IMPLEMENT_CLASS( MainFrame, wxFrame )


/*
 * MainFrame event table definition
 */

BEGIN_EVENT_TABLE( MainFrame, wxFrame )

////@begin MainFrame event table entries
////@end MainFrame event table entries

END_EVENT_TABLE()


/*
 * MainFrame constructors
 */

MainFrame::MainFrame()
{
    Init();
}

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create( parent, id, caption, pos, size, style );
}


/*
 * MainFrame creator
 */

bool MainFrame::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin MainFrame creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    CreateControls();
    Centre();
////@end MainFrame creation
    return true;
}


/*
 * MainFrame destructor
 */

MainFrame::~MainFrame()
{
////@begin MainFrame destruction
////@end MainFrame destruction
}


/*
 * Member initialisation
 */

void MainFrame::Init()
{
////@begin MainFrame member initialisation
    mnuFile = NULL;
////@end MainFrame member initialisation
}


/*
 * Control creation for MainFrame
 */

void MainFrame::CreateControls()
{    
////@begin MainFrame content construction
    // Generated by DialogBlocks, 03/07/2017 14:48:23 (unregistered)

    MainFrame* itemFrame1 = this;

    wxMenuBar* menuBar = new wxMenuBar;
    mnuFile = new wxMenu;
    mnuFile->Append(ID_MENUITEM_QUIT, _("Quit"), wxEmptyString, wxITEM_NORMAL);
    menuBar->Append(mnuFile, _("File"));
    itemFrame1->SetMenuBar(menuBar);

    wxStatusBar* itemStatusBar5 = new wxStatusBar( itemFrame1, ID_STATUSBAR, wxST_SIZEGRIP|wxNO_BORDER );
    itemStatusBar5->SetFieldsCount(2);
    itemFrame1->SetStatusBar(itemStatusBar5);

    wxPanel* itemPanel6 = new wxPanel( itemFrame1, ID_PANEL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    itemPanel6->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);

    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    itemPanel6->SetSizer(itemBoxSizer7);

    wxNotebook* itemNotebook8 = new wxNotebook( itemPanel6, ID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );

    wxPanel* itemPanel9 = new wxPanel( itemNotebook8, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    itemPanel9->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxBoxSizer* itemBoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    itemPanel9->SetSizer(itemBoxSizer10);

    wxNotebook* itemNotebook11 = new wxNotebook( itemPanel9, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );

    wxPanel* itemPanel12 = new wxPanel( itemNotebook11, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    itemPanel12->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);

    itemNotebook11->AddPage(itemPanel12, _("Home"));

    itemBoxSizer10->Add(itemNotebook11, 1, wxGROW|wxALL, 5);

    itemNotebook8->AddPage(itemPanel9, _("Notes"));

    wxPanel* itemPanel13 = new wxPanel( itemNotebook8, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    itemPanel13->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);

    itemNotebook8->AddPage(itemPanel13, _("Quiz"));

    itemBoxSizer7->Add(itemNotebook8, 1, wxGROW|wxALL, 5);

////@end MainFrame content construction
}


/*
 * Should we show tooltips?
 */

bool MainFrame::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap MainFrame::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin MainFrame bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end MainFrame bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon MainFrame::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin MainFrame icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end MainFrame icon retrieval
}
