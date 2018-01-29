///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 28 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __EXERCISERUNDIALOG_H__
#define __EXERCISERUNDIALOG_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/radiobox.h>
#include <wx/panel.h>
#include <wx/dataview.h>
#include <wx/splitter.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ExerciseRunDialog
///////////////////////////////////////////////////////////////////////////////
class ExerciseRunDialog : public wxDialog 
{
	private:
	
	protected:
		wxBoxSizer* dialogSizer;
		wxStaticText* lblQuizName;
		wxSplitterWindow* listSplitter;
		wxPanel* pnlQuestion;
		wxBoxSizer* szQuestion;
		wxBoxSizer* bSizer10;
		wxStaticText* lblQuestion;
		wxButton* btnAudioPlay;
		wxButton* btnSkip;
		wxStaticText* lblAnswer;
		wxButton* btnRecord;
		wxButton* btnPlayAnswer;
		wxTextCtrl* txtQuestion;
		wxTextCtrl* txtAnswer;
		wxStaticText* m_staticText6;
		wxRadioBox* rdoEvaluation;
		wxButton* btnNext;
		wxButton* btnPlayCorrectAnswer;
		wxTextCtrl* txtCorrectAnswer;
		wxStaticText* lblStatus;
		wxPanel* pnlList;
		wxStaticText* m_staticText2;
		wxDataViewListCtrl* lstQuestions;
		wxDataViewColumn* colIndex;
		wxDataViewColumn* colQuestion;
		wxDataViewColumn* colAnswered;
		wxDataViewColumn* colResult;
		wxButton* btnClose;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInitDialog( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void AudioPlayOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void SkipOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void RecordOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void EvaluationOnRadioBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void NextOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void PlayCorrectAnswerOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void CloseOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		ExerciseRunDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Run Exercise"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 912,666 ), long style = wxCAPTION|wxCLOSE_BOX|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER ); 
		~ExerciseRunDialog();
		
		void listSplitterOnIdle( wxIdleEvent& )
		{
			listSplitter->SetSashPosition( 547 );
			listSplitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( ExerciseRunDialog::listSplitterOnIdle ), NULL, this );
		}
	
};

#endif //__EXERCISERUNDIALOG_H__
