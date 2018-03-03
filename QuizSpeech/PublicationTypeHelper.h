#pragma once

#include "PublicationType.h"
#include <wx/combobox.h>

class PublicationTypeHelper
{
public:
	PublicationTypeHelper();
	~PublicationTypeHelper();
	static void SetupPublicationTypes(wxComboBox* combo);
};

