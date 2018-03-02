#include "DictationContext.h"
#include "FileHandler.h"
#include "MyApp.h"

DictationContext::DictationContext() : 
	context(nullptr), 
	grammar(nullptr), 
	ccgrammar(nullptr),
	voice(nullptr), 
	waveFormat(nullptr),
	callbackInterface(new DictationCallback(this)),
	writingAudio(false),
	wavFilePath(L"")
{
}


DictationContext::~DictationContext()
{
	this->m_speech_recognized.disconnect_all_slots();
	this->m_speech_hypothesis.disconnect_all_slots();
	m_dictation_stopped.disconnect_all_slots();

	if(this->waveFormat != nullptr)
	{
		::CoTaskMemFree(this->waveFormat);
		this->waveFormat = nullptr;
	}

	if (audioStream != nullptr)
	{
		audioStream.Release();
		audioStream = nullptr;
	}

	if (this->grammar != nullptr)
	{
		grammar->UnloadDictation();
		grammar.Release();
		grammar = nullptr;
	}

	if (this->ccgrammar != nullptr)
	{
		ccgrammar.Release();
		ccgrammar = nullptr;
	}

	if (this->voice != nullptr)
	{
		this->voice.Release();
		this->voice = nullptr;
	}

	if (this->context != nullptr)
	{
		this->context.Release();
		this->context = nullptr;
	}
}


void DictationContext::CreateRecognitionContext(SpeechRecognitionEngine* engine)
{
	HRESULT hr = engine->GetEngine()->CreateRecoContext(&context);
	if (FAILED(hr))
	{
		const std::string message("Call to CreateRecoContext failed");
		::PrintError(L"Call to CreateRecoContext failed", hr);
		throw std::runtime_error(message);
	}

	hr = context->GetVoice(&this->voice);
	if (FAILED(hr))
	{
		const std::string message("Call to GetVoice failed");
		::PrintError(L"Call to GetVoice failed", hr);
		throw std::runtime_error(message);
	}

	hr = this->context->SetAudioOptions(SPAO_NONE, NULL, NULL);
	if (FAILED(hr))
	{
		const std::string message("Call to SetAudioOptions failed");
		::PrintError(L"Call to SetAudioOptions failed", hr);
		throw std::runtime_error(message);
	}


	ULONGLONG ullMyEvents = SPFEI(SPEI_RECOGNITION) | SPFEI(SPEI_SOUND_START)  | SPFEI(SPEI_SOUND_END) | SPFEI(SPEI_PHRASE_START) | SPFEI(SPEI_HYPOTHESIS) | SPFEI(SPEI_FALSE_RECOGNITION) | SPFEI(SPEI_INTERFERENCE);
	//ULONGLONG ullMyEvents = SPFEI(SPEI_RECOGNITION) | SPFEI(SPEI_SOUND_START)  | SPFEI(SPEI_SOUND_END | SPFEI(SPEI_RECO_STATE_CHANGE));
	//ULONGLONG ullMyEvents = SPFEI(SPEI_RECOGNITION);
	/*ULONGLONG ullMyEvents = SPFEI(SPEI_RECO_OTHER_CONTEXT) | 
			 SPFEI(SPEI_RECOGNITION) | 
			 SPFEI(SPEI_PHRASE_START) | 
			 SPFEI(SPEI_HYPOTHESIS) | 
			 SPFEI(SPEI_FALSE_RECOGNITION) | 
			 SPFEI(SPEI_RECO_STATE_CHANGE);
	*/
	
	hr = context->SetInterest(ullMyEvents, ullMyEvents);
	if (FAILED(hr))
	{
		const std::string message("Call to SetInterest failed");
		::PrintError(L"Call to SetInterest failed", hr);
		throw std::runtime_error(message);
	}

	hr = context->CreateGrammar(::GID_DICTATION, &grammar);
	if (FAILED(hr))
	{
		this->grammar.Release();
		const std::string message("Call to CreateGrammar failed");
		::PrintError(L"Call to CreateGrammar failed", hr);
		throw std::runtime_error(message);
	}
	
	hr = this->grammar->LoadDictation(NULL, SPLO_STATIC);
	
	if (FAILED(hr))
	{
		this->grammar.Release();
		const std::string message("Call to LoadDictation failed");
		::PrintError(L"Call to LoadDictation failed", hr);
		throw std::runtime_error(message);
	}

	//load command and control grammar for dictation
	this->ccgrammar.Release();
	hr = this->context->CreateGrammar(::GID_DICTATIONCC, &this->ccgrammar);
	if (FAILED(hr))
	{
		this->ccgrammar.Release();
		const std::string message("Call to CreateGrammar failed");
		::PrintError(L"Call to CreateGrammar failed", hr);
		throw std::runtime_error(message);
	}

	hr = this->ccgrammar->SetGrammarState(SPGS_DISABLED);
	if (FAILED(hr))
	{
		this->ccgrammar.Release();
		const std::string message("Call to SetGrammarState failed");
		::PrintError(L"Call to SetGrammarState failed", hr);
		throw std::runtime_error(message);
	}

	hr = this->ccgrammar->LoadCmdFromFile(MyApp::RULE_FILE_NAME_DICATIONCC.c_str(), SPLO_STATIC);
	if (FAILED(hr))
	{
		this->ccgrammar.Release();
		const std::string message("Call to LoadCmdFromFile failed");
		::PrintError(L"Call to LoadCmdFromFile failed", hr);
		throw std::runtime_error(message);
	}


	this->Disable();
}

void DictationContext::Enable()
{
	this->EnableDictation();
	HRESULT hr = this->context->SetAudioOptions(SPAO_NONE, NULL, NULL);
	if (FAILED(hr))
	{
		const std::string message("Call to SetAudioOptions failed");
		::PrintError(L"Call to SetAudioOptions failed", hr);
		throw std::runtime_error(message);
	}
	writingAudio = false;
	this->InnerEnable();
}

void DictationContext::Enable(std::wstring& wavFilePath)
{
	//this line must be called before bindaudio file because it clears out the previous
	//audio stream and closes it before opening another
	this->EnableDictation();
	this->wavFilePath = wavFilePath;
	this->BindAudioFile(this->wavFilePath);
	this->InnerEnable();
}

void DictationContext::InnerEnable()
{
	//set up the callback
	WPARAM wData = 0;
	LPARAM lData = 0;
	HRESULT hr = this->context->SetNotifyCallbackInterface(callbackInterface, wData, lData);
	if (FAILED(hr))
	{
		const std::string message("Call to SetNotifyCallbackInterface failed");
		::PrintError(L"Call to SetNotifyCallbackInterface failed", hr);
		throw std::runtime_error(message);
	}

	this->ChangeGrammarEnabledState(SPGS_ENABLED);
	hr = this->grammar->SetDictationState(SPRS_ACTIVE);
	if (FAILED(hr))
	{
		const std::string message("Call to SetDictationState failed");
		::PrintError(L"Call to SetDictationState failed", hr);
		throw std::runtime_error(message);
	}
	hr = this->ccgrammar->SetRuleState(NULL, NULL, SPRS_ACTIVE);
	if (FAILED(hr))
	{
		const std::string message("Call to SetRuleState failed");
		::PrintError(L"Call to SetRuleState failed", hr);
		throw std::runtime_error(message);
	}
}

void DictationContext::EnableDictation()
{
	if (this->writingAudio)
	{
		if (this->audioStream != NULL)
		{
			HRESULT hr = this->audioStream->Close();
			this->audioStream.Release();
		}
	}
}

void DictationContext::Disable()
{
	HRESULT hr = this->context->SetNotifySink(NULL);
	if (FAILED(hr))
	{
		const std::string message("Call to SetNotifySink failed");
		::PrintError(L"Call to SetNotifySink failed", hr);
		writingAudio = false;
		throw std::runtime_error(message);
	}
	this->ChangeGrammarEnabledState(SPGS_DISABLED);
	hr = this->grammar->SetDictationState(SPRS_INACTIVE);
	if (FAILED(hr))
	{
		const std::string message("Call to SetDictationState failed");
		::PrintError(L"Call to SetDictationState failed", hr);
		writingAudio = false;
		throw std::runtime_error(message);
	}
	hr = this->ccgrammar->SetRuleState(NULL, NULL, SPRS_INACTIVE);
	if (FAILED(hr))
	{
		const std::string message("Call to SetRuleState failed");
		::PrintError(L"Call to SetRuleState failed", hr);
		writingAudio = false;
		throw std::runtime_error(message);
	}
	hr = this->context->SetAudioOptions(SPAO_NONE, NULL, NULL);
	if (FAILED(hr))
	{
		const std::string message("Call to SetAudioOptions failed");
		::PrintError(L"Call to SetAudioOptions failed", hr);
		writingAudio = false;
		throw std::runtime_error(message);
	}

	if (this->writingAudio)
	{
		if (this->audioStream != NULL)
		{
			hr = this->audioStream->Close();
			this->audioStream.Release();
		}
	}
	writingAudio = false;
}

void DictationContext::ChangeGrammarEnabledState(SPGRAMMARSTATE stateFlag)
{
	HRESULT hr = this->grammar->SetGrammarState(stateFlag);
	if (FAILED(hr))
	{
		this->grammar.Release();
		const std::string message("Call to ChangeGrammarEnabledState failed");
		::PrintError(L"Call to ChangeGrammarEnabledState failed", hr);
		throw std::runtime_error(message);
	}

	hr = this->ccgrammar->SetGrammarState(stateFlag);
	if (FAILED(hr))
	{
		this->ccgrammar.Release();
		const std::string message("Call to ChangeGrammarEnabledState failed");
		::PrintError(L"Call to ChangeGrammarEnabledState failed", hr);
		throw std::runtime_error(message);
	}
}

CComPtr<ISpRecoContext> DictationContext::GetContext()
{
	return this->context;
}

void DictationContext::BindAudioFile(std::wstring& audioFile)
{
	this->audioStream = CComPtr<ISpStream>();
	GUID guidFormatId = GUID_NULL;
	HRESULT hr = SpConvertStreamFormatEnum(::SPEECH_AUDIO_FORMAT, &guidFormatId, &this->waveFormat);
	if (FAILED(hr))
	{
		const std::string message("Call to SpConvertStreamFormatEnum failed");
		::PrintError(L"Call to SpConvertStreamFormatEnum failed", hr);
		throw std::runtime_error(message);
	}
	// Tell the reco contexts to retain its audio in this format
	hr = this->context->SetAudioOptions(SPAO_RETAIN_AUDIO, &guidFormatId, this->waveFormat);
	if (FAILED(hr))
	{
		const std::string message("Call to SetAudioOptions failed");
		::PrintError(L"Call to SetAudioOptions failed", hr);
		throw std::runtime_error(message);
	}

	//std::wstring wavPath = audioFile;
	hr = SPBindToFile(audioFile.c_str(), SPFM_CREATE_ALWAYS, &this->audioStream, &guidFormatId, this->waveFormat, SPFEI_ALL_EVENTS);
	if (FAILED(hr))
	{
		const std::string message("Call to SPBindToFile failed");
		::PrintError(L"Call to SPBindToFile failed", hr);
		throw std::runtime_error(message);
	}
	writingAudio = true;
}

void DictationContext::RecognitionReceived(const std::wstring& text)
{
	::PrintError(text, S_OK);
	m_speech_recognized(text);
}

void DictationContext::HypothesisReceived(const std::wstring& hypothesisText)
{
	::PrintError(hypothesisText, S_OK);
	m_speech_hypothesis(hypothesisText);
}

void DictationContext::SoundStart()
{
	m_soundStart();
}

void DictationContext::SoundEnd()
{
	m_soundEnd();
}

void DictationContext::DictationStopped(const SpeechConstants::DictationCommand command)
{
	m_dictation_stopped(command);
}

boost::signals2::connection DictationContext::onSpeechRecognized(type_speechrecognized::slot_function_type subscriber)
{
	return m_speech_recognized.connect(subscriber);
}

boost::signals2::connection DictationContext::onDictationStopped(type_dictationstopped::slot_function_type subscriber)
{
	return m_dictation_stopped.connect(subscriber);
}

boost::signals2::connection DictationContext::onHypothesisRecognized(type_speechhypothesis::slot_function_type subscriber)
{
	return m_speech_hypothesis.connect(subscriber);
}

boost::signals2::connection DictationContext::onSoundStart(type_sound_start::slot_function_type subscriber)
{
	return m_soundStart.connect(subscriber);
}

boost::signals2::connection DictationContext::onSoundEnd(type_sound_end::slot_function_type subscriber)
{
	return m_soundEnd.connect(subscriber);
}

void DictationContext::WriteAudio(ISpRecoResult* pResult)
{
	if (pResult)
	{
		if (this->writingAudio)
		{
			CComPtr<ISpStreamFormat> cpStreamFormat;
			//if(pResult.get
			HRESULT hr = pResult->GetAudio(0, 0, &cpStreamFormat);
			if (FAILED(hr))
			{
				::PrintError(L"Error in GetAudio", hr);
				return;
			}

			if (SPERR_NO_AUDIO_DATA == hr)
			{
				//no audio to process
				return;
			}

			ULONG cbWritten = 0;
			while (TRUE)
			{
				// for logging purposes, the app can retrieve the recognized audio stream length in bytes
				STATSTG stats;
				hr = cpStreamFormat->Stat(&stats, NULL);
				// create a 1000-byte buffer for transferring
				BYTE bBuffer[1000];
				ULONG cbRead;

				// request 1000 bytes of data from the input stream
				hr = cpStreamFormat->Read(bBuffer, 1000, &cbRead);
				// if data was returned??

				if (SUCCEEDED(hr) && cbRead > 0)
				{
					hr = this->audioStream->Write(bBuffer, cbRead, &cbWritten);
					if (FAILED(hr))
					{
						::PrintError(L"Error in writeToWavFile", hr);
					}
				}
				

				//if (SUCCEEDED(hr) && cbRead > 0)
				//{
				//	hr = this->audioStream->Write(bBuffer, cbRead, &cbWritten);
				//}
				//else
				//{
				//	::PrintError(L"Error in writeToWavFile", hr);
				//}
				if (cbRead < 1000)
				{
					break;
				}
			}
		}
	}
}
