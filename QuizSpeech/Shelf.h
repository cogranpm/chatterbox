#pragma once
#include "BaseEntity.h"

class Shelf : public BaseEntity
{
public:
	Shelf(void);
	Shelf(const std::wstring& title);
	Shelf(const unsigned long shelfId, const std::wstring& title);
	Shelf (const Shelf &obj);
	virtual ~Shelf(void);
	Shelf& operator=(const Shelf &shelf);
	bool operator==(const Shelf  &shelf)   {return _shelfId == shelf.getShelfId();}

	void setTitle(const std::wstring &title) {_title = title;}
	const std::wstring& getTitle() const {return _title;} 

	unsigned long getShelfId() const {return _shelfId;} 
	void setShelfId(const unsigned long shelfId){ _shelfId = shelfId;}

	void setComments(const std::wstring &comments) { this->comments = comments; }
	const std::wstring& getComments() const { return comments; } 

	
private:
	unsigned long _shelfId;
	std::wstring _title;
	std::wstring comments;
};

