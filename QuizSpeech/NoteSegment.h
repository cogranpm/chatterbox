#pragma once

#include "stdafx.h"
#include <wx/datetime.h>
#include "BaseEntity.h"
//#include "NoteSegmentPanelImp.h"

class NoteSegment : public BaseEntity
{

public:
	NoteSegment(void);
	NoteSegment(const unsigned long noteId);
	~NoteSegment(void);
	NoteSegment& operator=(const NoteSegment &noteSegment);
	bool operator==(const NoteSegment  &noteSegment)  {return _noteSegmentId == noteSegment.GetNoteSegmentId();}


	const std::wstring& GetTitle() const { return _title;}
	void SetTitle(const std::wstring &title){ _title = title;}
		
	const std::wstring& GetBody() const { return _body;}
	void SetBody(const std::wstring &body){ _body = body;}
		
	const std::wstring& GetBodyFile() const { return _bodyFile;}
	void SetBodyFile(const std::wstring &bodyFile){ _bodyFile = bodyFile;}

	unsigned long GetNoteSegmentId() const {return _noteSegmentId;}
	void SetNoteSegmentId(unsigned long id) {_noteSegmentId = id;}
		
	unsigned long GetNoteId() const {return _noteId;}
	void SetNoteId(unsigned long id) {_noteId = id;}

	unsigned long GetNoteSegmentTypeId() const { return _noteSegmentTypeId; }
	void SetNoteSegmentTypeId(unsigned long id) { _noteSegmentTypeId = id; }

	const wxDateTime& GetCreatedDate() const { return _createdDate;}
	void SetCreatedDate(const wxDateTime &createdDate){ _createdDate = createdDate;}

	bool GetDeleted() const { return _deleted;}
	void SetDeleted(const bool deleted) { _deleted = deleted;}

private:
	unsigned long _noteSegmentId;
	unsigned long _noteId;
	//used to set the default font and size for note segments
	unsigned long _noteSegmentTypeId;
	std::wstring _body;
	std::wstring _title;
	std::wstring _bodyFile;
	wxDateTime _createdDate;
	bool _deleted;
	
};

