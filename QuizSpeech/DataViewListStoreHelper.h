#pragma 
#include <wx/dataview.h>

class DataViewListStoreHelper
{
public:
	DataViewListStoreHelper();
	~DataViewListStoreHelper();
	static int SortByString(const wxDataViewListStore* store, const wxDataViewItem &item1, const wxDataViewItem &item2, unsigned int column, bool ascending);
	static int SortByInt(const wxDataViewListStore* store, const wxDataViewItem &item1, const wxDataViewItem &item2, unsigned int column, bool ascending);
};

