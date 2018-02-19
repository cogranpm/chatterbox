#ifndef __DictationOverlayDialogImp__
#define __DictationOverlayDialogImp__

/**
@file
Subclass of OverlayDialog, which is generated by wxFormBuilder.
*/

#include "DictationOverlayDialog.h"
#include "stdafx.h"
#include <wx/timer.h>
#include "DictationOverlayUpdateTimer.h"
#include "DictationOverlayDialogHypothesisTimer.h"
#include "AudioPlayer.h"
#include "AudioPlayerPanelImp.h"
#include "CommandProperty.h"
//// end generated include

/** Implementing OverlayDialog */
class DictationOverlayDialogImp : public OverlayDialog
{

	enum class RecordingState { recorded, recording };
	RecordingState recordingState;
	bool recognitionReceived;
	DictationOverlayUpdateTimer timer;
	DictationOverlayDialogHypothesisTimer hypothesisTimer;
	std::wstring fileName;
	std::wstring fullAudioPath;
	std::wstring recognizedText;
	//AudioPlayer* audioPlayer;
	AudioPlayer player;
	AudioPlayerPanelImp* audioPlayerPanel;
	boost::signals2::connection  phraseReceivedConnection;
	boost::signals2::connection  hypothesisReceivedConnection;
	boost::signals2::connection  soundStartConnection;
	boost::signals2::connection  soundEndConnection;
	boost::signals2::connection  dictationStoppedConnection;

	void OnSpeechRecognized(const std::wstring& text);
	void OnHypothesisRecognized(const std::wstring& text);
	void OnSoundStart();
	void OnSoundEnd();
	void OnDictationStopped();
	void EndDication();
	void StartDictation();
	std::wstring& GetFullAudioPath() { return fullAudioPath; }
	void SetFileName(std::wstring& newFileName);
	void OnCommandRecognized(std::wstring& phrase, const std::vector<CommandProperty>& commandPropertyList);
	void EnableAllRules();

	protected:
		// Handlers for OverlayDialog events.
		void OnInitDialog(wxInitDialogEvent& event);
		void StopOnButtonClick( wxCommandEvent& event );
		void OnCancelButtonClick(wxCommandEvent& event);
		void OnOKButtonClick(wxCommandEvent& event);

	public:
		/** Constructor */
		DictationOverlayDialogImp( wxWindow* parent );
		DictationOverlayDialogImp(wxWindow* parent, const std::wstring& fileName);
		~DictationOverlayDialogImp();
	//// end generated class members
		//void GetRecognizedText(std::wstring& buffer) { buffer = std::wstring(txtPhrase->GetValue()); }
		void GetRecognizedText(std::wstring& buffer);
		
};



#endif // __DictationOverlayDialogImp__
