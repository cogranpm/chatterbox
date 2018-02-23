#ifndef __MainFrameImp__
#define __MainFrameImp__

#include "stdafx.h"
#include "MainFrame.h"
#include "Shelf.h"
#include "Subject.h"
#include "Publication.h"
#include "CommandProperty.h"

class MainFrameImp : public MainFrame
{

private:
	wxDataViewListStore* shelfModel;
	wxDataViewListStore* subjectModel;
	wxDataViewListStore* publicationModel;
	Shelf* GetCurrentShelf();
	std::vector<std::wstring> ruleNames;


	void OnSelectShelf(Shelf* shelf);
	void AddShelf();
	void DeleteShelf();
	void EditShelf();
	Subject* GetCurrentSubject();
	void OnSelectSubject(Subject* subject);
	void EditSubject();
	void AddSubject();
	void DeleteSubject();
	void SetCurrentShelf(Shelf* shelf);
	void SetCurrentSubject(Subject* subject);
	void SetCurrentPublication(Publication* publication);
	void EditPublication(void);
	void AddPublication();
	void DeletePublication();
	Publication* GetCurrentPublication();
	void enableShelfButtons(bool enable);
	void enableSubjectButtons(bool enable);
	void SetupSpeechHandlers();
	

	protected:

		//menu handlers
		void menuFileQuitOnMenuSelection( wxCommandEvent& event );

		// Handlers for MainFrame events.
		void EditShelfOnButtonClick( wxCommandEvent& event );
		void OnShelfItemActivated( wxDataViewEvent& event );
		void OnShelfSelectionChanged(wxDataViewEvent& event);
		void AddShelfOnButtonClick( wxCommandEvent& event );
		void DeleteShelfOnButtonClick( wxCommandEvent& event );
		void OnShelfColumnSort(wxDataViewEvent& event);
		void AddSubjectOnButtonClick( wxCommandEvent& event );
		void DeleteSubjectOnButtonClick( wxCommandEvent& event );
		void EditSubjectOnButtonClick( wxCommandEvent& event );
		void OnSubjectItemActivated( wxDataViewEvent& event );
		void SubjectOnSelectionChanged( wxDataViewEvent& event );
		void OnSubjectColumnSort(wxDataViewEvent& event);
		void AddPublicationOnButtonClick( wxCommandEvent& event );
		void AddPublicationOnUpdateUI( wxUpdateUIEvent& event );
		void DeletePublicationOnButtonClick( wxCommandEvent& event );
		void DeletePublicationOnUpdateUI( wxUpdateUIEvent& event );
		void EditPublicationOnButtonClick( wxCommandEvent& event );
		void OnPublicationItemActivated( wxDataViewEvent& event );
		void EditPublicationOnUpdateUI( wxUpdateUIEvent& event );
		void PublicationSelectionChanged( wxDataViewEvent& event );
		void OnPublicationColumnSort(wxDataViewEvent& event);
		void OnNotebookPageClose(wxAuiNotebookEvent& event);
		void OnNotebookPageChanged(wxAuiNotebookEvent& event);
	
		void RenderShelves(Shelf* shelf);
		void RenderSubjects(Subject* subject);
		void RenderPublications(Publication* publication);



		//speech handlers
		void OnCommandRecognized(std::wstring& phrase, std::vector<CommandProperty> commandPropertyList);

	public:
		MainFrameImp( wxWindow* parent );
		~MainFrameImp();
		wxAuiNotebook* GetShelfNotebook();


	
};

#endif // __MainFrameImp__
