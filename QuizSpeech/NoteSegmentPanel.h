///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug  4 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __NOTESEGMENTPANEL_H__
#define __NOTESEGMENTPANEL_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class NoteSegmentPanel
///////////////////////////////////////////////////////////////////////////////
class NoteSegmentPanel : public wxPanel 
{
	private:
	
	protected:
		wxStaticText* lblTitle;
		wxButton* btnBodyRecord;
		wxButton* btnBodyClear;
		wxTextCtrl* txtValue;
		
		// Virtual event handlers, overide them in your derived class
		virtual void BodyRecordOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickClearBody( wxCommandEvent& event ) { event.Skip(); }
		virtual void ValueOnKillFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void ValueOnSetFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void DeleteOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxBoxSizer* szAudioPlayer;
		wxButton* btnDelete;
		
		NoteSegmentPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 765,297 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxT("NoteSegmentPanel") ); 
		~NoteSegmentPanel();
	
};

#endif //__NOTESEGMENTPANEL_H__
