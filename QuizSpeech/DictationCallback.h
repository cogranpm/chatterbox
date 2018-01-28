#pragma once
#include "stdafx.h"


class DictationContext;

class DictationCallback : public ISpNotifyCallback
{
public:
	DictationCallback(DictationContext* context);
	~DictationCallback();
	HRESULT STDMETHODCALLTYPE NotifyCallback(WPARAM wParam, LPARAM lParam);

private:
	DictationContext* context;

};

