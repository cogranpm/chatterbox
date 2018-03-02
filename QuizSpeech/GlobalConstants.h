#pragma once

#include "stdafx.h"



namespace
{

	const MFTIME ONE_SECOND = 10000000;
	const LONG   ONE_MSEC = 1000;

	const SPSTREAMFORMAT SPEECH_AUDIO_FORMAT = SPSF_16kHz16BitMono; // SPSF_8kHz8BitMono; // SPSF_22kHz16BitStereo; //SPSF_8kHz8BitMono
	const std::wstring NULL_LIST_INDICATOR = L"-";
	
	typedef enum GRAMMARIDS
	{
		GID_DICTATION,      // ID for the dictation grammar
		GID_DICTATIONCC,    // ID for the C&C grammar that's active during dictation
		GID_CC              // ID for the C&C grammar that's active when dictation is not
	};
/*
	namespace GlobalConstants
	{*/
		enum class DictationCommand: short
		{
			ACCEPT = 0,
			CANCEL,
			STOP
		};
	//}

	const ULONGLONG GRAMMARID = 161;

	void PrintError(const std::wstring& message, HRESULT code)
	{
		std::cerr << message.c_str();

		wchar_t buf[256];
		::FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, 256, NULL);

		std::wstringstream outputStream;
		outputStream << message;
		outputStream << std::endl;
		outputStream << code;
		outputStream << std::endl;
		outputStream << buf;
		std::wstring output = outputStream.str();
		::OutputDebugStringW(output.c_str());
	}

	void Convert(int value, int &hour, int &minute, int &seconds)
	{
		hour = value / 3600;
		minute = (value % 3600) / 60;
		seconds = value % 60;
	}

	
}