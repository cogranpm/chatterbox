#include "ExerciseViewModel.h"



ExerciseViewModel::ExerciseViewModel(Publication* publication) :
	ExerciseViewModel(publication, 0)
{
}

ExerciseViewModel::ExerciseViewModel(Publication* publication, const unsigned long quizId) :
	publication(publication),
	quiz(publication->getPublicationId()),
	questionList(new boost::ptr_vector<Question>()),
	currentQuestion(nullptr),
	topicList()
{
	quiz.SetQuizId(quizId);
}


ExerciseViewModel::~ExerciseViewModel()
{
	if (questionList != nullptr)
	{
		delete questionList;
		questionList = nullptr;
	}
}


void ExerciseViewModel::ResetNewQuestion()
{
	newQuestion.SetQuestionFile(L"");
	newQuestion.SetQuestionText(L"");
	newQuestion.SetQuestionId(0);
	newQuestion.GetAnswer()->SetAnswerFile(L"");
	newQuestion.GetAnswer()->SetAnswerText(L"");
	newQuestion.GetAnswer()->SetAnswerId(0);
}

bool ExerciseViewModel::IsDirty()
{
	if (GetQuiz().GetDirty())
	{
		return true;
	}
	if (GetCurrentQuestion() != nullptr)
	{
		if (GetCurrentQuestion()->GetDirty() || GetCurrentQuestion()->GetAnswer()->GetDirty())
		{
			return true;
		}
	}
	return false;
	
}