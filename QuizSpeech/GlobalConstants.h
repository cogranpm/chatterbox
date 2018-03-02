#pragma once

#include "stdafx.h"

namespace GlobalConstants
{

	const MFTIME ONE_SECOND = 10000000;
	const LONG   ONE_MSEC = 1000;
	const std::wstring NULL_LIST_INDICATOR = L"-";

	void PrintError(const std::wstring& message, HRESULT code);
	void Convert(int value, int &hour, int &minute, int &seconds);
	
	
}