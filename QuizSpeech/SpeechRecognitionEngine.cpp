#include "SpeechRecognitionEngine.h"
#include "GlobalConstants.h"


SpeechRecognitionEngine::SpeechRecognitionEngine() : recognitionEngine(nullptr)
{
}


SpeechRecognitionEngine::~SpeechRecognitionEngine()
{
	if (this->recognitionEngine != nullptr)
	{
		this->recognitionEngine.Release();
		this->recognitionEngine = nullptr;
	}
}

void SpeechRecognitionEngine::CreateEngine()
{
	//creates the recognition engine which is first step in any speech recognition
	//can create two types of instances, inproc or shared, there are pros and cons of both
	//CLSID_SpInprocRecognizer, CLSID_SpSharedRecognizer
	HRESULT hr = recognitionEngine.CoCreateInstance(CLSID_SpInprocRecognizer);
	if (FAILED(hr))
	{
		const std::string message("Could not create Speech Recognition Engine");
		::PrintError(L"Could not create Speech Recognition Engine", hr);
		throw std::runtime_error(message);
	}

	CComPtr<ISpObjectToken> cpAudioToken;

	if (SUCCEEDED(hr))
	{
		hr = SpGetDefaultTokenFromCategoryId(SPCAT_AUDIOIN, &cpAudioToken);
	}
	if (FAILED(hr))
	{
		const std::string message("Call to SpGetDefaultTokenFromCategoryId failed");
		::PrintError(L"Call to SpGetDefaultTokenFromCategoryId failed", hr);
		throw std::runtime_error(message);
	}

	if (SUCCEEDED(hr))
	{
		hr = this->recognitionEngine->SetInput(cpAudioToken, TRUE);
	}
	if (FAILED(hr))
	{
		const std::string message("Call to SetInput failed");
		::PrintError(L"Call to SetInput failed", hr);
		throw std::runtime_error(message);
	}

	CComPtr<ISpAudio> cpAudio;
	if (SUCCEEDED(hr))
	{
		hr = SpCreateDefaultObjectFromCategoryId(SPCAT_AUDIOIN, &cpAudio);	
	}
	if (FAILED(hr))
	{
		const std::string message("Call to SpCreateDefaultObjectFromCategoryId failed");
		::PrintError(L"Call to SpCreateDefaultObjectFromCategoryId failed", hr);
		throw std::runtime_error(message);
	}

	if (SUCCEEDED(hr))
	{
		hr = this->recognitionEngine->SetInput(cpAudio, TRUE);
	}
	if (FAILED(hr))
	{
		const std::string message("Call to SetInput failed");
		::PrintError(L"Call to SetInput failed", hr);
		throw std::runtime_error(message);
	}


}

CComPtr<ISpRecognizer> SpeechRecognitionEngine::GetEngine()
{
	return this->recognitionEngine;
}
