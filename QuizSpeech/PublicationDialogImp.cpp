#include "PublicationDialogImp.h"
#include <wx/valtext.h>
#include <wx/log.h> 
#include <wx/infobar.h>
#include <wx/event.h>
#include "MyApp.h"
#include "ActionCommandParser.h"
#include "GlobalConstants.h"
#include "PublicationTypeHelper.h"

PublicationDialogImp::PublicationDialogImp( wxWindow* parent )
:
PublicationDialog( parent ), ruleNames()
{

}

PublicationDialogImp::~PublicationDialogImp()
{
	
}

void PublicationDialogImp::OnInitDialog( wxInitDialogEvent& event )
{
	PublicationTypeHelper::SetupPublicationTypes(m_cboTypes);

	/* just so happens that index matches key for this combo box */
	this->m_cboTypes->SetSelection(this->_type);
	txtTitle->SetValue(_title);
	txtComments->SetValue(_comments);

	ruleNames.push_back(MyApp::RULE_PUBLICATION_DIALOG);
	ruleNames.push_back(MyApp::RULE_DIALOG_ACTIONS);
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->SetupSpeechHandlers(ruleNames,
		this->GetName().ToStdString(),
		boost::bind(&PublicationDialogImp::OnCommandRecognized, this, _1, _2));

}


void PublicationDialogImp::OnCommandRecognized(std::wstring& phrase, const std::vector<CommandProperty>& commandPropertyList)
{
	std::wstring actionName;
	std::wstring actionTarget;
	std::wstring targetValue;
	std::wstring ruleName;
	ActionCommandParser actionParser;
	actionParser.Parse(commandPropertyList, actionName, actionTarget, targetValue, ruleName);

	if (boost::algorithm::equals(actionName, MyApp::COMMAND_ACTION_OK))
	{
		wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->Disconnect();
		wxCommandEvent evt(wxEVT_COMMAND_BUTTON_CLICKED, this->btnStdOK->GetId());
		this->btnStdOK->Command(evt);
		return;
	}
	else if (boost::algorithm::equals(actionName, MyApp::COMMAND_ACTION_CANCEL))
	{
		this->Close();
		return;
	}
	else if (boost::algorithm::equals(actionName, MyApp::CONTROL_ACTION_CLEAR))
	{
		if (this->txtTitle->HasFocus())
		{
			this->txtTitle->Clear();
		}
		else if (this->m_cboTypes->HasFocus())
		{
			/* not sure what to do */
		}
		else if (txtComments->HasFocus())
		{
			txtComments->Clear();
		}
		return;
	}
	else if (boost::algorithm::equals(actionName, MyApp::CONTROL_ACTION_SELECT))
	{
		if (this->txtTitle->HasFocus())
		{
			this->txtTitle->SelectAll();
		}
		else if (this->m_cboTypes->HasFocus())
		{
			/* not sure what to do */
			m_cboTypes->Dismiss();
		}
		if (this->txtComments->HasFocus())
		{
			this->txtComments->SelectAll();
		}
		return;
	}
	else if (boost::algorithm::equals(actionName, MyApp::CONTROL_ACTION_SHOW))
	{
		if (this->m_cboTypes->HasFocus())
		{
			m_cboTypes->Popup();
		}
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
	else if (boost::algorithm::equals(actionTarget, L"type"))
	{
		m_cboTypes->SetFocus();
		return;
	}
	else if (boost::algorithm::equals(actionName, L"type"))
	{
		if (boost::algorithm::equals(actionTarget, L"av"))
		{
			m_cboTypes->SetSelection(0);
		}
		else if (boost::algorithm::equals(actionTarget, L"book"))
		{
			m_cboTypes->SetSelection(1);
		}
		else if (boost::algorithm::equals(actionTarget, L"lecture"))
		{
			m_cboTypes->SetSelection(2);
		}
		else if (boost::algorithm::equals(actionTarget, L"link"))
		{
			m_cboTypes->SetSelection(3);
		}
		else if (boost::algorithm::equals(actionTarget, L"list"))
		{
			m_cboTypes->SetSelection(4);
		}
		else if (boost::algorithm::equals(actionTarget, L"notebook"))
		{
			m_cboTypes->SetSelection(5);
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


void PublicationDialogImp::OnOKButtonClick( wxCommandEvent& event )
{
	this->txtTitle->GetValidator()->TransferFromWindow();
	txtComments->GetValidator()->TransferFromWindow();
	if(this->_title.IsEmpty())
	{
		this->infoCtrl->ShowMessage("Title may not be empty");
		this->txtTitle->SetFocus();
	}
	else
	{
		PublicationType* data = dynamic_cast<PublicationType*>(this->m_cboTypes->GetClientObject(this->m_cboTypes->GetSelection()));
		this->_type = data->getKey();
		event.Skip();
	}
}

void PublicationDialogImp::TitleOnKillFocus(wxFocusEvent& event)
{ 
	GlobalConstants::PrintError(L"kill focus title", S_OK);
	//DisableWindow(true);
	ruleNames.clear();
	ruleNames.push_back(MyApp::RULE_PUBLICATION_DIALOG);
	ruleNames.push_back(MyApp::RULE_DIALOG_ACTIONS);
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->EnableRules(ruleNames, this->GetName().ToStdString());
	//DisableWindow(false);
	event.Skip(); 
}


void PublicationDialogImp::TitleOnSetFocus(wxFocusEvent& event)
{
	GlobalConstants::PrintError(L"set focus title", S_OK);
	//DisableWindow(true);
	ruleNames.clear();
	ruleNames.push_back(MyApp::RULE_PUBLICATION_DIALOG);
	ruleNames.push_back(MyApp::RULE_DICTATION_ENTRY);
	ruleNames.push_back(MyApp::RULE_DIALOG_ACTIONS);
	ruleNames.push_back(MyApp::CONTROL_ACTION);
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->EnableRules(ruleNames, this->GetName().ToStdString());
	//DisableWindow(false);
	event.Skip(); 
}


void PublicationDialogImp::TypesOnKillFocus(wxFocusEvent& event)
{
	GlobalConstants::PrintError(L"kill focus type", S_OK);
	//DisableWindow(true);
	ruleNames.clear();
	ruleNames.push_back(MyApp::RULE_PUBLICATION_DIALOG);
	ruleNames.push_back(MyApp::RULE_DIALOG_ACTIONS);
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->EnableRules(ruleNames, this->GetName().ToStdString());
	//DisableWindow(false);
	event.Skip();
}

void PublicationDialogImp::TypesOnSetFocus(wxFocusEvent& event)
{
	GlobalConstants::PrintError(L"set focus type", S_OK);
	//DisableWindow(true);
	ruleNames.clear();
	ruleNames.push_back(MyApp::RULE_PUBLICATION_DIALOG);
	ruleNames.push_back(MyApp::RULE_DIALOG_ACTIONS);
	ruleNames.push_back(L"PUBLICATION_TYPES");
	ruleNames.push_back(MyApp::CONTROL_ACTION);
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->EnableRules(ruleNames, this->GetName().ToStdString());
	//DisableWindow(false);
	event.Skip();
}


void PublicationDialogImp::DisableWindow(bool flag)
{
	if (!flag)
	{
		this->txtTitle->Enable();
		this->m_cboTypes->Enable();
		txtComments->Enable();
	}
	else
	{
		this->txtTitle->Disable();
		this->m_cboTypes->Disable();
		txtComments->Disable();
	}
}