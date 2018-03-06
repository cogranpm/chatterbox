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
	bool CreateTable(const wxString& tableName, const wxString& ddl);
	long GetLastRowID();
	void CreateDeleteTrigger(const wxString& tableName, const wxString& childTableName, const wxString& foreignKeyName);
	bool AddColumn(const wxString& tableName, const wxString& columnName, const wxString& columnDef);
};

