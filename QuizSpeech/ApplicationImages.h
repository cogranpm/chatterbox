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
	//not sure these even need to be pointers
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
	std::unique_ptr<wxBitmap> taskcomplete_icon;
	std::unique_ptr<wxBitmap> taskreject_icon;
	std::unique_ptr<wxIcon> taskCompleteIcon;
	std::unique_ptr<wxIcon> taskRejectIcon;
	std::unique_ptr<wxBitmap> docpreview_bmp;
	std::unique_ptr<wxIcon> docpreview_icon;
};

