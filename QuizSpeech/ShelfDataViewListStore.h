#pragma once
#include <wx/dataview.h>

class ShelfDataViewListStore :
	public wxDataViewListStore
{
public:
	ShelfDataViewListStore();
	~ShelfDataViewListStore();
	int Compare(const wxDataViewItem &item1, const wxDataViewItem &item2, unsigned int column, bool ascending) const;
};

