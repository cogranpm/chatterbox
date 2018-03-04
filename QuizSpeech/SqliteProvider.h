#pragma once
#include "wx/wxsqlite3.h"

//provider helpers
#include "SqliteDDLProvider.h"
#include "SqlIteQuizProvider.h"
#include "SqliteNoteSegmentTypeProvider.h"
//entities
#include "Shelf.h"
#include "Subject.h"
#include "Publication.h"
#include "Topic.h"
#include "Note.h"
#include "NoteSegment.h"
#include "NoteSegmentTypeHeader.h"
#include "NoteSegmentType.h"

class SqliteProvider
{
public:
	SqliteProvider(void);
	~SqliteProvider(void);
	void Close();
	void initDB(const wxString dbPath);
	SqlIteQuizProvider& GetQuizProvider() { return *this->quizProvider; }
	SqliteNoteSegmentTypeProvider& GetNoteSegmentTypeProvider() { return *this->noteSegmentTypeProvider; }

	void Insert(Shelf* shelf);
	void Update(Shelf* shelf);
	void Delete(Shelf* shelf);
	void GetAllShelves(boost::ptr_vector<Shelf>* shelfList);
	

	void Insert(Subject* subject);
	void Update(Subject* subject);
	void Delete(Subject* subject);
	void GetSubjectsByShelf(Shelf* shelf, boost::ptr_vector<Subject>* subjectList);

	void Insert(Publication* publication);
	void Update(Publication* publication);
	void Delete(Publication* publication);
	void GetPublicationsBySubject(Subject* subject, boost::ptr_vector<Publication>* publicationList);

	void Insert(Topic* topic);
	void Update(Topic* topic);
	void Delete(Topic* topic);
	void GetTopicsByPublication(Publication* publication, boost::ptr_vector<Topic>* topicList);

	void Insert(Note* note);
	void Update(Note* note);
	void Delete(Note* note);
	void GetNotesByTopic(Topic* topic, boost::ptr_vector<Note>* noteList);
	int GetSegmentCount(Note* note);
	void GetSegmentDisplay(Note* note, std::wstring& displayBuffer);

	void Insert(NoteSegment* noteSegment);
	void Update(NoteSegment* noteSegment);
	void Delete(NoteSegment* noteSegment);
	void GetNoteSegmentsByNote(Note* note, boost::ptr_vector<NoteSegment>* noteSegmentList);


	void CreateSystemData();
	void CreateSampleData();

private:
	wxSQLite3Database* db;
	SqliteDDLProvider* ddl;
	std::unique_ptr<SqlIteQuizProvider> quizProvider;
	std::unique_ptr<SqliteNoteSegmentTypeProvider> noteSegmentTypeProvider;

	void SetShelfFromRecord(Shelf* shelf, wxSQLite3ResultSet& set);
	void SetSubjectFromRecord(Subject* subject, wxSQLite3ResultSet& set);
	void SetPublicationFromRecord(Publication* publication, wxSQLite3ResultSet& set);
	void SetTopicFromRecord(Topic* topic, wxSQLite3ResultSet& set);
	void SetNoteFromRecord(Note* note, wxSQLite3ResultSet& set);
	void SetNoteSegmentFromRecord(NoteSegment* noteSegement, wxSQLite3ResultSet& set);

	void SetVersion(int version);
	int GetVersion();
};

