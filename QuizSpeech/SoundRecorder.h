#pragma once
#include "stdafx.h"

class SoundRecorder
{
public:
	SoundRecorder();
	~SoundRecorder();
	void Record(const std::wstring filePath);
};

