#pragma once
#include "stdafx.h"
#include "QuizRunHeader.h"
#include "QuizRunQuestion.h"
#include "Question.h"


class ExerciseRunViewModel
{

	QuizRunHeader header;
	boost::ptr_vector<QuizRunQuestion> runQuestions;
	boost::ptr_vector<Question> questions;
	int currentQuestionIndex;

public:
	ExerciseRunViewModel(unsigned long quizId);
	~ExerciseRunViewModel();
	QuizRunHeader& GetHeader() { return header; }
	boost::ptr_vector<QuizRunQuestion>& GetRunQuestions() { return runQuestions; }
	boost::ptr_vector<Question>& GetQuestions() { return questions; }
	void CreateRunQuestions();
	void SetCurrentQuestionIndex(const int index) { currentQuestionIndex = index; }
	int GetCurrentQuestionIndex() { return currentQuestionIndex; }
};

