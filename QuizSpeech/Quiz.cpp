#include "stdafx.h"
#include "Quiz.h"


Quiz::Quiz(const unsigned long publicationId) : Quiz(publicationId, L"")
{

}

Quiz::Quiz(const unsigned long publicationId, const std::wstring& name) : publicationId(publicationId), name(name), topicId(0), quizId(0)
{
	
}


void Quiz::SetQuizId(const unsigned long quizId)
{
	this->quizId = quizId;
}

void Quiz::SetName(const std::wstring& name)
{ 
	std::wstring oldValue = this->name;
	this->name = name; 
	FirePropertyChange(oldValue, name);
}

void Quiz::SetTopicId(const unsigned long topicId) 
{ 
	unsigned long oldValue = this->topicId;
	this->topicId = topicId; 
	FirePropertyChange(oldValue, this->topicId);
}

