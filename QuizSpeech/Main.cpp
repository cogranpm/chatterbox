#include "MyApp.h"
#include <wx/mediactrl.h>
#include <wx/stdpaths.h>
#include <wx/image.h> 

wxIMPLEMENT_APP(MyApp);

const size_t MyApp::HOME_PAGE_INDEX = 0;
const std::string MyApp::DATABASE_FILE_NAME = "data.db";
const std::wstring MyApp::RULE_FILE_NAME = L"rules.xml";
const std::wstring MyApp::RULE_FILE_NAME_DICATIONCC = L"rulescc.xml";
const std::wstring MyApp::RULE_FILE_MENU = L"FILE_MENU";
const std::wstring MyApp::RULE_HOME_SCREEN = L"HOME_SCREEN";
const std::wstring MyApp::RULE_SHELF_DIALOG = L"SHELF_DIALOG";
const std::wstring MyApp::RULE_SUBJECT_DIALOG = L"SUBJECT_DIALOG";
const std::wstring MyApp::RULE_TOPIC_DIALOG = L"TOPIC_DIALOG";
const std::wstring MyApp::RULE_PUBLICATION_DIALOG = L"PUBLICATION_DIALOG";
const std::wstring MyApp::RULE_PUBLICATION_TYPES = L"PUBLICATION_TYPES";
const std::wstring MyApp::RULE_PUBLICATION_CONTROLS = L"PUBLICATION_CONTROLS";
const std::wstring MyApp::RULE_DIALOG_ACTIONS = L"DIALOG_ACTIONS";
const std::wstring MyApp::RULE_DICTATION_ENTRY = L"DICTATION_ENTRY";
const std::wstring MyApp::RULE_SELECT_SHELF = L"SELECT_SHELF";
const std::wstring MyApp::RULE_SELECT_SUBJECT = L"SELECT_SUBJECT";
const std::wstring MyApp::RULE_SELECT_PUBLICATION = L"SELECT_PUBLICATION";

/* PUBLICATION PANEL */
const std::wstring MyApp::RULE_PUBLICATION_PANEL = L"PUBLICATION_PANEL";
const std::wstring MyApp::RULE_PUBLICATION_PANEL_CONTROLS = L"PUBLICATION_PANEL_CONTROLS";
/* EXERCISE PANEL */
const std::wstring MyApp::RULE_EXERCISE_DIALOG = L"EXERCISE_DIALOG";
const std::wstring MyApp::RULE_EXERCISE_CONTROLS = L"EXERCISE_CONTROLS";
/* NOTE PANEL */
const std::wstring MyApp::RULE_NOTE_DIALOG = L"NOTE_DIALOG";
const std::wstring MyApp::RULE_NOTE_CONTROLS = L"NOTE_CONTROLS";

const std::wstring MyApp::COMMAND_FILE = L"file";
const std::wstring MyApp::COMMAND_FILE_MENU_QUIT = L"quit";
const std::wstring MyApp::COMMAND_ACTION = L"action";
const std::wstring MyApp::COMMAND_ACTION_DELETE = L"delete";
const std::wstring MyApp::COMMAND_ACTION_ADD = L"add";
const std::wstring MyApp::COMMAND_ACTION_EDIT = L"edit";
const std::wstring MyApp::COMMAND_ACTION_OK = L"ok";
const std::wstring MyApp::COMMAND_ACTION_CANCEL = L"cancel";

const std::wstring MyApp::CONTROL_ACTION = L"CONTROL_ACTIONS";
const std::wstring MyApp::CONTROL_ACTION_FOCUS = L"focus";
const std::wstring MyApp::CONTROL_ACTION_CLEAR = L"clear";
const std::wstring MyApp::CONTROL_ACTION_SELECT = L"select";
const std::wstring MyApp::CONTROL_ACTION_CUT = L"cut";
const std::wstring MyApp::CONTROL_ACTION_COPY = L"copy";
const std::wstring MyApp::CONTROL_ACTION_PASTE = L"paste";
const std::wstring MyApp::CONTROL_ACTION_SHOW = L"show";

const std::wstring MyApp::VALUE_NAME_ENTITY = L"entity";
const std::wstring MyApp::ENTITY_SHELF = L"shelf";
const std::wstring MyApp::ENTITY_SUBJECT = L"subject";
const std::wstring MyApp::ENTITY_PUBLICATION = L"publication";
const std::wstring MyApp::ENTITY_NOTE = L"note";
const std::wstring MyApp::ENTITY_NOTESEGMENT = L"notesegment";


/* window names */
const std::string MyApp::MAIN_FRAME_WINDOW_NAME = "MainFrame";
const std::string MyApp::PUBLICATION_PANEL_WINDOW_NAME = "PublicationPanel";
const std::string MyApp::AUDIOPLAYER_PANEL_WINDOW_NAME = "AudioPlayerPanel";
const std::string MyApp::EXERCISE_PANEL_WINDOW_NAME = "ExercisePanel";
const std::string MyApp::DICTATION_OVERLAY_DIALOG_WINDOW_NAME = "DictationOverlayDialog";
const std::string MyApp::EXERCISERUN_DIALOG_WINDOW_NAME = "ExerciseRunDialog";
const std::string MyApp::NOTE_DIALOG_WINDOW_NAME = "NoteDialog";
const std::string MyApp::NOTSEGMENT_PANEL_WINDOW_NAME = "NoteSegmentPanel";
const std::string MyApp::PUBLICATION_DIALOG_WINDOW_NAME = "PublicationDialog";
const std::string MyApp::SA_CONFIRM_DIALOG_WINDOW_NAME = "SAConfirmDialog";
const std::string MyApp::SEGEMENT_TEMPLATE_DIALOG_WINDOW_NAME = "SegmentTemplateDialog";
const std::string MyApp::SHELF_DIALOG_WINDOW_NAME = "ShelfDialog";
const std::string MyApp::SUBJECT_DIALOG_WINDOW_NAME = "SubjectDialog";
const std::string MyApp::TOPIC_DIALOG_WINDOW_NAME = "TopicDialog";


const int MyApp::DEFAULT_INDEX_COLUMN_WIDTH = 20;

//const SPSTREAMFORMAT spFormat = SPSF_22kHz16BitStereo;

bool MyApp::OnInit()
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if(FAILED(hr))
	{
		return false;
	}
	
	try
	{
	
		viewModel = std::make_unique<MainFrameViewModel>();

		//initialize the database provider
		dataProvider = std::make_unique<SqliteProvider>();

		wxString databaseName;
#ifdef _DEBUG
		databaseName = wxGetCwd() + "/" + MyApp::DATABASE_FILE_NAME;
#endif // _DEBUG

#ifndef _DEBUG
		databaseName = wxGetApp().GetUserDataDirectory() + "/" + MyApp::DATABASE_FILE_NAME;
#endif // !_DEBUG


		this->dataProvider->initDB(databaseName);
		
		//set up the current path in the FileHandler instance.
		//note currentPath is set when MakeDirectory is called
		std::wstring userDir;
#ifdef _DEBUG
		userDir = wxGetCwd();
#endif // _DEBUG

#ifndef _DEBUG
		userDir = wxGetApp().GetUserDataDirectory();
#endif // !_DEBUG

		
		
		wxGetApp().GetFileHandler().SetCurrentPath(userDir);
		//pass empty folder and it will make the current directory
		wxGetApp().GetFileHandler().MakeDirectory(std::wstring(L""));
		std::wstring audioDirectory = userDir + L"\\Audio\\";
		wxGetApp().GetFileHandler().MakeDirectory(L"Audio");
		wxGetApp().GetFileHandler().SetCurrentPath(audioDirectory);
		wxGetApp().GetFileHandler().SetAudioPath(audioDirectory);

		//sp.setStopWord(L"orange");
		sp.InitSpeech();
	}
	catch (std::runtime_error& re)
	{
		//show error message and exit
		wxMessageBox(re.what(), L"Error", wxICON_ERROR);
		return false;
	}
	catch (std::exception& ex)
	{
		//show a message here and exit etc
		wxMessageBox(ex.what(), L"Error", wxICON_ERROR);
		return false;
	}

	//(works)
	//this->getAudioWorker().playSoundFile(L"c:\\\\Projects\\AudioSamples\\2171000000.wav");

	//(works)
	//this->GetSpeechListener().SpeakText(L"Hello, initializing speech ");

	try
	{
		AudioPlayer::Init();
		this->images = std::make_unique<ApplicationImages>();
		this->images->Init();
		frame = new MainFrameImp(NULL);
		frame->Show(true);
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
		std::string  cs(e.what());
		std::wstring ws;
		copy(cs.begin(), cs.end(), std::back_inserter(ws));
		GlobalConstants::PrintError(ws, S_OK);
		wxMessageBox(e.what(), L"Error", wxICON_ERROR);
		return false;
	}
	catch (...)
	{
		return false;
	}

    return true;
}

const std::wstring MyApp::GetUserDataDirectory()
{
	return ::wxStandardPaths::Get().GetUserLocalDataDir().ToStdWstring();
}

void MyApp::OnCommandRecognized (std::wstring& phrase, const std::vector<CommandProperty>& commandPropertyList)
{
	std::vector<CommandProperty>::const_iterator it;
	for (it = commandPropertyList.begin(); it != commandPropertyList.end(); it++)
	{
		CommandProperty property = *(it);
		if (boost::algorithm::equals(property.GetPropertyName(), MyApp::COMMAND_FILE))
		{
			if (boost::algorithm::equals(property.GetPropertyValue(), MyApp::COMMAND_FILE_MENU_QUIT))
			{
				frame->Close();
				break;
			}
		}
	}
}

boost::signals2::connection* MyApp::GetCommandReceivedConnection()
{
	return &this->commandReceivedConnection;
}

void MyApp::DisconnectSpeechHandler(boost::signals2::connection* connection)
{
	if (connection->connected())
	{
		connection->disconnect();
	}
}

void MyApp::DisconnectFromSpeech()
{
	DisconnectSpeechHandler(GetCommandReceivedConnection());
	GetSpeechListener().GetSpeechRecognitionContext()->Disable();
}


MainFrameViewModel* MyApp::GetMainFrameViewModel()
{
	return viewModel.get();
}

ApplicationImages& MyApp::GetImages()
{
	return *images;
}

MainFrameImp* MyApp::GetMainFrame()
{
	return frame;
}

int MyApp::OnExit()
{
	this->DisconnectSpeechHandler(&this->commandReceivedConnection);
	AudioPlayer::ShutDown();
	CoUninitialize();
	return 0;
}

