#include "SubjectDialogImp.h"
#include <wx/valtext.h>
#include <wx/log.h> 
#include <wx/infobar.h>
#include <wx/event.h>
#include "MyApp.h"
#include "ActionCommandParser.h"


SubjectDialogImp::SubjectDialogImp( wxWindow* parent )
:
SubjectDialog( parent )
{

}


void SubjectDialogImp::OnClose( wxCloseEvent& event )
{
	event.Skip();
}


void SubjectDialogImp::OnInitDialog( wxInitDialogEvent& event )
{
	this->m_txtTitle->SetValue(this->_title);
	this->m_txtTitle->SetFocus();

	std::vector<std::wstring> ruleNames;
	ruleNames.push_back(MyApp::RULE_SUBJECT_DIALOG);
	ruleNames.push_back(MyApp::RULE_DIALOG_ACTIONS);

	wxGetApp().DisconnectSpeechHandler(wxGetApp().GetCommandReceivedConnection());
	boost::signals2::connection* commandConnection = wxGetApp().GetCommandReceivedConnection();
	*(commandConnection) = wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->onCommandRecognized(boost::bind(&SubjectDialogImp::OnCommandRecognized, this, _1, _2));
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->EnableRules(ruleNames, this->GetName().ToStdString());


}

void SubjectDialogImp::OnCommandRecognized(std::wstring& phrase, std::vector<CommandProperty> commandPropertyList)
{
	std::wstring actionName;
	std::wstring actionTarget;
	std::wstring targetValue;
	std::wstring ruleName;
	ActionCommandParser actionParser;
	actionParser.Parse(commandPropertyList, actionName, actionTarget, targetValue, ruleName);
	if (boost::algorithm::equals(actionName, MyApp::COMMAND_ACTION_OK))
	{
		wxCommandEvent evt(wxEVT_COMMAND_BUTTON_CLICKED, this->btnStdOK->GetId());
		this->btnStdOK->Command(evt);
		return;
	}
	else if (boost::algorithm::equals(actionName, MyApp::COMMAND_ACTION_CANCEL))
	{
		this->Close();
		return;
	}
	else
	{
		//must be free text
		this->m_txtTitle->AppendText(phrase);
		return;
	}

	
}



void SubjectDialogImp::OnOKButtonClick( wxCommandEvent& event )
{
	this->m_txtTitle->GetValidator()->TransferFromWindow();
	if(this->_title.IsEmpty())
	{
		this->m_infoCtrl->ShowMessage("Title may not be empty");
		this->m_txtTitle->SetFocus();
	}
	else
	{
		event.Skip();
	}
}
	