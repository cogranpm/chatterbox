#include "Publication.h"


Publication::Publication(void) : Publication(0, L"")
{

}

Publication::Publication(const unsigned long subjectId, const std::wstring& title) 
	: _subjectId(subjectId), _title(title), _publicationId(0), _type(0), comments()
{
	
}

Publication::Publication(const Publication &publication) {
	
	this->setPublicationId(publication.getPublicationId());
	this->setTitle(publication.getTitle());
	this->setType(publication.getType());
	this->setSubjectId(publication.getSubjectId());
	this->setComments(publication.getComments());
}


Publication::~Publication(void)
{

}

Publication& Publication::operator=(const Publication &publication)
{
	if(this != &publication)
	{
		this->setTitle(publication.getTitle());
		this->setSubjectId(publication.getSubjectId());
	}
	return *this;
}

void Publication::setTitle(const std::wstring &title) 
{
	std::wstring oldValue = this->_title;
	_title = title;
	FirePropertyChange(oldValue, _title);
}

void Publication::setSubjectId(unsigned long subjectId) 
{
	unsigned long oldValue = this->_subjectId;
	_subjectId = subjectId;
	FirePropertyChange(oldValue, _subjectId);
}

void Publication::setComments(const std::wstring &comments) 
{ 
	std::wstring oldValue = this->comments;
	this->comments = comments; 
	FirePropertyChange(oldValue, this->comments);
}

void Publication::setType(short type)
{
	short oldValue = _type;
	this->_type = type;
	FirePropertyChange(oldValue, _type);
}
