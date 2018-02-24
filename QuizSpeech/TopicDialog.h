///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 24 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __TOPICDIALOG_H__
#define __TOPICDIALOG_H__

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
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class TopicDialog
///////////////////////////////////////////////////////////////////////////////
class TopicDialog : public wxDialog 
{
	private:
	
	protected:
		wxInfoBar* m_infoCtrl1;
		wxStaticText* m_staticText6;
		wxTextCtrl* txtTitle;
		wxStdDialogButtonSizer* m_sdbSizer2;
		wxButton* m_sdbSizer2OK;
		wxButton* m_sdbSizer2Cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInitDialog( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOKButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxString _title; 
		
		TopicDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Topic"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 473,147 ), long style = wxDEFAULT_DIALOG_STYLE, const wxString& name = wxT("TopicDialog") ); 
		~TopicDialog();
	
};

#endif //__TOPICDIALOG_H__
