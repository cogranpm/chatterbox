#ifndef __ExerciseRunDialogImp__
#define __ExerciseRunDialogImp__

/**
@file
Subclass of ExerciseRunDialog, which is generated by wxFormBuilder.
*/

#include "ExerciseRunDialog.h"

//// end generated include

#include "Quiz.h"
#include "ExerciseRunViewModel.h"
#include "ApplicationImages.h"
//#include "AudioPlayerWrapperClient.h"
//#include "AudioPlayerWrapper.h"
//#include "AudioPlayerPanelHelper.h"
#include "AudioPlayerPanelImp.h"
#include "AudioPlayer.h"

/** Implementing ExerciseRunDialog */
class ExerciseRunDialogImp : public ExerciseRunDialog//, AudioPlayerWrapperClient
{
	wxIcon deleteIcon;
	wxIcon taskCompleteIcon;
	wxIcon taskRejectIcon;
	ExerciseRunViewModel viewModel;
	void RenderQuestions();
	void SetQuestion(QuizRunQuestion& question);
	
	AudioPlayer playerQuestion;
	AudioPlayerPanelImp* playerPanelQuestion;

	AudioPlayer playerAnswer;
	AudioPlayerPanelImp* playerPanelAnswer;
	AudioPlayer playerCorrectAnswer;
	AudioPlayerPanelImp* playerPanelCorrectAnswer;
	
	bool Save();
	bool Validate();
	void GoNextQuestion();
	bool MoreQuestions();
	bool IsFirstQuestion();
	void RenderComplete();
	void ShowComplete();
	void HideComplete();
	void PlayQuestion();
	void Init();
	QuizRunQuestion* FindSelectedQuizRunQuestion(long questionId);

	protected:
		// Handlers for ExerciseRunDialog events.
		void CloseOnButtonClick( wxCommandEvent& event );
		void OnInitDialog(wxInitDialogEvent& event);
		void RecordOnButtonClick(wxCommandEvent& event);
		void SkipOnButtonClick(wxCommandEvent& event);
		void EvaluationOnRadioBox(wxCommandEvent& event);
		void NextOnButtonClick(wxCommandEvent& event);
		void QuestionsSelectionChanged(wxDataViewEvent& event);
	public:
		/** Constructor */
		ExerciseRunDialogImp(wxWindow* parent, QuizRunHeader& quizRunHeader);
		ExerciseRunDialogImp( wxWindow* parent, unsigned long quizId );
	//// end generated class members
		//void PlayCompleted();
};

#endif // __ExerciseRunDialogImp__
