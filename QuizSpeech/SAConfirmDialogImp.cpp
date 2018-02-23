#include "SAConfirmDialogImp.h"
#include "MyApp.h"
#include <wx/app.h> 
#include "ActionCommandParser.h"
#include <wx/event.h>

SAConfirmDialogImp::SAConfirmDialogImp( wxWindow* parent)
:
SAConfirmDialog( parent )
{

}

SAConfirmDialogImp::SAConfirmDialogImp(wxWindow* parent, const wxString& title, const wxString& message)
	:
	SAConfirmDialog(parent, wxID_ANY, title), message(message)
{

}

SAConfirmDialogImp::~SAConfirmDialogImp()
{
	wxGetApp().DisconnectFromSpeech();
}

void SAConfirmDialogImp::OnInitDialog( wxInitDialogEvent& event )
{
	if (!message.empty())
	{
		txtMessage->SetLabel(message);
	}
	std::vector<std::wstring> ruleNames;
	ruleNames.push_back(L"DIALOG_CONFIRM_ACTIONS");
	wxGetApp().DisconnectSpeechHandler(wxGetApp().GetCommandReceivedConnection());
	boost::signals2::connection* commandConnection = wxGetApp().GetCommandReceivedConnection();
	*(commandConnection) = wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->onCommandRecognized(boost::bind(&SAConfirmDialogImp::OnCommandRecognized, this, _1, _2));
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->EnableRules(ruleNames, this->GetName().ToStdString());
}

void SAConfirmDialogImp::NoButtonClick( wxCommandEvent& event )
{
	this->EndModal(wxNO);
}

void SAConfirmDialogImp::YesButtonClick( wxCommandEvent& event )
{
	this->EndModal(wxYES);
}

void SAConfirmDialogImp::OnCommandRecognized(std::wstring& phrase, std::vector<CommandProperty> commandPropertyList)
{
	std::wstring actionName;
	std::wstring actionTarget;
	std::wstring targetValue;
	std::wstring ruleName;
	ActionCommandParser actionParser;
	actionParser.Parse(commandPropertyList, actionName, actionTarget, targetValue, ruleName);
	bool handled = false;
	if (boost::algorithm::equals(actionName, "yes"))
	{
		wxCommandEvent evt(wxEVT_COMMAND_BUTTON_CLICKED, sbSizerYes->GetId());
		sbSizerYes->Command(evt);
	}
	else
	{
		wxCommandEvent evt(wxEVT_COMMAND_BUTTON_CLICKED, sbSizerNo->GetId());
		sbSizerNo->Command(evt);
	}
}
