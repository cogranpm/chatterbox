#include "DictationCallback.h"
#include "DictationRecognitionResult.h"


DictationCallback::DictationCallback(DictationContext* context) :
	context(context)
{
}


DictationCallback::~DictationCallback()
{
}


HRESULT STDMETHODCALLTYPE DictationCallback::NotifyCallback(WPARAM wParam, LPARAM lParam)
{
	HRESULT hr = S_OK;
	
	DictationRecognitionResult result(this->context);
	result.Process();
	
	return S_OK;
}
