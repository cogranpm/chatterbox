// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "stdafx.h"
#include "MainFrameImp.h"
#include "MainFrameViewModel.h"
#include "AudioWorker.h"
#include "SpeechListener.h"
#include "FileHandler.h"
#include "SqliteProvider.h"
#include "ApplicationImages.h"
#include "AudioPlayer.h"


class MyApp: public wxApp
{

public:
    
	virtual bool OnInit();
	int OnExit();
	SpeechListener& GetSpeechListener() { return sp; }
	FileHandler& GetFileHandler() { return fh;}
	MainFrameViewModel* GetMainFrameViewModel();
	MainFrameImp* GetMainFrame();
	SqliteProvider* GetProvider() { return dataProvider.get();}
	ApplicationImages& GetImages();
	void OnCommandRecognized(std::wstring& phrase, const std::vector<CommandProperty>& commandPropertyList);
	void DisconnectFromSpeech();
	boost::signals2::connection* GetCommandReceivedConnection(void);
	void DisconnectSpeechHandler(boost::signals2::connection* connection);
	const std::wstring GetUserDataDirectory();

	//constants
	static const size_t HOME_PAGE_INDEX;
	static const std::string DATABASE_FILE_NAME;
	static const std::wstring RULE_FILE_NAME;
	static const std::wstring RULE_FILE_NAME_DICATIONCC;
	static const std::wstring RULE_FILE_MENU;
	static const std::wstring RULE_HOME_SCREEN;
	static const std::wstring RULE_SHELF_DIALOG;
	static const std::wstring RULE_SUBJECT_DIALOG;
	static const std::wstring RULE_TOPIC_DIALOG;
	static const std::wstring RULE_PUBLICATION_DIALOG;
	static const std::wstring RULE_PUBLICATION_TYPES;
	static const std::wstring RULE_PUBLICATION_CONTROLS;
	static const std::wstring RULE_DIALOG_ACTIONS;
	static const std::wstring RULE_DICTATION_ENTRY;
	static const std::wstring RULE_SELECT_SHELF;
	static const std::wstring RULE_SELECT_SUBJECT;
	static const std::wstring RULE_SELECT_PUBLICATION;
	static const std::wstring RULE_SELECT_TOPIC;
	static const std::wstring RULE_SELECT_NOTE;
	static const std::wstring RULE_SELECT_QUIZ;

	/* publication panel */
	static const std::wstring RULE_PUBLICATION_PANEL;
	static const std::wstring RULE_PUBLICATION_PANEL_CONTROLS;
	/* exercise panel */
	static const std::wstring RULE_EXERCISE_DIALOG;
	static const std::wstring RULE_EXERCISE_CONTROLS;
	/* exercise run dialog*/
	static const std::wstring RULE_EXERCISERUN_DIALOG;
	/* note dialog */
	static const std::wstring RULE_NOTE_DIALOG;
	static const std::wstring RULE_NOTE_CONTROLS;

	static const std::wstring COMMAND_FILE;
	static const std::wstring COMMAND_FILE_MENU_QUIT;
	static const std::wstring COMMAND_ACTION;
	static const std::wstring COMMAND_ACTION_DELETE;
	static const std::wstring COMMAND_ACTION_ADD;
	static const std::wstring COMMAND_ACTION_EDIT;
	static const std::wstring COMMAND_ACTION_OK;
	static const std::wstring COMMAND_ACTION_CANCEL;
	static const std::wstring COMMAND_ACTION_CLOSE;
	static const std::wstring CONTROL_ACTION;
	static const std::wstring CONTROL_ACTION_FOCUS;
	static const std::wstring CONTROL_ACTION_CLEAR;
	static const std::wstring CONTROL_ACTION_SELECT;
	static const std::wstring CONTROL_ACTION_CUT;
	static const std::wstring CONTROL_ACTION_COPY;
	static const std::wstring CONTROL_ACTION_PASTE;
	static const std::wstring CONTROL_ACTION_SHOW;
	static const std::wstring VALUE_NAME_ENTITY;
	static const std::wstring ENTITY_SHELF;
	static const std::wstring ENTITY_SUBJECT;
	static const std::wstring ENTITY_PUBLICATION;
	static const std::wstring ENTITY_NOTE;
	static const std::wstring ENTITY_NOTESEGMENT;

	static const std::string MAIN_FRAME_WINDOW_NAME;
	static const std::string PUBLICATION_PANEL_WINDOW_NAME;
	static const std::string AUDIOPLAYER_PANEL_WINDOW_NAME;
	static const std::string EXERCISE_PANEL_WINDOW_NAME;
	static const std::string DICTATION_OVERLAY_DIALOG_WINDOW_NAME;
	static const std::string EXERCISERUN_DIALOG_WINDOW_NAME;
	static const std::string NOTE_DIALOG_WINDOW_NAME;
	static const std::string NOTSEGMENT_PANEL_WINDOW_NAME;
	static const std::string PUBLICATION_DIALOG_WINDOW_NAME;
	static const std::string SA_CONFIRM_DIALOG_WINDOW_NAME;
	static const std::string SEGEMENT_TEMPLATE_DIALOG_WINDOW_NAME;
	static const std::string SHELF_DIALOG_WINDOW_NAME;
	static const std::string SUBJECT_DIALOG_WINDOW_NAME;
	static const std::string TOPIC_DIALOG_WINDOW_NAME;

	static const int DEFAULT_INDEX_COLUMN_WIDTH;
	
private:
	MainFrameImp *frame;
	std::unique_ptr<SqliteProvider> dataProvider;
	SpeechListener sp;
	FileHandler fh;
	std::unique_ptr<ApplicationImages> images;
	boost::signals2::connection  commandReceivedConnection;
	std::unique_ptr<MainFrameViewModel> viewModel;
};

/* allows the wxGetApp() function to be used throughout the application, allows access to this class and its members and functions */
wxDECLARE_APP(MyApp);

