#include "PublicationDialogImp.h"
#include "PublicationType.h"
#include <wx/valtext.h>
#include <wx/log.h> 
#include <wx/infobar.h>
#include <wx/event.h>
#include "MyApp.h"
#include "ActionCommandParser.h"
#include "GlobalConstants.h"

PublicationDialogImp::PublicationDialogImp( wxWindow* parent )
:
PublicationDialog( parent )
{

}

PublicationDialogImp::~PublicationDialogImp()
{
	wxGetApp().DisconnectFromSpeech();
}

void PublicationDialogImp::OnInitDialog( wxInitDialogEvent& event )
{
	this->m_cboTypes->SetClientObject(0, new PublicationType(0));
	this->m_cboTypes->SetClientObject(1, new PublicationType(1));
	this->m_cboTypes->SetClientObject(2, new PublicationType(2));
	this->m_cboTypes->SetClientObject(3, new PublicationType(3));

	/* just so happens that index matches key for this combo box */
	this->m_cboTypes->SetSelection(this->_type);

	std::vector<std::wstring> ruleNames;
	ruleNames.push_back(MyApp::RULE_PUBLICATION_DIALOG);
	//ruleNames.push_back(MyApp::RULE_DICTATION_ENTRY);
	//ruleNames.push_back(MyApp::RULE_PUBLICATION_TYPES);
	//ruleNames.push_back(MyApp::RULE_PUBLICATION_CONTROLS);
	ruleNames.push_back(MyApp::RULE_DIALOG_ACTIONS);

	wxGetApp().DisconnectSpeechHandler(wxGetApp().GetCommandReceivedConnection());
	boost::signals2::connection* commandConnection = wxGetApp().GetCommandReceivedConnection();
	*(commandConnection) = wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->onCommandRecognized(boost::bind(&PublicationDialogImp::OnCommandRecognized, this, _1, _2));
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->EnableRules(ruleNames, this->GetName().ToStdString());

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
		return;
	}
	else
	{
		//must be free text
		this->txtTitle->AppendText(phrase);
		return;
	}
	

}


void PublicationDialogImp::OnOKButtonClick( wxCommandEvent& event )
{
	this->txtTitle->GetValidator()->TransferFromWindow();
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
	::PrintError(L"kill focus title", S_OK);
	//DisableWindow(true);
	std::vector<std::wstring> ruleNames;
	ruleNames.push_back(MyApp::RULE_PUBLICATION_DIALOG);
	ruleNames.push_back(MyApp::RULE_DIALOG_ACTIONS);
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->EnableRules(ruleNames, this->GetName().ToStdString());
	//DisableWindow(false);
	event.Skip(); 
}


void PublicationDialogImp::TitleOnSetFocus(wxFocusEvent& event)
{
	::PrintError(L"set focus title", S_OK);
	//DisableWindow(true);
	std::vector<std::wstring> ruleNames;
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
	::PrintError(L"kill focus type", S_OK);
	//DisableWindow(true);
	std::vector<std::wstring> ruleNames;
	ruleNames.push_back(MyApp::RULE_PUBLICATION_DIALOG);
	ruleNames.push_back(MyApp::RULE_DIALOG_ACTIONS);
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->EnableRules(ruleNames, this->GetName().ToStdString());
	//DisableWindow(false);
	event.Skip();
}

void PublicationDialogImp::TypesOnSetFocus(wxFocusEvent& event)
{
	::PrintError(L"set focus type", S_OK);
	//DisableWindow(true);
	std::vector<std::wstring> ruleNames;
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
	}
	else
	{
		this->txtTitle->Disable();
		this->m_cboTypes->Disable();
	}
}