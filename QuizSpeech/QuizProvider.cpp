#include "stdafx.h"
#include "QuizProvider.h"


int myrandom (int i) { return std::rand()%i;}

QuizProvider::QuizProvider() 
{
	
}

void QuizProvider::Init()
{
	/*
	DataProvider::Init(session);
	bool createFlag = false;
	createFlag = DataProvider::CreateTable("Shelf", "CREATE TABLE Shelf (ShelfId INTEGER PRIMARY KEY AUTOINCREMENT, Title VARCHAR, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
	createFlag = DataProvider::CreateTable("Subject", "CREATE TABLE Subject (SubjectId INTEGER PRIMARY KEY AUTOINCREMENT, ShelfId INTEGER, Name VARCHAR, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
	createFlag = DataProvider::CreateTable("Publication", "CREATE TABLE Publication (PublicationId INTEGER PRIMARY KEY AUTOINCREMENT, SubjectId INTEGER, Title VARCHAR, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
	createFlag = DataProvider::CreateTable("Topic", "CREATE TABLE Topic (TopicId INTEGER PRIMARY KEY AUTOINCREMENT, PublicationId INTEGER, Name VARCHAR, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
	createFlag = DataProvider::CreateTable("Note", "CREATE TABLE Note (NoteId INTEGER PRIMARY KEY AUTOINCREMENT, TopicId INTEGER, Title VARCHAR, Body VARCHAR, BodyFile VARCHAR, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
	createFlag = DataProvider::CreateTable("Quiz", "CREATE TABLE Quiz (QuizId INTEGER PRIMARY KEY AUTOINCREMENT, PublicationId INTEGER, TopicId INTEGER, Name VARCHAR, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
	createFlag = DataProvider::CreateTable("Question", "CREATE TABLE Question (QuestionId INTEGER PRIMARY KEY AUTOINCREMENT, QuizId INTEGER, Title VARCHAR, Body VARCHAR, BodyFile VARCHAR, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
	createFlag = DataProvider::CreateTable("Answer", "CREATE TABLE Answer (AnswerId INTEGER PRIMARY KEY AUTOINCREMENT, QuestionId INTEGER, Body VARCHAR, BodyFile VARCHAR, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
	*/
	
	/* Quiz
		Questions
			Answers

	*/
	//createFlag = DataProvider::CreateTable("Question", "CREATE TABLE Question (QuestionId INTEGER PRIMARY KEY AUTOINCREMENT, QuizId INTEGER, QuestionText VARCHAR, QuestionFile VARCHAR, AnswerText VARCHAR, AnswerFile VARCHAR, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
	//createFlag = DataProvider::CreateTable("AnswerSequence", "CREATE TABLE AnswerSequence (AnswerSequenceId INTEGER PRIMARY KEY AUTOINCREMENT, QuestionId INTEGER, Phrase VARCHAR, MustMatchAll INTEGER, OrderSignificant INTEGER, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
	//createFlag = DataProvider::CreateTable("QuizRunHeader", "CREATE TABLE QuizRunHeader (QuizRunHeaderId INTEGER PRIMARY KEY AUTOINCREMENT, QuizId INTEGER, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
	//createFlag = DataProvider::CreateTable("QuizRunQuestion", "CREATE TABLE QuizRunQuestion (QuizRunQuestionId INTEGER PRIMARY KEY AUTOINCREMENT, QuizRunHeaderId INTEGER, QuestionId INTEGER, AnswerText VARCHAR, AnswerFile VARCHAR, IsCorrect INTEGER, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
}

void QuizProvider::Insert(Shelf& shelf)
{
	/*
	std::string tmpTitle;
	Poco::UnicodeConverter::toUTF8(shelf.getTitle(), tmpTitle);
	Poco::Data::Statement insertShelf(*_session);
	insertShelf << "INSERT INTO Shelf(Title) VALUES(?)",	
	Poco::Data::use(tmpTitle);
	Poco::UInt32 nextId = insertShelf.execute();
	long id = DataProvider::GetLastRowID();
	shelf.setShelfId(id);
	*/
}


void QuizProvider::Insert(Subject& subject)
{
	/*
	std::string tmpTitle;
	Poco::UnicodeConverter::toUTF8(subject.getTitle(), tmpTitle);
	Poco::Data::Statement insertSubject(*_session);
	insertSubject << "INSERT INTO Subject(ShelfId, Title) VALUES(?, ?)",	
	Poco::Data::use(Poco::UInt32(subject.getShelfId())),
	Poco::Data::use(tmpTitle);
	Poco::UInt32 nextId = insertSubject.execute();
	long id = DataProvider::GetLastRowID();
	subject.setSubjectId(id);
	*/
}

void QuizProvider::Insert(Publication& publication)
{
	/*
	std::string tmpName;
	Poco::UnicodeConverter::toUTF8(publication.getTitle(), tmpName);
	Poco::Data::Statement insertPublication(*_session);
	insertPublication << "INSERT INTO Publication(SubjectId, Title) VALUES(?, ?)",
		Poco::Data::use(Poco::UInt32(publication.getSubjectId())),
		Poco::Data::use(tmpName);
	Poco::UInt32 nextId = insertPublication.execute();
	long id = DataProvider::GetLastRowID();
	publication.setPublicationId(id);
	*/
}


void QuizProvider::Insert(Topic& topic)
{
	/*
	std::string tmpName;
	Poco::UnicodeConverter::toUTF8(topic.getName(), tmpName);
	Poco::Data::Statement insertTopic(*_session);
	insertTopic << "INSERT INTO Topic(PublicationId, Name) VALUES(?, ?)",
		Poco::Data::use(Poco::UInt32(topic.getPublicationId())),
		Poco::Data::use(tmpName);
	Poco::UInt32 nextId = insertTopic.execute();
	long id = DataProvider::GetLastRowID();
	topic.setTopicId(id);
	*/
}

void QuizProvider::Insert(Note& note)
{
	/*
	std::string tmpTitle;
	std::string tmpBody;
	std::string tmpBodyFile;
	Poco::UnicodeConverter::toUTF8(note.GetTitle(), tmpTitle);
	Poco::UnicodeConverter::toUTF8(note.GetBody(), tmpBody);
	Poco::UnicodeConverter::toUTF8(note.GetBodyFile(), tmpBodyFile);
	Poco::Data::Statement insert(*_session);
	insert << "INSERT INTO Note(TopicId, Title, Body, BodyFile) VALUES(?, ?, ?, ?)",
	Poco::Data::use(Poco::UInt32(note.GetTopicId())),
	Poco::Data::use(tmpTitle),
	Poco::Data::use(tmpBody),
	Poco::Data::use(tmpBodyFile);
	Poco::UInt32 nextId = insert.execute();
	long id = DataProvider::GetLastRowID();
	note.SetNoteId(id);
	*/
}

/*
void QuizProvider::Insert(QuizRunHeader& quizRunHeader)
{
	Poco::Data::Statement insert(*_session);
	insert << "INSERT INTO QuizRunHeader(QuizId) VALUES(?)",
	Poco::Data::use(Poco::UInt32(quizRunHeader.GetQuizId()));
	Poco::UInt32 nextId = insert.execute();
	long id = DataProvider::GetLastRowID();
	quizRunHeader.SetQuizRunHeaderId(id);
}

void QuizProvider::Insert(QuizRunQuestion& quizRunQuestion)
{
	//QuizRunHeaderId INTEGER, QuestionId INTEGER, AnswerText VARCHAR, AnswerFile VARCHAR, IsCorrect INTEGER

	std::string tmpAnswerText;
	std::string tmpAnswerFile;
	Poco::UnicodeConverter::toUTF8(quizRunQuestion.GetAnswerText(), tmpAnswerText);
	Poco::UnicodeConverter::toUTF8(quizRunQuestion.GetAnswerFile(), tmpAnswerFile);
	Poco::UInt32 isCorrect;
	if(quizRunQuestion.GetIsCorrect())
	{
		isCorrect = 1;
	}
	else
	{
		isCorrect = 0;
	}
	Poco::Data::Statement insert(*_session);
	insert << "INSERT INTO QuizRunQuestion(QuizRunHeaderId, QuestionId, AnswerText, AnswerFile, IsCorrect) VALUES(?, ?, ?, ?, ?)",
		Poco::Data::use(Poco::UInt32(quizRunQuestion.GetQuizRunHeaderId())),
		Poco::Data::use(Poco::UInt32(quizRunQuestion.GetQuestionId())),
		Poco::Data::use(tmpAnswerText),
		Poco::Data::use(tmpAnswerFile),
		Poco::Data::use(Poco::UInt32(isCorrect));
	Poco::UInt32 nextId = insert.execute();
	long id = DataProvider::GetLastRowID();
	quizRunQuestion.SetQuizRunQuestionId(id);
}


void QuizProvider::Insert(AnswerSequence& answerSequence)
{
	std::string tmpPhrase;
	Poco::UnicodeConverter::toUTF8(answerSequence.getPhrase(), tmpPhrase);
	Poco::Data::Statement insertSequence(*_session);
	insertSequence << "INSERT INTO AnswerSequence(QuestionId, Phrase, MustMatchAll, OrderSignificant) VALUES(?, ?, ?, ?)",	
	Poco::Data::use(Poco::UInt32(answerSequence.GetQuestionId())),
	Poco::Data::use(tmpPhrase),
	Poco::Data::use(GetIntegerFromBool(answerSequence.GetMustMatchAll())),
	Poco::Data::use(GetIntegerFromBool(answerSequence.GetOrderSignificant()));
	Poco::UInt32 nextId = insertSequence.execute();
	long id = DataProvider::GetLastRowID();
	answerSequence.setAnswerSequenceId(id);
}
*/

/*
Poco::UInt32 QuizProvider::GetIntegerFromBool(bool bVal)
{
	if(bVal)
	{
		return Poco::UInt32(1);
	}
	else
	{
		return Poco::UInt32(0);
	}
}
*/

void QuizProvider::Update(Subject& subject)
{

}


void QuizProvider::Delete(Subject& subject)
{

}

/*

bool QuizProvider::GetByName(Shelf& shelf, std::wstring title)
{
	bool result = false;

	std::string title_ex;
	Poco::UnicodeConverter::toUTF8(title, title_ex);

	Poco::Data::Statement select(*_session);
	select << "SELECT Title, ShelfId FROM Shelf WHERE Title = ?",
		Poco::Data::use(title_ex);
	select.execute();

	Poco::Data::RecordSet rs(select);
	
	bool more = rs.moveFirst();
	while (more)
	{
		this->SetCategoryFromRecordset(category, rs);
		more = rs.moveNext();
		result = true;
	}

	return result;

}



bool QuizProvider::GetByName(Book& book, std::wstring title)
{
	bool result = false;

	std::string title_ex;
	Poco::UnicodeConverter::toUTF8(title, title_ex);
	long categoryId = book.getCategoryId();

	Poco::Data::Statement select(*_session);
	select << "SELECT Title, BookId, CategoryId FROM Book WHERE Title = ? AND CategoryId = ?",
		Poco::Data::use(title_ex),
		Poco::Data::use(categoryId);
	select.execute();

	Poco::Data::RecordSet rs(select);
	
	bool more = rs.moveFirst();
	while (more)
	{
		this->SetBookFromRecordset(book, rs);
		more = rs.moveNext();
		result = true;
	}

	return result;

}

bool QuizProvider::GetByName(Quiz& quiz, std::wstring name)
{
	bool result = false;

	std::string name_ex;
	Poco::UnicodeConverter::toUTF8(name, name_ex);

	Poco::Data::Statement select(*_session);
	select << "SELECT Name, QuizId, BookId FROM Quiz WHERE NAME = ? AND BookId = ?",
		Poco::Data::use(name_ex),
		Poco::Data::use(Poco::UInt32(quiz.GetBookId()));
	select.execute();

	Poco::Data::RecordSet rs(select);
	
	bool more = rs.moveFirst();
	while (more)
	{
		this->SetQuizFromRecordset(quiz, rs);
		more = rs.moveNext();
		result = true;
	}

	return result;

}



bool QuizProvider::GetByName(Note& note, std::wstring name)
{
	bool result = false;

	std::string name_ex;
	Poco::UnicodeConverter::toUTF8(name, name_ex);

	Poco::Data::Statement select(*_session);
	select << "SELECT Title, NoteId, QuizId, Body, BodyFile FROM Note WHERE TITLE = ? AND QuizId = ?",
		Poco::Data::use(name_ex),
		Poco::Data::use(Poco::UInt32(note.GetQuizId()));
	select.execute();

	Poco::Data::RecordSet rs(select);
	
	bool more = rs.moveFirst();
	while (more)
	{
		this->SetNoteFromRecordset(note, rs);
		more = rs.moveNext();
		result = true;
	}

	return result;

}



void QuizProvider::AddQuestion(Quiz& quiz, Question& question)
{
	//insert a question, settting the quiz id value
	std::string questionText;
	std::string answerText;
	std::string questionFile;
	std::string answerFile;

	Poco::UnicodeConverter::toUTF8(question.GetQuestionText(), questionText);
	Poco::UnicodeConverter::toUTF8(question.GetAnswerText(), answerText);
	Poco::UnicodeConverter::toUTF8(question.GetQuestionFile(), questionFile);
	Poco::UnicodeConverter::toUTF8(question.GetAnswerFile(), answerFile);


	Poco::Data::Statement insertQuestion(*_session);
	insertQuestion << "INSERT INTO Question(QuizId, QuestionText, AnswerText, QuestionFile, AnswerFile) VALUES(?, ?, ?, ?, ?)",
		Poco::Data::use(Poco::UInt32(quiz.GetQuizId())),
		Poco::Data::use(questionText),
		Poco::Data::use(answerText),
		Poco::Data::use(questionFile),
		Poco::Data::use(answerFile);
	insertQuestion.execute();
	long id = DataProvider::GetLastRowID();
	question.SetQuestionId(id);
}

long QuizProvider::GetQuestionCount(Quiz& quiz)
{
	int questionCount = 0;
	int quizId;
	quizId = quiz.GetQuizId();
	Poco::Data::Statement select(*_session);
	select << "SELECT COUNT(*) FROM Question WHERE QuizId = ?",
		Poco::Data::use(quizId),
		Poco::Data::into(questionCount),
		Poco::Data::now;
	return questionCount;
}

void QuizProvider::GetCategoryList(std::vector<EntityItem>& list)
{
	
	Poco::Data::Statement select(*_session);
	select << "SELECT Title, CategoryId FROM Category ORDER BY Title ASC";
	select.execute();

	Poco::Data::RecordSet rs(select);
	
	bool more = rs.moveFirst();
	while (more)
	{
		std::string categoryTitle = rs[0].convert<std::string>();
		long categoryId = rs[1].convert<long>();
		std::wstring categoryTitleEx;
		Poco::UnicodeConverter::toUTF16(categoryTitle, categoryTitleEx);
		EntityItem item;
		item.description = categoryTitleEx;
		item.entityId = categoryId;
		list.push_back(item);
		more = rs.moveNext();
		
	}

	
}

void QuizProvider::GetBookList(Category& category, std::vector<EntityItem>& list)
{
	
	Poco::Data::Statement select(*_session);
	select << "SELECT Title, BookId FROM Book WHERE CategoryId = ? ORDER BY Title ASC",
		Poco::Data::use(Poco::UInt32(category.getCategoryId()));
	select.execute();

	Poco::Data::RecordSet rs(select);
	
	bool more = rs.moveFirst();
	while (more)
	{
		std::string bookTitle = rs[0].convert<std::string>();
		long bookId = rs[1].convert<long>();
		std::wstring bookTitleEx;
		Poco::UnicodeConverter::toUTF16(bookTitle, bookTitleEx);
		EntityItem item;
		item.description = bookTitleEx;
		item.entityId = bookId;
		list.push_back(item);
		more = rs.moveNext();
		
	}
}

void QuizProvider::GetChapterList(Book& book, std::vector<EntityItem>& list)
{

	Poco::Data::Statement select(*_session);
	select << "SELECT Name, QuizId FROM Quiz WHERE BookId = ? ORDER BY CreatedDate ASC",
		Poco::Data::use(Poco::UInt32(book.getBookId()));
	select.execute();

	Poco::Data::RecordSet rs(select);
	
	bool more = rs.moveFirst();
	while (more)
	{
		std::string chapterName = rs[0].convert<std::string>();
		long quizId = rs[1].convert<long>();
		std::wstring chapterNameEx;
		Poco::UnicodeConverter::toUTF16(chapterName, chapterNameEx);
		EntityItem item;
		item.description = chapterNameEx;
		item.entityId = quizId;
		list.push_back(item);
		more = rs.moveNext();
		
	}

}

void QuizProvider::GetNoteList(Quiz& quiz, std::vector<EntityItem>& list)
{

	Poco::Data::Statement select(*_session);
	select << "SELECT Title, NoteId FROM Note WHERE QuizId = ? ORDER BY CreatedDate ASC",
		Poco::Data::use(Poco::UInt32(quiz.GetQuizId()));
	select.execute();

	Poco::Data::RecordSet rs(select);
	
	bool more = rs.moveFirst();
	while (more)
	{
		std::string title = rs[0].convert<std::string>();
		long noteId = rs[1].convert<long>();
		std::wstring titleEx;
		Poco::UnicodeConverter::toUTF16(title, titleEx);
		EntityItem item;
		item.description = titleEx;
		item.entityId = noteId;
		list.push_back(item);
		more = rs.moveNext();
		
	}

}

void QuizProvider::GetQuestionList(Quiz& quiz, std::vector<EntityItem>& list)
{

	Poco::Data::Statement select(*_session);
	select << "SELECT QuestionText, QuestionId FROM Question WHERE QuizId = ? ORDER BY CreatedDate ASC",
		Poco::Data::use(Poco::UInt32(quiz.GetQuizId()));
	select.execute();

	Poco::Data::RecordSet rs(select);
	
	bool more = rs.moveFirst();
	while (more)
	{
		std::string title = rs[0].convert<std::string>();
		long questionId = rs[1].convert<long>();

		if(title.size() > 50)
		{
			std::string smallTitle  = title.substr(0, 50);
			smallTitle += " ...";
			title = smallTitle;
		}

		std::wstring titleEx;
		Poco::UnicodeConverter::toUTF16(title, titleEx);
		EntityItem item;
		item.description = titleEx;
		item.entityId = questionId;
		list.push_back(item);
		more = rs.moveNext();
	}
}

bool QuizProvider::GetById(Question& question, long id)
{
	bool result = false;
	
	Poco::Data::Statement select(*_session);
	select << "SELECT QuestionId, QuizId, QuestionText, QuestionFile, AnswerText, AnswerFile FROM Question WHERE QuestionId = ?",
		Poco::Data::use(id);
	select.execute();

	Poco::Data::RecordSet rs(select);
	
	bool more = rs.moveFirst();
	while (more)
	{
		SetQuestionFromRecordset(question, rs);
		more = rs.moveNext();
		result = true;
	}

	return result;
}

bool QuizProvider::GetById(Category& category, long id)
{
	bool result = false;
	
	Poco::Data::Statement select(*_session);
	select << "SELECT Title, CategoryId FROM Category WHERE CategoryId = ?",
		Poco::Data::use(id);
	select.execute();

	Poco::Data::RecordSet rs(select);
	
	bool more = rs.moveFirst();
	while (more)
	{
		SetCategoryFromRecordset(category, rs);
		more = rs.moveNext();
		result = true;
	}

	return result;
}

bool QuizProvider::GetById(Quiz& quiz, long id)
{
	bool result = false;
	Poco::Data::Statement select(*_session);
	select << "SELECT QuizId, BookId, Name FROM Quiz WHERE QuizId = ?",
		Poco::Data::use(id);
	select.execute();
	Poco::Data::RecordSet rs(select);
	bool more = rs.moveFirst();
	while (more)
	{
		SetQuizFromRecordset(quiz, rs);
		more = rs.moveNext();
		result = true;
	}
	return result;
}

bool QuizProvider::GetById(Book& book, long id)
{
	bool result = false;
	Poco::Data::Statement select(*_session);
	select << "SELECT BookId, CategoryId, Title  FROM Book WHERE BookId = ?",
		Poco::Data::use(id);
	select.execute();
	Poco::Data::RecordSet rs(select);
	bool more = rs.moveFirst();
	while (more)
	{
		SetBookFromRecordset(book, rs);
		more = rs.moveNext();
		result = true;
	}
	return result;

}

bool QuizProvider::GetById(Note& note, long id)
{
	bool result = false;
	Poco::Data::Statement select(*_session);
	select << "SELECT NoteId, QuizId, Title, Body, BodyFile  FROM Note WHERE NoteId = ?",
		Poco::Data::use(id);
	select.execute();
	Poco::Data::RecordSet rs(select);
	bool more = rs.moveFirst();
	while (more)
	{
		SetNoteFromRecordset(note, rs);
		more = rs.moveNext();
		result = true;
	}
	return result;
}



void QuizProvider::GetQuestionsByQuiz(std::vector<QuestionPtr>& list, Quiz& quiz)
{
	// given a quiz, find all the questions and populate the provided vector 
	Poco::Data::Statement select(*_session);
	select << "SELECT QuestionId, QuizId, QuestionText, QuestionFile, AnswerText, AnswerFile FROM Question WHERE QuizId = ? ORDER BY CreatedDate DESC",
		Poco::Data::use(Poco::UInt32(quiz.GetQuizId()));
	select.execute();

	Poco::Data::RecordSet rs(select);
	bool more = rs.moveFirst();
	while (more)
	{
		Question* question = new Question();
		SetQuestionFromRecordset(*question, rs);
		QuestionPtr item(question);
		list.push_back(item);
		more = rs.moveNext();
	}
	std::random_shuffle ( list.begin(), list.end(), myrandom);

}


void QuizProvider::SetQuestionFromRecordset(Question& question, Poco::Data::RecordSet& rs)
{
	long questionId = rs["QuestionId"].convert<long>();
	long quizId = rs["QuizId"].convert<long>();
	std::string questionText = rs["QuestionText"].convert<std::string>();
	std::string questionFile = rs["QuestionFile"].convert<std::string>();
	std::string answerText = rs["AnswerText"].convert<std::string>();
	std::string answerFile = rs["AnswerFile"].convert<std::string>();

	std::wstring questionTextEx;
	std::wstring questionFileEx;
	std::wstring answerTextEx;
	std::wstring answerFileEx;
	Poco::UnicodeConverter::toUTF16(questionText, questionTextEx);
	Poco::UnicodeConverter::toUTF16(questionFile, questionFileEx);
	Poco::UnicodeConverter::toUTF16(answerText, answerTextEx);
	Poco::UnicodeConverter::toUTF16(answerFile, answerFileEx);

	question.SetQuestionId(questionId);
	question.SetQuizId(quizId);
	question.SetQuestionText(questionTextEx);
	question.SetQuestionFile(questionFileEx);
	question.SetAnswerFile(answerFileEx);
	question.SetAnswerText(answerTextEx);
	
}


void QuizProvider::SetQuizFromRecordset(Quiz& quiz, Poco::Data::RecordSet& rs)
{
	std::string quizName = rs["Name"].convert<std::string>();
	long quizId = rs["QuizId"].convert<long>();
	long bookId = rs["BookId"].convert<long>();
	std::wstring quizNameEx;
	Poco::UnicodeConverter::toUTF16(quizName, quizNameEx);
	quiz.SetName(quizNameEx);
	quiz.SetQuizId(quizId);
	quiz.SetBookId(bookId);
}

void QuizProvider::SetShelfFromRecordset(Shelf& shelf, Poco::Data::RecordSet& rs)
{
	std::string title = rs["Title"].convert<std::string>();
	long shelfId = rs["ShelfId"].convert<long>();
	std::wstring titleEx;
	Poco::UnicodeConverter::toUTF16(title, titleEx);
	shelf.setTitle(titleEx);
	shelf.setShelfId(shelfId);
}


void QuizProvider::SetNoteFromRecordset(Note& note, Poco::Data::RecordSet& rs)
{
	std::string title = rs["Title"].convert<std::string>();
	long noteId = rs["NoteId"].convert<long>();
	long quizId = rs["QuizId"].convert<long>();
	std::string body = rs["Body"].convert<std::string>();
	std::string bodyFile = rs["BodyFile"].convert<std::string>();
	std::wstring titleEx;
	std::wstring bodyEx;
	std::wstring bodyFileEx;
	Poco::UnicodeConverter::toUTF16(title, titleEx);
	Poco::UnicodeConverter::toUTF16(body, bodyEx);
	Poco::UnicodeConverter::toUTF16(bodyFile, bodyFileEx);
	note.SetTitle(titleEx);
	note.SetBody(bodyEx);
	note.SetBodyFile(bodyFileEx);
	note.SetQuizId(quizId);
	note.SetNoteId(noteId);
}


void QuizProvider::SetBookFromRecordset(Book& book, Poco::Data::RecordSet& rs)
{
	std::string bookTitle = rs["Title"].convert<std::string>();
	long bookId = rs["BookId"].convert<long>();
	long categoryId = rs["CategoryId"].convert<long>();
	std::wstring bookTitleEx;
	Poco::UnicodeConverter::toUTF16(bookTitle, bookTitleEx);
	book.setTitle(bookTitleEx);
	book.setBookId(bookId);
	book.setCategoryId(categoryId);
}

void QuizProvider::GetQuizRunScore(int quizRunHeaderId, QuizScore& quizScore)
{
	std::string query = "select c.Total, y.Correct from (select count(*) as Total, QuizRunHeaderid from quizrunquestion group by quizrunheaderid) c inner join (select count(*) as Correct, QuizRunHeaderid from quizrunquestion where IsCorrect = 1 group by quizrunheaderid) y on y.QuizRunHeaderid = c.QuizRunHeaderid WHERE c.QuizRunHeaderId = ?";
	Poco::Data::Statement select(*_session);
	select << query,
		Poco::Data::use(quizRunHeaderId);
	select.execute();

	Poco::Data::RecordSet rs(select);
	
	bool more = rs.moveFirst();
	while (more)
	{
		int numAnswered = rs["Total"].convert<int>();
		int numCorrect = rs["Correct"].convert<int>();
		quizScore.SetNumAnswered(numAnswered);
		quizScore.SetNumCorrect(numCorrect);
		more = rs.moveNext();
	}

}

bool QuizProvider::GetAnswerSequenceByQuestionId(AnswerSequence& answerSequence, long questionId)
{
	bool wasFound = false;
	std::string query = "select AnswerSequenceId, QuestionId, Phrase, MustMatchAll, OrderSignificant  from AnswerSequence WHERE QuestionId = ?";
	Poco::Data::Statement select(*_session);
	select << query,
		Poco::Data::use(questionId);
	select.execute();

	Poco::Data::RecordSet rs(select);
	
	bool more = rs.moveFirst();
	while (more)
	{
	
		std::string phrase = rs["Phrase"].convert<std::string>();
		long answerSequenceId = rs["AnswerSequenceId"].convert<long>();
		long questionId = rs["QuestionId"].convert<long>();
		int mustMatchAll = rs["MustMatchAll"].convert<int>();
		int orderSignificant = rs["OrderSignificant"].convert<int>();
		
		std::wstring phraseEx;
		Poco::UnicodeConverter::toUTF16(phrase, phraseEx);

		answerSequence.setPhrase(phraseEx);
		answerSequence.setAnswerSequenceId(answerSequenceId);
		answerSequence.SetQuestionId(questionId);
		answerSequence.SetMustMatchAll(mustMatchAll > 0);
		answerSequence.SetOrderSignificant(orderSignificant > 0);
		wasFound = true;
		more = rs.moveNext();
	}
	return wasFound;
}

*/