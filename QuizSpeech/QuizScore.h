#pragma once
class QuizScore
{
public:
	QuizScore(void);
	~QuizScore(void);

	int GetNumAnswered() {return _numAnswered;}
	int GetNumCorrect() { return _numCorrect;}
	int GetNumIncorrect() { return _numAnswered - _numCorrect;}
	int GetNumSkipped() {return _totalQuestions - _numAnswered;}
	int GetScore();

	void SetNumAnswered(int numAnswered) { _numAnswered = numAnswered;}
	void SetNumCorrect(int numCorrect) {_numCorrect = numCorrect;}
	void SetTotalQuestions(int totalQuestions) {_totalQuestions = totalQuestions;}
private:
	int _totalQuestions;
	int _numAnswered;
	int _numCorrect;
	int _numIncorrect;
	int _numSkipped;
	
};

