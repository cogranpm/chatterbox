#pragma once
#include "QuizRunQuestion.h"
#include "BaseEntity.h"

class QuizRunHeader : public BaseEntity
{
public:
	QuizRunHeader(unsigned long quizId);
	virtual ~QuizRunHeader(void);
	const unsigned long GetQuizRunHeaderId() {return _quizRunHeaderId;} const
	void SetQuizRunHeaderId(const unsigned long quizRunHeaderId) {_quizRunHeaderId = quizRunHeaderId;}
	const unsigned long GetQuizId() {return _quizId;} const
	void SetQuizId(const unsigned long quizId) {_quizId = quizId;}

	//QuizRunQuestion& GetCurrentQuizRunQuestion() {return _currentQuizRunQuestion;}


private:
	unsigned long _quizRunHeaderId;
	unsigned long _quizId;
	//QuizRunQuestion _currentQuizRunQuestion;
};

