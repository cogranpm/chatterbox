#include "stdafx.h"
#include "SpeechListener.h"
#include "FileHandler.h"
#include "MyApp.h"
#include "GlobalConstants.h"

SpeechListener::SpeechListener() : 
engine(new SpeechRecognitionEngine()),
speechContext(new SpeechRecognitionContext()),
dictationContext(new DictationContext()),
callbackInterface(new SpeechRecognitionCallback(this->speechContext))
{

}


SpeechListener::~SpeechListener(void)
{
	if (engine != nullptr)
	{
		delete engine;
		engine = nullptr;
	}

	if (speechContext != nullptr)
	{
		delete speechContext;
		speechContext = nullptr;
	}

	if (dictationContext != nullptr)
	{
		delete dictationContext;
		dictationContext = nullptr;
	}

	if (callbackInterface != nullptr)
	{
		delete callbackInterface;
		callbackInterface = nullptr;
	}
}

void SpeechListener::InitSpeech(void)
{
	this->engine->CreateEngine();
	this->dictationContext->CreateRecognitionContext(this->engine);
	this->speechContext->CreateRecognitionContext(this->engine);
	this->speechContext->Enable();
}


void SpeechListener::StartDictation(void)
{
	this->speechContext->Disable();
	this->dictationContext->Enable();
}

void SpeechListener::StartDictation(std::wstring& wavPath)
{
	this->speechContext->Disable();
	this->dictationContext->Enable(wavPath);
}


void SpeechListener::StopDictation(void)
{
	this->dictationContext->Disable();
	this->speechContext->Enable();

}


/***********************************************************************************/
/***********************************************************************************/
/*************** this is all old stuff to be phased out ***************************/


//void SpeechListener::SpeakText(std::wstring text)
//{
//	hr = this->speechContext->GetVoice()->Speak(text.c_str(), SPF_DEFAULT, 0);
//}

//void SpeechListener::EnableRules(std::vector<std::wstring>& ruleNames)
//{
//	this->speechContext->EnableRules(ruleNames);
//}


//
//
//void SpeechListener::SwitchRule(std::wstring ruleName, std::vector<EntityItem>& list)
//{
//	dictating = false;
//	if(cpRecoGrammar != 0)
//	{
//		hr = cpRecoGrammar->SetDictationState(SPRS_INACTIVE);
//		if ( FAILED(hr))
//		{
//			::PrintError(L"Error in SwitchRule", hr);
//			return;
//		}
//
//		cpRecoGrammar.Release();
//	}
//
//	hr = cpRecoContext->CreateGrammar(GRAMMARID1, &cpRecoGrammar);
//	if ( FAILED(hr))
//	{
//		::PrintError(L"Error in SwitchRule", hr);
//		return;
//	}
//
//	hr = cpRecoGrammar->SetGrammarState(SPGS_DISABLED);
//    if (FAILED(hr))
//    {
//		::PrintError(L"Error in SwitchRule", hr);
//        cpRecoGrammar.Release();
//		return;
//    }
//
//	hr = cpRecoGrammar->LoadCmdFromFile(this->GetRulesFile().c_str(), SPLO_DYNAMIC);
//    if (FAILED(hr))
//    {
//		::PrintError(L"Error in SwitchRule", hr);
//		cpRecoGrammar.Release();
//		return;
//    }	
//
//	/*****************************************
//	dynamic start here */
//	SPSTATEHANDLE hRule;
//    hr = cpRecoGrammar->GetRule(L"DYNAMIC_RULE", NULL, SPRAF_Dynamic, FALSE, &hRule);
//	hr = cpRecoGrammar->ClearRule(hRule);
//
//	std::vector<EntityItem>::iterator itr;
//	int counter = 0;
//	for(itr = list.begin(); itr != list.end(); itr++)
//	{
//		counter++;
//		EntityItem item = *itr;
//		std::wstring description = item.description;
//		hr = cpRecoGrammar->AddWordTransition(hRule, NULL,description.c_str(), NULL, SPWT_LEXICAL, 1, NULL);
//		std::wstringstream ss;
//		ss << counter;
//		hr = cpRecoGrammar->AddWordTransition(hRule, NULL, ss.str().c_str(), NULL, SPWT_LEXICAL, 1, NULL);
//	}
//
//	
//	hr = cpRecoGrammar->Commit(NULL);
//	/*****************************************
//	dynamic end here */
//
//
//	hr = cpRecoGrammar->SetGrammarState(SPGS_ENABLED);    
//    if (FAILED(hr))
//    {
//		::PrintError(L"Error in SwitchRule", hr);
//        cpRecoGrammar.Release();
//		return;
//    }	
//
//	hr = cpRecoGrammar->SetRuleState(ruleName.c_str(), NULL, SPRS_ACTIVE);
//    if (FAILED(hr))
//    {
//		::PrintError(L"Error in SwitchRule", hr);
//        cpRecoGrammar.Release();
//		return;
//    }	
//
//
//	this->StartCommanding();
//	
//
//}
//
//void SpeechListener::SwitchRule(std::wstring ruleName)
//{
//	this->SwitchRule(ruleName, false);
//}
//
//void SpeechListener::SwitchRule(std::wstring ruleName, bool dynamicStopWord, std::wstring audioFile)
//{
//	this->SwitchRule(ruleName, dynamicStopWord);
//
//	_wavPath = audioFile;
//	CSpStreamFormat Fmt(SPEECH_AUDIO_FORMAT, &hr);
//	// Enabled audio retention in the SAPI runtime, and set the retained audio format
//	hr = cpRecoContext->SetAudioOptions( SPAO_RETAIN_AUDIO, &Fmt.FormatId(), Fmt.WaveFormatExPtr());
//	if (FAILED(hr))
//	{
//		::PrintError(L"Error in SwitchRule", hr);
//		return;
//	}
//	dictating = true;
//	if(this->getWriting())
//	{
//		//bind to file outside of the listening loop to make sure all recognitions are stored to the same file
//		_cpStream = CComPtr<ISpStream>();
//		hr = SPBindToFile(_wavPath.c_str(), SPFM_CREATE_ALWAYS, &_cpStream, &Fmt.FormatId(), Fmt.WaveFormatExPtr(), SPFEI_ALL_EVENTS);
//		if ( FAILED(hr))
//		{
//			::PrintError(L"Error in SwitchRule", hr);
//			return;
//		}
//	}
//
//}

//void SpeechListener::SwitchRule(std::wstring ruleName, bool dynamicStopWord)
//{
//	dictating = false;
//	if(cpRecoGrammar != 0)
//	{
//		hr = cpRecoGrammar->SetDictationState(SPRS_INACTIVE);
//		if ( FAILED(hr))
//		{
//			::PrintError(L"Error in SwitchRule", hr);
//			return;
//		}
//	}
//
//	cpRecoGrammar.Release();
//
//	hr = cpRecoContext->CreateGrammar(GRAMMARID1, &cpRecoGrammar);
//	if ( FAILED(hr))
//	{
//		::PrintError(L"Error in SwitchRule", hr);
//		return;
//	}
//
//	hr = cpRecoGrammar->SetGrammarState(SPGS_DISABLED);
//    if (FAILED(hr))
//    {
//		::PrintError(L"Error in SwitchRule", hr);
//        cpRecoGrammar.Release();
//		return;
//    }
//
//	hr = cpRecoGrammar->LoadCmdFromFile(this->GetRulesFile().c_str(), SPLO_DYNAMIC);
//    if (FAILED(hr))
//    {
//		::PrintError(L"Error in SwitchRule", hr);
//        cpRecoGrammar.Release();
//		return;
//    }	
//
//	/*****************************************
//	dynamic start here */
//	if(dynamicStopWord)
//	{
//		SPSTATEHANDLE hRule;
//		hr = cpRecoGrammar->GetRule(L"DYNAMIC_RULE", NULL, SPRAF_Dynamic, FALSE, &hRule);
//		hr = cpRecoGrammar->ClearRule(hRule);
//		hr = cpRecoGrammar->AddWordTransition(hRule, NULL, this->getStopWord().c_str(), NULL, SPWT_LEXICAL, 1, NULL);
//		hr = cpRecoGrammar->Commit(NULL);
//	}
//	/*****************************************
//	dynamic end here */
//
//	
//	hr = cpRecoGrammar->SetRuleState(ruleName.c_str(), NULL, SPRS_ACTIVE);
//    if (FAILED(hr))
//    {
//		::PrintError(L"Error in SwitchRule", hr);
//        cpRecoGrammar.Release();
//		return;
//    }	
//
//	hr = cpRecoGrammar->SetGrammarState(SPGS_ENABLED);    
//    if (FAILED(hr))
//    {
//		::PrintError(L"Error in SwitchRule", hr);
//        cpRecoGrammar.Release();
//		return;
//    }	
//
//	this->StartCommanding();
//
//}




//HRESULT SpeechListener::StartListening(std::wstring wavPath)
//{
//	WPARAM wData = 0;
//	LPARAM lData = 0;
//	
//	//hr = cpRecoContext->SetNotifyCallbackInterface(this, wData, lData);
//	hr = cpRecoContext->SetNotifyCallbackInterface(callbackInterface, wData, lData);
//    if (FAILED(hr))
//    {
//		::PrintError(L"Error in StartListening", hr);
//        cpRecoGrammar.Release();
//		return hr;
//    }	
//	_wavPath = wavPath;
//	CSpStreamFormat Fmt(SPEECH_AUDIO_FORMAT, &hr);
//	// Enabled audio retention in the SAPI runtime, and set the retained audio format
//	hr = cpRecoContext->SetAudioOptions( SPAO_RETAIN_AUDIO, &Fmt.FormatId(), Fmt.WaveFormatExPtr());
//	if (FAILED(hr))
//	{
//		::PrintError(L"Error in StartListening", hr);
//		return hr;
//	}
//
//	if(this->getWriting())
//	{
//		//bind to file outside of the listening loop to make sure all recognitions are stored to the same file
//		_cpStream = CComPtr<ISpStream>();
//		hr = SPBindToFile(wavPath.c_str(), SPFM_CREATE_ALWAYS, &_cpStream, &Fmt.FormatId(), Fmt.WaveFormatExPtr(), SPFEI_ALL_EVENTS);
//		if ( FAILED(hr))
//		{
//			::PrintError(L"Error in StartListening", hr);
//			return hr;
//		}
//	}
//
//	// activate dictation
//	hr = cpRecoGrammar->SetDictationState(SPRS_ACTIVE);
//	// Check hr
//	if ( FAILED(hr))
//	{
//		::PrintError(L"Error in StartListening", hr);
//		return hr;
//	}
//	return S_OK;
//}
//


//HRESULT STDMETHODCALLTYPE SpeechListener::NotifyCallback(WPARAM wParam, LPARAM lParam)
//{
//	HRESULT hr = S_OK;
//	CComPtr<ISpRecoResult> cpRecoResult;
//	//CSpEvent spEvent;
//	CSpStreamFormat Fmt(SPEECH_AUDIO_FORMAT, &hr);
//	//this->ProcessRecognitionEvent(cpRecoResult);
//	
//	hr = spEvent.GetFrom(cpRecoContext);
//	if(FAILED(hr))
//	{
//		::PrintError(L"Error in NotifyCallback GetFrom", hr);
//		return hr;
//	}
//
//	// verify that the event is a recognition event
//	::OutputDebugStringW(L"\n");
//	if (SPEI_RECOGNITION == spEvent.eEventId)
//	{
//		cpRecoResult = spEvent.RecoResult();
//	}
//	else if (SPEI_HYPOTHESIS == spEvent.eEventId)
//	{
//		::OutputDebugStringW(L"hypothesis");
//		
//	}
//	else if (SPEI_SOUND_START == spEvent.eEventId)
//	{
//		::OutputDebugStringW(L"sound start");
//		
//	}
//	else if (SPEI_SOUND_END == spEvent.eEventId)
//	{
//		::OutputDebugStringW(L"sound end");
//		
//	}
//	else if (SPEI_PHRASE_START == spEvent.eEventId)
//	{
//		::OutputDebugStringW(L"phrase start");
//		
//	}
//	else if (SPEI_FALSE_RECOGNITION == spEvent.eEventId)
//	{
//		::OutputDebugStringW(L"false recognition");
//		
//	}
//	else if (SPEI_INTERFERENCE == spEvent.eEventId)
//	{
//		::OutputDebugStringW(L"Interference");
//		
//	}
//	else if(SPEI_RECO_STATE_CHANGE == spEvent.eEventId)
//	{
//		::OutputDebugStringW(L"Reco State Change");
//		if (spEvent.RecoState() == SPRST_INACTIVE)
//		{
//			//SetGrammarState( (event.RecoState() != SPRST_INACTIVE) );
//			::OutputDebugStringW(L"Looks like we got set to inactive");
//		}
//		
//	}
//
//	spEvent.Clear();
//
//	if (cpRecoResult)
//	{
//
//        CSpDynamicString dstrText;
//
//		/* phrase contains a bunch of data about the recognition */
//		SPPHRASE* pPhrase;
//		hr = cpRecoResult->GetPhrase(&pPhrase);
//		if(S_OK != hr)
//		{
//			if(hr == E_POINTER)
//			{
//				::PrintError(L" Error in NotifyCallback GetPhrase - InvalidPointer", hr);
//			}
//			else
//			{
//				::PrintError(L" Error in NotifyCallback GetPhrase", hr);
//			}
//			return hr;
//		}
//		hr = cpRecoResult->GetText(SP_GETWHOLEPHRASE, SP_GETWHOLEPHRASE,  TRUE, &dstrText, NULL);
//		if(S_OK != hr)
//		{
//			::PrintError(L" Error in NotifyCallback GetText", hr);
//			return hr;
//		}
//		
//		WCHAR* text = dstrText.Copy();
//		std::wstring recognizedText = text;
//		std::wstring lcaseText = text;
//		::OutputDebugStringW(text);
//		std::transform(recognizedText.begin(), recognizedText.end(), lcaseText.begin(), ::towlower);
//
//		if (!dictating)
//		{
//
//			//there can be multiple semantic properties
//			//pPhrase->pProperties->pNextSibling
//
//			std::wstring phraseValue(L"");
//			//if there is a value associated with the phrase return it
//			if (pPhrase->pProperties->pszValue != NULL)
//			{
//				phraseValue = std::wstring(pPhrase->pProperties->pszValue);
//			}
//
//			std::wstring phraseProperty(L"");
//			if (pPhrase->pProperties->pszName != NULL)
//			{
//				phraseProperty = std::wstring(pPhrase->pProperties->pszName);
//			}
//
//			std::vector<CommandProperty> commandPropertyList;
//			CommandProperty item(phraseProperty, phraseValue);
//			commandPropertyList.push_back(item);
//			this->speechContext->m_command_completed(recognizedText, commandPropertyList);
//			this->FreePhrase(pPhrase);
//			return S_OK;
//		}
//
//		if(lcaseText == this->getStopWord())
//		{
//			this->StopListening();
//			this->FreePhrase(pPhrase);
//			return S_OK;
//		}
//
//		if(this->getWriting() && _textPath.size() > 0)
//		{
//			FileHandler fh;
//			fh.AppendText(recognizedText, _textPath);
//		}
//
//			
//		if(this->getWriting())
//		{
//			/* make this CComPtr<ISpStreamFormat> a class member so it is available for the client to 
//			begin the writing to wav file process, and remove the code below into a seperate function */
//			CComPtr<ISpStreamFormat> cpStreamFormat;
//			hr = cpRecoResult->GetAudio( 0, 0, &cpStreamFormat);
//			// Check hr
//			if ( FAILED( hr ) )
//			{
//				::PrintError(L"Error in NotifyCallback GetAudio", hr);
//				this->FreePhrase(pPhrase);
//				return hr;
//			}
//			this->writeToWavFile(cpStreamFormat);
//		}
//
//
//		if(lcaseText.length() > this->getStopWord().size())
//		{
//			bool lastIsStop = boost::algorithm::ends_with(lcaseText, this->getStopWord());
//			if(lastIsStop)
//			{
//				this->StopListening();
//				this->FreePhrase(pPhrase);
//				return S_OK;
//			}
//		}
//
//		//this->speechContext->m_speech_recognized(recognizedText);
//		this->FreePhrase(pPhrase);
//	}
//
//	
//	return S_OK;
//}
//
//void SpeechListener::FreePhrase(SPPHRASE* phrase)
//{
//	if (phrase) ::CoTaskMemFree(phrase);
//
//}

//HRESULT SpeechListener::writeToWavFile(CComPtr<ISpStreamFormat> cpStreamFormat)
//{
//	ULONG cbWritten = 0;
//	while (TRUE)
//	{
//		// for logging purposes, the app can retrieve the recognized audio stream length in bytes
//		STATSTG stats;
//		hr = cpStreamFormat->Stat(&stats, NULL);
//		// create a 1000-byte buffer for transferring
//		BYTE bBuffer[1000];
//		ULONG cbRead;
//
//		// request 1000 bytes of data from the input stream
//		hr = cpStreamFormat->Read(bBuffer, 1000, &cbRead);
//		// if data was returned??
//		if (SUCCEEDED(hr) && cbRead > 0)
//		{
//			hr = _cpStream->Write(bBuffer, cbRead, &cbWritten);
//		}
//		else
//		{
//			::PrintError(L"Error in writeToWavFile", hr);
//			return hr;
//		}
//		if (cbRead < 1000)
//		{
//			break;
//		}
//	}
//	return S_OK;
//}
//
//
//
//void SpeechListener::StopListening()
//{
//	hr = cpRecoContext->SetNotifySink(NULL);
//	if(this->getWriting())
//	{
//		hr = _cpStream->Close();
//	}
//	hr = cpRecoGrammar->SetDictationState(SPRS_INACTIVE);
//	//this->speechContext->m_dictation_completed();
//}


//
//std::wstring SpeechListener::GetRulesFile()
//{
//	return this->rulesFile;
//}





//void SpeechListener::ProcessRecognitionEvent(CComPtr<ISpRecoResult> cpRecoResult)
//{
//		
//    CSpEvent event;
//    LPARAM iNewPhrase;
//	
//    if (cpRecoContext)
//    {
//        while (event.GetFrom(cpRecoContext) == S_OK)
//        {
//            switch (event.eEventId)
//            {
//                   
//				case SPEI_INTERFERENCE: 
//                { 
//                     
//					CSpDynamicString dstr;
//                     switch(event.Interference())
//                     {
//                     case SPINTERFERENCE_NONE:
//                         dstr = L"Interference - None";
//                         break;
//                     case SPINTERFERENCE_NOISE:
//                         dstr = L"Interference - Noise";
//                         break;
//                     case SPINTERFERENCE_NOSIGNAL:
//                         dstr = L"Interference - No signal";
//                         break;
//                     case SPINTERFERENCE_TOOLOUD:
//                         dstr = L"Interference - Too loud";
//                         break;
//                     case SPINTERFERENCE_TOOQUIET:
//                         dstr = L"Interference - Too quiet";
//                         break;
//                     case SPINTERFERENCE_TOOFAST:
//                         dstr = L"Dictation mode: Interference - Too fast";
//                         break;
//                     case SPINTERFERENCE_TOOSLOW:
//                         dstr = L"Dictation mode: Interference - Too slow";
//                         break;
//                     default:
//                         dstr = L"Unrecognized Interference Event";
//                     }
//                       
//				}
//                break;
//
//                case SPEI_PROPERTY_NUM_CHANGE:
//                    {
//                        TCHAR sz[MAX_PATH * 2];
//                        WCHAR *pwszPropertyName = NULL;
//                        if ( event.PropertyName() )
//                        {
//                            pwszPropertyName = _wcsdup( event.PropertyName() );
//                        }
//                        else
//                        {
//                            pwszPropertyName = _wcsdup( L"<no name>" );
//                        }
//                        if ( pwszPropertyName )
//                        {
//                            free( pwszPropertyName );
//                        }
//                    }
//                    break;
//
//                case SPEI_PROPERTY_STRING_CHANGE:
//                    {
//                        TCHAR sz[MAX_PATH * 2];
//                        WCHAR *pwszPropertyName = NULL;
//                        if ( event.PropertyName() )
//                        {
//                            pwszPropertyName = _wcsdup( event.PropertyName() );
//                        }
//                        else
//                        {
//                            pwszPropertyName = _wcsdup( L"<no name>" );
//                        }
//
//                        WCHAR *pwszPropertyStringValue = NULL;
//                        if ( event.PropertyStringValue() )
//                        {
//                            pwszPropertyStringValue = _wcsdup( event.PropertyStringValue() );
//                        }
//                        else
//                        {
//                            pwszPropertyStringValue = _wcsdup( L"<no string value>" );
//                        }
//                        if ( pwszPropertyName )
//                        {
//                            free( pwszPropertyName );
//                        }
//                        if ( pwszPropertyStringValue )
//                        {
//                            free( pwszPropertyStringValue );
//                        }
//                        
//                    }
//                    break;
//                
//                case SPEI_RECO_STATE_CHANGE:
//                    break;
//
//
//
//                case SPEI_SOUND_START:
//                    m_bInSound = TRUE;
//                    break;
//
//                case SPEI_SOUND_END:
//                    if (m_bInSound)
//                    {
//                        m_bInSound = FALSE;
//                        if (!m_bGotReco)
//                        {
//                            const WCHAR wszNoise[] = L"(Noise without speech)";
//                        }
//                        m_bGotReco = FALSE;
//                    }
//                    break;
//
//                case SPEI_RECO_OTHER_CONTEXT:
//                    {
//                        m_bGotReco = TRUE;
//                    }
//                    break;
//
//                case SPEI_FALSE_RECOGNITION:
//                case SPEI_HYPOTHESIS:
//                case SPEI_RECOGNITION:
//                    {
//                        
//                        CComPtr<ISpRecoResult> cpResult;
//                        cpResult = event.RecoResult();
//
//                        m_bGotReco = TRUE;
//						CSpDynamicString dstrText;
//                        cpResult->GetText(SP_GETWHOLEPHRASE, SP_GETWHOLEPHRASE, TRUE, &dstrText, NULL);
//
//                        if (event.eEventId == SPEI_FALSE_RECOGNITION)
//                            dstrText.Append(L"<FALSERECO>");
//
//						WCHAR* text = dstrText.Copy();
//						std::wstring recognizedText = text;
//						::PrintError(recognizedText, S_OK);
//            	
//                        cpResult.Release();
//                    }
//                    break;
//            }
//
//			            
//        }
//    }
//}