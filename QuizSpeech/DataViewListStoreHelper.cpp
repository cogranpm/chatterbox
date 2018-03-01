#include "DataViewListStoreHelper.h"



DataViewListStoreHelper::DataViewListStoreHelper()
{
}


DataViewListStoreHelper::~DataViewListStoreHelper()
{
}

int DataViewListStoreHelper::SortByString(const wxDataViewListStore* store, const wxDataViewItem &item1, const wxDataViewItem &item2, unsigned int column, bool ascending)
{
	wxString display;
	wxString display1;
	if (item1.IsOk())
	{
		wxVariant itemVar;
		wxVariant itemVar1;
		store->GetValue(itemVar, item1, column);
		store->GetValue(itemVar1, item2, column);
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

int DataViewListStoreHelper::SortByInt(const wxDataViewListStore* store, const wxDataViewItem &item1, const wxDataViewItem &item2, unsigned int column, bool ascending)
{
	int intItem;
	int intItem1;
	if (item1.IsOk())
	{
		wxVariant itemVar;
		wxVariant itemVar1;
		store->GetValue(itemVar, item1, column);
		store->GetValue(itemVar1, item2, column);
		intItem = itemVar.GetInteger();
		intItem1 = itemVar1.GetInteger();
		if (ascending)
		{
			return intItem < intItem1;
		}
		else
		{
			return intItem > intItem1;
		}

	}
	return true;
}