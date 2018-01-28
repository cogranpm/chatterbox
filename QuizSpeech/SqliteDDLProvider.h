#pragma once

/************************************
provide re-usable ddl centered sqlite 
functionality such as creating tables,
triggers etc.
*************************************/

#include "wx/wxsqlite3.h"


class SqliteDDLProvider
{

private:
	wxSQLite3Database* db;

public:
	SqliteDDLProvider(wxSQLite3Database* db);
	~SqliteDDLProvider();
	bool CreateTable(wxString tableName, wxString ddl);
	long GetLastRowID();
	void CreateDeleteTrigger(wxString tableName, wxString childTableName, wxString foreignKeyName);

};

