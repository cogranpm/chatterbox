#include "ExportDialogImp.h"
#include "MyApp.h"
#include <wx/app.h> 
#include <wx/log.h> 

ExportDialogImp::ExportDialogImp( wxWindow* parent )
:
ExportDialog( parent )
{

}

void ExportDialogImp::OnOKButtonClick( wxCommandEvent& event )
{
	if (this->filePicker->GetPath().empty())
	{
		return;
	}
	wxGetApp().GetProvider()->Export(this->filePicker->GetPath().ToStdWstring());
	event.Skip();
}
