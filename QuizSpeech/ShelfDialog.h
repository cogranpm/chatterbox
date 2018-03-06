///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 23 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __SHELFDIALOG_H__
#define __SHELFDIALOG_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/infobar.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/valtext.h>
#include <wx/gbsizer.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ShelfDialog
///////////////////////////////////////////////////////////////////////////////
class ShelfDialog : public wxDialog 
{
	private:
	
	protected:
		wxTextCtrl* m_txtName;
		wxStaticText* m_staticText2;
		wxTextCtrl* txtComments;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnInitDialog( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnOKButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxInfoBar* m_infoCtrl;
		wxString _title; 
		wxString _comments; 
		
		ShelfDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Shelf"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 516,240 ), long style = wxDEFAULT_DIALOG_STYLE, const wxString& name = wxT("ShelfDialog") ); 
		~ShelfDialog();
	
};

#endif //__SHELFDIALOG_H__
