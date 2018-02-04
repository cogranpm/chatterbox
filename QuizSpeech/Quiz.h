#ifndef QUIZ_H
#define QUIZ_H


//#include "Question.h"
//#include "QuizRunHeader.h"

#include "BaseEntity.h"

class Quiz : public BaseEntity
{
	public:
		Quiz(const unsigned long publicationId, const std::wstring& name);
		Quiz(const unsigned long publicationId);
		Quiz();
		
		virtual ~Quiz(){}
		
		std::wstring GetName(){ return name;}
		void SetName(const std::wstring& name);

		const unsigned long GetQuizId() {return quizId;} 
		void SetQuizId(const unsigned long quizId);

		const unsigned long GetPublicationId() {return publicationId;} 
		void SetPublicationId(const unsigned long publicationId) { this->publicationId = publicationId;}

		const unsigned long GetTopicId() { return topicId; } 
		void SetTopicId(const unsigned long topicId);

		//	QuizRunHeader& getCurrentQuizRunHeader(){return _quizRunHeader;}
		bool IsNew() { return !(quizId > 0); }

private:
	unsigned long quizId;
	std::wstring name;
	unsigned long publicationId;
	unsigned long topicId;
//	QuizRunHeader _quizRunHeader;
	
};


#endif