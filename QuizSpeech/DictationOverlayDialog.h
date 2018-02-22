///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug  4 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __DICTATIONOVERLAYDIALOG_H__
#define __DICTATIONOVERLAYDIALOG_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/gauge.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/valtext.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class OverlayDialog
///////////////////////////////////////////////////////////////////////////////
class OverlayDialog : public wxDialog 
{
	private:
	
	protected:
		wxButton* btnStop;
		wxGauge* playbackGauge;
		wxStaticText* lblHypothesis;
		wxTextCtrl* txtHypothesis;
		wxStaticText* lblSpeech;
		wxTextCtrl* txtPhrase;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInitDialog( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void StopOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOKButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxBoxSizer* szAudioPlayer;
		wxString recognizedText; 
		
		OverlayDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 464,289 ), long style = 0, const wxString& name = wxT("DictationOverlayDialog") ); 
		~OverlayDialog();
	
};

#endif //__DICTATIONOVERLAYDIALOG_H__
