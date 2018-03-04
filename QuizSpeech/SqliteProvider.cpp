#include "SqliteProvider.h"
#include "HelpConstants.h"
#include "GlobalConstants.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif



SqliteProvider::SqliteProvider(void) : db(nullptr), ddl(nullptr)
{
}


SqliteProvider::~SqliteProvider(void)
{
	if(db != nullptr)
	{
		try { db->Close(); } catch (const std::exception& e) { /* */ }
		delete db;
		db = nullptr;
	}

	if (ddl != nullptr)
	{
		delete ddl;
		ddl = nullptr;
	}
}

void SqliteProvider::Close()
{
	try 
	{ 
		db->Close(); 
	}
	catch (const std::exception& e) 
	{ 
		/* to do : logit*/ 
	}
}

void SqliteProvider::initDB(const wxString dbPath)
{
	try
	{
		this->db = new wxSQLite3Database();
		db->Open(dbPath);
		this->ddl = new SqliteDDLProvider(db);
		quizProvider = std::make_unique<SqlIteQuizProvider>(db, ddl);
		noteSegmentTypeProvider = std::make_unique<SqliteNoteSegmentTypeProvider>(db, ddl);

		bool createFlag = false;
		createFlag = this->ddl->CreateTable("Shelf", "CREATE TABLE Shelf (ShelfId INTEGER PRIMARY KEY AUTOINCREMENT, Title VARCHAR(60) NOT NULL, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
		createFlag = this->ddl->CreateTable("Subject", "CREATE TABLE Subject (SubjectId INTEGER PRIMARY KEY AUTOINCREMENT, ShelfId INTEGER NOT NULL, Title VARCHAR(60) NOT NULL, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP, FOREIGN KEY(ShelfId) REFERENCES Shelf(ShelfId) ON DELETE CASCADE)");
		createFlag = this->ddl->CreateTable("Publication", "CREATE TABLE Publication (PublicationId INTEGER PRIMARY KEY AUTOINCREMENT, SubjectId INTEGER, Title VARCHAR(60) NOT NULL, Type int, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP, FOREIGN KEY(SubjectId) REFERENCES Subject(SubjectId) ON DELETE CASCADE)");
		createFlag = this->ddl->CreateTable("Topic", "CREATE TABLE Topic (TopicId INTEGER PRIMARY KEY AUTOINCREMENT, PublicationId INTEGER NOT NULL, Name VARCHAR(60) NOT NULL, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP, FOREIGN KEY(PublicationId) REFERENCES Publication(PublicationId) ON DELETE CASCADE)");
		createFlag = this->ddl->CreateTable("Note", "CREATE TABLE Note (NoteId INTEGER PRIMARY KEY AUTOINCREMENT, TopicId INTEGER NOT NULL, Title VARCHAR(60), Description VARCHAR, TitleAudioFile VARCHAR, DescriptionAudioFile VARCHAR, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
		//createFlag = this->CreateTable("Note", "CREATE TABLE Note (NoteId INTEGER PRIMARY KEY AUTOINCREMENT, TopicId INTEGER, Title VARCHAR(60) NOT NULL, Body VARCHAR, BodyFile VARCHAR, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
		createFlag = this->ddl->CreateTable("NoteSegment", "CREATE TABLE NoteSegment (NoteSegmentId INTEGER PRIMARY KEY AUTOINCREMENT, NoteId INTEGER NOT NULL, NoteSegmentTypeId INTEGER, Title VARCHAR(60) NOT NULL, Body VARCHAR NOT NULL, BodyFile VARCHAR, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP, FOREIGN KEY(NoteId) REFERENCES Note(NoteId) ON DELETE CASCADE)");
		
	
		 /* triggers */
		this->ddl->CreateDeleteTrigger("Shelf", "Subject", "ShelfId");
		this->ddl->CreateDeleteTrigger("Subject", "Publication", "SubjectId");
		this->ddl->CreateDeleteTrigger("Publication", "Topic", "PublicationId");
		this->ddl->CreateDeleteTrigger("Topic", "Note", "TopicId");
		this->ddl->CreateDeleteTrigger("Note", "NoteSegment", "NoteId");
		
		
		bool noteSegmentTypeProviderCreateFlag = noteSegmentTypeProvider->InitDB();
		bool quizCreateFlag = this->quizProvider->InitDB();
			
		
		if (createFlag)
		{
			this->CreateSystemData();
			this->CreateSampleData();
		}

		int ver = GetVersion();
		if (ver == 0)
		{
			SetVersion(1);
		}
	}
	catch (wxSQLite3Exception &e)
	{
	//	::PrintError(e.GetMessage(), 0);
		throw e.GetMessage();
	}

}

void SqliteProvider::SetVersion(int version)
{
	try
	{
		wxString statement = wxString::Format("PRAGMA USER_VERSION = %d;", version);
		wxSQLite3Statement stmt = db->PrepareStatement(statement);
		stmt.ExecuteUpdate();
	}
	catch (wxSQLite3Exception& ex)
	{
		throw ex.GetMessage();
	}
}


int SqliteProvider::GetVersion()
{
	int val = 0;
	wxSQLite3ResultSet set = db->ExecuteQuery(wxString("PRAGMA USER_VERSION;"));
	while (set.NextRow())
	{
		val = set.GetInt(0, 0);
	}
	return val;
}



void SqliteProvider::Insert(Shelf* shelf)
{
	wxSQLite3Statement stmt = db->PrepareStatement("insert into Shelf(Title) values (?);");
	stmt.Bind(1, shelf->getTitle());
    stmt.ExecuteUpdate();	
	long id = this->ddl->GetLastRowID();
	shelf->setShelfId(id);
}

void SqliteProvider::Update(Shelf* shelf)
{
	wxSQLite3Statement stmt = db->PrepareStatement("update Shelf set Title = ? where ShelfId = ?;");
	stmt.Bind(1, shelf->getTitle());
	stmt.Bind(2, wxLongLong(shelf->getShelfId()));
    stmt.ExecuteUpdate();	
}


void SqliteProvider::Delete(Shelf* shelf)
{
	wxSQLite3Statement stmt = db->PrepareStatement("delete from Shelf where ShelfId = ?;");
	stmt.Bind(1, wxLongLong(shelf->getShelfId()));
	stmt.ExecuteUpdate();
}


void SqliteProvider::GetAllShelves(boost::ptr_vector<Shelf>* _shelfList)
{

	wxSQLite3ResultSet set = db->ExecuteQuery(wxString("SELECT Title, ShelfId FROM Shelf ORDER BY UPPER(Title);"));
	while(set.NextRow())
	{
		Shelf* shelf = new Shelf();
		this->SetShelfFromRecord(shelf, set);
		_shelfList->push_back(shelf);
	}
}

void SqliteProvider::SetShelfFromRecord(Shelf* shelf, wxSQLite3ResultSet& set)
{
	shelf->setShelfId(set.GetInt64("ShelfId").ToLong());
	shelf->setTitle(set.GetAsString("Title").ToStdWstring());
}

void SqliteProvider::Insert(Subject* subject)
{
	if(subject->getShelfId() < 1)
	{
		throw "Invalid argument, Subject had null ShelfId";
		return;
	}
	wxSQLite3Statement stmt = db->PrepareStatement("insert into Subject(ShelfId, Title) values (?, ?);");
	stmt.Bind(1, wxLongLong(subject->getShelfId()));
	stmt.Bind(2, subject->getTitle());
    stmt.ExecuteUpdate();	
	long id = this->ddl->GetLastRowID();
	subject->setSubjectId(id);
}


void SqliteProvider::Update(Subject* subject)
{
	try
	{
		wxSQLite3Statement stmt = db->PrepareStatement("update Subject set Title = ?, ShelfId = ? where SubjectId = ?;");
		stmt.Bind(1, subject->getTitle());
		stmt.Bind(2, wxLongLong(subject->getShelfId()));
		stmt.Bind(3, wxLongLong(subject->getSubjectId()));
		stmt.ExecuteUpdate();
	}
	catch(wxSQLite3Exception& e)
	{
		throw e.GetMessage().ToStdWstring();
	}
}

void SqliteProvider::Delete(Subject* subject)
{
	wxSQLite3Statement stmt = db->PrepareStatement("delete from Subject where SubjectId = ?;");
	stmt.Bind(1, wxLongLong(subject->getSubjectId()));
	stmt.ExecuteUpdate();
}

void SqliteProvider::GetSubjectsByShelf(Shelf* shelf, boost::ptr_vector<Subject>* _subjectList)
{
	wxSQLite3Statement stmt = db->PrepareStatement("SELECT SubjectId, Title, ShelfId FROM Subject WHERE ShelfId = ? ORDER BY UPPER(Title);");
	stmt.Bind(1, wxLongLong(shelf->getShelfId()));
	wxSQLite3ResultSet set = stmt.ExecuteQuery();
	while(set.NextRow())
	{
		Subject* subject = new Subject();
		this->SetSubjectFromRecord(subject, set);
		_subjectList->push_back(subject);
	}
}

void SqliteProvider::SetSubjectFromRecord(Subject* subject, wxSQLite3ResultSet& set)
{
	subject->setShelfId(set.GetInt64("ShelfId").ToLong());
	subject->setSubjectId(set.GetInt64("SubjectId").ToLong());
	subject->setTitle(set.GetAsString("Title").ToStdWstring());
}

void SqliteProvider::Insert(Publication* publication)
{
	if( publication->getSubjectId() < 1)
	{
		throw "Invalid argument, Publication had null SubjectId";
		return;
	}
	wxSQLite3Statement stmt = db->PrepareStatement("insert into Publication(SubjectId, Title, Type) values (?, ?, ?);");
	stmt.Bind(1, wxLongLong(publication->getSubjectId()));
	stmt.Bind(2, publication->getTitle());
	stmt.Bind(3, publication->getType());
    stmt.ExecuteUpdate();	
	long id = this->ddl->GetLastRowID();
	publication->setPublicationId(id);
}

void SqliteProvider::Update(Publication* publication)
{
	try
	{
		wxSQLite3Statement stmt = db->PrepareStatement("update Publication set Title = ?, SubjectId = ?, Type = ? where PublicationId = ?;");
		stmt.Bind(1, publication->getTitle());
		stmt.Bind(2, wxLongLong(publication->getSubjectId()));
		stmt.Bind(3, publication->getType());
		stmt.Bind(4, wxLongLong(publication->getPublicationId()));
		stmt.ExecuteUpdate();
	}
	catch(wxSQLite3Exception& e)
	{
		throw e.GetMessage().ToStdWstring();
	}
}

void SqliteProvider::Delete(Publication* publication)
{
	wxSQLite3Statement stmt = db->PrepareStatement("delete from Publication where PublicationId = ?;");
	stmt.Bind(1, wxLongLong(publication->getPublicationId()));
	stmt.ExecuteUpdate();
}

void SqliteProvider::GetPublicationsBySubject(Subject* subject, boost::ptr_vector<Publication>* publicationList)
{
	wxSQLite3Statement stmt = db->PrepareStatement("SELECT PublicationId, Title, Type, SubjectId FROM Publication WHERE SubjectId = ? ORDER BY UPPER(Title);");
	stmt.Bind(1, wxLongLong(subject->getSubjectId()));
	wxSQLite3ResultSet set = stmt.ExecuteQuery();
	while(set.NextRow())
	{
		Publication* publication = new Publication();
		this->SetPublicationFromRecord(publication, set);
		publicationList->push_back(publication);
	}
}

void SqliteProvider::SetPublicationFromRecord(Publication* publication, wxSQLite3ResultSet& set)
{
	publication->setSubjectId(set.GetInt64("SubjectId").ToLong());
	publication->setPublicationId(set.GetInt64("PublicationId").ToLong());
	publication->setTitle(set.GetAsString("Title").ToStdWstring());
	publication->setType(set.GetInt("Type"));
}

void SqliteProvider::Insert(Topic* topic)
{
	if(topic->getPublicationId() < 1)
	{
		throw "Invalid argument, Topic had null PublicationId";
		return;
	}
	wxSQLite3Statement stmt = db->PrepareStatement("insert into Topic(PublicationId, Name) values (?, ?);");
	stmt.Bind(1, wxLongLong(topic->getPublicationId()));
	stmt.Bind(2, topic->getName());
	
    stmt.ExecuteUpdate();	
	long id = this->ddl->GetLastRowID();
	topic->setTopicId(id);
}

void SqliteProvider::Update(Topic* topic)
{
	try
	{
		wxSQLite3Statement stmt = db->PrepareStatement("update Topic set Name = ?, PublicationId = ? where TopicId = ?;");
		stmt.Bind(1, topic->getName());
		stmt.Bind(2, wxLongLong(topic->getPublicationId()));
		stmt.Bind(3, wxLongLong(topic->getTopicId()));
		stmt.ExecuteUpdate();
	}
	catch(wxSQLite3Exception& e)
	{
		throw e.GetMessage().ToStdWstring();
	}
}

void SqliteProvider::Delete(Topic* topic)
{
	wxSQLite3Statement stmt = db->PrepareStatement("delete from Topic where TopicId = ?;");
	stmt.Bind(1, wxLongLong(topic->getTopicId()));
	stmt.ExecuteUpdate();
}

void SqliteProvider::GetTopicsByPublication(Publication* publication, boost::ptr_vector<Topic>* topicList)
{
	wxSQLite3Statement stmt = db->PrepareStatement("SELECT PublicationId, Name, TopicId FROM Topic WHERE PublicationId = ? ORDER BY CreatedDate ASC;");
	stmt.Bind(1, wxLongLong(publication->getPublicationId()));
	wxSQLite3ResultSet set = stmt.ExecuteQuery();
	while(set.NextRow())
	{
		Topic* topic = new Topic();
		this->SetTopicFromRecord(topic, set);
		topicList->push_back(topic);
	}
}

void SqliteProvider::SetTopicFromRecord(Topic* topic, wxSQLite3ResultSet& set)
{
	topic->setPublicationId(set.GetInt64("PublicationId").ToLong());
	topic->setTopicId(set.GetInt64("TopicId").ToLong());
	topic->setName(set.GetAsString("Name").ToStdWstring());
	
}


void SqliteProvider::Insert(Note* note)
{
	if(note->GetTopicId() < 1)
	{
		throw "Invalid argument, Note had null TopicId";
		return;
	}
	// need something field to begin with, will get the actual timestamp from database subsequent reloads 
	note->SetCreatedDate(wxDateTime::Now());
	wxSQLite3Statement stmt = db->PrepareStatement("insert into Note(TopicId, Title, Description, TitleAudioFile, DescriptionAudioFile) values (?, ?, ?, ?, ?);");
	stmt.Bind(1, wxLongLong(note->GetTopicId()));

	if (note->GetTitle().empty())
	{
		stmt.BindNull(2);
	}
	else
	{
		stmt.Bind(2, note->GetTitle());
	}

	if (note->GetDescription().empty())
	{
		stmt.BindNull(3);
	}
	else
	{
		stmt.Bind(3, note->GetDescription());
	}

	if (note->GetDescriptionAudioFile().empty())
	{
		stmt.BindNull(4);
	}
	else
	{
		stmt.Bind(4, note->GetDescriptionAudioFile());
	}

	if (note->GetTitleAudioFile().empty())
	{
		stmt.BindNull(5);
	}
	else
	{
		stmt.Bind(5, note->GetTitleAudioFile());
	}


	//stmt.Bind(2, wxLongLong(note->GetType()));
    stmt.ExecuteUpdate();	
	long id = this->ddl->GetLastRowID();
	note->SetNoteId(id);
}

void SqliteProvider::Update(Note* note)
{
	try
	{
		wxSQLite3Statement stmt = db->PrepareStatement("update Note set TopicId = ?, Title = ?, Description = ?, TitleAudioFile = ?, DescriptionAudioFile = ? where NoteId = ?;");
		stmt.Bind(1, wxLongLong(note->GetTopicId()));
		//stmt.Bind(2, wxLongLong(note->GetType()));
		if (note->GetTitle().empty())
		{
			stmt.BindNull(2);
		}
		else
		{
			stmt.Bind(2, note->GetTitle());
		}

		if (note->GetDescription().empty())
		{
			stmt.BindNull(3);
		}
		else
		{
			stmt.Bind(3, note->GetDescription());
		}

		if (note->GetTitleAudioFile().empty())
		{
			stmt.BindNull(4);
		}
		else
		{
			stmt.Bind(4, note->GetTitleAudioFile());
		}

		if (note->GetDescriptionAudioFile().empty())
		{
			stmt.BindNull(5);
		}
		else
		{
			stmt.Bind(5, note->GetDescriptionAudioFile());
		}
		stmt.Bind(6, wxLongLong(note->GetNoteId()));
		stmt.ExecuteUpdate();	
	}
	catch(wxSQLite3Exception& e)
	{
		throw e.GetMessage().ToStdWstring();
	}
	
}

void SqliteProvider::Delete(Note* note)
{
	wxSQLite3Statement stmt = db->PrepareStatement("delete from Note where NoteId = ?;");
	stmt.Bind(1, wxLongLong(note->GetNoteId()));
	stmt.ExecuteUpdate();
}

void SqliteProvider::GetNotesByTopic(Topic* topic, boost::ptr_vector<Note>* noteList)
{
	wxSQLite3Statement stmt = db->PrepareStatement("SELECT NoteId, TopicId, Title, Description, TitleAudioFile, DescriptionAudioFile, CreatedDate FROM Note WHERE TopicId = ? ORDER BY CreatedDate ASC;");
	stmt.Bind(1, wxLongLong(topic->getTopicId()));
	wxSQLite3ResultSet set = stmt.ExecuteQuery();
	while(set.NextRow())
	{
		Note* note = new Note();
		this->SetNoteFromRecord(note, set);
		noteList->push_back(note);
	}
}

int SqliteProvider::GetSegmentCount(Note* note)
{
	int segmentCount = 0;
	wxSQLite3Statement stmt = db->PrepareStatement("SELECT count(*) as segmentCount FROM NoteSegment WHERE NoteId = ?;");
	stmt.Bind(1, wxLongLong(note->GetNoteId()));
	wxSQLite3ResultSet set = stmt.ExecuteQuery();
	while(set.NextRow())
	{
		segmentCount = set.GetInt(0);
	}
	set.Finalize();
	stmt.Finalize();
	return segmentCount;
}

void SqliteProvider::GetSegmentDisplay(Note* note, std::wstring& displayBuffer)
{
	wxSQLite3Statement stmt = db->PrepareStatement("SELECT Title FROM NoteSegment WHERE NoteId = ? limit 10;");
	stmt.Bind(1, wxLongLong(note->GetNoteId()));
	wxSQLite3ResultSet set = stmt.ExecuteQuery();
	while(set.NextRow())
	{
		wxString title = set.GetString(0, "");
		if(displayBuffer.length() > 0)
		{
			displayBuffer.append(L" ... ");
		}
		displayBuffer.append(title.ToStdWstring());
	}
	set.Finalize();
	stmt.Finalize();
}


void SqliteProvider::SetNoteFromRecord(Note* note, wxSQLite3ResultSet& set)
{
	note->SetNoteId(set.GetInt64("NoteId").ToLong());
	//note->SetType(set.GetInt64("Type").ToLong());
	if (!set.IsNull("Title"))
	{
		note->SetTitle(set.GetAsString("Title").ToStdWstring());
	}
	if (!set.IsNull("Description"))
	{
		note->SetDescription(set.GetAsString("Description").ToStdWstring());
	}
	if (!set.IsNull("TitleAudioFile"))
	{
		note->SetTitleAudioFile(set.GetAsString("TitleAudioFile").ToStdWstring());
	}
	if (!set.IsNull("DescriptionAudioFile"))
	{
		note->SetDescriptionAudioFile(set.GetAsString("DescriptionAudioFile").ToStdWstring());
	}
	note->SetTopicId(set.GetInt64("TopicId").ToLong());
	note->SetCreatedDate(set.GetDateTime("CreatedDate"));
}


void SqliteProvider::Insert(NoteSegment* noteSegment){
	if(noteSegment->GetNoteId() < 1)
	{
		throw "Invalid argument, NoteSegment had null NoteId";
		return;
	}
	// need something field to begin with, will get the actual timestamp from database subsequent reloads 
	noteSegment->SetCreatedDate(wxDateTime::Now());
	wxSQLite3Statement stmt = db->PrepareStatement("insert into NoteSegment(NoteId, NoteSegmentTypeId, Title, Body, BodyFile) values (?, ?, ?, ?, ?);");
	stmt.Bind(1, wxLongLong(noteSegment->GetNoteId()));
	stmt.Bind(2, wxLongLong(noteSegment->GetNoteSegmentTypeId()));
	stmt.Bind(3, noteSegment->GetTitle());
	stmt.Bind(4, noteSegment->GetBody());
	wxString bodyFile(noteSegment->GetBodyFile());
	if(bodyFile.IsEmpty())
	{
		stmt.BindNull(5);
	}
	else
	{
		stmt.Bind(5, bodyFile);
	}

	
    stmt.ExecuteUpdate();	
	long id = this->ddl->GetLastRowID();
	noteSegment->SetNoteSegmentId(id);
}


void SqliteProvider::Update(NoteSegment* noteSegment)
{
	try
	{
		wxSQLite3Statement stmt = db->PrepareStatement("update NoteSegment set NoteId = ?, NoteSegmentTypeId = ?, Title = ?,  Body = ?, BodyFile = ? where NoteSegmentId = ?;");
		stmt.Bind(1, wxLongLong(noteSegment->GetNoteId()));
		stmt.Bind(2, wxLongLong(noteSegment->GetNoteSegmentTypeId()));
		stmt.Bind(3, noteSegment->GetTitle());
		stmt.Bind(4, noteSegment->GetBody());
		stmt.Bind(5, noteSegment->GetBodyFile());
		stmt.Bind(6, wxLongLong(noteSegment->GetNoteSegmentId()));
		stmt.ExecuteUpdate();	
	}
	catch(wxSQLite3Exception& e)
	{
		throw e.GetMessage().ToStdWstring();
	}
}


void SqliteProvider::Delete(NoteSegment* noteSegment)
{
	wxSQLite3Statement stmt = db->PrepareStatement("delete from NoteSegment where NoteSegmentId = ?;");
	stmt.Bind(1, wxLongLong(noteSegment->GetNoteSegmentId()));
	stmt.ExecuteUpdate();
}

void SqliteProvider::GetNoteSegmentsByNote(Note* note, boost::ptr_vector<NoteSegment>* noteSegmentList)
{
	wxSQLite3Statement stmt = db->PrepareStatement("SELECT NoteId, NoteSegmentTypeId, NoteSegmentId, Title, Body, BodyFile, CreatedDate FROM NoteSegment WHERE NoteId = ? ORDER BY CreatedDate ASC;");
	stmt.Bind(1, wxLongLong(note->GetNoteId()));
	wxSQLite3ResultSet set = stmt.ExecuteQuery();
	while(set.NextRow())
	{
		NoteSegment* noteSegment = new NoteSegment();
		this->SetNoteSegmentFromRecord(noteSegment, set);
		noteSegmentList->push_back(noteSegment);
	}
}

void SqliteProvider::SetNoteSegmentFromRecord(NoteSegment* noteSegment, wxSQLite3ResultSet& set)
{
	noteSegment->SetNoteSegmentId(set.GetInt64("NoteSegmentId").ToLong());
	noteSegment->SetNoteId(set.GetInt64("NoteId").ToLong());
	if (!set.IsNull("NoteSegmentTypeId"))
	{
		noteSegment->SetNoteSegmentTypeId(set.GetInt64("NoteSegmentTypeId").ToLong());
	}
	noteSegment->SetTitle(set.GetString("Title").ToStdWstring());
	noteSegment->SetBody(set.GetString("Body").ToStdWstring());
	noteSegment->SetCreatedDate(set.GetDateTime("CreatedDate"));
	if(!set.IsNull("BodyFile"))
	{
		noteSegment->SetBodyFile(set.GetString("BodyFile").ToStdWstring());
	}

}



void SqliteProvider::CreateSystemData()
{
	this->noteSegmentTypeProvider->CreateSystemData();

}


void SqliteProvider::CreateSampleData()
{
	this->noteSegmentTypeProvider->CreateSampleData();
	Shelf shelf(L"Household");
	this->Insert(&shelf);
	Subject subject(shelf.getShelfId(), L"Cooking");
	this->Insert(&subject);
	Publication publication(subject.getSubjectId(), L"Moosewood Cookbook");
	this->Insert(&publication);
	Topic topic(publication.getPublicationId(), L"Table of Conversions");
	this->Insert(&topic);
	Note note(topic.getTopicId());
	note.SetTitle(L"Conversions");
	note.SetDescription(L"Conversions for Dry and Buld Ingredients");
	this->Insert(&note);
	NoteSegment noteSegmentDry(note.GetNoteId());
	noteSegmentDry.SetTitle(L"Dry Ingredients");
	noteSegmentDry.SetBody(L"Beans (any type): 1/2 cup = 100 grams");
	this->Insert(&noteSegmentDry);
	NoteSegment noteSegmentBulk(note.GetNoteId());
	noteSegmentBulk.SetTitle(L"Bulk Ingredients");
	noteSegmentBulk.SetBody(L"Cheese: 1lb = 4 to 5 cups (packed), grated");
	this->Insert(&noteSegmentBulk);
	this->quizProvider->CreateSampleData(&topic);
}