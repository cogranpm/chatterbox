#pragma once
#include "stdafx.h"
#include "BaseEntity.h"

class NoteSegmentType : public BaseEntity
{
public:
	NoteSegmentType();
	NoteSegmentType(unsigned long headerId);
	~NoteSegmentType();

	bool operator==(const NoteSegmentType  &noteSegmentType) { return id == noteSegmentType.getId(); }

	void setTitle(const std::wstring &title);
	std::wstring getTitle() const { return title; } 

	unsigned long getId() const { return id; } 
	void setId(const unsigned long id) { this->id = id; }

	unsigned long getNoteSegmentTypeHeaderId() const { return noteSegmentTypeHeaderId; } 
	void setNoteSegmentTypeHeaderId(const unsigned long headerId) { noteSegmentTypeHeaderId = headerId; }

	void setFontDesc(const std::string &fontDesc);
	std::string getFontDesc() const { return fontDesc; } 

private:
	unsigned long id;
	unsigned long noteSegmentTypeHeaderId;
	std::wstring title;
	std::string fontDesc;


};

