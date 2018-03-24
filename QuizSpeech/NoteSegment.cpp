#include "NoteSegment.h"


NoteSegment::NoteSegment(void) : NoteSegment(0)
{
}

NoteSegment::NoteSegment(const unsigned long noteId) : _noteId(noteId), _noteSegmentTypeId(0), _body(L""), _bodyFile(L""), _title(L""), _noteSegmentId(0), _deleted(false)
{
}



NoteSegment::~NoteSegment(void)
{
}

NoteSegment& NoteSegment::operator=(const NoteSegment &noteSegment)
{
	if(this != &noteSegment)
	{
		this->SetNoteId(noteSegment.GetNoteId());
		this->SetNoteSegmentTypeId(noteSegment.GetNoteSegmentTypeId());
		this->SetTitle(noteSegment.GetTitle());
		this->SetBody(noteSegment.GetBody());
		this->SetBodyFile(noteSegment.GetBodyFile());
		this->SetCreatedDate(noteSegment.GetCreatedDate());
	}
	return *this;
}

void NoteSegment::SetTitle(const std::wstring &title) {
	std::wstring oldValue = _title;
	_title = title; 
	FirePropertyChange(oldValue, _title);
}

void NoteSegment::SetBody(const std::wstring &body) 
{ 
	std::wstring oldValue = _body;
	_body = body; 
	FirePropertyChange(oldValue, _body);
}

void NoteSegment::SetBodyFile(const std::wstring &bodyFile) 
{ 
	std::wstring oldValue = _bodyFile;
	_bodyFile = bodyFile; 
	FirePropertyChange(oldValue, _bodyFile);
}

void NoteSegment::SetNoteId(unsigned long id) 
{ 
	unsigned long oldValue = _noteId;
	_noteId = id; 
	FirePropertyChange(oldValue, _noteId);
}

void NoteSegment::SetNoteSegmentTypeId(unsigned long id) 
{ 
	unsigned long oldValue = _noteSegmentTypeId;
	_noteSegmentTypeId = id; 
	FirePropertyChange(oldValue, _noteSegmentTypeId);
}

void NoteSegment::SetDeleted(const bool deleted) 
{
	bool oldValue = _deleted;
	_deleted = deleted; 
	FirePropertyChange(oldValue, _deleted);
}
