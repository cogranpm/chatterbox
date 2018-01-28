#pragma once

#include "stdafx.h"

class CommandProperty
{
public:
	CommandProperty();
	CommandProperty(const std::wstring& actionName, const std::wstring& actionValue, const std::wstring& ruleName);
	~CommandProperty();
	const std::wstring GetPropertyName();
	const std::wstring GetPropertyValue();
	const std::wstring GetRuleName();
	void SetPropertyName(const std::wstring& propertyName);
	void SetPropertyValue(const std::wstring& propertyValue);
	void SetRuleName(const std::wstring& ruleName);
private:
	std::wstring propertyName;
	std::wstring propertyValue;
	std::wstring ruleName;

};

