#include "ShelfDialogImp.h"
#include <wx/valtext.h>
#include <wx/log.h> 
#include <wx/infobar.h>
#include <wx/event.h>
#include "MyApp.h"
#include "ActionCommandParser.h"

ShelfDialogImp::ShelfDialogImp( wxWindow* parent) : ShelfDialog(parent)
{
}


ShelfDialogImp::~ShelfDialogImp(void)
{
	wxGetApp().DisconnectFromSpeech();
}


void ShelfDialogImp::OnClose( wxCloseEvent& event )
{
	event.Skip();
}

void ShelfDialogImp::OnInitDialog( wxInitDialogEvent& event )
{
	this->m_txtName->SetValue(this->_title);
	this->SetupSpeechHandlers();
}

void ShelfDialogImp::SetupSpeechHandlers()
{
	std::vector<std::wstring> ruleNames;
	ruleNames.push_back(MyApp::RULE_SHELF_DIALOG);
	ruleNames.push_back(MyApp::RULE_DIALOG_ACTIONS);
	boost::signals2::connection* commandConnection = wxGetApp().GetCommandReceivedConnection();
	*(commandConnection) = wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->onCommandRecognized(boost::bind(&ShelfDialogImp::OnCommandRecognized, this, _1, _2));
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->EnableRules(ruleNames, this->GetName().ToStdString());
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
//		wxEvtHandler* okHandler = this->m_sdbSizer1OK->GetEventHandler();
		/*
		if (!this->OnOK())
		{
			this->Close();
		}*/
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
		return false;
	}
}

bool ShelfDialogImp::OnCancel()
{
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