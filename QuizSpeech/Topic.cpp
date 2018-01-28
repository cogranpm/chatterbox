#include "Topic.h"


Topic::Topic(void)
{
}

Topic::Topic(const unsigned long publicationId, const std::wstring& name) : _publicationId(publicationId), _name(name)
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
