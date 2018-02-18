#include "DictationRecognitionResult.h"
#include "DictationContext.h"
#include "GlobalConstants.h"
#include "CommandProperty.h"
#include "ActionCommandParser.h"

DictationRecognitionResult::DictationRecognitionResult(DictationContext* context) : context(context)
{
}


DictationRecognitionResult::~DictationRecognitionResult()
{
}

bool recognitionReceived = false;
bool hypothesisReceived = false;

void DictationRecognitionResult::ProcessRecognition(CSpEvent& event, std::wstring& recognizedText, std::wstring& hypothesisText, bool& recognitionReceived, bool& hypothesisReceived, bool& stopReceived)
{
	ISpRecoResult* pResult = event.RecoResult();
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

		
		std::wstring ruleName(pPhrase->Rule.pszName);
		const SPPHRASEPROPERTY* pProp = pPhrase->pProperties;
		std::vector<CommandProperty> commandPropertyList;

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
		//ActionCommandParser parser;
		//std::wstring actionName;
		//std::wstring ruleNamea;
		//std::wstring targetName;
		//std::wstring targetValue;
		//parser.Parse(commandPropertyList, actionName, targetName, targetValue, ruleNamea);
		//if (actionName == L"stop" && targetName == L"recording")
		//{
		//	/* user has told us to stop dictating based on diction command and control rules */
		//	stopReceived = true;
		//	hypothesisReceived = false;
		//	recognitionReceived = false;
		//	return;
		//}
		CSpDynamicString dstrText;
		BYTE dwAttributes;
		hr = pResult->GetText(SP_GETWHOLEPHRASE, SP_GETWHOLEPHRASE, TRUE, &dstrText, &dwAttributes);
		WCHAR* text = dstrText.Copy();
		if (text == L"stop recording")
		{
			/* user has told us to stop dictating based on diction command and control rules */
			stopReceived = true;
			hypothesisReceived = false;
			recognitionReceived = false;
			return;
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

		if (event.eEventId == SPEI_HYPOTHESIS)
		{
			hypothesisText.append(text);
			hypothesisReceived = true;
		}
		else
		{
			recognizedText.append(text);
			recognitionReceived = true;
			this->context->WriteAudio(pResult);
		}
	}

}

void DictationRecognitionResult::Process()
{
	CSpEvent event;
	std::wstring recognizedText;
	std::wstring hypothesisText;
	ISpRecoResult* pResult;
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
			pResult = event.RecoResult();
			//event.RetainedAudioStream.
			if (pResult)
			{
				this->context->WriteAudio(pResult);
			}
			break;
		}
		case SPEI_RECO_OTHER_CONTEXT:
			// HYPOTHESIS: One of a set of ongoing "guesses" that the engine makes.
			//              Any number of these can precede an SPEI_RECOGNITION
			// RECOGNITION: The engine is done processing the utterance and has a result
		case SPEI_HYPOTHESIS:
		{
			::PrintError(std::wstring(L"hypothesis"), S_OK);
		}
		case SPEI_RECOGNITION:
		{
			ProcessRecognition(event, recognizedText, hypothesisText, recognitionReceived, hypothesisReceived, stopReceived);
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

	if (!hypothesisText.empty() && hypothesisReceived)
	{
		this->context->HypothesisReceived(hypothesisText);
	}
	
	if (!recognizedText.empty() && recognitionReceived)
	{
		this->context->RecognitionReceived(recognizedText);
	}

	event.Clear();

}
