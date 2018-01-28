#pragma once

#include "stdafx.h"
#include "CommandRecognitionResult.h"

class SpeechRecognitionContext;

class SpeechRecognitionCallback : public ISpNotifyCallback
{
public:
	SpeechRecognitionCallback(SpeechRecognitionContext* context);
	~SpeechRecognitionCallback();
	//callbacks
	HRESULT STDMETHODCALLTYPE NotifyCallback(WPARAM wParam, LPARAM lParam);

private:
	SpeechRecognitionContext* context;
	
};

