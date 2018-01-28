#include "SegmentTypeViewModel.h"


SegmentTypeViewModel::SegmentTypeViewModel(NoteSegmentTypeHeader* header) : segmentList(new boost::ptr_vector<NoteSegmentType>()),
isNew(false), modifiedHeader(*header), selectedSegmentType(nullptr)
{
}

SegmentTypeViewModel::SegmentTypeViewModel() : segmentList(new boost::ptr_vector<NoteSegmentType>()), isNew(true), modifiedHeader(), selectedSegmentType(nullptr)
{
}


SegmentTypeViewModel::~SegmentTypeViewModel()
{
	if (segmentList != nullptr)
	{
		delete segmentList;
		segmentList = nullptr;
	}
}


NoteSegmentType* SegmentTypeViewModel::AddSegmentType()
{
	SetSelectedSegmentType(new NoteSegmentType(modifiedHeader.getId()));
	//segmentList->push_back(GetSelectedSegmentType());
	return GetSelectedSegmentType();
}

