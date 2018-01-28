#include "Answer.h"



Answer::Answer() : Answer(0)
{
}

Answer::Answer(unsigned long questionId) : questionId(questionId), answerId(0)
{

}

Answer::~Answer()
{
}

void Answer::SetAnswerText(const std::wstring& answerText)
{ 
	std::wstring oldValue = this->answerText;
	this->answerText = answerText; 
	FirePropertyChange(oldValue, this->answerText);
}

void Answer::SetAnswerFile(const std::wstring& audioFile)
{ 
	std::wstring oldValue = this->answerFile;
	answerFile = audioFile; 
	FirePropertyChange(oldValue, this->answerFile);
}
