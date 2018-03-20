///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 23 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __NOTEDIALOG_H__
#define __NOTEDIALOG_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/gbsizer.h>
#include <wx/listbox.h>
#include <wx/html/htmlwin.h>
#include <wx/statbox.h>
#include <wx/scrolwin.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class pnlNote
///////////////////////////////////////////////////////////////////////////////
class pnlNote : public wxPanel 
{
	private:
	
	protected:
		wxBoxSizer* dialogSizer;
		wxButton* btnPlayAll;
		wxButton* btnStopAll;
		wxStaticText* m_staticText1;
		wxTextCtrl* txtTitle;
		wxButton* btnUnlockTitle;
		wxButton* btnRecordTitle;
		wxButton* btnClearTitle;
		wxStaticText* m_staticText2;
		wxTextCtrl* txtDescription;
		wxButton* btnUnlockDescription;
		wxButton* btnRecordDescription;
		wxButton* btnClearDescription;
		wxButton* btnAddSegment;
		wxButton* btnClear;
		wxButton* btnNewSegment;
		wxButton* btnEditSegment;
		wxListBox* lstTypes;
		wxHtmlWindow* typeInfo;
		wxScrolledWindow* segmentContainer;
		wxBoxSizer* panelSizer;
		wxStaticBoxSizer* sbSegments;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1Apply;
		wxButton* m_sdbSizer1Cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInitDialog( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void PlayAllOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void StopAllOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void UnlockTitleOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void RecordTitleOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void ClearTitleOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void UnlockDescriptionOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void RecordDescriptionOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void ClearDescriptionOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void AddSegmentOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void ClearSegmentOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void NewSegmentOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void EditSegmentOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void TypesOnListBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void TypesOnListBoxDClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOKButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxBoxSizer* szTitlePlayer;
		wxBoxSizer* szDescriptionPlayer;
		
		pnlNote( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL ); 
		~pnlNote();
	
};

#endif //__NOTEDIALOG_H__
