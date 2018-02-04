#include "StdAfx.h"
#include "QuizRunHeader.h"


QuizRunHeader::QuizRunHeader() : QuizRunHeader(0)
{
}


QuizRunHeader::QuizRunHeader(unsigned long quizId) : _quizId(quizId), _quizRunHeaderId(0), isComplete(false), quiz()
{
}


QuizRunHeader::~QuizRunHeader(void)
{
}


