#include "SettingsDialogImp.h"

SettingsDialogImp::SettingsDialogImp( wxWindow* parent )
:
DlgSettings( parent ), dataDirectory(), dataDirectoryDirty(false)
{

}

void SettingsDialogImp::OnInitDialog(wxInitDialogEvent& event)
{
	dataDirPicker->SetPath(dataDirectory);
}

void SettingsDialogImp::OnOKButtonClick( wxCommandEvent& event )
{
	SetDataDirectory(dataDirPicker->GetPath());
	event.Skip();
}

void SettingsDialogImp::DataDirectoryOnDirChanged(wxFileDirPickerEvent& event)
{
	dataDirectoryDirty = true;
}
