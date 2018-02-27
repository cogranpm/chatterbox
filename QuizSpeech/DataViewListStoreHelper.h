#pragma 
#include <wx/dataview.h>

class DataViewListStoreHelper
{
public:
	DataViewListStoreHelper();
	~DataViewListStoreHelper();
	static int SortByString(wxDataViewListStore& store, const wxDataViewItem &item1, const wxDataViewItem &item2, unsigned int column, bool ascending);
};

