#include "StdAfx.h"
#include "Note.h"


Note::Note(void) : Note(0)
{
}

Note::Note(const unsigned long topicId) : _topicId(topicId), _noteId(0), _description(L""), _title(L""), titleAudioFile(L""), descriptionAudioFile(L"")
{

}


Note::~Note(void)
{
}

Note& Note::operator=(const Note &note)
{
	if(this != &note)
	{
		this->SetTopicId(note.GetTopicId());
		this->SetDescription(note.GetDescription());
		this->SetTitle(note.GetTitle());
		this->SetTitleAudioFile(note.GetTitleAudioFile());
		this->SetCreatedDate(note.GetCreatedDate());
	}
	return *this;
}
