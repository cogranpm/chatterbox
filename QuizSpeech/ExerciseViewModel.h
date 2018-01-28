#pragma once

#include "Publication.h"
#include "Quiz.h"
#include "stdafx.h"
#include "Question.h"
#include "Answer.h"
#include "Topic.h"

class ExerciseViewModel
{
	
	Publication* publication;
	Quiz quiz;
	boost::ptr_vector<Question>* questionList;
	Question* currentQuestion;
	/* this is a holder variable for a new question until 
	apply is clicked then it is copied into the questionList for 
	permanent memory location */
	Question newQuestion;
	boost::ptr_vector<Topic> topicList;

public:
	ExerciseViewModel(Publication* publication);
	ExerciseViewModel(Publication* publication, const unsigned long quizId);
	~ExerciseViewModel();
	Publication* GetPublication() { return publication; }
	Quiz& GetQuiz() { return quiz; }
	boost::ptr_vector<Question>* GetQuestionList() { return questionList; }
	Question* GetCurrentQuestion() { return currentQuestion; }
	void SetCurrentQuestion(Question* question) { currentQuestion = question; }
	Question& GetNewQuestion() { return newQuestion; }
	void ResetNewQuestion();
	boost::ptr_vector<Topic>* GetTopicList() { return &topicList; }
	bool IsDirty();
};

