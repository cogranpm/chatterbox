#ifndef __NoteSegmentPanelImp__
#define __NoteSegmentPanelImp__

/**
@file
Subclass of NoteSegmentPanel, which is generated by wxFormBuilder.
*/

#include "NoteSegmentPanel.h"
#include "NoteViewModel.h"
#include "NoteSegment.h"
#include "AudioPlayer.h"
#include "AudioPlayerPanelImp.h"
//// end generated include

/** Implementing NoteSegmentPanel */
class NoteSegmentPanelImp : public NoteSegmentPanel
{

private:
	NoteViewModel& noteViewModel;
	NoteSegment* noteSegment;
	void UpdateUI(bool isRecording);
	AudioPlayer player;
	AudioPlayerPanelImp* playerPanel;
	void ClearBody();


protected:
	void DeleteOnButtonClick( wxCommandEvent& event );
	void ValueOnKillFocus(wxFocusEvent& event);
	void ValueOnSetFocus(wxFocusEvent& event);
	void BodyRecordOnButtonClick(wxCommandEvent& event);
	void OnButtonClickClearBody(wxCommandEvent& event);
	
	public:
		/** Constructor */
		NoteSegmentPanelImp( wxWindow* parent, NoteViewModel& noteViewModel, NoteSegment* noteSegment );
		~NoteSegmentPanelImp();
		wxTextCtrl* GetBodyControl();
		wxStaticText* GetBodyLabelControl();
		NoteSegment* GetNoteSegment() { return this->noteSegment; }
		
	//// end generated class members
	
};

#endif // __NoteSegmentPanelImp__
