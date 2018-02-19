#include "MainFrameImp.h"
#include "PublicationPanelImp.h"
#include "MyApp.h"
#include <wx/app.h> 
#include <wx/log.h> 
#include "ShelfDialogImp.h"
#include "SubjectDialogImp.h"
#include "PublicationDialogImp.h"
#include "ActionCommandParser.h"
#include "SAConfirmDialogImp.h"
#include "PublicationPanelImp.h"


MainFrameImp::MainFrameImp( wxWindow* parent )
:
MainFrame( parent ), shelfModel(nullptr), subjectModel(nullptr), publicationModel(nullptr)
{

	/* icons */
	m_btnEditShelf->SetBitmap(*wxGetApp().GetImages().edit_icon);
	btnEditSubject->SetBitmap(*wxGetApp().GetImages().edit_icon);
	btnEditPublication->SetBitmap(*wxGetApp().GetImages().edit_icon);

	m_btnAddShelf->SetBitmap(*wxGetApp().GetImages().add_icon);
	btnAddSubject->SetBitmap(*wxGetApp().GetImages().add_icon);
	btnAddPublication->SetBitmap(*wxGetApp().GetImages().add_icon);

	m_btnDeleteShelf->SetBitmap(*wxGetApp().GetImages().delete_icon);
	btnDeleteSubject->SetBitmap(*wxGetApp().GetImages().delete_icon);
	btnDeletePublication->SetBitmap(*wxGetApp().GetImages().delete_icon);

	/* columns on list views */
	this->m_lstSubjectColTitle->SetWidth(wxCOL_WIDTH_AUTOSIZE);
	this->m_lstSubjectColTitle->SetFlag(wxDATAVIEW_COL_SORTABLE);

	this->m_dvlcShelfName->SetWidth(wxCOL_WIDTH_AUTOSIZE);
	this->m_dvlcShelfName->SetFlag(wxDATAVIEW_COL_SORTABLE);

	this->lstPublicationColTitle->SetWidth(wxCOL_WIDTH_AUTOSIZE);
	this->lstPublicationColTitle->SetFlag(wxDATAVIEW_COL_SORTABLE);

	shelfModel = new wxDataViewListStore();
	subjectModel = new wxDataViewListStore();
	publicationModel = new wxDataViewListStore();
	this->m_dvlShelf->AssociateModel(shelfModel);
	this->m_lstSubject->AssociateModel(subjectModel);
	this->lstPublication->AssociateModel(publicationModel);
	shelfModel->DecRef();
	subjectModel->DecRef();
	publicationModel->DecRef();

	SetupSpeechHandlers();

	/* load shelves from provider */
	boost::ptr_vector<Shelf>* shelfList = wxGetApp().GetMainFrameViewModel()->getShelfList();
	shelfList->clear();
	wxGetApp().GetProvider()->GetAllShelves(shelfList);
	this->RenderShelves(NULL);
	

}

MainFrameImp::~MainFrameImp()
{
	if(this->shelfModel != nullptr)
	{
		this->shelfModel->DeleteAllItems();
		this->shelfModel = nullptr;
		delete this->shelfModel;
		
	}

	if(this->subjectModel != nullptr)
	{
		this->subjectModel->DeleteAllItems();
		this->subjectModel = nullptr;
		delete this->subjectModel;
		
	}

	if(this->publicationModel != nullptr)
	{
		this->publicationModel->DeleteAllItems();
		this->publicationModel = nullptr;
		delete this->publicationModel;
		
	}
}

void MainFrameImp::SetupSpeechHandlers()
{
	//wxGetApp().GetSpeechListener().SwitchRule(MainFrameImp::RULE_HOME_SCREEN);
	//use enable rule instead
	std::vector<std::wstring> ruleNames;
	ruleNames.push_back(MyApp::RULE_HOME_SCREEN);
	ruleNames.push_back(MyApp::RULE_FILE_MENU);

	wxGetApp().DisconnectSpeechHandler(wxGetApp().GetCommandReceivedConnection());
	//keeping the signal connection in the main instance to avoid having connections floating
	//around everywhere that a dialog / panel needs to use one
	boost::signals2::connection* commandConnection = wxGetApp().GetCommandReceivedConnection();
	*(commandConnection) = wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->onCommandRecognized(boost::bind(&MainFrameImp::OnCommandRecognized, this, _1, _2));
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->EnableRules(ruleNames);
}

void MainFrameImp::menuFileQuitOnMenuSelection( wxCommandEvent& event )
{
	this->Close();
}

//this is a technique of wxAuiNotebook to disallow closing the HOME SCREEN tab
//by removing the close button altogether when it is focussed
//by using the SetWindowStyle
void MainFrameImp::OnNotebookPageClose(wxAuiNotebookEvent& event)
{
	if (event.GetOldSelection() == MyApp::HOME_PAGE_INDEX || event.GetSelection() == MyApp::HOME_PAGE_INDEX)
	{
		//can't close tab MyApp::HOME_PAGE_INDEX old boy
		event.Veto();
	}
	else
	{
		event.Skip();
	}
}

void MainFrameImp::OnNotebookPageChanged(wxAuiNotebookEvent& event)
{ 
	if (event.GetSelection() == MyApp::HOME_PAGE_INDEX)
	{
		this->m_auiShelf->SetWindowStyle(0);
	}
	else
	{
		this->m_auiShelf->SetWindowStyle(wxAUI_NB_CLOSE_ON_ACTIVE_TAB);
	}
	wxWindow* win = this->m_auiShelf->GetCurrentPage();
	if (win->GetName() == "PublicationPanel")
	{
		PublicationPanelImp* panel = (PublicationPanelImp*)win;
		if (panel != nullptr)
		{
			//refresh the exercise panel
			panel->Refresh();
		}
	}
	event.Skip();
}

Shelf* MainFrameImp::GetCurrentShelf()
{
	 return wxGetApp().GetMainFrameViewModel()->GetCurrentShelf();
}

Subject* MainFrameImp::GetCurrentSubject()
{
	return wxGetApp().GetMainFrameViewModel()->GetCurrentSubject();
}

void MainFrameImp::SetCurrentShelf(Shelf* shelf)
{
	wxGetApp().GetMainFrameViewModel()->SetCurrentShelf(shelf);
	if(shelf == NULL)
	{
		this->enableShelfButtons(false);
		this->m_lstSubject->DeleteAllItems();
		wxGetApp().GetMainFrameViewModel()->getSubjectList()->clear();
		this->RenderSubjects(NULL);
	}
	else
	{
		this->enableShelfButtons(true);
		wxGetApp().GetMainFrameViewModel()->getSubjectList()->clear();
		wxGetApp().GetProvider()->GetSubjectsByShelf(shelf, wxGetApp().GetMainFrameViewModel()->getSubjectList());
		this->RenderSubjects(NULL);
	}
	if (m_lstSubject->GetSelectedRow() == wxNOT_FOUND)
	{
		wxGetApp().GetMainFrameViewModel()->getPublicationList()->clear();
		this->RenderPublications(NULL);
	}
}

void MainFrameImp::SetCurrentSubject(Subject* subject)
{
	wxGetApp().GetMainFrameViewModel()->SetCurrentSubject(subject);
	if(subject == NULL)
	{
		this->enableSubjectButtons(false);
		this->lstPublication->DeleteAllItems();
		wxGetApp().GetMainFrameViewModel()->getPublicationList()->clear();
	}
	else
	{
		this->enableSubjectButtons(true);
		wxGetApp().GetMainFrameViewModel()->getPublicationList()->clear();
		wxGetApp().GetProvider()->GetPublicationsBySubject(subject, wxGetApp().GetMainFrameViewModel()->getPublicationList());
	}
	this->RenderPublications(NULL);
}

void MainFrameImp::enableShelfButtons(bool enable)
{
	this->m_btnEditShelf->Enable(enable);
	this->m_btnDeleteShelf->Enable(enable);
	this->btnAddSubject->Enable(enable);
}

void MainFrameImp::enableSubjectButtons(bool enable)
{
	this->btnDeleteSubject->Enable(enable);
	this->btnEditSubject->Enable(enable);
}

void MainFrameImp::SetCurrentPublication(Publication* publication)
{
	wxGetApp().GetMainFrameViewModel()->SetCurrentPublication(publication);
}

Publication* MainFrameImp::GetCurrentPublication()
{
	return wxGetApp().GetMainFrameViewModel()->GetCurrentPublication();
}

void MainFrameImp::RenderShelves(Shelf* shelf)
{
	this->shelfModel->DeleteAllItems();
	wxVector<wxVariant> data;
	boost::ptr_vector<Shelf>* shelfList = wxGetApp().GetMainFrameViewModel()->getShelfList();
	for(int i = 0; i < shelfList->size(); i ++ )
	{
		data.clear();
		data.push_back(shelfList->at(i).getTitle());
		shelfModel->AppendItem( data, wxUIntPtr(&shelfList->at(i)));
		if(shelf != NULL && shelfList->at(i).getShelfId() == shelf->getShelfId())
		{
			this->m_dvlShelf->SelectRow(i);
		}
	}	
	if ((m_dvlShelf->GetSelectedRow() == wxNOT_FOUND) && m_dvlShelf->GetItemCount() > 0)
	{
		m_dvlShelf->SelectRow(0);
		OnSelectShelf(&shelfList->at(0));
	}
}


void MainFrameImp::OnShelfSelectionChanged(wxDataViewEvent& event)
{
	wxDataViewItem item = event.GetItem();
	if(item == NULL)
	{
		return;
	}
	Shelf* shelf = (Shelf*)this->m_dvlShelf->GetItemData(item);
	this->OnSelectShelf(shelf);

}

void MainFrameImp::OnSelectShelf(Shelf* shelf)
{
	this->SetCurrentShelf(shelf);
}

void MainFrameImp::EditShelfOnButtonClick( wxCommandEvent& event )
{
	//wxInfoMessageBox(this);
	this->EditShelf();
}

void MainFrameImp::OnShelfItemActivated( wxDataViewEvent& event )
{
	this->EditShelf();
}

void MainFrameImp::OnShelfColumnSort(wxDataViewEvent& event)
{ 
	event.Skip(); 
}

void MainFrameImp::EditShelf()
{
	ShelfDialogImp shelfDialog(this);
	Shelf* currentShelf = wxGetApp().GetMainFrameViewModel()->GetCurrentShelf();
	if (currentShelf == nullptr)
	{
		return;
	}
	shelfDialog._title = currentShelf->getTitle();
	if(shelfDialog.ShowModal() == wxID_OK && !(shelfDialog._title.IsEmpty()))
	{
		wxString currentTitle(currentShelf->getTitle());
		if(!(currentTitle.IsSameAs(shelfDialog._title)))
		{
			currentShelf->setTitle(shelfDialog._title.ToStdWstring());
			wxGetApp().GetProvider()->Update(currentShelf);
			this->RenderShelves(currentShelf);
		}
	}
	this->SetupSpeechHandlers();

}

void MainFrameImp::AddShelfOnButtonClick( wxCommandEvent& event )
{
	this->AddShelf();
}

void MainFrameImp::AddShelf()
{
	Shelf* newShelf = new Shelf();
	ShelfDialogImp shelfDialog(this);
	if (shelfDialog.ShowModal() == wxID_OK && !(shelfDialog._title.IsEmpty()))
	{
		newShelf->setTitle(shelfDialog._title.ToStdWstring());
		wxGetApp().GetProvider()->Insert(newShelf);
		boost::ptr_vector<Shelf>* shelfList = wxGetApp().GetMainFrameViewModel()->getShelfList();
		shelfList->push_back(newShelf);
		this->RenderShelves(newShelf);
		this->SetCurrentShelf(newShelf);
	}
	this->SetupSpeechHandlers();

}

void MainFrameImp::DeleteShelfOnButtonClick( wxCommandEvent& event )
{
	this->DeleteShelf();
}

void MainFrameImp::DeleteShelf()
{
	Shelf* currentShelf = this->GetCurrentShelf();
	if (currentShelf == NULL)
	{
		return;
	}

	SAConfirmDialogImp confirmDlg(this);
	if (confirmDlg.ShowModal() == wxYES)
	{
		boost::ptr_vector<Shelf>* shelfList = wxGetApp().GetMainFrameViewModel()->getShelfList();
		wxGetApp().GetProvider()->Delete(currentShelf);
		shelfList->erase(std::find(shelfList->begin(), shelfList->end(), *currentShelf));
		this->RenderShelves(NULL);
		this->SetCurrentShelf(NULL);
	}
	this->SetupSpeechHandlers();
}


void MainFrameImp::AddSubjectOnButtonClick( wxCommandEvent& event )
{
	this->AddSubject();
}

void MainFrameImp::AddSubject()
{
	Shelf* currentShelf = this->GetCurrentShelf();
	if (currentShelf == NULL)
	{
		return;
	}
	Subject* subject = new Subject(currentShelf->getShelfId(), wxString("").ToStdWstring());
	SubjectDialogImp subjectDialog(this);
	if (subjectDialog.ShowModal() == wxID_OK && !(subjectDialog._title.IsEmpty()))
	{
		subject->setTitle(subjectDialog._title.ToStdWstring());
		boost::ptr_vector<Subject>* subjectList = wxGetApp().GetMainFrameViewModel()->getSubjectList();
		wxGetApp().GetProvider()->Insert(subject);
		subjectList->push_back(subject);
		this->RenderSubjects(subject);
		this->SetCurrentSubject(subject);
	}
	this->SetupSpeechHandlers();
}

void MainFrameImp::DeleteSubjectOnButtonClick( wxCommandEvent& event )
{
	this->DeleteSubject();
}

void MainFrameImp::DeleteSubject()
{
	Subject* currentSubject = this->GetCurrentSubject();
	if (currentSubject == NULL)
	{
		return;
	}

	SAConfirmDialogImp confirmDlg(this);
	if (confirmDlg.ShowModal() == wxYES)
	{
		boost::ptr_vector<Subject>* subjectList = wxGetApp().GetMainFrameViewModel()->getSubjectList();
		wxGetApp().GetProvider()->Delete(currentSubject);
		subjectList->erase(std::find(subjectList->begin(), subjectList->end(), *currentSubject));
		this->RenderSubjects(NULL);
		this->SetCurrentSubject(NULL);
	}
	this->SetupSpeechHandlers();
}

void MainFrameImp::EditSubject()
{
	Subject* currentSubject = this->GetCurrentSubject();
	if (currentSubject == NULL)
	{
		return;
	}
	SubjectDialogImp subjectDialog(this);
	subjectDialog._title = currentSubject->getTitle();
	if (subjectDialog.ShowModal() == wxID_OK && !(subjectDialog._title.IsEmpty()))
	{
		wxString currentTitle(currentSubject->getTitle());
		if (!(currentTitle.IsSameAs(subjectDialog._title)))
		{
			currentSubject->setTitle(subjectDialog._title.ToStdWstring());
			wxGetApp().GetProvider()->Update(currentSubject);
			this->RenderSubjects(currentSubject);
		}
	}
	this->SetupSpeechHandlers();
}


void MainFrameImp::EditSubjectOnButtonClick( wxCommandEvent& event )
{
	this->EditSubject();
}

void MainFrameImp::OnSubjectItemActivated( wxDataViewEvent& event )
{
	this->EditSubject();
}

void MainFrameImp::RenderSubjects(Subject* subject)
{
	this->subjectModel->DeleteAllItems();
	wxVector<wxVariant> data;
	boost::ptr_vector<Subject>* itemsList = wxGetApp().GetMainFrameViewModel()->getSubjectList();
	for(int i = 0; i < itemsList->size(); i ++ )
	{
		data.clear();
		data.push_back(itemsList->at(i).getTitle());
		this->subjectModel->AppendItem( data, wxUIntPtr(&itemsList->at(i)));
		if(subject != NULL && itemsList->at(i).getSubjectId() == subject->getSubjectId())
		{
			this->m_lstSubject->SelectRow(i);
		}
	}	
	if ((m_lstSubject->GetSelectedRow() == wxNOT_FOUND) && m_lstSubject->GetItemCount() > 0)
	{
		m_lstSubject->SelectRow(0);
		OnSelectSubject(&itemsList->at(0));
	}

	/* using the list ctrl, something wrong when clicking on first item in list, is null
	this->m_lstSubject->Hide();
	this->m_lstSubject->DeleteAllItems();
	boost::ptr_vector<Subject>* subjectList = wxGetApp().getMainFrameViewModel()->getSubjectList();
	for(int i = 0; i < subjectList->size(); i ++ )
	{
		long tmp = this->m_lstSubject->InsertItem(i, subjectList->at(i).getTitle());
		this->m_lstSubject->SetItem(tmp, 0, subjectList->at(i).getTitle(), 0);
		this->m_lstSubject->SetItemData(tmp, (long)&(subjectList->at(i)));
		if(subject != NULL && subjectList->at(i).getSubjectId() == subject->getSubjectId())
		{
			this->m_lstSubject->SetItemState(tmp, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
		}
	}	
	this->m_lstSubject->Show();
	*/
}

void MainFrameImp::SubjectOnSelectionChanged( wxDataViewEvent& event )
{
	wxDataViewItem item = event.GetItem();
	if(item == NULL)
	{
		return;
	}
	Subject* subject = (Subject*)this->m_lstSubject->GetItemData(item);
	if(subject != NULL)
	{
		this->OnSelectSubject(subject);
		/*boost::ptr_vector<Subject>* subjectList = wxGetApp().getMainFrameViewModel()->getSubjectList();
		boost::ptr_vector<Subject>::iterator i = std::find(subjectList->begin(), subjectList->end(), *subject);	
		if(i != subjectList->end())
		{
			this->OnSelectSubject(&(*i));
		}
		*/
	}
}

void MainFrameImp::OnSubjectColumnSort(wxDataViewEvent& event)
{ 
	event.Skip(); 
}


void MainFrameImp::OnSelectSubject(Subject* subject)
{
	this->SetCurrentSubject(subject);
}

void MainFrameImp::AddPublicationOnButtonClick( wxCommandEvent& event ) 
{
	this->AddPublication();
}

void MainFrameImp::AddPublication()
{
	Subject* currentSubject = this->GetCurrentSubject();
	if (currentSubject == NULL)
	{
		return;
	}
	Publication* publication = new Publication(currentSubject->getSubjectId(), wxString("").ToStdWstring());
	PublicationDialogImp dialog(this);
	if (dialog.ShowModal() == wxID_OK && !(dialog._title.IsEmpty()))
	{
		publication->setTitle(dialog._title.ToStdWstring());
		publication->setType(dialog.GetType());
		boost::ptr_vector<Publication>* publicationList = wxGetApp().GetMainFrameViewModel()->getPublicationList();
		wxGetApp().GetProvider()->Insert(publication);
		publicationList->push_back(publication);
		this->RenderPublications(publication);
		this->SetCurrentPublication(publication);

		wxPanel* pnlNewPublication = new PublicationPanelImp(this->m_auiShelf, publication);
		this->m_auiShelf->AddPage(pnlNewPublication, "Publication - " + publication->getTitle(), true);
	}
	this->SetupSpeechHandlers();
}

void MainFrameImp::RenderPublications(Publication* publication)
{
	this->publicationModel->DeleteAllItems();
	wxVector<wxVariant> data;
	boost::ptr_vector<Publication>* itemsList = wxGetApp().GetMainFrameViewModel()->getPublicationList();
	for(int i = 0; i < itemsList->size(); i ++ )
	{
		data.clear();
		data.push_back(itemsList->at(i).getTitle());
		this->publicationModel->AppendItem( data, wxUIntPtr(&itemsList->at(i)));
		if(publication != NULL && itemsList->at(i).getPublicationId() == publication->getPublicationId())
		{
			this->lstPublication->SelectRow(i);
		}
	}	
	if ((lstPublication->GetSelectedRow() == wxNOT_FOUND) && lstPublication->GetItemCount() > 0)
	{
		lstPublication->SelectRow(0);
		SetCurrentPublication(&itemsList->at(0));
		lstPublication->SetFocus();
	}
}


void MainFrameImp::PublicationSelectionChanged( wxDataViewEvent& event )
{
	wxDataViewItem item = event.GetItem();
	if(item == NULL)
	{
		return;
	}
	Publication* publication = (Publication*)this->lstPublication->GetItemData(item);
	if(publication != NULL)
	{
		this->SetCurrentPublication(publication);
	}
}

void MainFrameImp::AddPublicationOnUpdateUI( wxUpdateUIEvent& event )
{
	if(this->GetCurrentSubject() != NULL)
	{
		this->btnAddPublication->Enable(true);
	}
	else
	{
		this->btnAddPublication->Enable(false);
	}
}

void MainFrameImp::DeletePublicationOnButtonClick( wxCommandEvent& event )
{
	this->DeletePublication();
}

void MainFrameImp::DeletePublication()
{
	Publication* currentPublication = this->GetCurrentPublication();
	if (currentPublication == NULL)
	{
		return;
	}
	SAConfirmDialogImp confirmDlg(this);
	if (confirmDlg.ShowModal() == wxYES)
	{
		boost::ptr_vector<Publication>* list = wxGetApp().GetMainFrameViewModel()->getPublicationList();
		wxGetApp().GetProvider()->Delete(currentPublication);
		list->erase(std::find(list->begin(), list->end(), *currentPublication));
		this->RenderPublications(NULL);
		this->SetCurrentPublication(NULL);
	}
	this->SetupSpeechHandlers();
}

void MainFrameImp::DeletePublicationOnUpdateUI( wxUpdateUIEvent& event )
{
	if(this->GetCurrentPublication() != NULL)
	{
		this->btnDeletePublication->Enable(true);
	}
	else
	{
		this->btnDeletePublication->Enable(false);
	}
}


void MainFrameImp::EditPublication(void)
{
	if(this->GetCurrentPublication() == NULL)
	{
		return;
	}
	wxPanel* pnlNewPublication  = new PublicationPanelImp(this->m_auiShelf, this->GetCurrentPublication());
	this->m_auiShelf->AddPage(pnlNewPublication, "Publication - " + this->GetCurrentPublication()->getTitle(), true);
	
}

void MainFrameImp::EditPublicationOnButtonClick( wxCommandEvent& event )
{
	this->EditPublication();
}

void MainFrameImp::OnPublicationItemActivated( wxDataViewEvent& event )
{
	this->EditPublication();
}

void MainFrameImp::OnPublicationColumnSort(wxDataViewEvent& event) 
{ 
	event.Skip(); 
}

void MainFrameImp::EditPublicationOnUpdateUI( wxUpdateUIEvent& event )
{
	if(this->GetCurrentPublication() != NULL)
	{
		this->btnEditPublication->Enable(true);
	}
	else
	{
		this->btnEditPublication->Enable(false);
	}
}

wxAuiNotebook* MainFrameImp::GetShelfNotebook()
{
	return m_auiShelf;
}


void MainFrameImp::OnCommandRecognized(std::wstring& phrase, std::vector<CommandProperty> commandPropertyList)
{
	std::wstring actionName;
	std::wstring actionTarget;
	std::wstring targetValue;
	std::wstring ruleName;
	ActionCommandParser actionParser;
	actionParser.Parse(commandPropertyList, actionName, actionTarget, targetValue, ruleName);
	bool handled = false;
	if (boost::algorithm::equals(actionName, MyApp::COMMAND_ACTION_DELETE))
	{
		if (boost::algorithm::equals(actionTarget, MyApp::ENTITY_SHELF))
		{
			//delete the shelf;
			this->DeleteShelf();
			return;
		}
		else if (boost::algorithm::equals(actionTarget, MyApp::ENTITY_SUBJECT))
		{
			//delete the subject
			this->DeleteSubject();
			return;
		}
		else if (boost::algorithm::equals(actionTarget, MyApp::ENTITY_PUBLICATION))
		{
			//delete the publication
			this->DeletePublication();
			return;
		}
	}
	else if (boost::algorithm::equals(actionName, MyApp::COMMAND_ACTION_ADD))
	{
		if (boost::algorithm::equals(actionTarget, MyApp::ENTITY_SHELF))
		{
			//add shelf;
			this->AddShelf();
			return;
		}
		else if (boost::algorithm::equals(actionTarget, MyApp::ENTITY_SUBJECT))
		{
			//add subject
			this->AddSubject();
			return;
		}
		else if (boost::algorithm::equals(actionTarget, MyApp::ENTITY_PUBLICATION))
		{
			//add publication
			this->AddPublication();
			return;
		}
	}
	else if (boost::algorithm::equals(actionName, MyApp::COMMAND_ACTION_EDIT))
	{
		if (boost::algorithm::equals(actionTarget, MyApp::ENTITY_SHELF))
		{
			//edit shelf;
			this->EditShelf();
			return;
		}
		else if (boost::algorithm::equals(actionTarget, MyApp::ENTITY_SUBJECT))
		{
			//edit subject
			this->EditSubject();
			return;
		}
		else if (boost::algorithm::equals(actionTarget, MyApp::ENTITY_PUBLICATION))
		{
			//edit publication
			this->EditPublication();
			return;
		}
	}

	//if frame doesn't handle the spoken command, send it to the application
	wxGetApp().OnCommandRecognized(phrase, commandPropertyList);
}