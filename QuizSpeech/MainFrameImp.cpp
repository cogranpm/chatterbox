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
#include "ShelfDataViewListStore.h"
#include "SettingsDialogImp.h"
#include "ExportDialogImp.h"

MainFrameImp::MainFrameImp( wxWindow* parent )
:
MainFrame( parent ), shelfModel(nullptr), subjectModel(nullptr), publicationModel(nullptr), ruleNames(), initialized(false)
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
	colSubjectIndex->SetWidth(MyApp::DEFAULT_INDEX_COLUMN_WIDTH);
	colSubjectIndex->SetFlag(wxDATAVIEW_COL_SORTABLE);

	this->m_dvlcShelfName->SetWidth(wxCOL_WIDTH_AUTOSIZE);
	this->m_dvlcShelfName->SetFlag(wxDATAVIEW_COL_SORTABLE);
	colShelfIndex->SetWidth(MyApp::DEFAULT_INDEX_COLUMN_WIDTH);
	colShelfIndex->SetFlag(wxDATAVIEW_COL_SORTABLE);

	m_dvlShelf->AllowMultiColumnSort(true);

	this->lstPublicationColTitle->SetWidth(wxCOL_WIDTH_AUTOSIZE);
	this->lstPublicationColTitle->SetFlag(wxDATAVIEW_COL_SORTABLE);
	colPublicationIndex->SetWidth(MyApp::DEFAULT_INDEX_COLUMN_WIDTH);
	colPublicationIndex->SetFlag(wxDATAVIEW_COL_SORTABLE);

	shelfModel = new ShelfDataViewListStore();
	shelfModel->AppendColumn(wxEmptyString);
	shelfModel->AppendColumn(wxEmptyString);
	
	subjectModel = new ShelfDataViewListStore();
	subjectModel->AppendColumn(wxEmptyString);
	subjectModel->AppendColumn(wxEmptyString);

	publicationModel = new ShelfDataViewListStore();
	publicationModel->AppendColumn(wxEmptyString);
	publicationModel->AppendColumn(wxEmptyString);

	this->m_dvlShelf->AssociateModel(shelfModel);
	this->m_lstSubject->AssociateModel(subjectModel);
	this->lstPublication->AssociateModel(publicationModel);
	shelfModel->DecRef();
	subjectModel->DecRef();
	publicationModel->DecRef();

	LoadShelves();
	
	ruleNames.push_back(MyApp::RULE_HOME_SCREEN);
	ruleNames.push_back(MyApp::RULE_FILE_MENU);
	ruleNames.push_back(MyApp::RULE_LIST_ACTIONS);
	SetupSpeechHandlers();
	initialized = true;
}



MainFrameImp::~MainFrameImp()
{
	//wxGetApp().DisconnectFromSpeech();
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->Disconnect();
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


void MainFrameImp::ChangeDatabase()
{
	size_t shelfCount = m_auiShelf->GetPageCount();
	if (shelfCount > 1)
	{
		for (int i = 1; i <= shelfCount; i++)
		{
			m_auiShelf->GetPage(i)->Close();
		}
	}
	LoadShelves();
}

void MainFrameImp::LoadShelves()
{
	/* load shelves from provider */
	boost::ptr_vector<Shelf>* shelfList = wxGetApp().GetMainFrameViewModel()->getShelfList();
	shelfList->clear();
	wxGetApp().GetProvider()->GetAllShelves(shelfList);
	this->RenderShelves(NULL);
}

void MainFrameImp::SetupSpeechHandlers()
{
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->SetupSpeechHandlers(ruleNames,
		this->GetName().ToStdString(),
		boost::bind(&MainFrameImp::OnCommandRecognized, this, _1, _2));

	//if (wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->GetWindowName() == this->GetName())
	//{
	//	if (!wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->IsEnabled())
	//	{
	//		wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->EnableRules();
	//	}
	//}
	//else
	//{
	//	std::vector<std::wstring> ruleNames;
	//	ruleNames.push_back(MyApp::RULE_HOME_SCREEN);
	//	ruleNames.push_back(MyApp::RULE_FILE_MENU);

	//	wxGetApp().DisconnectSpeechHandler(wxGetApp().GetCommandReceivedConnection());
	//	//keeping the signal connection in the main instance to avoid having connections floating
	//	//around everywhere that a dialog / panel needs to use one
	//	boost::signals2::connection* commandConnection = wxGetApp().GetCommandReceivedConnection();
	//	*(commandConnection) = wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->onCommandRecognized(boost::bind(&MainFrameImp::OnCommandRecognized, this, _1, _2));
	//	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->EnableRules(ruleNames, this->GetName().ToStdString());
	//}
}

void MainFrameImp::menuFileQuitOnMenuSelection( wxCommandEvent& event )
{
	this->Close();
}

void MainFrameImp::menuEditSettingsOnMenuSelection(wxCommandEvent& event)
{
	SettingsDialogImp dlg(this);
	dlg.SetDataDirectory(wxGetApp().GetDataDirectory());
	if (dlg.ShowModal() == wxID_OK)
	{
		if (dlg.GetDataDirectoryDirty())
		{
			/* open and shut the database and all that good stuff */
			wxGetApp().ChangeDataDirectory(dlg.GetDataDirectory().ToStdWstring());
		}
	}
}

void MainFrameImp::FileExportOnMenuSelection(wxCommandEvent& event)
{
	ExportDialogImp dlg(this);
	if (dlg.ShowModal() == wxID_OK)
	{
		

	}
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
		if (initialized)
		{
			Refresh();
		}
	}
	else
	{
		this->m_auiShelf->SetWindowStyle(wxAUI_NB_CLOSE_ON_ACTIVE_TAB);
	}
	wxWindow* win = this->m_auiShelf->GetCurrentPage();
	if (win->GetName().ToStdString() == MyApp::PUBLICATION_PANEL_WINDOW_NAME)
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
void MainFrameImp::Refresh()
{
	SetupSpeechHandlers();
	/* redraw the publications in case the name changed */
	RenderPublications(wxGetApp().GetMainFrameViewModel()->GetCurrentPublication());
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
	
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->BeginCreateDynamicRule(MyApp::RULE_MAINFRAME_LOOKUP);
	
	for(int i = 0; i < shelfList->size(); i ++ )
	{
		data.clear();
		std::wstring index(boost::lexical_cast<std::wstring>(i + 1));
		data.push_back(index);
		data.push_back(shelfList->at(i).getTitle());
		shelfModel->AppendItem( data, wxUIntPtr(&shelfList->at(i)));
		if(shelf != NULL && shelfList->at(i).getShelfId() == shelf->getShelfId())
		{
			this->m_dvlShelf->SelectRow(i);
		}
		
		/* dynamic rule adding phrase for index (numeric) and title (string)*/
		wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->CreateDynamicRule(shelfList->at(i).getTitle(), index, std::wstring(L"shelf"));
	}	
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->EndCreateDynamicRule();

	//if ((m_dvlShelf->GetSelectedRow() == wxNOT_FOUND) && m_dvlShelf->GetItemCount() > 0)
	//{
	//	m_dvlShelf->SelectRow(0);
	//	OnSelectShelf(&shelfList->at(0));
	//}
	shelfModel->Resort();
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
	shelfDialog._comments = currentShelf->getComments();
	if(shelfDialog.ShowModal() == wxID_OK && !(shelfDialog._title.IsEmpty()))
	{
		wxString currentTitle(currentShelf->getTitle());
		wxString currentComments(currentShelf->getComments());
		if(!(currentTitle.IsSameAs(shelfDialog._title)) || !(currentComments.IsSameAs(shelfDialog._comments)))
		{
			currentShelf->setTitle(shelfDialog._title.ToStdWstring());
			currentShelf->setComments(shelfDialog._comments.ToStdWstring());
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
		newShelf->setComments(shelfDialog._title.ToStdWstring());
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
		subject->setComments(subjectDialog._comments.ToStdWstring());
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
	subjectDialog._comments = currentSubject->getComments();
	if (subjectDialog.ShowModal() == wxID_OK && !(subjectDialog._title.IsEmpty()))
	{
		currentSubject->setTitle(subjectDialog._title.ToStdWstring());
		currentSubject->setComments(subjectDialog._comments.ToStdWstring());
		if (currentSubject->GetDirty())
		{
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
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->BeginCreateDynamicRule(MyApp::RULE_SELECT_SUBJECT);
	for(int i = 0; i < itemsList->size(); i ++ )
	{
		data.clear();
		std::wstring index(boost::lexical_cast<std::wstring>(m_dvlShelf->GetItemCount() + i + 1));
		data.push_back(index);
		data.push_back(itemsList->at(i).getTitle());
		this->subjectModel->AppendItem( data, wxUIntPtr(&itemsList->at(i)));
		if(subject != NULL && itemsList->at(i).getSubjectId() == subject->getSubjectId())
		{
			this->m_lstSubject->SelectRow(i);
		}
		wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->CreateDynamicRule(itemsList->at(i).getTitle(), index, std::wstring(L"subject"));
	}	
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->EndCreateDynamicRule();
	subjectModel->Resort();
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
		publication->setComments(dialog._comments.ToStdWstring());
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
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->BeginCreateDynamicRule(MyApp::RULE_SELECT_PUBLICATION);
	for(int i = 0; i < itemsList->size(); i ++ )
	{
		data.clear();
		std::wstring index(boost::lexical_cast<std::wstring>(m_dvlShelf->GetItemCount() + m_lstSubject->GetItemCount() + i + 1));
		data.push_back(index);
		data.push_back(itemsList->at(i).getTitle());
		this->publicationModel->AppendItem( data, wxUIntPtr(&itemsList->at(i)));
		if(publication != NULL && itemsList->at(i).getPublicationId() == publication->getPublicationId())
		{
			this->lstPublication->SelectRow(i);
		}
		wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->CreateDynamicRule(itemsList->at(i).getTitle(), index, std::wstring(L"publication"));

	}	
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->EndCreateDynamicRule();
	//if ((lstPublication->GetSelectedRow() == wxNOT_FOUND) && lstPublication->GetItemCount() > 0)
	//{
	//	lstPublication->SelectRow(0);
	//	SetCurrentPublication(&itemsList->at(0));
	//	lstPublication->SetFocus();
	//}
}

void MainFrameImp::OnSelectPublication(Publication* publication)
{
	if (publication != NULL)
	{
		this->SetCurrentPublication(publication);
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
	OnSelectPublication(publication);
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
	else if (boost::algorithm::equals(ruleName, L"LIST_ACTIONS"))
	{
		if (boost::algorithm::equals(actionName, L"enter"))
		{
			if (m_dvlShelf->HasFocus())
			{
				this->EditShelf();
			}
			else if (m_lstSubject->HasFocus())
			{
				this->EditSubject();
			}
			else if (lstPublication->HasFocus())
			{
				this->EditPublication();
			}
		}
		else if (boost::algorithm::equals(actionName, L"next"))
		{

		}
		else if (boost::algorithm::equals(actionName, L"previous"))
		{

		}
		else if (boost::algorithm::equals(actionName, L"start"))
		{

		}
		else if (boost::algorithm::equals(actionName, L"end"))
		{

		}
	}
	else if(boost::algorithm::equals(ruleName, MyApp::RULE_MAINFRAME_LOOKUP))
	{
		ProcessShelfLookup(actionName, actionTarget);
		return;
	}
	else if (boost::algorithm::equals(ruleName, MyApp::RULE_SELECT_SUBJECT))
	{
		ProcessSubjectLookup(actionName, actionTarget);
	}
	else if (boost::algorithm::equals(ruleName, MyApp::RULE_SELECT_PUBLICATION))
	{
		ProcessPublicationLookup(actionName, actionTarget);
		return;
	}

	//if frame doesn't handle the spoken command, send it to the application
	wxGetApp().OnCommandRecognized(phrase, commandPropertyList);
}


void MainFrameImp::ProcessShelfLookup(const std::wstring& actionName, const std::wstring& actionTarget)
{
	int columnToSearch = 0;
	if (boost::algorithm::equals(actionName, "shelf display"))
	{
		columnToSearch = 1;
	}
	for (int i = 0; i < m_dvlShelf->GetItemCount(); i++)
	{
		wxString itemText = m_dvlShelf->GetTextValue(i, columnToSearch);
		if (boost::algorithm::equals(actionTarget, itemText.ToStdWstring()))
		{
			m_dvlShelf->SetFocus();
			m_dvlShelf->SelectRow(i);
			Shelf* shelf = (Shelf*)this->m_dvlShelf->GetItemData(m_dvlShelf->GetSelection());
			if (shelf != nullptr)
			{
				OnSelectShelf(shelf);
			}
			return;
		}
	}

}

void MainFrameImp::ProcessSubjectLookup(const std::wstring& actionName, const std::wstring& actionTarget)
{
	int columnToSearch = 0;
	if (boost::algorithm::equals(actionName, "subject display"))
	{
		columnToSearch = 1;
	}
	for (int i = 0; i < m_lstSubject->GetItemCount(); i++)
	{
		wxString itemText = m_lstSubject->GetTextValue(i, columnToSearch);
		if (boost::algorithm::equals(actionTarget, itemText.ToStdWstring()))
		{
			m_lstSubject->SetFocus();
			m_lstSubject->SelectRow(i);
			Subject* subject = (Subject*)this->m_lstSubject->GetItemData(m_lstSubject->GetSelection());
			if (subject != nullptr)
			{
				OnSelectSubject(subject);
			}
			return;
		}
	}
}

void MainFrameImp::ProcessPublicationLookup(const std::wstring& actionName, const std::wstring& actionTarget)
{
	int columnToSearch = 0;
	if (boost::algorithm::equals(actionName, "publication display"))
	{
		columnToSearch = 1;
	}
	for (int i = 0; i < lstPublication->GetItemCount(); i++)
	{
		wxString itemText = lstPublication->GetTextValue(i, columnToSearch);
		if (boost::algorithm::equals(actionTarget, itemText.ToStdWstring()))
		{
			lstPublication->SetFocus();
			lstPublication->SelectRow(i);
			Publication* publication = (Publication*)this->lstPublication->GetItemData(lstPublication->GetSelection());
			if (publication != nullptr)
			{
				OnSelectPublication(publication);
			}
			return;
		}
	}
}