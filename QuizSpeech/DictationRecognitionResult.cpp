#include "DictationRecognitionResult.h"
#include "DictationContext.h"
#include "GlobalConstants.h"
#include "CommandProperty.h"
#include "ActionCommandParser.h"
#include "MyApp.h"

DictationRecognitionResult::DictationRecognitionResult(DictationContext* context) : context(context)
{
}


DictationRecognitionResult::~DictationRecognitionResult()
{
}



void DictationRecognitionResult::ProcessHypothesis(ISpRecoResult* pResult, std::wstring& hypothesisText)
{
	//ISpRecoResult* pResult = event.RecoResult();
	if (!pResult)
	{
		// We expect these events to come with reco results
		return;
	}
	SPPHRASE* pPhrase = NULL;
	HRESULT hr = pResult->GetPhrase(&pPhrase);

	CSpDynamicString dstrText;
	BYTE dwAttributes;
	hr = pResult->GetText(SP_GETWHOLEPHRASE, SP_GETWHOLEPHRASE, TRUE, &dstrText, &dwAttributes);
	if (FAILED(hr))
	{
		//maybe need to do something here, not sure
		return;
	}

	if (dwAttributes & SPAF_ONE_TRAILING_SPACE)
	{
		dstrText.Append(L" ");
	}
	else if (dwAttributes & SPAF_TWO_TRAILING_SPACES)
	{
		dstrText.Append(L"  ");
	}
	else if ((dwAttributes & SPAF_CONSUME_LEADING_SPACES))
	{
		dstrText.Append(L"  ");
	}

	WCHAR* text = dstrText.Copy();
	if (text != NULL)
	{
		hypothesisText.append(text);
	}
	hypothesisText.append(text);
	
}

void DictationRecognitionResult::ProcessRecognition(ISpRecoResult* pResult, std::wstring& recognizedText, bool& recognitionReceived, bool& stopReceived)
{
	//ISpRecoResult* pResult = event.RecoResult();
	stopReceived = false;
	if (!pResult)
	{
		// We expect these events to come with reco results
		return;
	}
	SPPHRASE* pPhrase = NULL;
	HRESULT hr = pResult->GetPhrase(&pPhrase);

	switch (pPhrase->ullGrammarID)
	{
	case GID_DICTATION:
		break;
	case GID_DICTATIONCC:

		//CSpDynamicString dstrText;
		//BYTE dwAttributes;
		//hr = pResult->GetText(SP_GETWHOLEPHRASE, SP_GETWHOLEPHRASE, TRUE, &dstrText, &dwAttributes);
		//std::wstring commandText(dstrText.Copy());
		//if (commandText == L"stop recording")
		//{
		//	/* user has told us to stop dictating based on diction command and control rules */
		//	stopReceived = true;
		//	recognitionReceived = false;
		//	return;
		//}


		hr = pResult->GetPhrase(&pPhrase);
		std::wstring ruleName(pPhrase->Rule.pszName);
		std::vector<CommandProperty> commandPropertyList;
		const SPPHRASEPROPERTY* pProp = pPhrase->pProperties;
		while (pProp != NULL)
		{

			std::wstring phraseValue(L"");
			std::wstring phraseProperty(L"");

			if (pProp->pszValue != NULL)
			{
				phraseValue = std::wstring(pProp->pszValue);
			}
			if (pProp->pszName != NULL)
			{
				phraseProperty = std::wstring(pProp->pszName);
			}
			CommandProperty commandProperty(phraseProperty, phraseValue, ruleName);
			commandPropertyList.push_back(commandProperty);
			pProp = pProp->pNextSibling;
		}
		ActionCommandParser actionParser;
		std::wstring actionName;
		std::wstring actionTarget;
		std::wstring targetValue;
		actionParser.Parse(commandPropertyList, actionName, actionTarget, targetValue, ruleName);

		/* not sure if allowing OK and cancel is smart because they are too common as words 
			should enforce a phrase like stop recording 
		*/
		//if (boost::algorithm::equals(actionName, MyApp::COMMAND_ACTION_OK))
		//{
		//	//stopReceived = true;
		//	//recognitionReceived = false;
		//}
		//else if (boost::algorithm::equals(actionName, MyApp::COMMAND_ACTION_CANCEL))
		//{
		//	//stopReceived = true;
		//	//recognitionReceived = false;
		//}
		//else 
		if (boost::algorithm::equals(actionName, L"stop"))
		{
			stopReceived = true;
			recognitionReceived = false;
		}
	}

	SPRECORESULTTIMES times;
	pResult->GetResultTimes(&times);
	//maybe not be useful, times has length in 100 nanoseconds

	CSpDynamicString dstrText;
	BYTE dwAttributes;
	hr = pResult->GetText(SP_GETWHOLEPHRASE, SP_GETWHOLEPHRASE, TRUE, &dstrText, &dwAttributes);
	if (FAILED(hr))
	{
		//maybe need to do something here, not sure
		return;
	}

	if (dwAttributes & SPAF_ONE_TRAILING_SPACE)
	{
		dstrText.Append(L" ");
	}
	else if (dwAttributes & SPAF_TWO_TRAILING_SPACES)
	{
		dstrText.Append(L"  ");
	}
	else if ((dwAttributes & SPAF_CONSUME_LEADING_SPACES))
	{
		dstrText.Append(L"  ");
	}

	//probably just for atl stuff- here just for reference
	//BSTR bstrText = ::SysAllocString(dstrText);
	//if (!bstrText)
	//{
	//	return;
	//}
	//::SysFreeString(bstrText);
	WCHAR* text = dstrText.Copy();
	if (text != NULL)
	{

		//if (event.eEventId == SPEI_HYPOTHESIS)
		//{
		//	hypothesisText.append(text);
		//	hypothesisReceived = true;
		//}
		//else
		//{
			recognizedText.append(text);
			recognitionReceived = true;
			
		//}
	}
	//this->context->WriteAudio(pResult);

}

void DictationRecognitionResult::Process()
{
	CSpEvent event;
	std::wstring recognizedText;
	std::wstring hypothesisText;
	ISpRecoResult* pResult = nullptr;
	bool recognitionReceived = false;
	bool hypothesisReceived = false;
	bool stopReceived = false;
	
	while (event.GetFrom(context->GetContext()) == S_OK)
	{
		
		//DUMP_EVENT_NAME(event.eEventId);
		
		switch (event.eEventId)
		{
		case SPEI_SOUND_START:
		{
			::PrintError(L"sound start", S_OK);
			context->SoundStart();
			break;
		}
		case SPEI_SOUND_END:
		{
			::PrintError(std::wstring(L"end sound"), S_OK);
			context->SoundEnd();
			break;
		}
		case SPEI_PHRASE_START:
		{
			::PrintError(std::wstring(L"Phrase Start"), S_OK);
			//could use this as gui updater, maybe show some graphic etc
			break;
		}
		case SPEI_RECO_STATE_CHANGE:
			if (event.RecoState() == SPRST_INACTIVE)
			{
				::PrintError(std::wstring(L"Reco State Change"), S_OK);
			}
			break;
		case SPEI_FALSE_RECOGNITION:
		{
			::PrintError(std::wstring(L"false recognition"), S_OK);
			//if (pResult)
			//{
			//	//this->context->WriteAudio(pResult);
			//}
			break;
		}
		case SPEI_RECO_OTHER_CONTEXT:
			// HYPOTHESIS: One of a set of ongoing "guesses" that the engine makes.
			//              Any number of these can precede an SPEI_RECOGNITION
			// RECOGNITION: The engine is done processing the utterance and has a result
		case SPEI_HYPOTHESIS:
		{
			::PrintError(std::wstring(L"hypothesis"), S_OK);
			hypothesisReceived = true;
			pResult = event.RecoResult();
			ProcessHypothesis(pResult, hypothesisText);
			break;
		}
		case SPEI_RECOGNITION:
		{
			pResult = event.RecoResult();
			ProcessRecognition(pResult, recognizedText, recognitionReceived, stopReceived);
			if (!stopReceived)
			{
				this->context->WriteAudio(pResult);
			}
			break;
		}
		case SPEI_INTERFERENCE:
			break;

		default:
			break;
		}
	}

	/* let the context object broadcast this out to listeners */
	if (stopReceived)
	{
		this->context->DictationStopped();
	}
	else
	{
		if (!hypothesisText.empty() && hypothesisReceived)
		{
			this->context->HypothesisReceived(hypothesisText);
		}

		if (!recognizedText.empty() && recognitionReceived)
		{
			this->context->RecognitionReceived(recognizedText);
			//this->context->WriteAudio(pResult);
		}

		//if (pResult != NULL)
		//{
		//	this->context->WriteAudio(pResult);
		//}
	}

	event.Clear();

}
