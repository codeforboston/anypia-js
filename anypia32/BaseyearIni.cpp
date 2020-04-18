// $Id: BaseyearIni.cpp 1.5.1.1 2012/03/08 06:55:15EST 277133 Development 277133(2012/03/08 06:55:49EST) $
//
// Functions to handle base year in an ini file.

#include "stdafx.h"
#include "BaseyearIni.h"

const char *BaseYearIni::section = "Computation Year";
const char *BaseYearIni::entry = "Year";

// Description: Initializes base year info.
BaseYearIni::BaseYearIni() : BaseYear()
{ }

// Description: Reads base year from registry or ini file.
void BaseYearIni::read()
{
   theYear = AfxGetApp()->GetProfileInt(section, entry, 0);
}

// Description: Saves base year to registry or ini file.
void BaseYearIni::write()
{
   AfxGetApp()->WriteProfileInt(section, entry, theYear);
}

// Description: Clears entry from registry.
void BaseYearIni::clear()
{
   AfxGetApp()->WriteProfileString(section, entry, NULL);
}
