#pragma once

#include "stdafx.h"
#include "Publication.h"
#include "Topic.h"
#include "Note.h"
#include "Quiz.h"

class PublicationViewModel
{

private:
	Publication* _publication;
	Topic* _topic;
	Note* _note;
	Quiz* quiz;
	boost::ptr_vector<Topic>* _topicList;
	boost::ptr_vector<Note>* _noteList;
	boost::ptr_vector<Quiz>* _quizList;


public:
	PublicationViewModel(void);
	PublicationViewModel(Publication* publication);
	~PublicationViewModel(void);

	Publication* GetPublication();
	void AddTopic(Topic* topic);
	void SetTopic(Topic* topic);
	Topic* GetTopic() { return _topic;}
	void SetNote(Note* note);
	Note* GetNote() { return _note;}
	void SetExercise(Quiz* quiz) { this->quiz = quiz; }
	Quiz* GetExercise() { return quiz; }
	boost::ptr_vector<Topic>* GetTopicList() {return _topicList;}
	boost::ptr_vector<Note>* GetNoteList() { return _noteList;}
	boost::ptr_vector<Quiz>* GetQuizList() { return _quizList;}

};

