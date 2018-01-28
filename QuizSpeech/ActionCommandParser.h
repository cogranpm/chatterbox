#pragma once

#include "stdafx.h"
#include "CommandProperty.h"
class ActionCommandParser
{
public:
	ActionCommandParser();
	~ActionCommandParser();
	void Parse(std::vector<CommandProperty>& commandPropertyList, std::wstring& actionName, std::wstring& targetName, std::wstring& targetValue, std::wstring& ruleName);
};

