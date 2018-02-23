#pragma once
#include "shelfdialog.h"
#include "Shelf.h"
#include "CommandProperty.h"

class ShelfDialogImp :
	public ShelfDialog
{
public:
	ShelfDialogImp(wxWindow* parent);
	~ShelfDialogImp(void);
	void OnClose( wxCloseEvent& event );
	void OnInitDialog( wxInitDialogEvent& event );
	void OnOKButtonClick(wxCommandEvent& event);
	void SetupSpeechHandlers();
	void OnCommandRecognized(std::wstring& phrase, std::vector<CommandProperty> commandPropertyList);
	/*void SetShelf(Shelf* shelf);
	Shelf* GetShelf();*/
private:
	//Shelf* shelf;
	bool OnOK();
	bool OnCancel();
	std::vector<std::wstring> ruleNames;
};

