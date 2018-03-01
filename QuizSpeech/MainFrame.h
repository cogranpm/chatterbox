///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 28 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/dataview.h>
#include <wx/splitter.h>
#include <wx/aui/auibook.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_QUIT 1000
#define wxID_ADD_SHELF 1001
#define wxID_DELETE_SHELF 1002
#define wxID_EDIT_SHELF 1003
#define wxID_ADDPUBLICATION 1004

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menubar1;
		wxMenu* menuFile;
		wxStatusBar* m_statusBar1;
		wxAuiNotebook* m_auiShelf;
		wxPanel* m_panelNotes;
		wxSplitterWindow* m_splitter1;
		wxPanel* pnlShelf;
		wxPanel* pnlShelfHeader;
		wxStaticText* m_staticText5;
		wxButton* m_btnAddShelf;
		wxButton* m_btnDeleteShelf;
		wxButton* m_btnEditShelf;
		wxPanel* pnlShelfList;
		wxDataViewListCtrl* m_dvlShelf;
		wxDataViewColumn* colShelfIndex;
		wxDataViewColumn* m_dvlcShelfName;
		wxPanel* pnlShelfChildren;
		wxSplitterWindow* m_splitter2;
		wxPanel* pnlSubject;
		wxPanel* pnlSubjectHeader;
		wxStaticText* m_staticText7;
		wxButton* btnAddSubject;
		wxButton* btnDeleteSubject;
		wxButton* btnEditSubject;
		wxPanel* pnlSubjectList;
		wxDataViewListCtrl* m_lstSubject;
		wxDataViewColumn* colSubjectIndex;
		wxDataViewColumn* m_lstSubjectColTitle;
		wxPanel* pnlPublication;
		wxPanel* pnlPublicationHeader;
		wxStaticText* m_staticText6;
		wxButton* btnAddPublication;
		wxButton* btnDeletePublication;
		wxButton* btnEditPublication;
		wxPanel* pnlPublicationList;
		wxDataViewListCtrl* lstPublication;
		wxDataViewColumn* colPublicationIndex;
		wxDataViewColumn* lstPublicationColTitle;
		
		// Virtual event handlers, overide them in your derived class
		virtual void menuFileQuitOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNotebookPageChanged( wxAuiNotebookEvent& event ) { event.Skip(); }
		virtual void OnNotebookPageClose( wxAuiNotebookEvent& event ) { event.Skip(); }
		virtual void AddShelfOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void DeleteShelfOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void EditShelfOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnShelfColumnSort( wxDataViewEvent& event ) { event.Skip(); }
		virtual void OnShelfItemActivated( wxDataViewEvent& event ) { event.Skip(); }
		virtual void OnShelfSelectionChanged( wxDataViewEvent& event ) { event.Skip(); }
		virtual void AddSubjectOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void DeleteSubjectOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void EditSubjectOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSubjectColumnSort( wxDataViewEvent& event ) { event.Skip(); }
		virtual void OnSubjectItemActivated( wxDataViewEvent& event ) { event.Skip(); }
		virtual void SubjectOnSelectionChanged( wxDataViewEvent& event ) { event.Skip(); }
		virtual void AddPublicationOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void AddPublicationOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void DeletePublicationOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void DeletePublicationOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void EditPublicationOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void EditPublicationOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnPublicationColumnSort( wxDataViewEvent& event ) { event.Skip(); }
		virtual void OnPublicationItemActivated( wxDataViewEvent& event ) { event.Skip(); }
		virtual void PublicationSelectionChanged( wxDataViewEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Main Frame"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1133,716 ), long style = wxDEFAULT_FRAME_STYLE|wxMAXIMIZE|wxTAB_TRAVERSAL, const wxString& name = wxT("MainFrame") );
		
		~MainFrame();
		
		void m_splitter1OnIdle( wxIdleEvent& )
		{
			m_splitter1->SetSashPosition( 248 );
			m_splitter1->Disconnect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::m_splitter1OnIdle ), NULL, this );
		}
		
		void m_splitter2OnIdle( wxIdleEvent& )
		{
			m_splitter2->SetSashPosition( 0 );
			m_splitter2->Disconnect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::m_splitter2OnIdle ), NULL, this );
		}
	
};

#endif //__MAINFRAME_H__
