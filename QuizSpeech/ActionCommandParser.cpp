#include "ActionCommandParser.h"
#include "MyApp.h"


ActionCommandParser::ActionCommandParser()
{
}


ActionCommandParser::~ActionCommandParser()
{
}

void ActionCommandParser::Parse(std::vector<CommandProperty>& commandPropertyList, std::wstring& actionName, std::wstring& targetName, std::wstring& targetValue, std::wstring& ruleName)
{
	//loop through a list of CommandProperty to find the pattern for actions which are name/value pairs
	//eg action=add/delete/edit, entity=shelf, there might also be a targetValue from the ui, such as a shelf name, 
	//which would be used to select an item from a list for example
	std::vector<CommandProperty>::const_iterator it;
	for (it = commandPropertyList.begin(); it != commandPropertyList.end(); it++)
	{
		CommandProperty property = *(it);
		if (boost::algorithm::equals(property.GetPropertyName(), MyApp::COMMAND_ACTION) || boost::algorithm::equals(property.GetPropertyName(), MyApp::CONTROL_ACTION))
		{
			actionName = property.GetPropertyValue();
		}
		else if (boost::algorithm::equals(property.GetPropertyName(), MyApp::VALUE_NAME_ENTITY))
		{
			targetName = property.GetPropertyValue();
		}
		else
		{
			actionName = property.GetPropertyName();
			targetName = property.GetPropertyValue();
		}
		ruleName = property.GetRuleName();
	}
}
