#include "SqliteNoteSegmentTypeProvider.h"
#include "HelpConstants.h"
#include "FontBuilder.h"

SqliteNoteSegmentTypeProvider::SqliteNoteSegmentTypeProvider(wxSQLite3Database* db, SqliteDDLProvider* ddl) : db(db), ddl(ddl), createFlag(false)
{
}


SqliteNoteSegmentTypeProvider::~SqliteNoteSegmentTypeProvider()
{
}

bool SqliteNoteSegmentTypeProvider::InitDB()
{

	createFlag = this->ddl->CreateTable("NoteSegmentTypeHeader", "CREATE TABLE NoteSegmentTypeHeader (NoteSegmentTypeHeaderId INTEGER PRIMARY KEY AUTOINCREMENT, Title VARCHAR NOT NULL, HelpText VARCHAR, CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
	createFlag = this->ddl->CreateTable("NoteSegmentType", R"(CREATE TABLE NoteSegmentType (NoteSegmentTypeId INTEGER PRIMARY KEY AUTOINCREMENT, 
	NoteSegmentTypeHeaderId INTEGER NOT NULL, Title VARCHAR(60), FontDesc VARCHAR,
	CreatedDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP, FOREIGN KEY(NoteSegmentTypeHeaderId) 
	REFERENCES NoteSegmentTypeHeader(NoteSegmentTypeHeaderId) ON DELETE CASCADE))");
	this->ddl->CreateDeleteTrigger("NoteSegmentTypeHeader", "NoteSegmentType", "NoteSegmentTypeHeaderId");
	return this->createFlag;
}



void SqliteNoteSegmentTypeProvider::Insert(NoteSegmentTypeHeader* noteSegmentTypeHeader)
{
	try
	{
		wxSQLite3Statement stmt = db->PrepareStatement("insert into NoteSegmentTypeHeader(Title, HelpText) values (?, ?);");
		stmt.Bind(1, noteSegmentTypeHeader->getTitle());
		stmt.Bind(2, noteSegmentTypeHeader->getHelpText());
		stmt.ExecuteUpdate();
		long id = this->ddl->GetLastRowID();
		noteSegmentTypeHeader->setId(id);
		noteSegmentTypeHeader->SetDirty(false);
	}
	catch (wxSQLite3Exception& e)
	{
		throw e.GetMessage().ToStdWstring();
	}
}

void SqliteNoteSegmentTypeProvider::Update(NoteSegmentTypeHeader* noteSegmentTypeHeader)
{
	try
	{
		wxSQLite3Statement stmt = db->PrepareStatement("update NoteSegmentTypeHeader set Title = ?, HelpText = ? where NoteSegmentTypeHeaderId = ?;");
		stmt.Bind(1, noteSegmentTypeHeader->getTitle());
		stmt.Bind(2, noteSegmentTypeHeader->getHelpText());
		stmt.Bind(3, wxLongLong(noteSegmentTypeHeader->getId()));
		stmt.ExecuteUpdate();
		noteSegmentTypeHeader->SetDirty(false);
	}
	catch (wxSQLite3Exception& e)
	{
		throw e.GetMessage().ToStdWstring();
	}
}

void SqliteNoteSegmentTypeProvider::Delete(NoteSegmentTypeHeader* noteSegmentTypeHeader)
{
	try
	{
		wxSQLite3Statement stmt = db->PrepareStatement("delete from NoteSegmentTypeHeader where NoteSegmentTypeHeaderId = ?;");
		stmt.Bind(1, wxLongLong(noteSegmentTypeHeader->getId()));
		stmt.ExecuteUpdate();
	}
	catch (wxSQLite3Exception& e)
	{
		throw e.GetMessage().ToStdWstring();
	}
}

void SqliteNoteSegmentTypeProvider::Insert(NoteSegmentType* noteSegmentType)
{
	try
	{
		if (noteSegmentType->getNoteSegmentTypeHeaderId() < 1)
		{
			throw "Invalid argument, NoteSegmentType had null HeaderId";
			return;
		}

		std::string sql = R"(insert into NoteSegmentType(NoteSegmentTypeHeaderId, Title, FontDesc) 
		values (?, ?, ?);)";
		wxSQLite3Statement stmt = db->PrepareStatement(sql);
		stmt.Bind(1, wxLongLong(noteSegmentType->getNoteSegmentTypeHeaderId()));

		wxString titleValue(noteSegmentType->getTitle());
		if (titleValue.IsEmpty())
		{
			stmt.BindNull(2);
		}
		else
		{
			stmt.Bind(2, titleValue);
		}

		wxString fontDesc(noteSegmentType->getFontDesc());
		if (fontDesc.IsEmpty())
		{
			stmt.BindNull(3);
		}
		else
		{
			stmt.Bind(3, fontDesc);
		}
		stmt.ExecuteUpdate();
		long id = this->ddl->GetLastRowID();
		noteSegmentType->setId(id);
		noteSegmentType->SetDirty(false);
	}
	catch (wxSQLite3Exception& e)
	{
		throw e.GetMessage().ToStdWstring();
	}
}

void SqliteNoteSegmentTypeProvider::Update(NoteSegmentType* noteSegmentType)
{
	try
	{
		wxSQLite3Statement stmt = db->PrepareStatement(R"(update NoteSegmentType 
		set NoteSegmentTypeHeaderId = ?, Title = ?,  FontDesc = ?
		where NoteSegmentTypeId = ?;)");
		stmt.Bind(1, wxLongLong(noteSegmentType->getNoteSegmentTypeHeaderId()));
		if(!noteSegmentType->getTitle().empty())
		{
			stmt.Bind(2, noteSegmentType->getTitle());
		}
		else
		{
			stmt.BindNull(2);
		}
		if (!noteSegmentType->getFontDesc().empty())
		{
			stmt.Bind(3, noteSegmentType->getFontDesc());
		}
		else
		{
			stmt.BindNull(3);
		}
		stmt.Bind(4, wxLongLong(noteSegmentType->getId()));
		stmt.ExecuteUpdate();
		noteSegmentType->SetDirty(false);
	}
	catch (wxSQLite3Exception& e)
	{
		throw e.GetMessage().ToStdWstring();
	}
}

void SqliteNoteSegmentTypeProvider::Delete(NoteSegmentType* noteSegmentType)
{
	try
	{
		wxSQLite3Statement stmt = db->PrepareStatement("delete from NoteSegmentType where NoteSegmentTypeId = ?;");
		stmt.Bind(1, wxLongLong(noteSegmentType->getId()));
		stmt.ExecuteUpdate();
	}
	catch (wxSQLite3Exception& e)
	{
		throw e.GetMessage().ToStdWstring();
	}
}

void SqliteNoteSegmentTypeProvider::GetAllNoteSegmentTypeHeaders(boost::ptr_vector<NoteSegmentTypeHeader>* list)
{
	wxSQLite3ResultSet set = db->ExecuteQuery(wxString("SELECT Title, HelpText, NoteSegmentTypeHeaderId FROM NoteSegmentTypeHeader ORDER BY Title;"));
	while (set.NextRow())
	{
		NoteSegmentTypeHeader* header = new NoteSegmentTypeHeader();
		this->SetNoteSegmentTypeHeaderFromRecord(header, set);
		list->push_back(header);
	}

}


void SqliteNoteSegmentTypeProvider::GetNoteSegmentTypeHeaderById(long id, NoteSegmentTypeHeader& header)
{
	try
	{
		wxSQLite3Statement stmt = db->PrepareStatement("SELECT * FROM NoteSegmentTypeHeader WHERE NoteSegmentTypeHeaderId = ?;");
		stmt.Bind(1, wxLongLong(id));
		wxSQLite3ResultSet set = stmt.ExecuteQuery();
		while (set.NextRow())
		{
			this->SetNoteSegmentTypeHeaderFromRecord(&header, set);
		}
	}
	catch (wxSQLite3Exception& e)
	{
		throw e.GetMessage().ToStdWstring();
	}

}


void SqliteNoteSegmentTypeProvider::GetNoteSegmentTypesByHeader(NoteSegmentTypeHeader* header, boost::ptr_vector<NoteSegmentType>* list)
{
	try
	{
		wxSQLite3Statement stmt = db->PrepareStatement(R"(SELECT NoteSegmentTypeHeaderId, NoteSegmentTypeId, Title, FontDesc, CreatedDate
		FROM NoteSegmentType WHERE NoteSegmentTypeHeaderId = ? ORDER BY CreatedDate;)");
		stmt.Bind(1, wxLongLong(header->getId()));
		wxSQLite3ResultSet set = stmt.ExecuteQuery();
		while (set.NextRow())
		{
			NoteSegmentType* noteSegmentType = new NoteSegmentType();
			this->SetNoteSegmentTypeFromRecord(noteSegmentType, set);
			list->push_back(noteSegmentType);
		}
	}
	catch (wxSQLite3Exception& e)
	{
		throw e.GetMessage().ToStdWstring();
	}
}


void SqliteNoteSegmentTypeProvider::GetNoteSegmentTypeById(long id, NoteSegmentType& noteSegmentType)
{
	try
	{
		wxSQLite3Statement stmt = db->PrepareStatement(R"(SELECT NoteSegmentTypeHeaderId, NoteSegmentTypeId, Title, FontDesc, CreatedDate FROM NoteSegmentType WHERE NoteSegmentTypeId = ?;)");
		stmt.Bind(1, wxLongLong(id));
		wxSQLite3ResultSet set = stmt.ExecuteQuery();
		while (set.NextRow())
		{
			this->SetNoteSegmentTypeFromRecord(&noteSegmentType, set);
		}
	}
	catch (wxSQLite3Exception& e)
	{
		throw e.GetMessage().ToStdWstring();
	}
}

void SqliteNoteSegmentTypeProvider::SetNoteSegmentTypeHeaderFromRecord(NoteSegmentTypeHeader* header, wxSQLite3ResultSet& set)
{
	header->setId(set.GetInt64("NoteSegmentTypeHeaderId").ToLong());
	header->setTitle(set.GetString("Title").ToStdWstring());
	if (!set.IsNull("HelpText"))
	{
		header->setHelpText(set.GetString("HelpText").ToStdWstring());
	}
	header->SetDirty(false);
}

void SqliteNoteSegmentTypeProvider::SetNoteSegmentTypeFromRecord(NoteSegmentType* noteSegmentType, wxSQLite3ResultSet& set)
{
	noteSegmentType->setId(set.GetInt64("NoteSegmentTypeId").ToLong());
	noteSegmentType->setNoteSegmentTypeHeaderId(set.GetInt64("NoteSegmentTypeHeaderId").ToLong());
	if (!set.IsNull("Title"))
	{
		noteSegmentType->setTitle(set.GetString("Title").ToStdWstring());
	}

	if (!set.IsNull("FontDesc"))
	{
		noteSegmentType->setFontDesc(set.GetString("FontDesc").ToStdString());
	}
	noteSegmentType->SetDirty(false);
}




void SqliteNoteSegmentTypeProvider::CreateSystemData()
{
	//create all the table data required by the application
	//basic note type
	FontBuilder fb;
	std::string fontDefaultDesc;
	std::string codeDefaultDesc;
	std::string summaryDefaultDesc;
	std::string footNoteDefaultDesc;
	fb.GetDefaultFontDesc(fontDefaultDesc);
	fb.GetCodeFontDesc(codeDefaultDesc);
	fb.GetSummaryFontDesc(summaryDefaultDesc);
	fb.GetFootnoteFontDesc(footNoteDefaultDesc);

	NoteSegmentTypeHeader header;
	header.setHelpText(HelpConstants::HELP_TEXT_SEGMENTTYPE_BASIC);
	header.setTitle(L"Basic");
	this->Insert(&header);
	NoteSegmentType segmentType;
	segmentType.setNoteSegmentTypeHeaderId(header.getId());
	segmentType.setTitle(L"");
	segmentType.setFontDesc(fontDefaultDesc);
	this->Insert(&segmentType);


	//technical article note type
	NoteSegmentTypeHeader headerTechnical;
	headerTechnical.setHelpText(HelpConstants::HELP_TEXT_SEGMENTTYPE_TECHNICALNOTE);
	headerTechnical.setTitle(L"Technical Note");
	this->Insert(&headerTechnical);

	//summary segment
	NoteSegmentType segmentTypeTechnicalSummary;
	segmentTypeTechnicalSummary.setNoteSegmentTypeHeaderId(headerTechnical.getId());
	segmentTypeTechnicalSummary.setTitle(L"Summary");
	segmentTypeTechnicalSummary.setFontDesc(summaryDefaultDesc);
	this->Insert(&segmentTypeTechnicalSummary);

	//Body segment
	NoteSegmentType segmentTypeTechnicalBody;
	segmentTypeTechnicalBody.setNoteSegmentTypeHeaderId(headerTechnical.getId());
	segmentTypeTechnicalBody.setTitle(L"Body");
	segmentTypeTechnicalBody.setFontDesc(fontDefaultDesc);
	this->Insert(&segmentTypeTechnicalBody);

	//Example segment
	NoteSegmentType segmentTypeTechnicalExample;
	segmentTypeTechnicalExample.setNoteSegmentTypeHeaderId(headerTechnical.getId());
	segmentTypeTechnicalExample.setTitle(L"Example");
	segmentTypeTechnicalExample.setFontDesc(footNoteDefaultDesc);
	this->Insert(&segmentTypeTechnicalExample);

	//journal entry note type
	NoteSegmentTypeHeader headerJournal;
	headerJournal.setHelpText(HelpConstants::HELP_TEXT_SEGMENTTYPE_JOURNALENTRY);
	headerJournal.setTitle(L"Journal Entry");
	this->Insert(&headerJournal);

	//summary segment
	NoteSegmentType segmentTypeJournal;
	segmentTypeJournal.setNoteSegmentTypeHeaderId(headerJournal.getId());
	segmentTypeJournal.setTitle(L"[NOW]");
	segmentTypeJournal.setFontDesc(fontDefaultDesc);
	this->Insert(&segmentTypeJournal);
}


void SqliteNoteSegmentTypeProvider::CreateSampleData()
{

}