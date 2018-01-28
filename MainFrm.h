///-----------------------------------------------------------------
///
/// @file      MainFrm.h
/// @author    paulm
/// Created:   7/3/2017 2:55:36 PM
/// @section   DESCRIPTION
///            MainFrm class declaration
///
///------------------------------------------------------------------

#ifndef __MAINFRM_H__
#define __MAINFRM_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/menu.h>
////Header Include End

////Dialog Style Start
#undef MainFrm_STYLE
#define MainFrm_STYLE wxCAPTION | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class MainFrm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		MainFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("Quiz Speeach"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = MainFrm_STYLE);
		virtual ~MainFrm();
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxPanel *WxNoteBookPage1;
		wxNotebook *WxNotebook1;
		wxBoxSizer *WxBoxSizer1;
		wxPanel *WxPanel1;
		wxMenuBar *WxMenuBar1;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXNOTEBOOKPAGE1 = 4,
			ID_WXNOTEBOOK1 = 3,
			ID_WXPANEL1 = 1,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
