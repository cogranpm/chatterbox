///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 23 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __SUBJECTDIALOG_H__
#define __SUBJECTDIALOG_H__

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
/// Class SubjectDialog
///////////////////////////////////////////////////////////////////////////////
class SubjectDialog : public wxDialog 
{
	private:
	
	protected:
		wxInfoBar* m_infoCtrl;
		wxStaticText* m_staticText5;
		wxTextCtrl* m_txtTitle;
		wxStaticText* m_staticText2;
		wxTextCtrl* txtComments;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnInitDialog( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnOKButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxStdDialogButtonSizer* btnStd;
		wxButton* btnStdOK;
		wxButton* btnStdCancel;
		wxString _title; 
		wxString _comments; 
		
		SubjectDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Subject"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 641,276 ), long style = wxDEFAULT_DIALOG_STYLE, const wxString& name = wxT("SubjectDialog") ); 
		~SubjectDialog();
	
};

#endif //__SUBJECTDIALOG_H__
