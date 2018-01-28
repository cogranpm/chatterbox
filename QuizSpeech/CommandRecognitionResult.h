#pragma once
#include "stdafx.h"
#include "GlobalConstants.h"

class SpeechRecognitionContext;

class CommandRecognitionResult
{
public:
	CommandRecognitionResult(SpeechRecognitionContext* context);
	~CommandRecognitionResult();
	void Process();
private:
	void FreePhrase(SPPHRASE* phrase);
	SpeechRecognitionContext* context;
	CComPtr<ISpRecoResult> recognition;
	CSpEvent recognitionEvent;
	CSpDynamicString dstrText;
	/* phrase contains a bunch of data about the recognition */
	SPPHRASE* phrase;
};

