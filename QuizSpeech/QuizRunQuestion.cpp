#include "StdAfx.h"
#include "QuizRunQuestion.h"


QuizRunQuestion::QuizRunQuestion() :
	_quizRunHeaderId(0), _quizRunQuestionId(0), question(), _answerText(L""),
	_answerFile(L""), _isCorrect(false), isAnswered(false)
{

}

QuizRunQuestion::QuizRunQuestion(Question& question) :
	_quizRunHeaderId(0), _quizRunQuestionId(0), question(question), _answerText(L""),
	_answerFile(L""), _isCorrect(false), isAnswered(false)
{
}


QuizRunQuestion::~QuizRunQuestion(void)
{
}
