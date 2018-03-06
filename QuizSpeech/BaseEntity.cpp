#include "BaseEntity.h"



BaseEntity::BaseEntity() : isDeleted(false), isDirty(false)
{
	int i = 0;
}


BaseEntity::~BaseEntity()
{
}

void BaseEntity::FirePropertyChange()
{
	SetDirty(true);
}

void BaseEntity::FirePropertyChange(std::wstring oldValue, std::wstring newValue)
{
	if (oldValue != newValue)
	{
		SetDirty(true);
	}
}

void BaseEntity::FirePropertyChange(long oldValue, long newValue)
{
	if (oldValue != newValue)
	{
		SetDirty(true);
	}
}

//void BaseEntity::FirePropertyChange(short oldValue, short newValue)
//{
//	if (oldValue != newValue)
//	{
//		SetDirty(true);
//	}
//}