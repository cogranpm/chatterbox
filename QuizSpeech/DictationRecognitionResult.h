#pragma once

#include "stdafx.h"
#include "SpeechConstants.h"

class DictationContext;

class DictationRecognitionResult
{
public:
	DictationRecognitionResult(DictationContext* context);
	~DictationRecognitionResult();
	void Process();

private:
	DictationContext* context;
	bool ProcessRecognition(ISpRecoResult* pResult, std::wstring& recognizedText, bool& recognitionReceived, SpeechConstants::DictationCommand& command);
	void ProcessHypothesis(ISpRecoResult* pResult, std::wstring& hypothesisText);
};

