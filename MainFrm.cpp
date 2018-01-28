///-----------------------------------------------------------------
///
/// @file      MainFrm.cpp
/// @author    paulm
/// Created:   7/3/2017 2:55:36 PM
/// @section   DESCRIPTION
///            MainFrm class implementation
///
///------------------------------------------------------------------

#include "MainFrm.h"

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// MainFrm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(MainFrm,wxFrame)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(MainFrm::OnClose)
END_EVENT_TABLE()
////Event Table End

MainFrm::MainFrm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

MainFrm::~MainFrm()
{
}

void MainFrm::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxMenuBar1 = new wxMenuBar();

	WxPanel1 = new wxPanel(this, ID_WXPANEL1, wxPoint(54, 48), wxSize(474, 380));

	WxBoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizer(WxBoxSizer1);
	this->SetAutoLayout(true);

	WxNotebook1 = new wxNotebook(this, ID_WXNOTEBOOK1, wxPoint(5, 5), wxSize(289, 193), wxNB_DEFAULT);
	WxBoxSizer1->Add(WxNotebook1, 1, wxALIGN_CENTER | wxALL, 5);

	WxNoteBookPage1 = new wxPanel(WxNotebook1, ID_WXNOTEBOOKPAGE1, wxPoint(4, 24), wxSize(281, 165));
	WxNotebook1->AddPage(WxNoteBookPage1, _("Notes"));

	SetTitle(_("Quiz Speeach"));
	SetIcon(wxNullIcon);
	
	Layout();
	GetSizer()->Fit(this);
	GetSizer()->SetSizeHints(this);
	Center();
	
	////GUI Items Creation End
}

void MainFrm::OnClose(wxCloseEvent& event)
{
	Destroy();
}
