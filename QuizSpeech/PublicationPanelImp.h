#ifndef __PublicationPanelImp__
#define __PublicationPanelImp__

#include "PublicationViewModel.h"

/**
@file
Subclass of pnlMain, which is generated by wxFormBuilder.
*/

#include "PublicationPanel.h"
#include "NoteDialogImp.h"

//// end generated include

#include "NoteListAudioPlayer.h"
#include "NoteAudioPlayer.h"

/** Implementing pnlMain */
class PublicationPanelImp : public pnlMain
{

	private:

		wxDataViewListStore* _topicModel;
		wxDataViewListStore* _noteModel;
		wxDataViewListStore* _quizModel;
		wxDataViewListStore* quizRunModel;
		PublicationViewModel* _viewModel;
		NoteListAudioPlayer noteListAudioPlayer;
		NoteAudioPlayer noteAudioPlayer;
		void RenderTopics(Topic* topic);
		void EditTopic(Topic* topic);
		void OnSelectTopic(Topic* topic);
		void RenderNotes(Note* note);
		void OnSelectNote(Note* note);
		void BindModel();
		void OnAfterNoteDialogClosed(NoteDialogImp& dialog, Note* note);
		void OnEditNote();
		void RenderExercises(Quiz* quiz);
		void OnSelectExercise(Quiz* quiz);
		void OnEditExercise();
		void RenderQuizRuns();
		void SetupSpeechHandlers();
	protected:
		void OnInitDialog( wxInitDialogEvent& event );
		void TitleOnText( wxCommandEvent& event );
		void TypeOnCombobox( wxCommandEvent& event );
		void ApplyOnButtonClick( wxCommandEvent& event );
		void ApplyOnUpdateUI( wxUpdateUIEvent& event ) ;
		void CancelOnButtonClick( wxCommandEvent& event );
		void CancelOnUpdateUI( wxUpdateUIEvent& event ) ;
		 
		/* topics */
		void AddTopicOnButtonClick( wxCommandEvent& event );
		void DeleteTopicOnButtonClick( wxCommandEvent& event );
		void EditTopicOnButtonClick( wxCommandEvent& event );
		void OnTopicItemActivated( wxDataViewEvent& event );
		void OnTopicSelectionChanged( wxDataViewEvent& event );
		void EditTopicOnUpdateUI( wxUpdateUIEvent& event );
		void DeleteTopicOnUpdateUI( wxUpdateUIEvent& event );

		/* notes */
		void AddNoteOnButtonClick( wxCommandEvent& event );
		void AddNoteOnUpdateUI( wxUpdateUIEvent& event );
		void DeleteNoteOnButtonClick( wxCommandEvent& event );
		void DeleteNoteOnUpdateUI( wxUpdateUIEvent& event );
		void EditNoteOnButtonClick( wxCommandEvent& event );
		void EditNoteOnUpdateUI( wxUpdateUIEvent& event );
		void NotesOnItemActivated( wxDataViewEvent& event );
		void NotesOnSelectionChanged( wxDataViewEvent& event );
		void PlayOnButtonClick(wxCommandEvent& event);
		void PlayAllOnButtonClick(wxCommandEvent& event);
		void StopOnButtonClick(wxCommandEvent& event);
		void PlayOnUpdateUI(wxUpdateUIEvent& event);

		/* exercises */
		void AddQuizOnButtonClick(wxCommandEvent& event);
		void AddQuizOnUpdateUI(wxUpdateUIEvent& event);
		void DeleteQuizOnButtonClick(wxCommandEvent& event);
		void DeleteQuizOnUpdateUI(wxUpdateUIEvent& event);
		void EditQuizOnButtonClick(wxCommandEvent& event);
		void EditQuizOnUpdateUI(wxUpdateUIEvent& event);
		void QuizOnItemActivated(wxDataViewEvent& event);
		void QuizOnSelectionChanged(wxDataViewEvent& event);
		void RunQuizOnButtonClick(wxCommandEvent& event);
		void RunQuizOnUpdateUI(wxUpdateUIEvent& event);

		/* quiz run */
		void ViewQuizRunOnButtonClick(wxCommandEvent& event);
		void ViewQuizRunOnUpdateUI(wxUpdateUIEvent& event);
		void DeleteQuizRunOnButtonClick(wxCommandEvent& event);
		void DeleteQuizRunOnUpdateUI(wxUpdateUIEvent& event);
		void QuizRunOnItemActivated(wxDataViewEvent& event);
		void QuizRunOnSelectionChanged(wxDataViewEvent& event);


	public:
		/** Constructor */
		PublicationPanelImp( wxWindow* parent, Publication* publication );
		~PublicationPanelImp( );
		void Refresh();
	//// end generated class members
	
};

#endif // __PublicationPanelImp__
