#include "NoteSegment.h"


NoteSegment::NoteSegment(void) : NoteSegment(0)
{
}

NoteSegment::NoteSegment(const unsigned long noteId) : _noteId(noteId), _noteSegmentTypeId(0), _body(L""), _bodyFile(L""), _title(L""), _noteSegmentId(0)
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