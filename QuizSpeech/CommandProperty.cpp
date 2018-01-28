#include "CommandProperty.h"



CommandProperty::CommandProperty() : CommandProperty(L"", L"", L"")
{
}

CommandProperty::CommandProperty(const std::wstring& actionName, const std::wstring& actionValue, const std::wstring& ruleName) :
	propertyName(actionName),
	propertyValue(actionValue),
	ruleName(ruleName)
{

}


CommandProperty::~CommandProperty()
{
}

const std::wstring CommandProperty::GetPropertyName()
{
	return this->propertyName;
}

const std::wstring CommandProperty::GetPropertyValue()
{
	return this->propertyValue;
}

const std::wstring CommandProperty::GetRuleName()
{
	return this->ruleName;
}

void CommandProperty::SetPropertyName(const std::wstring& propertyName)
{
	this->propertyName = propertyName;
}

void CommandProperty::SetPropertyValue(const std::wstring& propertyValue)
{
	this->propertyValue = propertyValue;
}

void CommandProperty::SetRuleName(const std::wstring& ruleName)
{
	this->ruleName = ruleName;
}