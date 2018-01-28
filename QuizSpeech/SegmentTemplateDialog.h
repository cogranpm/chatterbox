///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Nov  6 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __SEGMENTTEMPLATEDIALOG_H__
#define __SEGMENTTEMPLATEDIALOG_H__

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
#include <wx/fontpicker.h>
#include <wx/button.h>
#include <wx/statbox.h>
#include <wx/dataview.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class SegmentTemplateDialog
///////////////////////////////////////////////////////////////////////////////
class SegmentTemplateDialog : public wxDialog 
{
	private:
	
	protected:
		wxInfoBar* headerInfo;
		wxStaticText* lblName;
		wxTextCtrl* txtName;
		wxStaticText* m_staticText5;
		wxTextCtrl* txtHelp;
		wxInfoBar* segmentInfo;
		wxStaticText* lblTitle;
		wxTextCtrl* txtTitle;
		wxStaticText* lblFont;
		wxFontPickerCtrl* fontPicker;
		wxButton* btnAddUpdate;
		wxButton* btnNew;
		wxButton* btnRemove;
		wxDataViewListCtrl* lstSegments;
		wxDataViewColumn* colTitle;
		wxDataViewColumn* colFont;
		wxDataViewColumn* colSize;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInitDialog( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void AddUpdateOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void NewOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void RemoveOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void RemoveOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnSegmentListSelectionChanged( wxDataViewEvent& event ) { event.Skip(); }
		virtual void OnCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOKButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxString name; 
		wxString helpText; 
		
		SegmentTemplateDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Segment Template"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1011,643 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxRESIZE_BORDER ); 
		~SegmentTemplateDialog();
	
};

#endif //__SEGMENTTEMPLATEDIALOG_H__
