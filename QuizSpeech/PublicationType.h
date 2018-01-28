#pragma once
#include <wx\clntdata.h>
class PublicationType :
	public wxClientData
{

private:
	short _key;

public:
	PublicationType(void);
	PublicationType(short key);
	~PublicationType(void);
	 short getKey () const { return _key; }
};

