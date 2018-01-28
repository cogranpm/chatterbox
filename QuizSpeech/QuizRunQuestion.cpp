#include "StdAfx.h"
#include "QuizRunQuestion.h"


QuizRunQuestion::QuizRunQuestion(Question& question) :
	_quizRunHeaderId(0), _quizRunQuestionId(0), question(question), _answerText(L""),
	_answerFile(L""), _isCorrect(false)
{
}


QuizRunQuestion::~QuizRunQuestion(void)
{
}
