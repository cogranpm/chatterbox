#include "SubjectDialogImp.h"
#include <wx/valtext.h>
#include <wx/log.h> 
#include <wx/infobar.h>
#include <wx/event.h>
#include "MyApp.h"
#include "ActionCommandParser.h"


SubjectDialogImp::SubjectDialogImp( wxWindow* parent )
:
SubjectDialog( parent ), ruleNames()
{

}


SubjectDialogImp::~SubjectDialogImp()
{
	//wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->Disconnect();
}

void SubjectDialogImp::OnClose( wxCloseEvent& event )
{
	//wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->Disconnect();
	event.Skip();
}


void SubjectDialogImp::OnInitDialog( wxInitDialogEvent& event )
{
	this->m_txtTitle->SetValue(this->_title);
	this->txtComments->SetValue(this->_comments);
	this->m_txtTitle->SetFocus();

	ruleNames.push_back(MyApp::RULE_SUBJECT_DIALOG);
	ruleNames.push_back(MyApp::RULE_DIALOG_ACTIONS);

	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->SetupSpeechHandlers(ruleNames,
		this->GetName().ToStdString(),
		boost::bind(&SubjectDialogImp::OnCommandRecognized, this, _1, _2));

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
		wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->Disconnect();
		this->Close();
		return;
	}
	else
	{
		//must be free text
		if (txtComments->HasFocus())
		{
			txtComments->AppendText(phrase);
		}
		else
		{
			this->m_txtTitle->AppendText(phrase);
		}
		return;
	}

	
}



void SubjectDialogImp::OnOKButtonClick( wxCommandEvent& event )
{
	m_txtTitle->GetValidator()->TransferFromWindow();
	txtComments->GetValidator()->TransferFromWindow();
	if(_title.IsEmpty())
	{
		m_infoCtrl->ShowMessage("Title may not be empty");
		m_txtTitle->SetFocus();
	}
	else
	{
		//wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->Disconnect();
		event.Skip();
	}
}
	