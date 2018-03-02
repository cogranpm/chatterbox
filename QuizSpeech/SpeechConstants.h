#pragma once
class SpeechConstants
{
public:

	enum class DictationCommand : short
	{
		ACCEPT = 0,
		CANCEL,
		STOP
	};

	SpeechConstants();
	~SpeechConstants();
};

