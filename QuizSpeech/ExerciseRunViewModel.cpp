#include "ExerciseRunViewModel.h"



ExerciseRunViewModel::ExerciseRunViewModel(unsigned long quizId) : header(quizId),
runQuestions(), currentQuestionIndex(0)
{
}


ExerciseRunViewModel::~ExerciseRunViewModel()
{
}

void ExerciseRunViewModel::CreateRunQuestions()
{
	for (int i = 0; i < questions.size(); ++i)
	{
		Question question = questions.at(i);
		QuizRunQuestion* runQuestion = new QuizRunQuestion(question);
		runQuestion->SetQuizRunHeaderId(header.GetQuizRunHeaderId());
		runQuestions.push_back(runQuestion);
	}
}