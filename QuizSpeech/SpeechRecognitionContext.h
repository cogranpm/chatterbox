#pragma once
#include "stdafx.h"
#include "SpeechRecognitionEngine.h"
#include "SpeechRecognitionCallback.h"
#include "CommandProperty.h"



class SpeechRecognitionContext
{
public:
	SpeechRecognitionContext();
	~SpeechRecognitionContext();

	void CreateRecognitionContext(SpeechRecognitionEngine* engine);
	void Enable();
	void Disable();
	void EnableRules(std::vector<std::wstring>& ruleNames);
	void CommandRecognitionReceived(const std::wstring& commandText, std::vector<CommandProperty> commandPropertyList);

	//getters
	CComPtr<ISpRecoContext> GetContext();
	//CComPtr<ISpVoice> GetVoice();
	//define the signals that this class will emit
	//typedef boost::signals2::signal<void(std::wstring)>  type_speechrecognized;
	//typedef boost::signals2::signal<void(void)>  type_dictationcompleted;
	typedef boost::signals2::signal<void(std::wstring, const std::vector<CommandProperty>&)>  type_commandrecognized;

	//boost::signals2::connection onSpeechRecognized(type_speechrecognized::slot_function_type subscriber);
	//boost::signals2::connection onDictationCompleted(type_dictationcompleted::slot_function_type subscriber);
	boost::signals2::connection onCommandRecognized(type_commandrecognized::slot_function_type subscriber);

	//temporarily public, place in getters later
	//type_speechrecognized m_speech_recognized;
	//type_dictationcompleted m_dictation_completed;
	type_commandrecognized m_command_completed;

protected:


private:

	void ChangeGrammarEnabledState(SPGRAMMARSTATE);

	CComPtr<ISpRecoContext> context;
	//CComPtr<ISpVoice>   voice;
	CComPtr<ISpRecoGrammar> grammar;
	SpeechRecognitionCallback* callbackInterface;
	
};

