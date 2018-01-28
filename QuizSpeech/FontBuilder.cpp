#include "FontBuilder.h"
#include <wx/font.h>


FontBuilder::FontBuilder()
{
}


FontBuilder::~FontBuilder()
{
}

void FontBuilder::GetDefaultFontDesc(std::string& buffer)
{
	buffer = wxNORMAL_FONT->GetNativeFontInfoDesc();
}

void FontBuilder::GetCodeFontDesc(std::string& buffer)
{
	buffer = wxSMALL_FONT->GetNativeFontInfoDesc();
}

void FontBuilder::GetSummaryFontDesc(std::string& buffer)
{
	buffer = wxITALIC_FONT->GetNativeFontInfoDesc();
}


void FontBuilder::GetFootnoteFontDesc(std::string& buffer)
{
	buffer = wxSWISS_FONT->GetNativeFontInfoDesc();
}