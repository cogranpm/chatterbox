#include "SqliteDDLProvider.h"



SqliteDDLProvider::SqliteDDLProvider(wxSQLite3Database* db) : db(db)
{
}


SqliteDDLProvider::~SqliteDDLProvider()
{
}

bool SqliteDDLProvider::CreateTable(wxString tableName, wxString ddl)
{
	if (!db->TableExists(tableName))
	{
		this->db->ExecuteUpdate(ddl);
		return true;
	}
	return false;
}

void SqliteDDLProvider::CreateDeleteTrigger(wxString tableName, wxString childTableName, wxString foreignKeyName)
{
	try
	{
		wxString trigger("");
		trigger.Append("CREATE TRIGGER IF NOT EXISTS delete_");
		trigger.Append(tableName);
		trigger.Append(" AFTER DELETE ON ");
		trigger.Append(tableName);
		trigger.Append(" FOR EACH ROW BEGIN ");
		trigger.Append(" DELETE FROM ");
		trigger.Append(childTableName);
		trigger.Append(" WHERE ");
		trigger.Append(foreignKeyName);
		trigger.Append(" = OLD.");
		trigger.Append(foreignKeyName);
		trigger.Append("; ");
		trigger.Append(" END ");
		db->ExecuteUpdate(trigger);

	}
	catch (wxSQLite3Exception &e)
	{
		throw e.GetMessage();
	}
}

long SqliteDDLProvider::GetLastRowID()
{
	long id;
	wxSQLite3ResultSet set = db->ExecuteQuery(wxString("select last_insert_rowid();"));
	while (set.NextRow())
	{
		id = set.GetInt64(0).ToLong();
	}
	return id;
}
