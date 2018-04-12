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
		if (ver == 1)
		{
			/* need to add a column comment to shelf, subject and publication */
			wxSQLite3Transaction trans(db);
			try
			{
				this->ddl->AddColumn("Shelf", "Comments", "VARCHAR");
				this->ddl->AddColumn("Subject", "Comments", "VARCHAR");
				this->ddl->AddColumn("Publication", "Comments", "VARCHAR");
				SetVersion(2);
				trans.Commit();
			}
			catch (wxSQLite3Exception &e)
			{
				trans.Rollback();
			}
		}

		if (ver == 2)
		{
			/* need to add a column comment to shelf, subject and publication */
			wxSQLite3Transaction trans(db);
			try
			{
				this->ddl->AddColumn("Topic", "Comments", "VARCHAR");
				SetVersion(3);
				trans.Commit();
			}
			catch (wxSQLite3Exception &e)
			{
				trans.Rollback();
			}
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
	shelf->SetDirty(false);
}

void SqliteProvider::Update(Shelf* shelf)
{
	wxSQLite3Statement stmt = db->PrepareStatement("update Shelf set Title = ?, Comments = ? where ShelfId = ?;");
	stmt.Bind(1, shelf->getTitle());
	if (shelf->getComments().empty())
	{
		stmt.BindNull(2);
	}
	else
	{
		stmt.Bind(2, shelf->getComments());
	}
	stmt.Bind(3, wxLongLong(shelf->getShelfId()));
    stmt.ExecuteUpdate();	
	shelf->SetDirty(false);
}


void SqliteProvider::Delete(Shelf* shelf)
{
	wxSQLite3Statement stmt = db->PrepareStatement("delete from Shelf where ShelfId = ?;");
	stmt.Bind(1, wxLongLong(shelf->getShelfId()));
	stmt.ExecuteUpdate();
}


void SqliteProvider::GetAllShelves(boost::ptr_vector<Shelf>* _shelfList)
{

	wxSQLite3ResultSet set = db->ExecuteQuery(wxString("SELECT Title, ShelfId, Comments FROM Shelf ORDER BY UPPER(Title);"));
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
	if (!set.IsNull("Comments"))
	{
		shelf->setComments(set.GetAsString("Comments").ToStdWstring());
	}
	shelf->SetDirty(false);
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
	subject->SetDirty(false);
}


void SqliteProvider::Update(Subject* subject)
{
	try
	{
		wxSQLite3Statement stmt = db->PrepareStatement("update Subject set Title = ?, Comments = ?, ShelfId = ? where SubjectId = ?;");
		stmt.Bind(1, subject->getTitle());
		if (subject->getComments().empty())
		{
			stmt.BindNull(2);
		}
		else
		{
			stmt.Bind(2, subject->getComments());
		}
		stmt.Bind(3, wxLongLong(subject->getShelfId()));
		stmt.Bind(4, wxLongLong(subject->getSubjectId()));
		stmt.ExecuteUpdate();
		subject->SetDirty(false);
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
	wxSQLite3Statement stmt = db->PrepareStatement("SELECT SubjectId, Title, ShelfId, Comments FROM Subject WHERE ShelfId = ? ORDER BY UPPER(Title);");
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
	if (!set.IsNull("Comments"))
	{
		subject->setComments(set.GetAsString("Comments").ToStdWstring());
	}
	subject->SetDirty(false);
}

void SqliteProvider::Insert(Publication* publication)
{
	if( publication->getSubjectId() < 1)
	{
		throw "Invalid argument, Publication had null SubjectId";
		return;
	}
	wxSQLite3Statement stmt = db->PrepareStatement("insert into Publication(SubjectId, Title, Comments, Type) values (?, ?, ?, ?);");
	stmt.Bind(1, wxLongLong(publication->getSubjectId()));
	stmt.Bind(2, publication->getTitle());
	if (publication->getComments().empty())
	{
		stmt.BindNull(3);
	}
	else
	{
		stmt.Bind(3, publication->getComments());
	}
	stmt.Bind(4, publication->getType());
    stmt.ExecuteUpdate();	
	long id = this->ddl->GetLastRowID();
	publication->setPublicationId(id);
	publication->SetDirty(false);
}

void SqliteProvider::Update(Publication* publication)
{
	try
	{
		wxSQLite3Statement stmt = db->PrepareStatement("update Publication set Title = ?, Comments = ?, SubjectId = ?, Type = ? where PublicationId = ?;");
		stmt.Bind(1, publication->getTitle());
		if (publication->getComments().empty())
		{
			stmt.BindNull(2);
		}
		else
		{
			stmt.Bind(2, publication->getComments());
		}
		stmt.Bind(3, wxLongLong(publication->getSubjectId()));
		stmt.Bind(4, publication->getType());
		stmt.Bind(5, wxLongLong(publication->getPublicationId()));
		stmt.ExecuteUpdate();
		publication->SetDirty(false);
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
	wxSQLite3Statement stmt = db->PrepareStatement("SELECT PublicationId, Title, Type, SubjectId, Comments FROM Publication WHERE SubjectId = ? ORDER BY UPPER(Title);");
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
	if (!set.IsNull("Comments"))
	{
		publication->setComments(set.GetAsString("Comments").ToStdWstring());
	}
	publication->SetDirty(false);
}

void SqliteProvider::Insert(Topic* topic)
{
	if(topic->getPublicationId() < 1)
	{
		throw "Invalid argument, Topic had null PublicationId";
		return;
	}
	wxSQLite3Statement stmt = db->PrepareStatement("insert into Topic(PublicationId, Name, Comments) values (?, ?, ?);");
	stmt.Bind(1, wxLongLong(topic->getPublicationId()));
	stmt.Bind(2, topic->getName());
	if (topic->getComments().empty())
	{
		stmt.BindNull(3);
	}
	else
	{
		stmt.Bind(3, topic->getComments());
	}
    stmt.ExecuteUpdate();	
	long id = this->ddl->GetLastRowID();
	topic->setTopicId(id);
}

void SqliteProvider::Update(Topic* topic)
{
	try
	{
		wxSQLite3Statement stmt = db->PrepareStatement("update Topic set Name = ?, PublicationId = ?, Comments = ? where TopicId = ?;");
		stmt.Bind(1, topic->getName());
		stmt.Bind(2, wxLongLong(topic->getPublicationId()));
		if (topic->getComments().empty())
		{
			stmt.BindNull(3);
		}
		else
		{
			stmt.Bind(3, topic->getComments());
		}
		stmt.Bind(4, wxLongLong(topic->getTopicId()));
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
	wxSQLite3Statement stmt = db->PrepareStatement("SELECT PublicationId, Name, Comments, TopicId FROM Topic WHERE PublicationId = ? ORDER BY CreatedDate ASC;");
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
	if (!set.IsNull("Comments"))
	{
		topic->setComments(set.GetAsString("Comments").ToStdWstring());
	}
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
	wxSQLite3Statement stmt = db->PrepareStatement("insert into Note(TopicId, Title, Description, DescriptionAudioFile, TitleAudioFile ) values (?, ?, ?, ?, ?);");
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
	note->SetDirty(false);
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
		note->SetDirty(false);
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
	note->SetDirty(false);
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
	noteSegment->SetDirty(false);
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
		noteSegment->SetDirty(false);
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
	noteSegment->SetDirty(false);
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

void SqliteProvider::Export(const std::wstring& path)
{
	/* IMPORT data from previous version of application with different structure */

	/* note header maps to subject */

	/* need to add a default publication - perhaps call it imported */

	/* need to add a default topic, call it Topic? */

	/* note detail maps to Note, need to add 2 segments for comments and source code, body maps to description in the note */

	wxSQLite3Database db;
	std::map<unsigned long, Subject> notebooks;
	std::map<unsigned long, Topic> topics;
	try
	{
		db.Open(path);

		Shelf shelf(L"Study Manager");
		Insert(&shelf);
		wxSQLite3Statement stmt = db.PrepareStatement("SELECT ID, NAME, COMMENTS FROM NoteBook;");
		wxSQLite3ResultSet set = stmt.ExecuteQuery();
		while (set.NextRow())
		{
			/* map notebook to subject */
			unsigned long id = set.GetInt64("ID").ToLong();
			std::wstring name = set.GetAsString("NAME").ToStdWstring();
			Subject subject(shelf.getShelfId(), name);
			if (!set.IsNull("COMMENTS"))
			{
				std::wstring comments = set.GetAsString("COMMENTS").ToStdWstring();
				subject.setComments(comments);
			}
			Insert(&subject);
			GlobalConstants::PrintError(L"Subect:" + subject.getTitle(), S_OK);
			notebooks.insert(std::make_pair(id, subject));
		}

		for (std::map<unsigned long, Subject>::iterator it = notebooks.begin(); it != notebooks.end(); ++it)
		{
			/* do a single publication for each subject */
			Publication pub(it->second.getSubjectId(), L"Default");
			pub.setType(5);
			pub.setComments(L"Imported from Study Manager");
			Insert(&pub);

			/* create a topic for each note header */
			stmt = db.PrepareStatement("SELECT ID, NAME, COMMENTS FROM NoteHeader WHERE NOTEBOOKID = ?;");
			stmt.Bind(1, wxLongLong(it->first));
			set = stmt.ExecuteQuery();
			while (set.NextRow())
			{
				unsigned long id = set.GetInt64("ID").ToLong();
				std::wstring name = set.GetAsString("NAME").ToStdWstring();
				Topic topic(pub.getPublicationId(), name);
				if (!set.IsNull("COMMENTS"))
				{
					std::wstring comments = set.GetAsString("COMMENTS").ToStdWstring();
					topic.setComments(comments);
				}
				Insert(&topic);
				topics.insert(std::make_pair(id, topic));
				GlobalConstants::PrintError(L"Toipic:" + topic.getName(), S_OK);
			}
		}

		for (std::map<unsigned long, Topic>::iterator it = topics.begin(); it != topics.end(); ++it)
		{
			stmt = db.PrepareStatement("SELECT ID, NAME, BODY, SOURCECODE, COMMENTS FROM NOTEDETAIL WHERE NOTEHEADERID = ?;");
			stmt.Bind(1, wxLongLong(it->first));
			set = stmt.ExecuteQuery();
			while (set.NextRow())
			{
				unsigned long id = set.GetInt64("ID").ToLong();
				std::wstring name;
				std::wstring body;
				std::wstring sourceCode;
				std::wstring comments;

				if (!set.IsNull("NAME"))
				{
					name = set.GetAsString("NAME").ToStdWstring();
				}
				if (!set.IsNull("BODY"))
				{
					body = set.GetAsString("BODY").ToStdWstring();
				}
				if (!set.IsNull("COMMENTS"))
				{
					comments = set.GetAsString("COMMENTS").ToStdWstring();
				}
				if (!set.IsNull("SOURCECODE"))
				{
					sourceCode = set.GetAsString("SOURCECODE").ToStdWstring();
				}

				Note note(it->second.getTopicId());
				note.SetTitle(name);
				note.SetDescription(comments);
				Insert(&note);

				if (body.size() > 0)
				{
					NoteSegment bodySegment(note.GetNoteId());
					bodySegment.SetBody(body);
					bodySegment.SetTitle(L"Body");
					Insert(&bodySegment);
				}

				if (sourceCode.size() > 0)
				{
					NoteSegment sourceSegment(note.GetNoteId());
					sourceSegment.SetBody(sourceCode);
					sourceSegment.SetTitle(L"Source Code");
					Insert(&sourceSegment);
				}

				GlobalConstants::PrintError(L"Note:" + note.GetTitle(), S_OK);
			}
		}
			
	}
	catch (wxSQLite3Exception& ex)
	{
		GlobalConstants::PrintError(ex.GetMessage().ToStdWstring(), S_OK);
	}

	db.Close();
}

void SqliteProvider::RelocateAudioFiles(FileHandler* fileHandler)
{
	wxString audioPaths ("select shelf, subject, publication, audiofile from VAUDIOBYFOLDER order by shelf, subject, publication;");
	wxSQLite3Statement stmt = db->PrepareStatement(audioPaths);
	wxSQLite3ResultSet set = stmt.ExecuteQuery();
	wxString shelf;
	wxString subject;
	wxString publication;
	wxString audioFile;
	while (set.NextRow())
	{
		shelf = set.GetAsString(0);
		subject = set.GetAsString(1);
		publication = set.GetAsString(2);
		audioFile = set.GetAsString(3);

		std::wstring shelfAudioPath = fileHandler->GetAudioPath() + "\\" + shelf.ToStdWstring() + "\\";
		//fileHandler->SetCurrentPath(shelfAudioPath);
		//fileHandler->MakeDirectory(std::wstring(L""));

		std::wstring subjectAudioPath = shelfAudioPath + "\\" + subject.ToStdWstring() + "\\";
		//fileHandler->SetCurrentPath(subjectAudioPath);
		//fileHandler->MakeDirectory(std::wstring(L""));

		std::wstring publicationAudioPath = subjectAudioPath + "\\" + publication.ToStdWstring() + "\\";
		//fileHandler->SetCurrentPath(publicationAudioPath);
	//	fileHandler->MakeDirectory(std::wstring(L""));


	}
	set.Finalize();
	stmt.Finalize();
	
	return;


	/*
	std::wstring audioDirectory = dataDirectory + L"\\Audio\\";
	wxGetApp().GetFileHandler().MakeDirectory(L"Audio");
	wxGetApp().GetFileHandler().SetCurrentPath(audioDirectory);
	wxGetApp().GetFileHandler().SetAudioPath(audioDirectory);
	*/

	/* create folders for each shelf, subject and publication */
	boost::ptr_vector<Shelf> shelfList;
	this->GetAllShelves(&shelfList);
	for (boost::ptr_vector<Shelf>::iterator it = shelfList.begin(); it != shelfList.end(); ++it)
	{
		std::wstring shelfName = it->getTitle();
		if (shelfName.length() > 259)
		{
			continue;
		}
		std::wstring shelfAudioPath = fileHandler->GetAudioPath() + "\\" + shelfName + "\\";
		fileHandler->SetCurrentPath(shelfAudioPath);
		fileHandler->MakeDirectory(std::wstring(L""));
		
		boost::ptr_vector<Subject> subjectList;
		this->GetSubjectsByShelf(&(*it), &subjectList);
		for (boost::ptr_vector<Subject>::iterator st = subjectList.begin(); st != subjectList.end(); ++st)
		{
			std::wstring subjectName = st->getTitle();
			if (subjectName.length() > 259)
			{
				continue;
			}
			std::wstring subjectAudioPath = shelfAudioPath + "\\" + subjectName + "\\";
			fileHandler->SetCurrentPath(subjectAudioPath);
			fileHandler->MakeDirectory(std::wstring(L""));

			boost::ptr_vector<Publication> publicationList;
			this->GetPublicationsBySubject(&(*st), &publicationList);

			for (boost::ptr_vector<Publication>::iterator pt = publicationList.begin(); pt != publicationList.end(); ++pt)
			{
				std::wstring publicationName = pt->getTitle();
				if (publicationName.length() > 259)
				{
					continue;
				}
				std::wstring publicationAudioPath = subjectAudioPath + "\\" + publicationName + "\\";
				fileHandler->SetCurrentPath(publicationAudioPath);
				try
				{
					fileHandler->MakeDirectory(std::wstring(L""));
				}
				catch (...)
				{
					//forget it, could be an issue with file name
				}

				//move all note audio files
				//move all note segment audio files
				//move all quiz audio files
				//move all quiz run audio files

			}
		}
	}
}