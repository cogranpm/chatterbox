#include "NoteSegmentTypeHeader.h"



NoteSegmentTypeHeader::NoteSegmentTypeHeader() : _id(0), _title(L""), _helpText(L"")
{
}


NoteSegmentTypeHeader::~NoteSegmentTypeHeader()
{
}


void NoteSegmentTypeHeader::setTitle(const std::wstring &title)
{ 
	std::wstring oldValue = this->_title;
	_title = title; 
	if (oldValue != _title)
	{
		FirePropertyChange();
	}
}

void NoteSegmentTypeHeader::setHelpText(const std::wstring &helpText)
{ 
	std::wstring oldValue = _helpText;
	_helpText = helpText; 
	if (oldValue != _helpText)
	{
		FirePropertyChange();
	}
}