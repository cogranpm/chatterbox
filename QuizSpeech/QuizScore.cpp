#include "stdafx.h"
#include "QuizScore.h"


QuizScore::QuizScore(void) : _numAnswered(0), _numIncorrect(0), _numCorrect(0), _totalQuestions(0), _numSkipped(0)
{
}


QuizScore::~QuizScore(void)
{
}

int QuizScore::GetScore() 
{ 
	float result = ((float)_numCorrect / (float)_totalQuestions);
	result *= 100;
	return std::ceil(result);
}

