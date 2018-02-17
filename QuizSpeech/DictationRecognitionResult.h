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
	void ProcessRecognition(CSpEvent& event, std::wstring& recognizedText, std::wstring& hypothesisText, bool& recognitionReceived, bool& hypothesisReceived, bool& stopReceived);
};

