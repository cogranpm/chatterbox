#pragma once

#include "EntityItem.h"
#include "SpeechRecognitionCallback.h"
#include "SpeechRecognitionEngine.h"
#include "SpeechRecognitionContext.h"
#include "DictationContext.h"


class SpeechListener  
{
public:
	SpeechListener();
	~SpeechListener(void);
	void InitSpeech(void);
	void StartDictation(void);
	void StartDictation(std::wstring& wavPath);
	void StopDictation(void);
	DictationContext* GetDictationContext() { return this->dictationContext; }
	SpeechRecognitionContext* GetSpeechRecognitionContext() { return this->speechContext;  }
	SpeechRecognitionEngine* GetSpeechEngine() { return this->engine; }
	
	//boost::signals2::connection onCommandRecognized(SpeechRecognitionContext::type_commandrecognized::slot_function_type subscriber);

	/* need to scavenge the dynamic rules stuff from this */
	//void EnableRules(std::vector<std::wstring>& ruleNames);

	//void SwitchRule(std::wstring ruleName);
	//void SwitchRule(std::wstring ruleName, bool dynamicStopWord);
	//void SwitchRule(std::wstring ruleName, std::vector<EntityItem>& list);
	//void SwitchRule(std::wstring ruleName, bool dynamicStopWord, std::wstring audioFile);
	//HRESULT writeToWavFile(CComPtr<ISpStreamFormat> cpStreamFormat);
	//VOID SpeakText(std::wstring text);
	//std::wstring GetRulesFile();

	/*
	bool getWriting() {return _wavPath.size() > 0;}
	std::wstring getStopWord() {return _stopWord;}
	void setStopWord(std::wstring stopWord) {_stopWord = stopWord;}*/


private:

	//speech recognition wrappers
	SpeechRecognitionEngine* engine;
	SpeechRecognitionContext* speechContext;
	DictationContext* dictationContext;
	SpeechRecognitionCallback* callbackInterface;


	//void FreePhrase(SPPHRASE* phrase);
	//bool m_bGotReco;
	//bool m_bInSound;
	//std::wstring _stopWord;
	//boost::thread m_thread;
	//HRESULT hr;
	//CComPtr<ISpRecoContext> cpRecoContext;
	//CComPtr<ISpRecognizer> m_cpRecoEngine;
	//CComPtr<ISpRecoGrammar> cpRecoGrammar;
	//CComPtr<ISpRecoResult> cpRecoResult;
	//CSpEvent spEvent;
	//WAVEFORMATEX* pexFormat;
	//SPAUDIOOPTIONS eAudioOptions;



	////callbacks
	//HRESULT STDMETHODCALLTYPE NotifyCallback(WPARAM wParam, LPARAM lParam);

	////stream
	//CComPtr<ISpStream> _cpStream;
	//
	//std::wstring _wavPath;
	//std::wstring _textPath;

	//bool dictating;
	//std::wstring rulesFile;


	
};

