#pragma once
#include "stdafx.h"


class FontBuilder
{
public:
	FontBuilder();
	~FontBuilder();
	void GetDefaultFontDesc(std::string& buffer);
	void GetCodeFontDesc(std::string& buffer);
	void GetSummaryFontDesc(std::string& buffer);
	void GetFootnoteFontDesc(std::string& buffer);
};

