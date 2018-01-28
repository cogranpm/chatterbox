#include "stdafx.h"
#include "Question.h"



Question::Question(const unsigned long quizId) : quizId(quizId), questionId(0), answer()
{

}

Question::Question() : Question(0)
{

}

void Question::SetQuestionText(const std::wstring& questionText) 
{ 
	std::wstring oldValue = this->questionText;
	this->questionText = questionText; 
	FirePropertyChange(oldValue, this->questionText);
}

void Question::SetQuestionFile(const std::wstring& audioFile) 
{ 
	std::wstring oldValue = this->questionFile;
	this->questionFile = audioFile;  
	FirePropertyChange(oldValue, this->questionFile);
}