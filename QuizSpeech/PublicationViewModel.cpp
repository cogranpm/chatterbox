#include "PublicationViewModel.h"



PublicationViewModel::PublicationViewModel(Publication* publication)
	:_publication(publication), _topicList(new boost::ptr_vector<Topic>()),
	_noteList(new boost::ptr_vector<Note>()),
	_quizList(new boost::ptr_vector<Quiz>()), 
	quizRunHeaderList(new boost::ptr_vector<QuizRunHeader>()),
	_topic(nullptr), _note(nullptr), quiz(nullptr)
{

}

PublicationViewModel::PublicationViewModel(void)
{
}


PublicationViewModel::~PublicationViewModel(void)
{
	if(_topicList != nullptr)
	{
		_topicList->clear();
		delete _topicList;
		_topicList = nullptr;
	}

	if(_noteList != nullptr)
	{
		_noteList->clear();
		delete _noteList;
		_noteList = nullptr;
	}

	if(_quizList != nullptr)
	{
		_quizList->clear();
		delete _quizList;
		_quizList = nullptr;
	}

	if (quizRunHeaderList != nullptr)
	{
		quizRunHeaderList->clear();
		delete quizRunHeaderList;
		quizRunHeaderList = nullptr;
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