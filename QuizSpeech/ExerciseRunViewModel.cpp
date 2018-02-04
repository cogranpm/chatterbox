#include "ExerciseRunViewModel.h"

ExerciseRunViewModel::ExerciseRunViewModel(QuizRunHeader header) : header(header),
runQuestions(), currentQuestionIndex(0)
{
}


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

QuizRunQuestion* ExerciseRunViewModel::GetCurrentQuestion()
{
	return &runQuestions.at(currentQuestionIndex);
}

bool ExerciseRunViewModel::IsAnswered()
{
	QuizRunQuestion* question = GetCurrentQuestion();
	return (question->GetQuizRunQuestionId() > 0 || 
		(!question->GetAnswerFile().empty()) || (!question->GetAnswerText().empty()));
}