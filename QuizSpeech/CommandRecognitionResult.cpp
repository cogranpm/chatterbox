#include "CommandRecognitionResult.h"
#include "SpeechRecognitionContext.h"
#include "CommandProperty.h"

CommandRecognitionResult::CommandRecognitionResult(SpeechRecognitionContext* context):
	context(context)
{
}


CommandRecognitionResult::~CommandRecognitionResult()
{
	this->FreePhrase(phrase);
	//do the other members free themselves?
	this->dstrText.Clear();
}

void CommandRecognitionResult::FreePhrase(SPPHRASE* phrase)
{
	if (phrase)
	{
		::CoTaskMemFree(phrase);
	}
}

void CommandRecognitionResult::Process()
{
	HRESULT hr = S_OK;
	CSpStreamFormat Fmt(SPEECH_AUDIO_FORMAT, &hr);
	hr = this->recognitionEvent.GetFrom(context->GetContext());
	if (FAILED(hr))
	{
		const std::string message("Call to GetFrom failed");
		::PrintError(L"Call to GetFrom failed", hr);
		throw std::runtime_error(message);
	}

	if (SPEI_RECOGNITION == recognitionEvent.eEventId)
	{
		recognition = recognitionEvent.RecoResult();
	}


	recognitionEvent.Clear();
	if (!recognition)
	{
		return;
	}

	hr = recognition->GetPhrase(&phrase);
	if (S_OK != hr)
	{
		if (hr == E_POINTER)
		{
			const std::string message("Error in NotifyCallback GetPhrase - InvalidPointer");
			::PrintError(L"Error in NotifyCallback GetPhrase - InvalidPointer", hr);
			throw std::runtime_error(message);
		}
		else
		{
			const std::string message("Error in NotifyCallback GetPhrase");
			::PrintError(L"Error in NotifyCallback GetPhrase", hr);
			throw std::runtime_error(message);
		}
		return;
	}
	hr = recognition->GetText(SP_GETWHOLEPHRASE, SP_GETWHOLEPHRASE, TRUE, &dstrText, NULL);
	if (S_OK != hr)
	{
		::PrintError(L" Error in NotifyCallback GetText", hr);
		return;
	}

	WCHAR* text = dstrText.Copy();
	std::wstring recognizedText = text;
	std::wstring lcaseText = text;
	std::transform(recognizedText.begin(), recognizedText.end(), lcaseText.begin(), ::towlower);

	//there can be multiple semantic properties
	//iterate them and place in a vertical list and return to user
	//use c++ move semantics on vector which allows to return a vector efficiently
	std::wstring ruleName(phrase->Rule.pszName);
	std::vector<CommandProperty> commandPropertyList;
	const SPPHRASEPROPERTY* pProp = phrase->pProperties;
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
	this->context->CommandRecognitionReceived(recognizedText, commandPropertyList);
}
