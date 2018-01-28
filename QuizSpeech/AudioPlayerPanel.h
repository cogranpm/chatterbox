///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 28 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __AUDIOPLAYERPANEL_H__
#define __AUDIOPLAYERPANEL_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/gauge.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class pnlPlayer
///////////////////////////////////////////////////////////////////////////////
class pnlPlayer : public wxPanel 
{
	private:
	
	protected:
		wxGauge* m_gauge2;
		wxStaticText* txtDuration;
		
		// Virtual event handlers, overide them in your derived class
		virtual void PlayOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxButton* btnPlay;
		
		pnlPlayer( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 289,32 ), long style = wxTAB_TRAVERSAL ); 
		~pnlPlayer();
	
};

#endif //__AUDIOPLAYERPANEL_H__
