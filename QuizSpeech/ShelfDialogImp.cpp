#include "ShelfDialogImp.h"
#include <wx/valtext.h>
#include <wx/log.h> 
#include <wx/infobar.h>
#include <wx/event.h>
#include "MyApp.h"
#include "ActionCommandParser.h"

ShelfDialogImp::ShelfDialogImp( wxWindow* parent) : ShelfDialog(parent), ruleNames()
{
}


ShelfDialogImp::~ShelfDialogImp(void)
{
	//wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->Disconnect();
}


void ShelfDialogImp::OnClose( wxCloseEvent& event )
{
	event.Skip();
}

void ShelfDialogImp::OnInitDialog( wxInitDialogEvent& event )
{
	this->m_txtName->SetValue(this->_title);
	ruleNames.push_back(MyApp::RULE_SHELF_DIALOG);
	ruleNames.push_back(MyApp::RULE_DIALOG_ACTIONS);
	this->SetupSpeechHandlers();
}

void ShelfDialogImp::SetupSpeechHandlers()
{
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->SetupSpeechHandlers(ruleNames,
		this->GetName().ToStdString(),
		boost::bind(&ShelfDialogImp::OnCommandRecognized, this, _1, _2));
}

void ShelfDialogImp::OnOKButtonClick(wxCommandEvent& event)
{
	if (!this->OnOK())
	{
		event.Skip();
	}
}


void ShelfDialogImp::OnCommandRecognized(std::wstring& phrase, std::vector<CommandProperty> commandPropertyList)
{
	std::wstring actionName;
	std::wstring actionTarget;
	std::wstring targetValue;
	std::wstring ruleName;
	ActionCommandParser actionParser;
	actionParser.Parse(commandPropertyList, actionName, actionTarget, targetValue, ruleName);
	if (boost::algorithm::equals(actionName, MyApp::COMMAND_ACTION_OK))
	{
		wxCommandEvent evt(wxEVT_COMMAND_BUTTON_CLICKED, this->m_sdbSizer1OK->GetId());
		this->m_sdbSizer1OK->Command(evt);
		return;
	}
	else if (boost::algorithm::equals(actionName, MyApp::COMMAND_ACTION_CANCEL))
	{
		this->OnCancel();
		return;
	}
	else
	{
		//must be free text
		this->m_txtName->AppendText(phrase);
		return;
	}

	//if frame doesn't handle the spoken command, send it to the application
	//wxGetApp().OnCommandRecognized(phrase, commandPropertyList);
}

bool ShelfDialogImp::OnOK()
{
	this->m_txtName->GetValidator()->TransferFromWindow();
	if (this->_title.IsEmpty())
	{
		this->m_infoCtrl->ShowMessage("Title may not be empty");
		this->m_txtName->SetFocus();
		return true;
	}
	else
	{
		//wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->Disconnect();
		return false;
	}
}

bool ShelfDialogImp::OnCancel()
{
	//wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->Disconnect();
	this->Close();
	return true;
}

/*
void ShelfDialogImp::SetShelf(Shelf* shelf)
{
	this->shelf = shelf;

}


Shelf* ShelfDialogImp::GetShelf()
{
	return this->shelf;
}
*/