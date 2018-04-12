///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 24 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __PUBLICATIONDIALOG_H__
#define __PUBLICATIONDIALOG_H__

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
#include <wx/combobox.h>
#include <wx/gbsizer.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class PublicationDialog
///////////////////////////////////////////////////////////////////////////////
class PublicationDialog : public wxDialog 
{
	private:
	
	protected:
		wxInfoBar* infoCtrl;
		wxStaticText* lblTitle;
		wxTextCtrl* txtTitle;
		wxStaticText* lblType;
		wxComboBox* m_cboTypes;
		wxStaticText* m_staticText3;
		wxTextCtrl* txtComments;
		wxStdDialogButtonSizer* btnStd;
		wxButton* btnStdOK;
		wxButton* btnStdCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInitDialog( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void TitleOnKillFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void TitleOnSetFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void TypesOnKillFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void TypesOnSetFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void OnOKButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxString _title; 
		wxString _comments; 
		
		PublicationDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Publication"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 456,328 ), long style = wxDEFAULT_DIALOG_STYLE, const wxString& name = wxT("PublicationDialog") ); 
		~PublicationDialog();
	
};

#endif //__PUBLICATIONDIALOG_H__
