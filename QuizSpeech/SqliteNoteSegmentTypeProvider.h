#pragma once

#include "stdafx.h"
#include "wx/wxsqlite3.h"
#include "SqliteDDLProvider.h"
#include "NoteSegmentTypeHeader.h"
#include "NoteSegmentType.h"


class SqliteNoteSegmentTypeProvider
{

private:
	wxSQLite3Database * db;
	SqliteDDLProvider* ddl;
	bool createFlag;

	void SetNoteSegmentTypeHeaderFromRecord(NoteSegmentTypeHeader* header, wxSQLite3ResultSet& set);
	void SetNoteSegmentTypeFromRecord(NoteSegmentType* noteSegmentType, wxSQLite3ResultSet& set);

public:
	SqliteNoteSegmentTypeProvider(wxSQLite3Database* db, SqliteDDLProvider* ddl);
	~SqliteNoteSegmentTypeProvider();
	void CreateSampleData();
	void CreateSystemData();
	bool InitDB();
	void Insert(NoteSegmentTypeHeader* noteSegmentTypeHeader);
	void Update(NoteSegmentTypeHeader* noteSegmentTypeHeader);
	void Delete(NoteSegmentTypeHeader* noteSegmentTypeHeader);
	void GetAllNoteSegmentTypeHeaders(boost::ptr_vector<NoteSegmentTypeHeader>* list);

	void Insert(NoteSegmentType* noteSegment);
	void Update(NoteSegmentType* noteSegment);
	void Delete(NoteSegmentType* noteSegment);

	void GetNoteSegmentTypesByHeader(NoteSegmentTypeHeader* header, boost::ptr_vector<NoteSegmentType>* list);
	void GetNoteSegmentTypeHeaderById(long id, NoteSegmentTypeHeader& header);
	void GetNoteSegmentTypeById(long id, NoteSegmentType& noteSegmentType);

};

