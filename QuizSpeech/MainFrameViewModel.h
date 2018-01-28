#pragma once

#include "stdafx.h"
#include "shelf.h"
#include "Subject.h"
#include "Publication.h"

class MainFrameViewModel
{
public:
	MainFrameViewModel(void);
	~MainFrameViewModel(void);
	boost::ptr_vector<Shelf>* getShelfList();
	boost::ptr_vector<Subject>* getSubjectList() { return _subjectList;}
	boost::ptr_vector<Publication>* getPublicationList() { return _publicationList;}
	void AddShelf(Shelf* shelf);
	void AddSubject(Subject* subject);
	void AddPublication(Publication* publication);
	void SetCurrentShelf(Shelf* shelf);
	void SetCurrentSubject(Subject* subject);
	void SetCurrentPublication(Publication* publication);
	Shelf* GetCurrentShelf();
	Subject* GetCurrentSubject();
	Publication* GetCurrentPublication();
private:
	boost::ptr_vector<Shelf>* _shelfList;
	boost::ptr_vector<Subject>* _subjectList;
	boost::ptr_vector<Publication>* _publicationList;
	Shelf* currentShelf;
	Subject* currentSubject;
	Publication* currentPublication;

};

