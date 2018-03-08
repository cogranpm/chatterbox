#pragma once

#include "stdafx.h"
#include "BaseEntity.h"

class Topic : public BaseEntity
{
public:
	Topic(void);
	~Topic(void);
	Topic(const unsigned long publicationId, const std::wstring& name);
	Topic& operator=(const Topic &topic);
	bool operator==(const Topic  &topic)   {return _topicId == topic.getTopicId();}

	unsigned long getTopicId() const {return _topicId;}
	void setTopicId(unsigned long topicId){_topicId = topicId;}

	void setName(const std::wstring& name);
	const std::wstring& getName() const {return _name;}

	void setComments(const std::wstring& comments);
	const std::wstring& getComments() const { return comments; }

	unsigned long getPublicationId() const {return _publicationId;}
	void setPublicationId(unsigned long publicationId);
	
private:
	unsigned long _topicId;
	unsigned long _publicationId;
	std::wstring _name;
	std::wstring comments;

};

