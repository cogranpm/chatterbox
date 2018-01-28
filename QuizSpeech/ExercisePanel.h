///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec  8 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __EXERCISEPANEL_H__
#define __EXERCISEPANEL_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/infobar.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/valtext.h>
#include <wx/combobox.h>
#include <wx/gbsizer.h>
#include <wx/button.h>
#include <wx/dataview.h>
#include <wx/panel.h>
#include <wx/splitter.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ExercisePanel
///////////////////////////////////////////////////////////////////////////////
class ExercisePanel : public wxPanel 
{
	private:
	
	protected:
		wxStaticText* lblExercise;
		wxInfoBar* quizMessage;
		wxStaticText* lblName;
		wxTextCtrl* txtName;
		wxStaticText* lblTopic;
		wxComboBox* cboTopics;
		wxStaticText* lblQuestions;
		wxSplitterWindow* m_splitter1;
		wxPanel* pnlGrid;
		wxButton* btnAddQuestion;
		wxButton* btnDeleteQuestion;
		wxDataViewListCtrl* lstQuestions;
		wxDataViewColumn* colIndex;
		wxDataViewColumn* colQuestion;
		wxDataViewColumn* colAnswer;
		wxPanel* pnlEdit;
		wxBoxSizer* sizerEdit;
		wxBoxSizer* sizerQuestionHeader;
		wxStaticText* lblQuestion;
		wxButton* btnRecordQuestion;
		wxButton* btnClearQuestion;
		wxBoxSizer* szQuestionAudioPlayer;
		wxInfoBar* questionMessage;
		wxTextCtrl* questionText;
		wxBoxSizer* sizerAnswerHeader;
		wxStaticText* lblAnswer;
		wxButton* btnRecordAnswer;
		wxButton* btnClearAnswer;
		wxBoxSizer* szAnswerAudioPlayer;
		wxInfoBar* answerMessage;
		wxTextCtrl* answerText;
		wxButton* btnCancel;
		wxButton* btnApply;
		
		// Virtual event handlers, overide them in your derived class
		virtual void ExercisePanelOnInitDialog( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void NameOnKillFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void NameOnSetFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void NameOnText( wxCommandEvent& event ) { event.Skip(); }
		virtual void TopicsOnCombobox( wxCommandEvent& event ) { event.Skip(); }
		virtual void AddQuestionOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void DeleteQuestionOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void DeleteQuestionOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void QuestionsItemActivated( wxDataViewEvent& event ) { event.Skip(); }
		virtual void QuestionsSelectionChanged( wxDataViewEvent& event ) { event.Skip(); }
		virtual void RecordQuestionOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void ClearQuestionOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void QuestionOnText( wxCommandEvent& event ) { event.Skip(); }
		virtual void RecordAnswerOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void ClearAnswerOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void AnswerOnText( wxCommandEvent& event ) { event.Skip(); }
		virtual void CancelOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void CancelOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void ApplyOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void ApplyOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		
	
	public:
		wxString dataName; 
		
		ExercisePanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 873,659 ), long style = wxTAB_TRAVERSAL ); 
		~ExercisePanel();
		
		void m_splitter1OnIdle( wxIdleEvent& )
		{
			m_splitter1->SetSashPosition( 350 );
			m_splitter1->Disconnect( wxEVT_IDLE, wxIdleEventHandler( ExercisePanel::m_splitter1OnIdle ), NULL, this );
		}
	
};

#endif //__EXERCISEPANEL_H__
