#pragma once

/**************************************
sqlite provider for quiz related entities:
Question
Answer
QuestionRun 

****************************************/
#include "stdafx.h"
#include "wx/wxsqlite3.h"
#include "SqliteDDLProvider.h"
#include "Question.h"
#include "Topic.h"
#include "Quiz.h"
#include "Publication.h"
#include "QuizRunHeader.h"
#include "QuizRunQuestion.h"
#include "QuizScore.h"

class SqlIteQuizProvider
{
private:
	wxSQLite3Database* db;
	SqliteDDLProvider* ddl;
	bool createFlag;
	void SetQuizFromRecord(Quiz* entity, wxSQLite3ResultSet& set);
	void SetQuestionFromRecord(Question* entity, wxSQLite3ResultSet& set);
	void SetAnswerFromRecord(Answer* entity, wxSQLite3ResultSet& set);
	void SetQuizRunHeaderFromRecord(QuizRunHeader* entity, wxSQLite3ResultSet& set);
	void SetQuizRunQuestionFromRecord(QuizRunQuestion* entity, wxSQLite3ResultSet& set);
	void GetAnswerByQuestion(Question* question);
	
public:
	SqlIteQuizProvider(wxSQLite3Database* db, SqliteDDLProvider* ddl);
	~SqlIteQuizProvider();

	void Insert(Quiz* entity);
	void Update(Quiz* entity);
	void Delete(Quiz* entity);
	void GetQuizByPublication(Publication* publication, boost::ptr_vector<Quiz>* list);
	void GetQuizById(const unsigned long quizId, Quiz* quiz);

	void Insert(Question* entity);
	void Update(Question* entity);
	void Delete(Question* entity);
	void GetQuestionsByQuiz(Quiz* quiz, boost::ptr_vector<Question>* list);
	void GetQuestionsByQuizId(unsigned long quizId, boost::ptr_vector<Question>* list);
	void GetQuestionById(unsigned long questionId, Question* question);
	void GetQuizRunQuestionsByQuiz(unsigned long quizId, unsigned long quizRunHeaderId, boost::ptr_vector<QuizRunQuestion>* list);

	void Insert(Answer* entity);
	void Update(Answer* entity);
	void Delete(Answer* entity);
	
	void Insert(QuizRunHeader& quizRunHeader);
	void Insert(QuizRunQuestion& quizRunQuestion);
	void Update(QuizRunHeader& entity);
	void Update(QuizRunQuestion& quizRunQuestion);
	void Delete(QuizRunHeader& entity);
	void Delete(QuizRunQuestion& entity);
	void GetQuizRunsByPublication(Publication* publication, boost::ptr_vector<QuizRunHeader>* list);
	void GetQuizRunsByQuiz(Quiz* quiz, boost::ptr_vector<QuizRunHeader>* list);
	//void GetQuizRunScore(int quizRunHeaderId, QuizScore& quizScore);

	void CreateSampleData(Topic* topic);
	bool InitDB();
};

