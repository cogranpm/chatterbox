#include "NoteViewModel.h"


NoteViewModel::NoteViewModel(void)
	: NoteViewModel(nullptr)
{
}

NoteViewModel::NoteViewModel(Note* note):
	_note(note), 
	_noteSegmentList(new boost::ptr_vector<NoteSegment>()),
	_noteTypeHeaderList(new boost::ptr_vector<NoteSegmentTypeHeader>()),
	_noteSegmentTypeList(new boost::ptr_vector<NoteSegmentType>())
{
	
}


NoteViewModel::~NoteViewModel(void)
{
	if (_noteSegmentList != nullptr)
	{
		delete _noteSegmentList;
		_noteSegmentList = nullptr;
	}

	if (_noteTypeHeaderList != nullptr)
	{
		delete _noteTypeHeaderList;
		_noteTypeHeaderList = nullptr;
	}

	if (_noteSegmentTypeList != nullptr)
	{
		delete _noteSegmentTypeList;
		_noteSegmentTypeList = nullptr;
	}
}


void NoteViewModel::EraseItem(NoteSegment* noteSegment)
{
	_noteSegmentList->erase(std::find(_noteSegmentList->begin(), _noteSegmentList->end(), *noteSegment));
}


bool NoteViewModel::IsNew()
{
	return (this->GetNote()->GetNoteId() == 0);
}