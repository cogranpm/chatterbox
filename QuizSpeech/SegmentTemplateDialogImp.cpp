#include "SegmentTemplateDialogImp.h"
#include "MyApp.h"
#include <wx/app.h> 
#include "GlobalConstants.h"


struct findSegmentTypeById
{
	findSegmentTypeById(unsigned long id) : _id(id) {};
	unsigned long _id;

	bool operator () (const NoteSegmentType& arg) const
	{
		return (_id == arg.getId());
	}
};

SegmentTemplateDialogImp::SegmentTemplateDialogImp( wxWindow* parent, SegmentTypeViewModel* viewModel) 
:
SegmentTemplateDialog( parent ), viewModel(viewModel), fontBuilder()
{
}

void SegmentTemplateDialogImp::OnInitDialog(wxInitDialogEvent& event)
{ 

	helpText = viewModel->GetModifiedHeader().getHelpText();
	name = viewModel->GetModifiedHeader().getTitle();

	this->btnNew->SetBitmap(*wxGetApp().GetImages().addnewitem_icon);
	this->btnRemove->SetBitmap(*wxGetApp().GetImages().delete_icon);

	this->colTitle->SetWidth(wxCOL_WIDTH_AUTOSIZE);
	this->colTitle->SetFlag(wxDATAVIEW_COL_SORTABLE);
	this->colFont->SetWidth(wxCOL_WIDTH_AUTOSIZE);
	this->colSize->SetWidth(wxCOL_WIDTH_AUTOSIZE);
	//go into new mode for segment types by default
	viewModel->AddSegmentType();
	if (!viewModel->IsNew())
	{
		this->TransferDataToWindow();
		//load the child segments
		wxGetApp().GetProvider()->GetNoteSegmentTypeProvider().GetNoteSegmentTypesByHeader(&viewModel->GetModifiedHeader(), viewModel->getSegmentList());
		RenderSegments();
	}
}

void SegmentTemplateDialogImp::RenderSegments()
{
	lstSegments->DeleteAllItems();
	wxVector<wxVariant> data;
	for (int i = 0; i < viewModel->getSegmentList()->size(); i++)
	{
		NoteSegmentType segmentType = viewModel->getSegmentList()->at(i);
		if (segmentType.GetDeleted())
		{
			continue;
		}
		unsigned long segmentTypeId = segmentType.getId();
		std::wstring title = segmentType.getTitle();
		if (title.empty())
		{
			title = ::NULL_LIST_INDICATOR;
		}
		std::string fontDesc = segmentType.getFontDesc();
		wxFont font(fontDesc);
	//	std::wstring fontSize(boost::lexical_cast<std::wstring>(segmentType.getFontSize()));
		data.push_back(wxVariant(title));
		if (font.IsOk())
		{
			data.push_back(wxVariant(font.GetFaceName().ToStdWstring()));
			data.push_back(wxVariant(boost::lexical_cast<std::wstring>(font.GetPointSize())));
		}
		else
		{
			data.push_back(wxVariant(::NULL_LIST_INDICATOR));
			data.push_back(wxVariant(::NULL_LIST_INDICATOR));
		}
		lstSegments->AppendItem(data, segmentTypeId);
		data.clear();
		//this->lstTypes->Append(header.getTitle(), reinterpret_cast<void*>(headerId));
		
	}
}

//bool SegmentTemplateDialogImp::TransferToWindow()
//{
//	this->txtName->SetValue(viewModel->GetModifiedHeader().getTitle());
//	//this->txtHelp->SetValue(viewModel->GetModifiedHeader().getHelpText());
//
//	return true;
//}

//bool SegmentTemplateDialogImp::TransferFromWindow()
//{
//	return true;
//}

void SegmentTemplateDialogImp::AddUpdateOnButtonClick( wxCommandEvent& event )
{
	int selectedRow = lstSegments->GetSelectedRow();
	GetSegmentTypeFromWindow();
	/* if new then need to add to the list */
	if (btnAddUpdate->GetLabelText() == "Add")
	{
		viewModel->getSegmentList()->push_back(viewModel->GetSelectedSegmentType());
	}
	RenderSegments();
	if (selectedRow != wxNOT_FOUND)
	{
		lstSegments->SelectRow(selectedRow);
	}
	txtTitle->SetFocus();
}

void SegmentTemplateDialogImp::NewOnButtonClick( wxCommandEvent& event )
{
	viewModel->AddSegmentType();
	SendSegmentTypeToWindow();
	btnAddUpdate->SetLabel(L"Add");
	fontPicker->SetSelectedFont(*wxNORMAL_FONT);
	txtTitle->SetFocus();
}

void SegmentTemplateDialogImp::RemoveOnButtonClick( wxCommandEvent& event )
{
	if (viewModel->GetSelectedSegmentType() != nullptr)
	{
		viewModel->GetSelectedSegmentType()->SetDeleted(true);
		RenderSegments();
	}
}

void SegmentTemplateDialogImp::RemoveOnUpdateUI( wxUpdateUIEvent& event )
{
	if (this->lstSegments->GetSelectedRow() == wxNOT_FOUND)
	{
		btnRemove->Disable();
	}
	else
	{
		btnRemove->Enable();
	}
}


void SegmentTemplateDialogImp::OnCancelButtonClick( wxCommandEvent& event )
{
	event.Skip();
}

void SegmentTemplateDialogImp::OnOKButtonClick( wxCommandEvent& event )
{
	this->txtName->GetValidator()->TransferFromWindow();
	this->txtHelp->GetValidator()->TransferFromWindow();
	if (this->txtName->IsEmpty())
	{
		//this->m_infoCtrl->ShowMessage("Title may not be empty");
		this->txtName->SetFocus();
	}
	else
	{
		viewModel->GetModifiedHeader().setTitle(name.ToStdWstring());
		viewModel->GetModifiedHeader().setHelpText(helpText.ToStdWstring());
		event.Skip();
	}
	
}

void SegmentTemplateDialogImp::OnSegmentListSelectionChanged(wxDataViewEvent& event) 
{ 
	EditItem();
}

void SegmentTemplateDialogImp::EditItem()
{
	wxDataViewItem item = lstSegments->GetSelection();
	if (item.IsOk())
	{
		wxUIntPtr data = lstSegments->GetItemData(item);
		NoteSegmentType* foundItem = FindSelectedNoteSegmentType(data);
		if (foundItem != nullptr)
		{

			viewModel->SetSelectedSegmentType(foundItem);
			SendSegmentTypeToWindow();
			btnAddUpdate->SetLabel(L"Update");
		}
	}
}

NoteSegmentType* SegmentTemplateDialogImp::FindSelectedNoteSegmentType(long id)
{
	boost::ptr_vector<NoteSegmentType>::iterator it = std::find_if(this->viewModel->getSegmentList()->begin(),
		this->viewModel->getSegmentList()->end(),
		findSegmentTypeById(id));
	
	if (it != this->viewModel->getSegmentList()->end())
	{
		size_t index = std::distance(this->viewModel->getSegmentList()->begin(), it);
		return &this->viewModel->getSegmentList()->at(index);
	}
	else
	{
		return nullptr;
	}
}

bool SegmentTemplateDialogImp::ValidateHeader()
{
	
	return true;
}

bool SegmentTemplateDialogImp::ValidateSegment()
{
	return true;
}

void SegmentTemplateDialogImp::SendSegmentTypeToWindow()
{
	NoteSegmentType* selectedItem = viewModel->GetSelectedSegmentType();
	//static_assert((foundItem == nullptr), "selectedSegmentType is null");
	txtTitle->SetValue(selectedItem->getTitle());
	wxFont itemFont(selectedItem->getFontDesc());
	fontPicker->SetSelectedFont(itemFont);
}

void SegmentTemplateDialogImp::GetSegmentTypeFromWindow()
{
	NoteSegmentType* selectedItem = viewModel->GetSelectedSegmentType();
	selectedItem->setTitle(txtTitle->GetValue().ToStdWstring());
	selectedItem->setFontDesc(fontPicker->GetSelectedFont().GetNativeFontInfoDesc().ToStdString());
}