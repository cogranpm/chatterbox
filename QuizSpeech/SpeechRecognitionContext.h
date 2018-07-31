#pragma once
#include "stdafx.h"
#include "SpeechRecognitionEngine.h"
#include "SpeechRecognitionCallback.h"
#include "CommandProperty.h"
#include "EntityItem.h"

class SpeechRecognitionContext
{
public:
	SpeechRecognitionContext();
	~SpeechRecognitionContext();

	typedef boost::signals2::signal<void(std::wstring, const std::vector<CommandProperty>&)>  type_commandrecognized;

	void CreateRecognitionContext(SpeechRecognitionEngine* engine);
	void Enable();
	void Disable();
	void EnableRules(const std::vector<std::wstring>& ruleNames, const std::string& windowName);
	void BeginCreateDynamicRule(const std::wstring& ruleName);
	void EndCreateDynamicRule();
	void CreateDynamicRule(const std::wstring& display, const std::wstring& index, const std::wstring& propertyName);
	void SetupSpeechHandlers(const std::vector<std::wstring>& ruleNames, const std::string& windowName, type_commandrecognized::slot_function_type subscriber);
	boost::signals2::connection onCommandRecognized(type_commandrecognized::slot_function_type subscriber);
	void CommandRecognitionReceived(const std::wstring& commandText, const std::vector<CommandProperty>& commandPropertyList);
	void ChangeGrammarEnabledState(SPGRAMMARSTATE);
	bool IsEnabled();
	std::string& GetWindowName() { return windowName; }
	boost::signals2::connection* GetCommandReceivedConnection(void);
	void Disconnect();

	//getters
	CComPtr<ISpRecoContext> GetContext();


protected:


private:
	std::string windowName;
	CComPtr<ISpRecoContext> context;
	//CComPtr<ISpVoice>   voice;
	CComPtr<ISpRecoGrammar> grammar;
	SpeechRecognitionCallback* callbackInterface;
	type_commandrecognized m_command_completed;

	/* holds dynamic rule handle whilst dynamic rules are created */
	SPSTATEHANDLE hRule;
	std::wstring dynamicRuleName;

	//our own private copy of the client supplied rule names
	std::vector<std::wstring>* ruleNames;
	boost::signals2::connection  commandReceivedConnection;
	void SetupCallback();
	void EnableRules();

};

