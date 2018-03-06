///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 23 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __EXPORTDIALOG_H__
#define __EXPORTDIALOG_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/filepicker.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ExportDialog
///////////////////////////////////////////////////////////////////////////////
class ExportDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxFilePickerCtrl* filePicker;
		wxStdDialogButtonSizer* sizerStdButtons;
		wxButton* sizerStdButtonsOK;
		wxButton* sizerStdButtonsCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnOKButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		ExportDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Export Data"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 594,238 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~ExportDialog();
	
};

#endif //__EXPORTDIALOG_H__
