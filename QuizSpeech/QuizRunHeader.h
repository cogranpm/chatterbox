#pragma once
#include "QuizRunQuestion.h"
#include "BaseEntity.h"
#include <wx/datetime.h>
#include "Quiz.h"

class QuizRunHeader : public BaseEntity
{
public:
	QuizRunHeader();
	QuizRunHeader(unsigned long quizId);
	virtual ~QuizRunHeader(void);
	const unsigned long GetQuizRunHeaderId() {return _quizRunHeaderId;} const
	void SetQuizRunHeaderId(const unsigned long quizRunHeaderId) {_quizRunHeaderId = quizRunHeaderId;}
	const unsigned long GetQuizId() {return _quizId;} const
	void SetQuizId(const unsigned long quizId) {_quizId = quizId;}

	//QuizRunQuestion& GetCurrentQuizRunQuestion() {return _currentQuizRunQuestion;}

	const wxDateTime& GetCreatedDate() const { return createdDate; }
	void SetCreatedDate(const wxDateTime &createdDate) { this->createdDate = createdDate; }
	bool GetIsComplete() { return isComplete; }
	void SetIsComplete(bool isComplete) { this->isComplete = isComplete; }

	Quiz& GetQuiz() { return quiz; }
private:
	unsigned long _quizRunHeaderId;
	unsigned long _quizId;
	wxDateTime createdDate;
	bool isComplete;
	Quiz quiz;
	//QuizRunQuestion _currentQuizRunQuestion;
};

