#pragma once
#include "stdafx.h"


class SpeechRecognitionEngine
{
public:
	SpeechRecognitionEngine();
	~SpeechRecognitionEngine();
	void CreateEngine();
	CComPtr<ISpRecognizer> GetEngine();
private:
	CComPtr<ISpRecognizer> recognitionEngine;
};

