#pragma once
#include "stdafx.h"
#include "Note.h"
#include "NoteSegment.h"
#include "NoteSegmentTypeHeader.h"
#include "NoteSegmentType.h"

class NoteViewModel
{

private:
	Note* _note;
	boost::ptr_vector<NoteSegment>* _noteSegmentList;
	boost::ptr_vector<NoteSegmentTypeHeader>* _noteTypeHeaderList;
	boost::ptr_vector<NoteSegmentType>* _noteSegmentTypeList;

public:
	NoteViewModel(void);
	NoteViewModel(Note* note);
	~NoteViewModel(void);

	Note* GetNote() { return _note;}
	boost::ptr_vector<NoteSegment>* GetNoteSegmentList() { return _noteSegmentList;}
	boost::ptr_vector<NoteSegmentTypeHeader>* GetNoteTypeList() { return _noteTypeHeaderList; }
	boost::ptr_vector<NoteSegmentType>* GetNoteTypeSegmentsList() { return _noteSegmentTypeList; }
	void EraseItem(NoteSegment* noteSegment);
	bool IsNew();
	bool IsDirty();
};

