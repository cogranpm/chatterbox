#ifndef QUIZPROVIDER_H
#define QUIZPROVIDER_H

//#include "DataProvider.h"
#include "Subject.h"
#include "Question.h"
#include "Publication.h"
#include "Shelf.h"
#include "EntityItem.h"
#include "Note.h"
#include "Topic.h"

/*
#include "Utils.h"
#include "QuizRunQuestion.h"
#include "QuizScore.h"
#include "AnswerSequence.h"
*/

class QuizProvider
{
public:
	QuizProvider();
	virtual ~QuizProvider(){}
	void Init();

	/* insert */
	void Insert(Subject& subject);
	void Insert(Publication& publication);
	void Insert(Topic& topic);
	void Insert(Shelf& shelf);
	void Insert(Note& note);
	/*
	void Insert(QuizRunHeader& quizRunHeader);
	void Insert(QuizRunQuestion& quizRunQuestion);
	void Insert(AnswerSequence& answerSequence);
	*/

	void Update(Subject& subject);

	void Delete(Subject& subject);

	/* by name */
	bool GetByName(Subject& quiz, std::wstring name);
	bool GetByName(Shelf& shelf, std::wstring title);
	bool GetByName(Publication& book, std::wstring title);
	bool GetByName(Note& note, std::wstring name);
	
	//bool GetById(Question& question, long id);
	bool GetById(Shelf& category, long id);
	bool GetById(Subject& quiz, long id);
	bool GetById(Publication& book, long id);
	bool GetById(Note& note, long id);

	//bool GetAnswerSequenceByQuestionId(AnswerSequence& answerSequence, long questionId);

	/* Lists */
	void GetShelfList(std::vector<EntityItem>& list);
	void GetPublicationList(Subject& subject, std::vector<EntityItem>& list);
	void GetSubjectList(Shelf& shelf, std::vector<EntityItem>& list);
	void GetNoteList(Publication& quiz, std::vector<EntityItem>& list);
	
	//void GetQuestionList(Quiz& quiz, std::vector<EntityItem>& list);

	/* Questions 
	void GetQuestionsByQuiz(std::vector<QuestionPtr>& list, Quiz& quiz);
	void AddQuestion(Quiz& quiz, Question& question);
	long GetQuestionCount(Quiz& quiz);
	void GetQuizRunScore(int quizRunHeaderId, QuizScore& quizScore);
	*/

private:
	//void SetQuestionFromRecordset(Question& question, Poco::Data::RecordSet& rs);
	//void SetShelfFromRecordset(Shelf& shelf, Poco::Data::RecordSet& rs);
	//void SetSubjectFromRecordset(Subject& subject, Poco::Data::RecordSet& rs);
	//void SetNoteFromRecordset(Note& note, Poco::Data::RecordSet& rs);
	//void SetBookFromRecordset(Publication& publication, Poco::Data::RecordSet& rs);
	//Poco::UInt32 GetIntegerFromBool(bool bVal);
};

#endif