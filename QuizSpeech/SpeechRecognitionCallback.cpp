
#include "SpeechRecognitionContext.h"
#include "SpeechRecognitionCallback.h"
#include "GlobalConstants.h"


SpeechRecognitionCallback::SpeechRecognitionCallback(SpeechRecognitionContext* context) :
	context(context)
{
}


SpeechRecognitionCallback::~SpeechRecognitionCallback()
{
}



HRESULT STDMETHODCALLTYPE SpeechRecognitionCallback::NotifyCallback(WPARAM wParam, LPARAM lParam)
{
	HRESULT hr = S_OK;
	CommandRecognitionResult result(this->context);
	result.Process();
	return S_OK;
}

