///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 28 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __SACONFIRMDIALOG_H__
#define __SACONFIRMDIALOG_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class SAConfirmDialog
///////////////////////////////////////////////////////////////////////////////
class SAConfirmDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* txtMessage;
		wxStdDialogButtonSizer* sbSizer;
		wxButton* sbSizerYes;
		wxButton* sbSizerNo;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInitDialog( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void NoButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void YesButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		SAConfirmDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Confirm Delete"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 423,105 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~SAConfirmDialog();
	
};

#endif //__SACONFIRMDIALOG_H__
