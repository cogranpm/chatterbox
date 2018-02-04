#include "SqlIteQuizProvider.h"



SqlIteQuizProvider::SqlIteQuizProvider(wxSQLite3Database* db, SqliteDDLProvider* ddl) : db(db), ddl(ddl), createFlag(false)
{
}


SqlIteQuizProvider::~SqlIteQuizProvider()
{

}

bool SqlIteQuizProvider::InitDB()
{
	//note: we'll have a silent Quiz parent for the questions that just mimics the Topic, which is its parent
	//this will allow a grouping of questions for some future expansion / grouping logic
	//we won't burden the user with having to create multiple quiz per topic at this stage
	this->createFlag = this->ddl->CreateTable("Quiz", "CREATE TABLE Quiz (QuizId INTEGER PRIMARY KEY AUTOINCREMENT, PublicationId INTEGER, TopicId INTEGER, Name VARCHAR(60) NOT NULL, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
	this->createFlag = this->ddl->CreateTable("Question", "CREATE TABLE Question (QuestionId INTEGER PRIMARY KEY AUTOINCREMENT, QuizId INTEGER NOT NULL, Body VARCHAR, BodyFile VARCHAR, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
	this->createFlag = this->ddl->CreateTable("Answer", "CREATE TABLE Answer (AnswerId INTEGER PRIMARY KEY AUTOINCREMENT, QuestionId INTEGER NOT NULL, Body VARCHAR, BodyFile VARCHAR, AnswerType INTEGER, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
	this->createFlag = this->ddl->CreateTable("QuizRunHeader", "CREATE TABLE QuizRunHeader (QuizRunHeaderId INTEGER PRIMARY KEY AUTOINCREMENT, QuizId INTEGER NOT NULL, IsComplete INTEGER, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
	this->createFlag = this->ddl->CreateTable("QuizRunQuestion", "CREATE TABLE QuizRunQuestion (QuizRunQuestionId INTEGER PRIMARY KEY AUTOINCREMENT, QuizRunHeaderId INTEGER, QuestionId INTEGER NOT NULL, AnswerText VARCHAR, AnswerFile VARCHAR, IsCorrect INTEGER, IsAnswered INTEGER, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
	this->ddl->CreateDeleteTrigger("Publication", "Quiz", "PublicationId");
	this->ddl->CreateDeleteTrigger("Topic", "Quiz", "TopicId");
	this->ddl->CreateDeleteTrigger("Quiz", "Question", "QuizId");
	this->ddl->CreateDeleteTrigger("Question", "Answer", "QuestionId");
	this->ddl->CreateDeleteTrigger("QuizRunHeader", "QuizRunQuestion", "QuizRunHeaderId");
	return this->createFlag;
}

void SqlIteQuizProvider::CreateSampleData(Topic* topic)
{

}

void SqlIteQuizProvider::Insert(Quiz* entity)
{
	try
	{
		wxSQLite3Statement stmt = db->PrepareStatement("insert into Quiz(PublicationId, TopicId, Name) values (?, ?, ?);");
		stmt.Bind(1, wxLongLong(entity->GetPublicationId()));
		if (entity->GetTopicId() > 0)
		{
			stmt.Bind(2, wxLongLong(entity->GetTopicId()));
		}
		else
		{
			stmt.BindNull(2);
		}
		stmt.Bind(3, entity->GetName());
		stmt.ExecuteUpdate();
		long id = this->ddl->GetLastRowID();
		entity->SetQuizId(id);
		entity->SetDirty(false);
	}
	catch (wxSQLite3Exception& e)
	{
		throw e.GetMessage().ToStdWstring();
	}
}

void SqlIteQuizProvider::Update(Quiz* entity)
{
	wxSQLite3Statement stmt = db->PrepareStatement("update Quiz set TopicId = ?, Name = ? where QuizId = ?;");
	if (entity->GetTopicId() > 0)
	{
		stmt.Bind(1, wxLongLong(entity->GetTopicId()));
	}
	else
	{
		stmt.BindNull(1);
	}
	stmt.Bind(2, entity->GetName());
	stmt.Bind(3, wxLongLong(entity->GetQuizId()));
	stmt.ExecuteUpdate();
}

void SqlIteQuizProvider::Delete(Quiz* entity)
{
	wxSQLite3Statement stmt = db->PrepareStatement("delete from Quiz where QuizId = ?;");
	stmt.Bind(1, wxLongLong(entity->GetQuizId()));
	stmt.ExecuteUpdate();
}

void SqlIteQuizProvider::SetQuizFromRecord(Quiz* entity, wxSQLite3ResultSet& set)
{
	entity->SetPublicationId(set.GetInt64("PublicationId").ToLong());
	if (set.IsNull("TopicId"))
	{
		entity->SetTopicId(0);
	}
	else
	{
		entity->SetTopicId(set.GetInt64("TopicId").ToLong());
	}
	entity->SetQuizId(set.GetInt64("QuizId").ToLong());
	entity->SetName(set.GetAsString("Name").ToStdWstring());
}


void SqlIteQuizProvider::GetQuizById(const unsigned long quizId, Quiz* quiz)
{
	wxSQLite3Statement stmt = db->PrepareStatement("SELECT * FROM Quiz WHERE QuizId = ?;");
	stmt.Bind(1, wxLongLong(quizId));
	wxSQLite3ResultSet set = stmt.ExecuteQuery();
	while (set.NextRow())
	{
		this->SetQuizFromRecord(quiz, set);
	}
}

void SqlIteQuizProvider::GetQuizByPublication(Publication* publication, boost::ptr_vector<Quiz>* list)
{
	wxSQLite3Statement stmt = db->PrepareStatement("SELECT * FROM Quiz WHERE PublicationId = ? ORDER BY CreatedDate DESC;");
	stmt.Bind(1, wxLongLong(publication->getPublicationId()));
	wxSQLite3ResultSet set = stmt.ExecuteQuery();
	while (set.NextRow())
	{
		Quiz* quiz = new Quiz(publication->getPublicationId());
		this->SetQuizFromRecord(quiz, set);
		list->push_back(quiz);
	}
}


void SqlIteQuizProvider::Insert(Question* entity)
{
	try
	{
		wxSQLite3Statement stmt = db->PrepareStatement("insert into Question(QuizId, Body, BodyFile) values (?, ?, ?);");
		stmt.Bind(1, wxLongLong(entity->GetQuizId()));
		if (!entity->GetQuestionText().empty())
		{
			stmt.Bind(2, entity->GetQuestionText());
		}
		else
		{
			stmt.BindNull(2);
		}
		if (!entity->GetQuestionFile().empty())
		{
			stmt.Bind(3, entity->GetQuestionFile());
		}
		else
		{
			stmt.BindNull(3);
		}
		stmt.ExecuteUpdate();
		long id = this->ddl->GetLastRowID();
		entity->SetQuestionId(id);
		entity->SetDirty(false);
	}
	catch (wxSQLite3Exception& e)
	{
		throw e.GetMessage().ToStdWstring();
	}
	/* insert the answer as well */
	entity->GetAnswer()->SetQuestionId(entity->GetQuestionId());
	Insert(entity->GetAnswer());
}

void SqlIteQuizProvider::Update(Question* entity)
{
	wxSQLite3Statement stmt = db->PrepareStatement("update Question set QuizId = ?, Body = ?, BodyFile = ? where QuestionId = ?;");
	stmt.Bind(1, wxLongLong(entity->GetQuizId()));
	if (!entity->GetQuestionText().empty())
	{
		stmt.Bind(2, entity->GetQuestionText());
	}
	else
	{
		stmt.BindNull(2);
	}
	if (!entity->GetQuestionFile().empty())
	{
		stmt.Bind(3, entity->GetQuestionFile());
	}
	else
	{
		stmt.BindNull(3);
	}
	stmt.Bind(4, wxLongLong(entity->GetQuestionId()));
	stmt.ExecuteUpdate();
	/* update the answer as well */
	Update(entity->GetAnswer());
}

void SqlIteQuizProvider::Delete(Question* entity)
{
	wxSQLite3Statement stmt = db->PrepareStatement("delete from Question where QuestionId = ?;");
	stmt.Bind(1, wxLongLong(entity->GetQuestionId()));
	stmt.ExecuteUpdate();
	Delete(entity->GetAnswer());
}

void SqlIteQuizProvider::SetQuestionFromRecord(Question* entity, wxSQLite3ResultSet& set)
{
	entity->SetQuizId(set.GetInt64("QuizId").ToLong());
	if (!set.IsNull("Body"))
	{
		entity->SetQuestionText(set.GetAsString("Body").ToStdWstring());
	}
	if (!set.IsNull("BodyFile"))
	{
		entity->SetQuestionFile(set.GetAsString("BodyFile").ToStdWstring());
	}
	entity->SetQuestionId(set.GetInt64("QuestionId").ToLong());
	
	/* set the Answer property of quiz immediately - one to one relationship*/
	this->GetAnswerByQuestion(entity);
}

void SqlIteQuizProvider::GetAnswerByQuestion(Question* question)
{
	wxSQLite3Statement stmt = db->PrepareStatement("SELECT * FROM Answer WHERE QuestionId = ?;");
	stmt.Bind(1, wxLongLong(question->GetQuestionId()));
	wxSQLite3ResultSet set = stmt.ExecuteQuery();
	while (set.NextRow())
	{
		this->SetAnswerFromRecord(question->GetAnswer(), set);
	}
}

void SqlIteQuizProvider::GetQuestionById(unsigned long questionId, Question* entity)
{
	wxSQLite3Statement stmt = db->PrepareStatement("SELECT * FROM Question WHERE QuestionId = ?;");
	stmt.Bind(1, wxLongLong(questionId));
	wxSQLite3ResultSet set = stmt.ExecuteQuery();
	while (set.NextRow())
	{
		this->SetQuestionFromRecord(entity, set);
	}
}

void SqlIteQuizProvider::GetQuestionsByQuiz(Quiz* quiz, boost::ptr_vector<Question>* list)
{
	GetQuestionsByQuizId(quiz->GetQuizId(), list);
}

void SqlIteQuizProvider::GetQuestionsByQuizId(unsigned long quizId, boost::ptr_vector<Question>* list)
{
	wxSQLite3Statement stmt = db->PrepareStatement("SELECT * FROM Question WHERE QuizId = ? ORDER BY CreatedDate DESC;");
	stmt.Bind(1, wxLongLong(quizId));
	wxSQLite3ResultSet set = stmt.ExecuteQuery();
	while (set.NextRow())
	{
		Question* entity = new Question(quizId);
		this->SetQuestionFromRecord(entity, set);
		list->push_back(entity);
	}
}

void SqlIteQuizProvider::Insert(Answer* entity)
{
	try
	{
		wxSQLite3Statement stmt = db->PrepareStatement("insert into Answer(QuestionId, Body, BodyFile) values (?, ?, ?);");
		stmt.Bind(1, wxLongLong(entity->GetQuestionId()));
		if (!entity->GetAnswerText().empty())
		{
			stmt.Bind(2, entity->GetAnswerText());
		}
		else
		{
			stmt.BindNull(2);
		}
		if (!entity->GetAnswerFile().empty())
		{
			stmt.Bind(3, entity->GetAnswerFile());
		}
		else
		{
			stmt.BindNull(3);
		}
		stmt.ExecuteUpdate();
		long id = this->ddl->GetLastRowID();
		entity->SetQuestionId(id);
		entity->SetDirty(false);
	}
	catch (wxSQLite3Exception& e)
	{
		throw e.GetMessage().ToStdWstring();
	}
}

void SqlIteQuizProvider::Update(Answer* entity)
{
	wxSQLite3Statement stmt = db->PrepareStatement("update Answer set Body = ?, BodyFile = ? where AnswerId = ?;");
	if (!entity->GetAnswerText().empty())
	{
		stmt.Bind(1, entity->GetAnswerText());
	}
	else
	{
		stmt.BindNull(1);
	}
	if (!entity->GetAnswerFile().empty())
	{
		stmt.Bind(2, entity->GetAnswerFile());
	}
	else
	{
		stmt.BindNull(2);
	}
	stmt.Bind(3, wxLongLong(entity->GetAnswerId()));
	stmt.ExecuteUpdate();
}

void SqlIteQuizProvider::Delete(Answer* entity)
{
	wxSQLite3Statement stmt = db->PrepareStatement("delete from Answer where AnswerId = ?;");
	stmt.Bind(1, wxLongLong(entity->GetAnswerId()));
	stmt.ExecuteUpdate();
}

void SqlIteQuizProvider::SetAnswerFromRecord(Answer* entity, wxSQLite3ResultSet& set)
{
	entity->SetAnswerId(set.GetInt64("AnswerId").ToLong());
	if (set.IsNull("Body"))
	{

	}
	else
	{
		entity->SetAnswerText(set.GetAsString("Body").ToStdWstring());
	}
	if (set.IsNull("BodyFile"))
	{

	}
	else
	{
		entity->SetAnswerFile(set.GetAsString("BodyFile").ToStdWstring());
	}
	entity->SetQuestionId(set.GetInt64("QuestionId").ToLong());
}


void SqlIteQuizProvider::Insert(QuizRunHeader& entity)
{

	try
	{
		wxSQLite3Statement stmt = db->PrepareStatement("insert into QuizRunHeader(QuizId, IsComplete) values (?, ?);");
		stmt.Bind(1, wxLongLong(entity.GetQuizId()));
		stmt.BindBool(2, entity.GetIsComplete());
		stmt.ExecuteUpdate();
		long id = this->ddl->GetLastRowID();
		entity.SetQuizRunHeaderId(id);
		entity.SetDirty(false);
	}
	catch (wxSQLite3Exception& e)
	{
		throw e.GetMessage().ToStdWstring();
	}
}

void SqlIteQuizProvider::Update(QuizRunHeader& entity)
{
	wxSQLite3Statement stmt = db->PrepareStatement("update QuizRunHeader set IsComplete = ? where QuizRunHeaderId = ?;");
	stmt.BindBool(1, entity.GetIsComplete());
	stmt.Bind(2, wxLongLong(entity.GetQuizRunHeaderId()));
	stmt.ExecuteUpdate();
}

void SqlIteQuizProvider::Insert(QuizRunQuestion& entity)
{
	try
	{
		wxSQLite3Statement stmt = db->PrepareStatement("insert into QuizRunQuestion(QuizRunHeaderId, QuestionId, AnswerText, AnswerFile, IsCorrect, IsAnswered) values (?, ?, ?, ?, ?, ?);");
		stmt.Bind(1, wxLongLong(entity.GetQuizRunHeaderId()));
		if (entity.GetQuestion().GetQuestionId() > 0)
		{
			stmt.Bind(2, wxLongLong(entity.GetQuestion().GetQuestionId()));
		}
		else
		{
			stmt.BindNull(2);
		}
		if (!entity.GetAnswerText().empty())
		{
			stmt.Bind(3, entity.GetAnswerText());
		}
		else
		{
			stmt.BindNull(3);
		}
		if (!entity.GetAnswerFile().empty())
		{
			stmt.Bind(4, entity.GetAnswerFile());
		}
		else
		{
			stmt.BindNull(4);
		}
		stmt.BindBool(5, entity.GetIsCorrect());
		stmt.BindBool(6, entity.GetIsAnswered());
		stmt.ExecuteUpdate();
		long id = this->ddl->GetLastRowID();
		entity.SetQuizRunQuestionId(id);
		entity.SetDirty(false);
	}
	catch (wxSQLite3Exception& e)
	{
		throw e.GetMessage().ToStdWstring();
	}
	
}

void SqlIteQuizProvider::Update(QuizRunQuestion& entity)
{
	wxSQLite3Statement stmt = db->PrepareStatement("update Question set AnswerText = ?, AnswerFile = ?, IsCorrect = ?, IsAnswered = ? where QuizRunQuestionId = ?;");
	
	if (!entity.GetAnswerText().empty())
	{
		stmt.Bind(1, entity.GetAnswerText());
	}
	else
	{
		stmt.BindNull(1);
	}
	if (!entity.GetAnswerFile().empty())
	{
		stmt.Bind(2, entity.GetAnswerFile());
	}
	else
	{
		stmt.BindNull(2);
	}
	stmt.BindBool(3, entity.GetIsCorrect());
	stmt.BindBool(4, entity.GetIsAnswered());
	stmt.Bind(5, wxLongLong(entity.GetQuizRunQuestionId()));
	stmt.ExecuteUpdate();
	
}

void SqlIteQuizProvider::Delete(QuizRunHeader& entity)
{
	wxSQLite3Statement stmt = db->PrepareStatement("delete from QuizRunHeader where QuizRunHeaderId = ?;");
	stmt.Bind(1, wxLongLong(entity.GetQuizRunHeaderId()));
	stmt.ExecuteUpdate();
}

void SqlIteQuizProvider::Delete(QuizRunQuestion& entity)
{
	wxSQLite3Statement stmt = db->PrepareStatement("delete from QuizRunQuestion where QuizRunQuestionId = ?;");
	stmt.Bind(1, wxLongLong(entity.GetQuizRunQuestionId()));
	stmt.ExecuteUpdate();
}


void SqlIteQuizProvider::SetQuizRunHeaderFromRecord(QuizRunHeader* entity, wxSQLite3ResultSet& set)
{
	entity->SetQuizId(set.GetInt64("QuizId").ToLong());
	entity->SetQuizRunHeaderId(set.GetInt64("QuizRunHeaderId").ToLong());
	if (!set.IsNull("IsComplete"))
	{
		entity->SetIsComplete(set.GetBool("IsComplete"));
	}
	else
	{
		entity->SetIsComplete(false);
	}
	
	entity->SetCreatedDate(set.GetDateTime("CreatedDate"));

	/* auto load the associated quiz */
	GetQuizById(entity->GetQuizId(), &entity->GetQuiz());
}

void SqlIteQuizProvider::SetQuizRunQuestionFromRecord(QuizRunQuestion* entity, wxSQLite3ResultSet& set)
{
	entity->SetQuizRunHeaderId(set.GetInt64("QuizRunHeaderId").ToLong());
	
	if (!set.IsNull("AnswerText"))
	{
		entity->SetAnswerText(set.GetAsString("AnswerText").ToStdWstring());
	}
	if (!set.IsNull("AnswerFile"))
	{
		entity->SetAnswerFile(set.GetAsString("AnswerFile").ToStdWstring());
	}
	if (!set.IsNull("IsCorrect"))
	{
		entity->SetIsCorrect(set.GetBool("IsCorrect"));
	}
	else
	{
		entity->SetIsCorrect(false);
	}
	if (!set.IsNull("IsAnswered"))
	{
		entity->SetIsAnswered(set.GetBool("IsAnswered"));
	}
	else
	{
		entity->SetIsAnswered(false);
	}
	entity->SetQuizRunQuestionId(set.GetInt64("QuizRunQuestionId").ToLong());

	/* automatically load the question */
	unsigned long questionId = set.GetInt64("QuestionId").ToLong();
	GetQuestionById(questionId, &entity->GetQuestion());
}

void SqlIteQuizProvider::GetQuizRunsByPublication(Publication* publication, boost::ptr_vector<QuizRunHeader>* list)
{
	wxSQLite3Statement stmt = db->PrepareStatement("SELECT QuizRunHeaderId, QuizId, IsComplete, datetime(CreatedDate, 'localtime') AS CreatedDate FROM QuizRunHeader WHERE QuizId in (select quizId from Quiz where publicationId = ? ) ORDER BY CreatedDate DESC;");
	stmt.Bind(1, wxLongLong(publication->getPublicationId()));
	wxSQLite3ResultSet set = stmt.ExecuteQuery();
	while (set.NextRow())
	{
		QuizRunHeader* header = new QuizRunHeader();
		this->SetQuizRunHeaderFromRecord(header, set);
		list->push_back(header);
	}
}


void SqlIteQuizProvider::GetQuizRunsByQuiz(Quiz* quiz, boost::ptr_vector<QuizRunHeader>* list)
{
	wxSQLite3Statement stmt = db->PrepareStatement("SELECT  QuizRunHeaderId, QuizId, IsComplete, datetime(CreatedDate, 'localtime') AS CreatedDate FROM QuizRunHeader WHERE QuizId = ? ORDER BY CreatedDate DESC;");
	stmt.Bind(1, wxLongLong(quiz->GetQuizId()));
	wxSQLite3ResultSet set = stmt.ExecuteQuery();
	while (set.NextRow())
	{
		QuizRunHeader* header = new QuizRunHeader(quiz->GetQuizId());
		this->SetQuizRunHeaderFromRecord(header, set);
		list->push_back(header);
	}
}

//void SqlIteQuizProvider::GetQuizRunScore(int quizRunHeaderId, QuizScore& quizScore)
//{
	//std::string query = "select c.Total, y.Correct from (select count(*) as Total, QuizRunHeaderid from quizrunquestion group by quizrunheaderid) c inner join (select count(*) as Correct, QuizRunHeaderid from quizrunquestion where IsCorrect = 1 group by quizrunheaderid) y on y.QuizRunHeaderid = c.QuizRunHeaderid WHERE c.QuizRunHeaderId = ?";
	//Poco::Data::Statement select(*_session);
	//select << query,
	//	Poco::Data::use(quizRunHeaderId);
	//select.execute();

	//Poco::Data::RecordSet rs(select);

	//bool more = rs.moveFirst();
	//while (more)
	//{
	//	int numAnswered = rs["Total"].convert<int>();
	//	int numCorrect = rs["Correct"].convert<int>();
	//	quizScore.SetNumAnswered(numAnswered);
	//	quizScore.SetNumCorrect(numCorrect);
	//	more = rs.moveNext();
	//}

//}


