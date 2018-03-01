#pragma once

#include "stdafx.h"
#include "GlobalConstants.h"

class DictationContext;

class DictationRecognitionResult
{
public:
	DictationRecognitionResult(DictationContext* context);
	~DictationRecognitionResult();
	void Process();

private:
	DictationContext* context;
	bool ProcessRecognition(ISpRecoResult* pResult, std::wstring& recognizedText, bool& recognitionReceived, DICTATION_COMMANDS& command);
	void ProcessHypothesis(ISpRecoResult* pResult, std::wstring& hypothesisText);
};

