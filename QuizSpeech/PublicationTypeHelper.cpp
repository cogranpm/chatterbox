#include "PublicationTypeHelper.h"



PublicationTypeHelper::PublicationTypeHelper()
{
}


PublicationTypeHelper::~PublicationTypeHelper()
{
}

void PublicationTypeHelper::SetupPublicationTypes(wxComboBox* combo)
{
	combo->SetClientObject(0, new PublicationType(0));
	combo->SetClientObject(1, new PublicationType(1));
	combo->SetClientObject(2, new PublicationType(2));
	combo->SetClientObject(3, new PublicationType(3));
	combo->SetClientObject(4, new PublicationType(4));
	combo->SetClientObject(5, new PublicationType(5));
}
