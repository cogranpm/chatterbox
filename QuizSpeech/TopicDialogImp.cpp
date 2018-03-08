#include "TopicDialogImp.h"
#include <wx/valtext.h>
#include <wx/log.h> 
#include <wx/infobar.h>
#include <wx/event.h>
#include "MyApp.h"
#include "ActionCommandParser.h"


TopicDialogImp::TopicDialogImp( wxWindow* parent )
:
TopicDialog( parent ), ruleNames()
{

}

void TopicDialogImp::OnCancelButtonClick( wxCommandEvent& event )
{
	OnCancel();
}

void TopicDialogImp::OnOKButtonClick( wxCommandEvent& event )
{
	if (!this->OnOK())
	{
		event.Skip();
	}
}

bool TopicDialogImp::OnOK()
{
	this->txtTitle->GetValidator()->TransferFromWindow();
	txtComments->GetValidator()->TransferFromWindow();
	if (this->_title.IsEmpty())
	{
		this->m_infoCtrl1->ShowMessage("Title may not be empty");
		this->txtTitle->SetFocus();
		return true;
	}
	else
	{
		
		return false;
	}
}

bool TopicDialogImp::OnCancel()
{
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->Disconnect();
	this->EndModal(wxID_CANCEL);
	return true;
}

void TopicDialogImp::OnInitDialog(wxInitDialogEvent& event)
{
	ruleNames.push_back(MyApp::RULE_TOPIC_DIALOG);
	ruleNames.push_back(MyApp::RULE_DIALOG_ACTIONS);
	ruleNames.push_back(MyApp::CONTROL_ACTION);
	ruleNames.push_back(MyApp::RULE_DICTATION_ENTRY);
	this->SetupSpeechHandlers();
	txtTitle->GetValidator()->TransferToWindow();
	txtComments->GetValidator()->TransferToWindow();
}


void TopicDialogImp::SetupSpeechHandlers()
{
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->SetupSpeechHandlers(ruleNames,
		this->GetName().ToStdString(),
		boost::bind(&TopicDialogImp::OnCommandRecognized, this, _1, _2));
}

void TopicDialogImp::OnCommandRecognized(std::wstring& phrase, std::vector<CommandProperty> commandPropertyList)
{
	std::wstring actionName;
	std::wstring actionTarget;
	std::wstring targetValue;
	std::wstring ruleName;
	ActionCommandParser actionParser;
	actionParser.Parse(commandPropertyList, actionName, actionTarget, targetValue, ruleName);
	if (boost::algorithm::equals(actionName, MyApp::COMMAND_ACTION_OK))
	{
		wxCommandEvent evt(wxEVT_COMMAND_BUTTON_CLICKED, this->m_sdbSizer2OK->GetId());
		this->m_sdbSizer2OK->Command(evt);
		return;
	}
	else if (boost::algorithm::equals(actionName, MyApp::COMMAND_ACTION_CANCEL))
	{
		this->OnCancel();
		return;
	}
	else if (boost::algorithm::equals(actionTarget, L"title"))
	{
		txtTitle->SetFocus();
		return;
	}
	else if (boost::algorithm::equals(actionTarget, L"comments"))
	{
		txtComments->SetFocus();
		return;
	}
	else if (boost::algorithm::equals(actionName, MyApp::CONTROL_ACTION_CLEAR))
	{
		if (this->txtTitle->HasFocus())
		{
			this->txtTitle->Clear();
		}
		else if (this->txtComments->HasFocus())
		{
			this->txtComments->Clear();
		}
		return;
	}
	else if (boost::algorithm::equals(actionName, MyApp::CONTROL_ACTION_SELECT))
	{
		if (this->txtTitle->HasFocus())
		{
			this->txtTitle->SelectAll();
		}
		else if (this->txtComments->HasFocus())
		{
			this->txtComments->SelectAll();
		}
		return;
	}
	else
	{
		//must be free text
		if (this->txtComments->HasFocus())
		{
			this->txtComments->AppendText(phrase);
		}
		else
		{
			this->txtTitle->AppendText(phrase);
		}
		return;
	}


}
