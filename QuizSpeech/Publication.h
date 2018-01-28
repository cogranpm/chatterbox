#pragma once

#include "stdafx.h"

class Publication
{

private:
	unsigned long _subjectId;
	unsigned long _publicationId;
	std::wstring _title;
	short _type;
	bool _dirty;


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
	
	bool getDirty() { return _dirty;} 
	void setDirty(bool dirty) { _dirty = dirty;}
	

};

