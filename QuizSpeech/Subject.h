#pragma once
#include "BaseEntity.h"

class Subject : public BaseEntity
{
public:
	Subject(void);
	Subject(std::wstring title);
	Subject(const unsigned long shelfId, const std::wstring& title);
	Subject(const Subject &obj);
	virtual ~Subject(void);
	Subject& operator=(const Subject &subject);
	bool operator==(const Subject  &subject)   {return _subjectId == subject.getSubjectId();}

	void setTitle(const std::wstring &title);
	const std::wstring& getTitle()const {return _title;} 

	unsigned long getSubjectId() const {return _subjectId;} 
	void setSubjectId(unsigned long subjectId) { _subjectId = subjectId;}

	unsigned long getShelfId() const {return _shelfId;} 
	void setShelfId(unsigned long shelfId) { _shelfId = shelfId;}
	
	void setComments(const std::wstring &comments);
	const std::wstring& getComments() const { return comments; } 

private:
	unsigned long _subjectId;
	std::wstring _title;
	unsigned long _shelfId;
	std::wstring comments;
};

