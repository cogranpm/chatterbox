#pragma once

#include <wx/msgdlg.h>
#include "CommandProperty.h"

class SpeechMessageDialog : public wxMessageDialog
{
	void OnCommandRecognized(std::wstring& phrase, std::vector<CommandProperty> commandPropertyList);
	void CloseHandler(wxCloseEvent& event);
public:
	SpeechMessageDialog(wxWindow*  parent,
		const wxString&  message,
		const wxString&  caption,
		long  style,
		const wxPoint&  pos );
	~SpeechMessageDialog();
	bool IsModal() const;
	int ShowModal();
};

