#include "GlobalConstants.h"

namespace GlobalConstants
{

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
