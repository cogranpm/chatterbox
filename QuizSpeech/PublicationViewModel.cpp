#include "PublicationViewModel.h"



PublicationViewModel::PublicationViewModel(Publication* publication)
	:_publication(publication), _topicList(new boost::ptr_vector<Topic>()),
	_noteList(new boost::ptr_vector<Note>()),
	_quizList(new boost::ptr_vector<Quiz>()), 
	_topic(nullptr), _note(nullptr), quiz(nullptr)
{

}

PublicationViewModel::PublicationViewModel(void)
{
}


PublicationViewModel::~PublicationViewModel(void)
{
	if(_topicList != 0)
	{
		_topicList->clear();
		delete _topicList;
		_topicList = 0;
	}

	if(_noteList != 0)
	{
		_noteList->clear();
		delete _noteList;
		_noteList = 0;
	}

	if(_quizList != 0)
	{
		_quizList->clear();
		delete _quizList;
		_quizList = 0;
	}
}


Publication* PublicationViewModel::GetPublication()
{
	return this->_publication;
}

void PublicationViewModel::AddTopic(Topic* topic)
{
	_topicList->push_back(topic);
	this->SetTopic(topic);
}

void PublicationViewModel::SetTopic(Topic* topic)
{
	_topic = topic;
}

void PublicationViewModel::SetNote(Note* note)
{
	_note = note;
}