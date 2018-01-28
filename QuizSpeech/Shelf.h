#pragma once

class Shelf 
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
	std::wstring getTitle() const {return _title;} const

	unsigned long getShelfId() const {return _shelfId;} const
	void setShelfId(const unsigned long shelfId){ _shelfId = shelfId;}
	
private:
	unsigned long _shelfId;
	std::wstring _title;
	
};

