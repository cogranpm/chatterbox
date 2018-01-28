#include "ApplicationImages.h"
#include "resource.h"

ApplicationImages::ApplicationImages() :
	start_icon(nullptr)
{
	
}


ApplicationImages::~ApplicationImages()
{
	
}

void ApplicationImages::Init()
{
	wxInitAllImageHandlers();
	start_icon = std::make_unique<wxBitmap>(wxBITMAP_PNG(icon_png_start));
	pause_icon = std::make_unique<wxBitmap>(wxBITMAP_PNG(icon_png_pause));
	record_icon = std::make_unique<wxBitmap>(wxBITMAP_PNG(icon_png_record));
	stop_icon = std::make_unique<wxBitmap>(wxBITMAP_PNG(icon_png_stop));
	delete_icon = std::make_unique<wxBitmap>(wxBITMAP_PNG(icon_png_delete));
	edit_icon = std::make_unique<wxBitmap>(wxBITMAP_PNG(icon_png_edit));
	edit_label_icon = std::make_unique<wxBitmap>(wxBITMAP_PNG(icon_png_editlabel));
	add_icon = std::make_unique<wxBitmap>(wxBITMAP_PNG(icon_png_add));
	addnewitem_icon = std::make_unique<wxBitmap>(wxBITMAP_PNG(icon_png_addnewitem));
	assign_icon = std::make_unique<wxBitmap>(wxBITMAP_PNG(icon_png_assign));
	playstep_icon = std::make_unique<wxBitmap>(wxBITMAP_PNG(icon_png_playstep));
	lock_icon = std::make_unique<wxBitmap>(wxBITMAP_PNG(icon_png_lock));
	unlock_icon = std::make_unique<wxBitmap>(wxBITMAP_PNG(icon_png_unlock));
	next_icon = std::make_unique<wxBitmap>(wxBITMAP_PNG(icon_png_next));
	disconnect_icon = std::make_unique<wxIcon>(wxICON(icon_ico_disconnect));
}
