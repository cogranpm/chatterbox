#include "MainFrameViewModel.h"


MainFrameViewModel::MainFrameViewModel(void) 
	: _shelfList(new boost::ptr_vector<Shelf>()), _subjectList(new boost::ptr_vector<Subject>()), _publicationList(new boost::ptr_vector<Publication>()),
	currentShelf(nullptr), currentPublication(nullptr), currentSubject(nullptr)
{
	
}


MainFrameViewModel::~MainFrameViewModel(void)
{
	if(_shelfList != nullptr)
	{
		_shelfList->clear();
		delete _shelfList;
		_shelfList = nullptr;
	}

	if(_subjectList != nullptr)
	{
		_subjectList->clear();
		delete _subjectList;
		_subjectList = nullptr;
	}

	if(_publicationList != nullptr)
	{
		_publicationList->clear();
		delete _publicationList;
		_publicationList = nullptr;
	}
}


boost::ptr_vector<Shelf>* MainFrameViewModel::getShelfList()
{
	return this->_shelfList;
}

void MainFrameViewModel::AddShelf(Shelf* shelf)
{
	this->_shelfList->push_back(shelf);
}


void MainFrameViewModel::AddSubject(Subject* subject)
{
	this->_subjectList->push_back(subject);
}

void MainFrameViewModel::AddPublication(Publication* publication)
{
	this->_publicationList->push_back(publication);
}

void MainFrameViewModel::SetCurrentShelf(Shelf* shelf)
{
	this->currentShelf = shelf;
}

Shelf* MainFrameViewModel::GetCurrentShelf()
{
	return this->currentShelf;
}

void MainFrameViewModel::SetCurrentSubject(Subject* subject)
{
	this->currentSubject = subject;
}

Subject* MainFrameViewModel::GetCurrentSubject()
{
	return this->currentSubject;
}

void MainFrameViewModel::SetCurrentPublication(Publication* publication)
{
	this->currentPublication = publication;
}

Publication* MainFrameViewModel::GetCurrentPublication()
{
	return this->currentPublication;
}