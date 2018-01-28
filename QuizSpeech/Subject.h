#pragma once

class Subject
{
public:
	Subject(void);
	Subject(std::wstring title);
	Subject(const unsigned long shelfId, const std::wstring& title);
	Subject(const Subject &obj);
	virtual ~Subject(void);
	Subject& operator=(const Subject &subject);
	bool operator==(const Subject  &subject)   {return _subjectId == subject.getSubjectId();}

	void setTitle(const std::wstring &title) {_title = title;}
	std::wstring getTitle()const {return _title;} const

	unsigned long getSubjectId() const {return _subjectId;} const
	void setSubjectId(unsigned long subjectId) { _subjectId = subjectId;}

	unsigned long getShelfId() const {return _shelfId;} const
	void setShelfId(unsigned long shelfId) { _shelfId = shelfId;}
	
private:
	unsigned long _subjectId;
	std::wstring _title;
	unsigned long _shelfId;
};

