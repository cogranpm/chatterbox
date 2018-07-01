#include "MyApp.h"
#include <wx/mediactrl.h>
#include <wx/stdpaths.h>
#include <wx/image.h> 
#include "SettingsDialogImp.h"


wxIMPLEMENT_APP(MyApp);

const size_t MyApp::HOME_PAGE_INDEX = 0;
const std::string MyApp::APPLICATION_NAME = "Chatterbox";
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
const std::wstring MyApp::RULE_PANEL_ACTIONS = L"PANEL_ACTIONS";
const std::wstring MyApp::RULE_DICTATION_ENTRY = L"DICTATION_ENTRY";
const std::wstring MyApp::RULE_MAINFRAME_LOOKUP = L"MAINFRAME_LOOKUP";
const std::wstring MyApp::RULE_SELECT_SUBJECT = L"SELECT_SUBJECT";
const std::wstring MyApp::RULE_SELECT_PUBLICATION = L"SELECT_PUBLICATION";
const std::wstring MyApp::RULE_SELECT_TOPIC = L"SELECT_TOPIC";
const std::wstring MyApp::RULE_SELECT_NOTE = L"SELECT_NOTE";
const std::wstring MyApp::RULE_SELECT_QUIZ = L"SELECT_QUIZ";
const std::wstring MyApp::RULE_LIST_ACTIONS = L"LIST_ACTIONS";

/* PUBLICATION PANEL */
const std::wstring MyApp::RULE_PUBLICATION_PANEL = L"PUBLICATION_PANEL";
const std::wstring MyApp::RULE_PUBLICATION_PANEL_CONTROLS = L"PUBLICATION_PANEL_CONTROLS";
/* EXERCISE PANEL */
const std::wstring MyApp::RULE_EXERCISE_DIALOG = L"EXERCISE_DIALOG";
const std::wstring MyApp::RULE_EXERCISE_CONTROLS = L"EXERCISE_CONTROLS";
/* EXERCISE RUN DIALOG */
const std::wstring MyApp::RULE_EXERCISERUN_DIALOG = L"EXERCISERUN_DIALOG";
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
const std::wstring MyApp::COMMAND_ACTION_CLOSE = L"close";
const std::wstring MyApp::COMMAND_ACTION_APPLY = L"apply";

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

/* config keys */
const std::wstring MyApp::CONFIGKEY_DATA_DIRECTORY = L"DataDirectory";

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
		/* if the following is set wxWidgets will use this at appropriate times internally
		also allows user to get the config using the static get function
		*/
		wxConfigBase::Set(new wxConfig(MyApp::APPLICATION_NAME));
		LoadDefaultSettings();
		//initialize the database provider
		dataProvider = std::make_unique<SqliteProvider>();
		bool result = SetDefaultPaths();
		if (!result)
		{
			int maxAttempts = 3;
			int currentAttempt = 0;
			while (currentAttempt < maxAttempts)
			{
				SettingsDialogImp dlg(NULL);
				dlg.SetDataDirectory(wxString(""));
				if (dlg.ShowModal() == wxID_OK)
				{
					if (dlg.GetDataDirectoryDirty())
					{
						dataDirectory = dlg.GetDataDirectory();
						wxConfigBase* config = wxConfigBase::Get();
						bool isWriteOk = config->Write(MyApp::CONFIGKEY_DATA_DIRECTORY, wxString(dataDirectory));

						if (SetDefaultPaths())
						{
							break;
						}
					}
				}
				currentAttempt++;
			}
			/* show the settings dialog and redo this if necessary */
		}
		return InitializeFrame();
		
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
   
}


bool MyApp::InitializeFrame()
{
	try
	{

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

bool MyApp::SetDefaultPaths()
{
	wxString databaseName;
	//databaseName = wxGetCwd() + "/" + MyApp::DATABASE_FILE_NAME;

	//lets make sure the datadirectory exists, things may have changed
	if (!wxGetApp().GetFileHandler().FolderExists(dataDirectory))
	{
		return false;
	}
	
	databaseName = dataDirectory + L"/" + MyApp::DATABASE_FILE_NAME;
	try
	{
		this->dataProvider->initDB(databaseName);
	}
	catch (std::exception e)
	{
		//could be an incorrect path to data file need to react
		return false;
	}

	//set up the current path in the FileHandler instance.
	//note currentPath is set when MakeDirectory is called
	wxGetApp().GetFileHandler().SetCurrentPath(dataDirectory);
	//pass empty folder and it will make the current directory
	wxGetApp().GetFileHandler().MakeDirectory(std::wstring(L""));
	std::wstring audioDirectory = dataDirectory + L"\\Audio\\";
	wxGetApp().GetFileHandler().MakeDirectory(L"Audio");
	wxGetApp().GetFileHandler().SetCurrentPath(audioDirectory);
	wxGetApp().GetFileHandler().SetAudioPath(audioDirectory);
	return true;
}

const std::wstring const MyApp::GetDataDirectory()
{
	return dataDirectory;
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

const std::wstring const MyApp::GetUserDataDirectory()
{
	return ::wxStandardPaths::Get().GetUserLocalDataDir().ToStdWstring();
}

void MyApp::LoadDefaultSettings()
{
	bool isWriteOk = true;
	wxString defaultDataDirectory;
	wxConfigBase* config = wxConfigBase::Get();
	if (config->Read(MyApp::CONFIGKEY_DATA_DIRECTORY, &defaultDataDirectory))
	{
		dataDirectory = defaultDataDirectory.ToStdWstring();
	}
	else
	{
		dataDirectory = GetUserDataDirectory();
		isWriteOk = config->Write(MyApp::CONFIGKEY_DATA_DIRECTORY, wxString(dataDirectory));
	}
}

void MyApp::ChangeDataDirectory(const std::wstring& newDataDirectory)
{
	dataDirectory = newDataDirectory;
	wxConfigBase* config = wxConfigBase::Get();
	bool isWriteOk = config->Write(MyApp::CONFIGKEY_DATA_DIRECTORY, wxString(dataDirectory));
	dataProvider->Close();
	SetDefaultPaths();
	frame->ChangeDatabase();
}
