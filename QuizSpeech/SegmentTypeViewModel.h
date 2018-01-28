#pragma once

#include "NoteSegmentTypeHeader.h"
#include "NoteSegmentType.h"

class SegmentTypeViewModel
{
	bool isNew;
	NoteSegmentTypeHeader modifiedHeader;
	boost::ptr_vector<NoteSegmentType>* segmentList;
	NoteSegmentType* selectedSegmentType;
	
public:
	SegmentTypeViewModel();
	SegmentTypeViewModel(NoteSegmentTypeHeader* header);
	~SegmentTypeViewModel();
	bool IsNew() { return isNew; }
	void SetIsNew(bool isNew) { this->isNew = isNew; }
	boost::ptr_vector<NoteSegmentType>* getSegmentList() { return segmentList; }
	NoteSegmentTypeHeader& GetModifiedHeader() { return modifiedHeader; }
	NoteSegmentType* GetSelectedSegmentType() { return selectedSegmentType; }
	void SetSelectedSegmentType(NoteSegmentType* segmentType) { selectedSegmentType = segmentType; }
	NoteSegmentType* AddSegmentType();
};

