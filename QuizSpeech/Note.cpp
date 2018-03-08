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

void Note::SetTopicId(unsigned long id) 
{
	unsigned long oldValue = this->_topicId;
	_topicId = id; 
	FirePropertyChange(oldValue, _topicId);
}

void Note::SetTitle(const std::wstring &title) 
{ 
	std::wstring oldValue = this->_title;
	_title = title; 
	FirePropertyChange(oldValue, this->_title);
}

void Note::SetDescription(const std::wstring &description) 
{ 
	std::wstring oldValue = this->_description;
	_description = description; 
	FirePropertyChange(oldValue, this->_description);
}

void Note::SetTitleAudioFile(const std::wstring &titleAudioFile) 
{ 
	std::wstring oldValue = this->titleAudioFile;
	this->titleAudioFile = titleAudioFile; 
	FirePropertyChange(oldValue, this->titleAudioFile);
}

void Note::SetDescriptionAudioFile(const std::wstring &descriptionAudioFile) 
{ 
	std::wstring oldValue = this->descriptionAudioFile;
	this->descriptionAudioFile = descriptionAudioFile; 
	FirePropertyChange(oldValue, this->descriptionAudioFile);
}

void Note::SetCreatedDate(const wxDateTime &createdDate) { _createdDate = createdDate; }