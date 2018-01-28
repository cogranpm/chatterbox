#pragma once

#include <memory>
#include <wx/bitmap.h>
#include <wx/icon.h>

class ApplicationImages
{
	
	

public:
	ApplicationImages();
	~ApplicationImages();
	void Init();
	std::unique_ptr<wxBitmap> start_icon;
	std::unique_ptr<wxBitmap> pause_icon;
	std::unique_ptr<wxBitmap> record_icon;
	std::unique_ptr<wxBitmap> stop_icon;
	std::unique_ptr<wxBitmap> delete_icon;
	std::unique_ptr<wxBitmap> edit_icon;
	std::unique_ptr<wxBitmap> edit_label_icon;
	std::unique_ptr<wxBitmap> add_icon;
	std::unique_ptr<wxBitmap> addnewitem_icon;
	std::unique_ptr<wxBitmap> assign_icon;
	std::unique_ptr<wxBitmap> playstep_icon;
	std::unique_ptr<wxBitmap> lock_icon;
	std::unique_ptr<wxBitmap> unlock_icon;
	std::unique_ptr<wxIcon> disconnect_icon;
	std::unique_ptr<wxBitmap> next_icon;
};

