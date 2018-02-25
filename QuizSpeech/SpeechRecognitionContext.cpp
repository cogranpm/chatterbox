#include "SpeechRecognitionContext.h"
#include "GlobalConstants.h"
#include "MyApp.h"



SpeechRecognitionContext::SpeechRecognitionContext() :
	callbackInterface(new SpeechRecognitionCallback(this)), grammar(nullptr), context(nullptr), windowName(""), ruleNames(nullptr)
{
}




SpeechRecognitionContext::~SpeechRecognitionContext()
{
	if (ruleNames != nullptr)
	{
		delete ruleNames;
		ruleNames = nullptr;
	}

	if (this->grammar != nullptr)
	{
		this->grammar.Release();
		this->grammar = nullptr;
	}
	
	if (this->context != nullptr)
	{
		this->context.Release();
		this->context = nullptr;
	}

}

void SpeechRecognitionContext::CreateRecognitionContext(SpeechRecognitionEngine* engine)
{
	HRESULT hr = engine->GetEngine()->CreateRecoContext(&context);
	if (FAILED(hr))
	{
		const std::string message("Call to CreateRecoContext failed");
		::PrintError(L"Call to CreateRecoContext failed", hr);
		throw std::runtime_error(message);
	}
	/*ULONGLONG ullMyEvents = SPFEI(SPEI_SOUND_START) | SPFEI(SPEI_SOUND_END) |
		SPFEI(SPEI_PHRASE_START) | SPFEI(SPEI_RECOGNITION) |
		SPFEI(SPEI_INTERFERENCE) | SPFEI(SPEI_RECO_STATE_CHANGE);
*/
	ULONGLONG ullMyEvents = SPFEI(SPEI_RECOGNITION);

	hr = context->SetInterest(ullMyEvents, ullMyEvents);
	if (FAILED(hr))
	{
		const std::string message("Call to SetInterest failed");
		::PrintError(L"Call to SetInterest failed", hr);
		throw std::runtime_error(message);
	}

	this->grammar.Release();
	hr = this->context->CreateGrammar(::GID_CC, &this->grammar);
	if (FAILED(hr))
	{
		this->grammar.Release();
		const std::string message("Call to CreateGrammar failed");
		::PrintError(L"Call to CreateGrammar failed", hr);
		throw std::runtime_error(message);
	}

	hr = this->grammar->SetGrammarState(SPGS_DISABLED);
	if (FAILED(hr))
	{
		this->grammar.Release();
		const std::string message("Call to SetGrammarState failed");
		::PrintError(L"Call to SetGrammarState failed", hr);
		throw std::runtime_error(message);
	}

	hr = this->grammar->LoadCmdFromFile(MyApp::RULE_FILE_NAME.c_str(), SPLO_DYNAMIC);
	if (FAILED(hr))
	{
		this->grammar.Release();
		const std::string message("Call to LoadCmdFromFile failed");
		::PrintError(L"Call to LoadCmdFromFile failed", hr);
		throw std::runtime_error(message);
	}

	this->Disable();
	SetupCallback();
}

void SpeechRecognitionContext::SetupCallback()
{
	WPARAM wData = 0;
	LPARAM lData = 0;
	HRESULT hr = this->context->SetNotifyCallbackInterface(callbackInterface, wData, lData);
	if (FAILED(hr))
	{
		this->grammar.Release();
		const std::string message("Call to SetNotifyCallbackInterface failed");
		::PrintError(L"Call to SetNotifyCallbackInterface failed", hr);
		throw std::runtime_error(message);
	}
}

void SpeechRecognitionContext::Enable()
{
	this->ChangeGrammarEnabledState(SPGS_ENABLED);
}

void SpeechRecognitionContext::Disable()
{
	//deactive all rules
	HRESULT hr = this->grammar->SetRuleState(NULL, NULL, SPRS_INACTIVE);
	if (FAILED(hr))
	{
		this->grammar.Release();
		const std::string message("Call to SetRuleState SPRS_INACTIVE failed");
		::PrintError(L"Call to SetRuleState SPRS_INACTIVE failed", hr);
		throw std::runtime_error(message);
	}
	this->ChangeGrammarEnabledState(SPGS_DISABLED);
}

void SpeechRecognitionContext::ChangeGrammarEnabledState(SPGRAMMARSTATE stateFlag)
{
	HRESULT hr = this->grammar->SetGrammarState(stateFlag);
	if (FAILED(hr))
	{
		this->grammar.Release();
		const std::string message("Call to ChangeGrammarEnabledState failed");
		::PrintError(L"Call to ChangeGrammarEnabledState failed", hr);
		throw std::runtime_error(message);
	}
	
}

boost::signals2::connection* SpeechRecognitionContext::GetCommandReceivedConnection(void)
{
	return &this->commandReceivedConnection;
}

void SpeechRecognitionContext::Disconnect()
{
	//Disable();
	//if (commandReceivedConnection.connected())
	//{
	//	commandReceivedConnection.disconnect();
	//}
	
}

void SpeechRecognitionContext::SetupSpeechHandlers(const std::vector<std::wstring>& ruleNames, const std::string& windowName, type_commandrecognized::slot_function_type subscriber)
{
	//Pause stops the SR engine at a synchronization point to change grammars and rule states
	this->context->Pause(0);
	if (GetWindowName() == windowName)
	{
		if (!IsEnabled())
		{
			EnableRules();
		}
	}
	else
	{
		if (commandReceivedConnection.connected())
		{
			commandReceivedConnection.disconnect();
		}
		commandReceivedConnection = onCommandRecognized(subscriber);
		EnableRules(ruleNames, windowName);
	}
	this->context->Resume(0);
}

//called by clients via the SpeechListener class when they have a set of rules to activate
//for example when a particular screen is made active
void SpeechRecognitionContext::EnableRules(const std::vector<std::wstring>& ruleNames, const std::string& windowName)
{
	this->windowName = windowName;
	//make all the rules in ruleNames active

	//first deactive all currently active rules
	HRESULT hr = this->grammar->SetRuleState(NULL, NULL, SPRS_INACTIVE);
	//this->ChangeGrammarEnabledState(SPGS_DISABLED);
	
	//copy the rules names so we can easily reload them
	this->ruleNames = new std::vector<std::wstring>(ruleNames);
	EnableRules();
}

void SpeechRecognitionContext::EnableRules()
{
	if (ruleNames == nullptr)
	{
		return;
	}
	Disable();
	HRESULT hr = S_OK;
	//this->ChangeGrammarEnabledState(SPGS_ENABLED);
	//all rule names in @ruleNames are made active
	for (std::vector<std::wstring>::iterator it = this->ruleNames->begin(); it != this->ruleNames->end(); ++it)
	{
		std::wstring ruleName = *(it);
		hr = this->grammar->SetRuleState(ruleName.c_str(), NULL, SPRS_ACTIVE);
		if (FAILED(hr))
		{
			this->grammar.Release();
			const std::string message("Call to SetRuleState Active failed");
			::PrintError(L"Call to SetRuleState Active failed", hr);
			throw std::runtime_error(message);
		}
	}
	//this->ChangeGrammarEnabledState(SPGS_ENABLED);
	Enable();
}


void SpeechRecognitionContext::BeginCreateDynamicRule()
{
	this->context->Pause(0);
	HRESULT hr = S_OK;
	//hr = this->grammar->SetRuleState(MyApp::RULE_DYNAMIC.c_str(), NULL, SPRS_INACTIVE);
	//if (FAILED(hr))
	//{
	//	this->grammar.Release();
	//	const std::string message("Call toSetRuleState failed");
	//	::PrintError(L"Call toSetRuleState failed", hr);
	//	throw std::runtime_error(message);
	//}

	hr = grammar->GetRule(MyApp::RULE_DYNAMIC.c_str(), NULL, SPRAF_Dynamic, FALSE, &hRule);
	if (FAILED(hr))
	{
		this->grammar.Release();
		const std::string message("Call to GetRule Active failed");
		::PrintError(L"Call to GetRule Active failed", hr);
		throw std::runtime_error(message);
	}
	hr = grammar->ClearRule(hRule);
	if (FAILED(hr))
	{
		this->grammar.Release();
		const std::string message("Call to ClearRule Active failed");
		::PrintError(L"Call to ClearRule Active failed", hr);
		throw std::runtime_error(message);
	}

}

void SpeechRecognitionContext::EndCreateDynamicRule()
{
	HRESULT hr = grammar->Commit(NULL);
	if (FAILED(hr))
	{
		this->grammar.Release();
		const std::string message("Call to Commit failed");
		::PrintError(L"Call to Commit failed", hr);
		throw std::runtime_error(message);
	}
	//hr = this->grammar->SetRuleState(MyApp::RULE_DYNAMIC.c_str(), NULL, SPRS_ACTIVE);
	//if (FAILED(hr))
	//{
	//	this->grammar.Release();
	//	const std::string message("Call toSetRuleState failed");
	//	::PrintError(L"Call toSetRuleState failed", hr);
	//	throw std::runtime_error(message);
	//}
	this->context->Resume(0);
}


void SpeechRecognitionContext::CreateDynamicRule(std::wstring& display, int index)
{
	HRESULT hr = grammar->AddWordTransition(hRule, NULL, display.c_str(), NULL, SPWT_LEXICAL, 1, NULL);
	if (FAILED(hr))
	{
		this->grammar.Release();
		const std::string message("Call to AddWordTransition Active failed");
		::PrintError(L"Call to AddWordTransition Active failed", hr);
		throw std::runtime_error(message);
	}
	std::wstringstream ss;
	ss << index;
	hr = grammar->AddWordTransition(hRule, NULL, ss.str().c_str(), NULL, SPWT_LEXICAL, 1, NULL);
	if (FAILED(hr))
	{
		this->grammar.Release();
		const std::string message("Call to AddWordTransition Active failed");
		::PrintError(L"Call to AddWordTransition Active failed", hr);
		throw std::runtime_error(message);
	}
}

bool SpeechRecognitionContext::IsEnabled()
{
	SPGRAMMARSTATE stateFlag;
	HRESULT hr = this->grammar->GetGrammarState(&stateFlag);
	return stateFlag == SPGS_ENABLED;
}

CComPtr<ISpRecoContext> SpeechRecognitionContext::GetContext()
{
	return this->context;
}

//CComPtr<ISpVoice> SpeechRecognitionContext::GetVoice()
//{
//	return this->voice;
//}

//this is called from the CommandRecognitionResult instance which is created by the callback inteface
//when command and control recognition events are received
//the CommandRecognitionResult instance is passed this intance in its constructor
//the calling client wires up the signals and slots that it is interested in, ie m_command_completed
void SpeechRecognitionContext::CommandRecognitionReceived(const std::wstring& commandText, const std::vector<CommandProperty>& commandPropertyList)
{
	//broadcast this to the listeners
	m_command_completed(commandText, commandPropertyList);
}

//signals and slots that clients wire up for speech recognition notifications
//the SpeechListener class forwards these calls to this instance

boost::signals2::connection SpeechRecognitionContext::onCommandRecognized(type_commandrecognized::slot_function_type subscriber)
{
	return m_command_completed.connect(subscriber);
}

//boost::signals2::connection SpeechRecognitionContext::onSpeechRecognized(type_speechrecognized::slot_function_type subscriber)
//{
//	return m_speech_recognized.connect(subscriber);
//}

//boost::signals2::connection SpeechRecognitionContext::onDictationCompleted(type_dictationcompleted::slot_function_type subscriber)
//{
//	return m_dictation_completed.connect(subscriber);
//}
