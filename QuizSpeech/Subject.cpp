#include "StdAfx.h"
#include "Subject.h"


Subject::Subject(void) : Subject(0, L"")
{
}


Subject::Subject(std::wstring title) :  Subject(0, title)
{

}

Subject::Subject(const unsigned long shelfId, const std::wstring& title) : _shelfId(shelfId), _title(title), _subjectId(0), comments()
{

}

Subject::Subject(const Subject &subject) {
	
	this->setTitle(subject.getTitle());
	this->setShelfId(subject.getShelfId());
}

Subject& Subject::operator=(const Subject &subject)
{
	if(this != &subject)
	{
		this->setTitle(subject.getTitle());
		this->setShelfId(subject.getShelfId());
	}
	return *this;
}



Subject::~Subject(void)
{
}




