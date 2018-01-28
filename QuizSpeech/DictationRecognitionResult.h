#pragma once

class DictationContext;

class DictationRecognitionResult
{
public:
	DictationRecognitionResult(DictationContext* context);
	~DictationRecognitionResult();
	void Process();

private:
	DictationContext* context;
};

