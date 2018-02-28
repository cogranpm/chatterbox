///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 28 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __PUBLICATIONPANEL_H__
#define __PUBLICATIONPANEL_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/valtext.h>
#include <wx/combobox.h>
#include <wx/button.h>
#include <wx/gbsizer.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/dataview.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/wrapsizer.h>
#include <wx/splitter.h>
#include <wx/notebook.h>

///////////////////////////////////////////////////////////////////////////

#define wxPublicationPanel 1000

///////////////////////////////////////////////////////////////////////////////
/// Class pnlMain
///////////////////////////////////////////////////////////////////////////////
class pnlMain : public wxPanel 
{
	private:
	
	protected:
		wxPanel* panelPublication;
		wxStaticText* m_staticText1;
		wxTextCtrl* txtTitle;
		wxStaticText* m_staticText2;
		wxComboBox* cboType;
		wxButton* btnApply;
		wxButton* btnCancel;
		wxSplitterWindow* splitterTopic;
		wxPanel* panelTopics;
		wxStaticText* m_staticText3;
		wxButton* btnAddTopic;
		wxButton* btnDeleteTopic;
		wxButton* btnEditTopic;
		wxDataViewListCtrl* lstTopics;
		wxDataViewColumn* colTopicIndex;
		wxDataViewColumn* colTopicTitle;
		wxPanel* panelTopicChildren;
		wxNotebook* notebookChildren;
		wxPanel* panelTopicChildNote;
		wxPanel* panelNotes;
		wxButton* btnAddNote;
		wxButton* btnDeleteNote;
		wxButton* btnEditNote;
		wxButton* btnPlayAll;
		wxButton* btnPlay;
		wxButton* btnStop;
		wxDataViewListCtrl* lstNotes;
		wxDataViewColumn* colNoteIndex;
		wxDataViewColumn* colNoteTitle;
		wxDataViewColumn* colNoteDescription;
		wxDataViewColumn* colNoteSegmentCount;
		wxDataViewColumn* colNoteSegmentTitle;
		wxDataViewColumn* colNotesCreatedDate;
		wxPanel* panelTopicChildQuiz;
		wxButton* btnAddQuiz;
		wxButton* btnDeleteQuiz;
		wxButton* btnEditQuiz;
		wxButton* btnRunQuiz;
		wxSplitterWindow* m_splitter2;
		wxPanel* panelExercise;
		wxDataViewListCtrl* lstQuiz;
		wxDataViewColumn* colQuizIndex;
		wxDataViewColumn* colQuizName;
		wxPanel* panelRun;
		wxStaticText* lblExam;
		wxButton* btnViewQuizRun;
		wxButton* btnDeleteQuizRun;
		wxDataViewListCtrl* lstQuizRun;
		wxDataViewColumn* colQuizRunIndex;
		wxDataViewColumn* colQuizRunDate;
		wxDataViewColumn* colQuizRunComplete;
		wxDataViewColumn* colQuizRunName;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInitDialog( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void TitleOnText( wxCommandEvent& event ) { event.Skip(); }
		virtual void TypeOnCombobox( wxCommandEvent& event ) { event.Skip(); }
		virtual void ApplyOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void ApplyOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void CancelOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void CancelOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void AddTopicOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void DeleteTopicOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void DeleteTopicOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void EditTopicOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void EditTopicOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnTopicItemActivated( wxDataViewEvent& event ) { event.Skip(); }
		virtual void OnTopicSelectionChanged( wxDataViewEvent& event ) { event.Skip(); }
		virtual void AddNoteOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void AddNoteOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void DeleteNoteOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void DeleteNoteOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void EditNoteOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void EditNoteOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void PlayAllOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void PlayOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void PlayOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void StopOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void NotesOnItemActivated( wxDataViewEvent& event ) { event.Skip(); }
		virtual void NotesOnSelectionChanged( wxDataViewEvent& event ) { event.Skip(); }
		virtual void AddQuizOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void AddQuizOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void DeleteQuizOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void DeleteQuizOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void EditQuizOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void EditQuizOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void RunQuizOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void RunQuizOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void QuizOnItemActivated( wxDataViewEvent& event ) { event.Skip(); }
		virtual void QuizOnSelectionChanged( wxDataViewEvent& event ) { event.Skip(); }
		virtual void ViewQuizRunOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void ViewQuizRunOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void DeleteQuizRunOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void DeleteQuizRunOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void QuizRunOnItemActivated( wxDataViewEvent& event ) { event.Skip(); }
		virtual void QuizRunOnSelectionChanged( wxDataViewEvent& event ) { event.Skip(); }
		
	
	public:
		wxString _title; 
		
		pnlMain( wxWindow* parent, wxWindowID id = wxPublicationPanel, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1010,827 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxT("PublicationPanel") ); 
		~pnlMain();
		
		void splitterTopicOnIdle( wxIdleEvent& )
		{
			splitterTopic->SetSashPosition( 255 );
			splitterTopic->Disconnect( wxEVT_IDLE, wxIdleEventHandler( pnlMain::splitterTopicOnIdle ), NULL, this );
		}
		
		void m_splitter2OnIdle( wxIdleEvent& )
		{
			m_splitter2->SetSashPosition( 0 );
			m_splitter2->Disconnect( wxEVT_IDLE, wxIdleEventHandler( pnlMain::m_splitter2OnIdle ), NULL, this );
		}
	
};

#endif //__PUBLICATIONPANEL_H__
