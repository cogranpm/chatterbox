#pragma once

#include "stdafx.h"
#include "BaseEntity.h"

class Publication : public BaseEntity
{

private:
	unsigned long _subjectId;
	unsigned long _publicationId;
	std::wstring _title;
	short _type;
	std::wstring comments;

public:
	Publication(void);
	Publication(const unsigned long subjectId, const std::wstring& title);
	Publication(const Publication &obj);
	virtual ~Publication(void);
	Publication& operator=(const Publication &publication);
	bool operator==(const Publication  &publication)   {return _publicationId == publication.getPublicationId();}


	std::wstring getTitle() const {return _title;} 
	void setTitle(const std::wstring &title);

	unsigned long getPublicationId() const {return _publicationId;} 
	void setPublicationId(unsigned long publicationId) { _publicationId = publicationId;}

	unsigned long getSubjectId() const {return _subjectId;}  
	void setSubjectId(unsigned long subjectId);

	short getType() const {return _type;}  
	void setType(short type);

	void setComments(const std::wstring &comments) { this->comments = comments; }
	const std::wstring& getComments() const { return comments; }

};

