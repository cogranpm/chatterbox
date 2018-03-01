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
		return DataViewListStoreHelper::SortByInt(this, item1, item2, column, ascending);
	}
	else if (column == 1)
	{
		return DataViewListStoreHelper::SortByString(this, item1, item2, column, ascending);
	}
}
