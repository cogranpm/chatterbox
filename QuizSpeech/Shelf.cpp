#include "StdAfx.h"
#include "Shelf.h"


Shelf::Shelf(void)
{
}


Shelf::Shelf(const std::wstring& title) : Shelf(0, title)
{

}

Shelf::Shelf(const unsigned long shelfId, const std::wstring& title) : _shelfId(shelfId), _title(title), comments()
{

}

Shelf::Shelf (const Shelf &shelf) {
	this->setShelfId(shelf.getShelfId());
	this->setTitle(shelf.getTitle());
	this->setComments(shelf.getComments());
}

Shelf& Shelf::operator=(const Shelf &shelf)
{
	if(this != &shelf)
	{
		this->setTitle(shelf.getTitle());
	}
	return *this;
}


Shelf::~Shelf(void)
{
}


