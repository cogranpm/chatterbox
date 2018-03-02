#pragma once
#include "stdafx.h"


class SpeechConstants
{
public:

	enum class DictationCommand : short
	{
		ACCEPT = 0,
		CANCEL,
		STOP
	};

	static const SPSTREAMFORMAT SPEECH_AUDIO_FORMAT;

	typedef enum GRAMMARIDS
	{
		GID_DICTATION,      // ID for the dictation grammar
		GID_DICTATIONCC,    // ID for the C&C grammar that's active during dictation
		GID_CC              // ID for the C&C grammar that's active when dictation is not
	};

	static const ULONGLONG GRAMMARID;

	SpeechConstants();
	~SpeechConstants();
};

