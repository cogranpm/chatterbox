#include "SpeechMessageDialog.h"
#include "MyApp.h"
#include <wx/app.h> 
#include "ActionCommandParser.h"
#include <wx/event.h>


SpeechMessageDialog::SpeechMessageDialog(wxWindow*  parent,
	const wxString&  message,
	const wxString&  caption = wxMessageBoxCaptionStr,
	long  style = wxOK | wxCANCEL | wxCENTRE,
	const wxPoint&  pos = wxDefaultPosition
) : wxMessageDialog(parent, message, caption, style, pos)
{
	this->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(SpeechMessageDialog::CloseHandler), NULL, this);

}


SpeechMessageDialog::~SpeechMessageDialog()
{
	this->Disconnect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(SpeechMessageDialog::CloseHandler), NULL, this);
}

void SpeechMessageDialog::CloseHandler(wxCloseEvent& event)
{

	event.Veto(true);
}

int SpeechMessageDialog::ShowModal()
{

	std::vector<std::wstring> ruleNames;
	ruleNames.push_back(L"DIALOG_CONFIRM_ACTIONS");
	wxGetApp().DisconnectSpeechHandler(wxGetApp().GetCommandReceivedConnection());
	//keeping the signal connection in the main instance to avoid having connections floating
	//around everywhere that a dialog / panel needs to use one
	boost::signals2::connection* commandConnection = wxGetApp().GetCommandReceivedConnection();
	*(commandConnection) = wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->onCommandRecognized(boost::bind(&SpeechMessageDialog::OnCommandRecognized, this, _1, _2));
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->EnableRules(ruleNames, this->GetName().ToStdString());
	
	return wxMessageDialog::ShowModal();
}

bool SpeechMessageDialog::IsModal() const
{
	return true;
}

void SpeechMessageDialog::OnCommandRecognized(std::wstring& phrase, std::vector<CommandProperty> commandPropertyList)
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
		int id = this->GetAffirmativeId();
		wxCommandEvent evt(wxEVT_COMMAND_BUTTON_CLICKED, this->GetAffirmativeId());
		wxWindow* winYes = this->FindWindowById((long)this->GetAffirmativeId());
		wxButton* btnYes = (wxButton*)winYes;
		wxArrayInt& vals = this->GetMainButtonIds();
	//	btnYes->Command(evt);
//		this->EndModal(wxYES);
	}
	else
	{
		this->SetReturnCode(wxNO);
		this->EndModal(wxNO);
		this->Close();
		this->SendDestroyEvent();
		//this->Destroy();
		//this->SetReturnCode(wxNO);
		//this->Show(false);
		
	}
}