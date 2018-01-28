#pragma once
#include "BaseEntity.h"
#include "Question.h"

class QuizRunQuestion : public BaseEntity
{
public:
	QuizRunQuestion(Question& question);
	~QuizRunQuestion(void);

	const unsigned long GetQuizRunHeaderId() {return _quizRunHeaderId;} const
	void SetQuizRunHeaderId(const unsigned long quizRunHeaderId) {_quizRunHeaderId = quizRunHeaderId;}

	const unsigned long GetQuizRunQuestionId() {return _quizRunQuestionId;} const
	void SetQuizRunQuestionId(const unsigned long quizRunQuestionId) {_quizRunQuestionId = quizRunQuestionId;}

	std::wstring GetAnswerText() { return _answerText;}
	void SetAnswerText(std::wstring answerText) {_answerText = answerText;}

	std::wstring GetAnswerFile() { return _answerFile;}
	void SetAnswerFile(std::wstring answerFile) {_answerFile = answerFile;}
	
	bool GetIsCorrect() {return _isCorrect;}
	void SetIsCorrect(bool isCorrect) {_isCorrect = isCorrect;}

	Question& GetQuestion() { return question; }
	void SetQuestion(Question& question) { this->question = question; }

private:
	unsigned long _quizRunQuestionId;
	unsigned long _quizRunHeaderId;
	Question question;
	
	std::wstring _answerText;
	std::wstring _answerFile;
	bool _isCorrect;


};

