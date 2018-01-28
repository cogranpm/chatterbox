#include "NoteSegmentType.h"



NoteSegmentType::NoteSegmentType() : NoteSegmentType(0)
{
}

NoteSegmentType::NoteSegmentType(unsigned long headerId) :
	id(0),
	noteSegmentTypeHeaderId(headerId),
	title(L"")
{

}


NoteSegmentType::~NoteSegmentType()
{
}

void NoteSegmentType::setFontDesc(const std::string &fontDesc)
{ 
	std::string oldValue(this->fontDesc);
	this->fontDesc = fontDesc; 
	if (oldValue != fontDesc)
	{
		FirePropertyChange();
	}
}

void NoteSegmentType::setTitle(const std::wstring &title)
{ 
	std::wstring oldValue = this->title;
	this->title = title; 
	if (oldValue != title)
	{
		FirePropertyChange();
	}
}
