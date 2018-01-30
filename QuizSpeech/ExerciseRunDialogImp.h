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
#include "AudioPlayerWrapperClient.h"
#include "AudioPlayerWrapper.h"

/** Implementing ExerciseRunDialog */
class ExerciseRunDialogImp : public ExerciseRunDialog, AudioPlayerWrapperClient
{
	wxIcon deleteIcon;
	ExerciseRunViewModel viewModel;
	void RenderQuestions();
	void SetQuestion(QuizRunQuestion& question);
	QuizRunQuestion* GetCurrentQuestion();
	AudioPlayerWrapper questionPlayer;
	AudioPlayerWrapper answerPlayer;
	AudioPlayerWrapper correctAnswerPlayer;
	
	protected:
		// Handlers for ExerciseRunDialog events.
		void CloseOnButtonClick( wxCommandEvent& event );
		void OnInitDialog(wxInitDialogEvent& event);
		void RecordOnButtonClick(wxCommandEvent& event);
		void AudioPlayOnButtonClick(wxCommandEvent& event);
		void SkipOnButtonClick(wxCommandEvent& event);
		void PlayCorrectAnswerOnButtonClick(wxCommandEvent& event);
		void EvaluationOnRadioBox(wxCommandEvent& event);
		void NextOnButtonClick(wxCommandEvent& event);
		void PlayAnswerOnButtonClick(wxCommandEvent& event);

	public:
		/** Constructor */
		ExerciseRunDialogImp( wxWindow* parent, unsigned long quizId );
	//// end generated class members
		void PlayCompleted();
};

#endif // __ExerciseRunDialogImp__
