#pragma once
#include "stdafx.h"
#include "BaseEntity.h"


class NoteSegmentTypeHeader : public BaseEntity
{
public:
	NoteSegmentTypeHeader();
	~NoteSegmentTypeHeader();

	bool operator==(const NoteSegmentTypeHeader  &header) { return _id == header.getId(); }

	void setTitle(const std::wstring &title);
	std::wstring getTitle() const { return _title; } 

	void setHelpText(const std::wstring &helpText);
	std::wstring getHelpText() const { return _helpText; } 

	unsigned long getId() const { return _id; } const
	void setId(const unsigned long headerId) { _id = headerId; }


private:
	unsigned long _id;
	std::wstring _title;
	std::wstring _helpText;
};

