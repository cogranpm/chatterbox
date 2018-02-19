#pragma once

#include "stdafx.h"

class DictationContext;

class DictationRecognitionResult
{
public:
	DictationRecognitionResult(DictationContext* context);
	~DictationRecognitionResult();
	void Process();

private:
	DictationContext* context;
	void ProcessRecognition(ISpRecoResult* pResult, std::wstring& recognizedText, bool& recognitionReceived, bool& stopReceived);
	void ProcessHypothesis(ISpRecoResult* pResult, std::wstring& hypothesisText);
};

