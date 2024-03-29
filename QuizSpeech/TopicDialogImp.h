#ifndef __TopicDialogImp__
#define __TopicDialogImp__

/**
@file
Subclass of TopicDialog, which is generated by wxFormBuilder.
*/

#include "TopicDialog.h"

//// end generated include

#include "CommandProperty.h"

/** Implementing TopicDialog */
class TopicDialogImp : public TopicDialog
{
	std::vector<std::wstring> ruleNames;
	void OnCommandRecognized(std::wstring& phrase, std::vector<CommandProperty> commandPropertyList);
	void SetupSpeechHandlers();
	bool OnOK();
	bool OnCancel();

	protected:
		// Handlers for TopicDialog events.
		void OnCancelButtonClick( wxCommandEvent& event );
		void OnOKButtonClick( wxCommandEvent& event );
		void OnInitDialog(wxInitDialogEvent& event);
	public:
		/** Constructor */
		TopicDialogImp( wxWindow* parent );
	//// end generated class members
	
};

#endif // __TopicDialogImp__
