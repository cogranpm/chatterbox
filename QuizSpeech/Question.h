
#ifndef QUESTION_H
#define QUESTION_H

//#include "AnswerSequence.h"
#include "Answer.h"
#include "BaseEntity.h"

class Question : public BaseEntity
{
	public:
		Question(const unsigned long quizId); 
		Question();
		virtual ~Question(){}
		bool operator==(const Question  &entity);

		const std::wstring GetQuestionText() const { return questionText;}
		std::wstring GetLimitedQuestionText()
		{ 
			if(questionText.size() > 0 )
			{
				if(questionText.size() < 50)
				{
					return questionText;
				}
				else
				{
					return questionText.substr(0, 50) + L" ...";
				}
			}
			else
			{
				return questionText;
			}

		}
		void SetQuestionText(const std::wstring& questionText);
		
		const std::wstring GetQuestionFile() const { return questionFile;}
		void SetQuestionFile(const std::wstring& audioFile);

		unsigned long GetQuestionId() const {return questionId;}
		void SetQuestionId(const unsigned long id) {questionId = id;}
		
		const unsigned long GetQuizId() const {return quizId;}
		void SetQuizId(const unsigned long id) {quizId = id;}

		Answer* GetAnswer() { return &answer; }
		bool IsNew() { return !(questionId > 0); }
private:
	unsigned long questionId;
	unsigned long quizId;
	std::wstring questionText;
	std::wstring questionFile;
	Answer answer;
};


#endif