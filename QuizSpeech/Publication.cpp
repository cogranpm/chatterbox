#include "Publication.h"


Publication::Publication(void) : Publication(0, L"")
{

}

Publication::Publication(const unsigned long subjectId, const std::wstring& title) : _subjectId(subjectId), _title(title), _publicationId(0), _type(0), _dirty(false)
{
	
}

Publication::Publication(const Publication &publication) {
	
	this->setTitle(publication.getTitle());
	this->setSubjectId(publication.getSubjectId());
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
	if(title != this->_title)
	{
		_dirty = true;
	}
	_title = title;
}

void Publication::setSubjectId(unsigned long subjectId) 
{
	if(subjectId != this->_subjectId)
	{
		_dirty = true;
	}
	_subjectId = subjectId;
}

void Publication::setType(short type)
{
	if(type != this->_type)
	{
		_dirty = true;
	}
	this->_type = type;
}
