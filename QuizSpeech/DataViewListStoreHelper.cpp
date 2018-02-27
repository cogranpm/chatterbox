#include "DataViewListStoreHelper.h"



DataViewListStoreHelper::DataViewListStoreHelper()
{
}


DataViewListStoreHelper::~DataViewListStoreHelper()
{
}

int DataViewListStoreHelper::SortByString(wxDataViewListStore& store, const wxDataViewItem &item1, const wxDataViewItem &item2, unsigned int column, bool ascending)
{
	wxString display;
	wxString display1;
	if (item1.IsOk())
	{
		wxVariant itemVar;
		wxVariant itemVar1;
		store.GetValue(itemVar, item1, column);
		store.GetValue(itemVar1, item2, column);
		display = itemVar.GetString();
		display1 = itemVar1.GetString();
		if (ascending)
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