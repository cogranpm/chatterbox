#pragma once

#include "stdafx.h"
#include "GlobalConstants.h"
#include "SpeechRecognitionEngine.h"
#include "DictationCallback.h"

enum DictationCommand : short;

class DictationContext
{

public:

	DictationContext();
	~DictationContext();
	void CreateRecognitionContext(SpeechRecognitionEngine* engine);
	void Enable();
	void Enable(std::wstring& wavFilePath);
	void Disable();
	CComPtr<ISpRecoContext> GetContext();
	void BindAudioFile(std::wstring& audioFile);
	bool GetWritingAudio() { return this->writingAudio; }
	void WriteAudio(ISpRecoResult* pResult);
	void RecognitionReceived(const std::wstring& text);
	void HypothesisReceived(const std::wstring& hypothesisText);
	void DictationStopped(const DictationCommand& command);
	void SoundStart();
	void SoundEnd();
	//void FalseRecognitionReceived();
	//void PhraseStart
	//void PhraseEnd
	

	//signals and slots for dictation events
	typedef boost::signals2::signal<void(const std::wstring&)>  type_speechrecognized;
	boost::signals2::connection onSpeechRecognized(type_speechrecognized::slot_function_type subscriber);

	typedef boost::signals2::signal<void(const DictationCommand& command)>  type_dictationstopped;
	boost::signals2::connection onDictationStopped(type_dictationstopped::slot_function_type subscriber);


	typedef boost::signals2::signal<void(const std::wstring&)>  type_speechhypothesis;
	boost::signals2::connection onHypothesisRecognized(type_speechhypothesis::slot_function_type subscriber);
	
	typedef boost::signals2::signal<void()>  type_sound_start;
	boost::signals2::connection onSoundStart(type_sound_start::slot_function_type subscriber);
	
	typedef boost::signals2::signal<void()>  type_sound_end;
	boost::signals2::connection onSoundEnd(type_sound_end::slot_function_type subscriber);
	


private:
	void InnerEnable();
	void ChangeGrammarEnabledState(SPGRAMMARSTATE);
	void EnableDictation();
	bool writingAudio;
	CComPtr<ISpRecoContext> context;
	CComPtr<ISpRecoGrammar> grammar;
	CComPtr<ISpRecoGrammar> ccgrammar;
	CComPtr<ISpVoice>   voice;
	CComPtr<ISpStream> audioStream;
	DictationCallback* callbackInterface;
	WAVEFORMATEX* waveFormat;
	std::wstring wavFilePath;
	type_sound_end m_soundEnd;
	type_sound_start m_soundStart;
	type_speechrecognized m_speech_recognized;
	type_speechhypothesis m_speech_hypothesis;
	type_dictationstopped m_dictation_stopped;
};

