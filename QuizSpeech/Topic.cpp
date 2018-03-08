#include "Topic.h"


Topic::Topic(void): Topic(0, L"")
{
}

Topic::Topic(const unsigned long publicationId, const std::wstring& name) : _publicationId(publicationId), _name(name), comments()
{

}

Topic::~Topic(void)
{
}


Topic& Topic::operator=(const Topic &topic)
{
	if(this != &topic)
	{
		this->setName(topic.getName());
		this->setPublicationId(topic.getPublicationId());
	}
	return *this;
}

void Topic::setPublicationId(unsigned long publicationId)
{ 
	unsigned long oldValue = this->_publicationId;
	_publicationId = publicationId; 
	FirePropertyChange(oldValue, this->_publicationId);
}

void Topic::setName(const std::wstring& name) 
{
	std::wstring oldValue = this->_name;
	_name = name; 
	FirePropertyChange(oldValue, this->_name);
}

void Topic::setComments(const std::wstring& comments) 
{
	std::wstring oldValue = this->comments;
	this->comments = comments; 
	FirePropertyChange(oldValue, this->comments);
}