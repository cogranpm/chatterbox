#ifndef __NoteDialogImp__
#define __NoteDialogImp__

/**
@file
Subclass of NoteDialog, which is generated by wxFormBuilder.
*/

#include "NoteSegmentPanelImp.h"
#include "NoteDialog.h"
#include "NoteViewModel.h"
#include "NoteSegmentTypeHeader.h"
#include "NoteSegmentType.h"
#include "AudioPlayer.h"
#include "AudioPlayerPanelImp.h"
#include "SegmentTypeViewModel.h"
#include "NoteAudioPlayer.h"
//// end generated include

#include "CommandProperty.h"


/** Implementing NoteDialog */
class NoteDialogImp : public pnlNote
{


private:
		enum
		{
			InitFormTimer
		};
		//std::unique_ptr<NoteViewModel> viewModel;
		NoteViewModel viewModel;
		NoteSegmentType defaultSegmentType;
		std::vector<NoteSegmentPanelImp*> segmentPanelList;
		AudioPlayer player;
		AudioPlayer titlePlayer;
		AudioPlayerPanelImp* playerPanel;
		AudioPlayerPanelImp* titlePlayerPanel;
		NoteAudioPlayer noteAudioPlayer;
		std::vector<std::wstring> ruleNames;
		wxTimer* timer;

		void RenderNote(void);
		void AddSelectedSegments();
		NoteSegmentPanelImp* AddSegment(NoteSegment* noteSegment, NoteSegmentType& noteSegmentType);
		NoteSegmentTypeHeader GetSelectedNoteType(int selectedIndex);
		void ChangeNoteType(int selectedIndex);
		void SetSegmentFocus(NoteSegmentPanelImp* panel);
		void SetupSpeechHandlers();
		void RenderNoteSegmentTypes();
		void SaveSegmentTypes(SegmentTypeViewModel& viewModel);

		void OnCommandRecognized(std::wstring& phrase, const std::vector<CommandProperty>& commandPropertyList);
		void CloseMe(wxCloseEvent* event);
		void RecordTitle();
		void RecordDescription();
		void NewSegment();
		void EditSegment();
		void DeleteSegment();
		void OnProgressTimer(wxTimerEvent& event);
		void OnSave();

	protected:
		void OnClose(wxCloseEvent& event);
		void OnInitDialog( wxInitDialogEvent& event );
		void AddSegmentOnButtonClick( wxCommandEvent& event );
		void ClearSegmentOnButtonClick(wxCommandEvent& event);
		void NewSegmentOnButtonClick(wxCommandEvent& event);
		void EditSegmentOnButtonClick(wxCommandEvent& event);

	//	void DeleteOnButtonClick( wxCommandEvent& event );
		void OnOKButtonClick( wxCommandEvent& event );
		void OnCancelButtonClick(wxCommandEvent& event);
		void TypesOnListBox(wxCommandEvent& event);
		void TypesOnListBoxDClick(wxCommandEvent& event);
		void UnlockTitleOnButtonClick(wxCommandEvent& event);
		void RecordTitleOnButtonClick(wxCommandEvent& event);
		void ClearTitleOnButtonClick(wxCommandEvent& event);
		void UnlockDescriptionOnButtonClick(wxCommandEvent& event);
		void RecordDescriptionOnButtonClick(wxCommandEvent& event);
		void ClearDescriptionOnButtonClick(wxCommandEvent& event);

		void PlayAllOnButtonClick(wxCommandEvent& event);
		void StopAllOnButtonClick(wxCommandEvent& event);


	public:
		/** Constructor */
		NoteDialogImp( wxWindow* parent, Note* note );
		~NoteDialogImp();
		//NoteViewModel& GetViewModel() { return *viewModel;}
		NoteViewModel& GetViewModel() { return viewModel; }
		//NoteDialogImp( wxWindow* parent );
	//// end generated class members

		wxDECLARE_EVENT_TABLE();
	
};

#endif // __NoteDialogImp__
