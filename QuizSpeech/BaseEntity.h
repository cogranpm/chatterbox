#pragma once
#include "stdafx.h"

class BaseEntity
{

	bool isDeleted;
	bool isDirty;

public:
	BaseEntity();
	~BaseEntity();
	bool GetDirty() { return isDirty; }
	void SetDirty(bool dirty) { isDirty = dirty; }
	bool GetDeleted() { return isDeleted; }
	void SetDeleted(bool deleted) { isDeleted = deleted; }
	void FirePropertyChange();
	void FirePropertyChange(std::wstring oldValue, std::wstring newValue);
	void FirePropertyChange(long oldValue, long newValue);
};

