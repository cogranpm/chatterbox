#include "ShelfDataViewListStore.h"
#include "DataViewListStoreHelper.h"

ShelfDataViewListStore::ShelfDataViewListStore() :wxDataViewListStore()
{
}


ShelfDataViewListStore::~ShelfDataViewListStore()
{
}

int ShelfDataViewListStore::Compare(const wxDataViewItem &item1, const wxDataViewItem &item2, unsigned int column, bool ascending) const
{

	if (column == 0)
	{
		return true;
	}
	else if (column == 1)
	{
		return DataViewListStoreHelper::SortByString(*this, item1, item2, column, ascending);
		wxString display;
		wxString display1;
		if (item1.IsOk())
		{
			wxVariant itemVar;
			wxVariant itemVar1;
			this->GetValue(itemVar, item1, column);
			this->GetValue(itemVar1, item2, column);
			display = itemVar.GetString();
			display1 = itemVar1.GetString();
			if(ascending)
			{ 
				return display.CmpNoCase(display1);
			}
			else
			{
				return display1.CmpNoCase(display);
			}
			
		}
		return true;
	}
}
