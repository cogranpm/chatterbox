#include "ExerciseRunViewModel.h"

ExerciseRunViewModel::ExerciseRunViewModel(QuizRunHeader& header) : header(header),
runQuestions(), currentQuestionIndex(0)
{
}


ExerciseRunViewModel::ExerciseRunViewModel(const unsigned long& quizId) : header(quizId),
runQuestions(), currentQuestionIndex(0)
{
}


ExerciseRunViewModel::~ExerciseRunViewModel()
{
}

void ExerciseRunViewModel::CreateRunQuestions()
{
	if (header.GetQuizRunHeaderId() > 0)
	{
		/* is there anything to do? */
	}
	else
	{
		for (int i = 0; i < questions.size(); ++i)
		{
			Question question = questions.at(i);
			QuizRunQuestion* runQuestion = new QuizRunQuestion(question);
			runQuestion->SetQuizRunHeaderId(header.GetQuizRunHeaderId());
			runQuestions.push_back(runQuestion);
		}
	}
}

QuizRunQuestion* ExerciseRunViewModel::GetCurrentQuestion()
{
	return &runQuestions.at(currentQuestionIndex - 1);
}

bool ExerciseRunViewModel::IsAnswered()
{
	QuizRunQuestion* question = GetCurrentQuestion();
	return (question->GetQuizRunQuestionId() > 0 || 
		(!question->GetAnswerFile().empty()) || (!question->GetAnswerText().empty()));
}