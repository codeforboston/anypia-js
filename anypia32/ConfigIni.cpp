// $Id: ConfigIni.cpp 1.4.1.1 2012/03/08 06:55:10EST 277133 Development 277133(2012/03/08 06:55:48EST) $
//
// Functions to handle Config stored in ini file.

#include "stdafx.h"
#include "ConfigIni.h"
#include "resource.h"
#include "comma.h"

const char *ConfigIni::section = "Settings";
const char *ConfigIni::ScreenPoints = "ScreenPoints";
const char *ConfigIni::PrinterPoints = "PrinterPoints";
const char *ConfigIni::TopMargin = "TopMargin";
const char *ConfigIni::LeftMargin = "LeftMargin";
const char *ConfigIni::Output = "Output";

// Description: Initializes report setting info.
ConfigIni::ConfigIni() : Config(), saveLongOutput(false),
 saveScreenPoints(false), savePrinterPoints(false), saveTopMargin(false),
 saveLeftMargin(false)
{ }

// Description: Reads report setting info from ini file.
void ConfigIni::read()
{
   CString temp = AfxGetApp()->GetProfileString(section, TopMargin);
   if (!temp.IsEmpty())
      setTopMargin((float)atof(temp));
   temp = AfxGetApp()->GetProfileString(section, LeftMargin);
   if (!temp.IsEmpty())
      setLeftMargin((float)atof(temp));
   int output = AfxGetApp()->GetProfileInt(section, Output, 2);
   if (output < 2)
      setLongOutput((output == 0) ? false : true);
   temp = AfxGetApp()->GetProfileString(section, ScreenPoints);
   if (!temp.IsEmpty())
      setScreenPoints(atoi(temp));
   temp = AfxGetApp()->GetProfileString(section, PrinterPoints);
   if (!temp.IsEmpty())
      setPrinterPoints(atoi(temp));
}

// Description: Saves report setting info to ini file.
void ConfigIni::write()
{
   if (saveTopMargin)
      AfxGetApp()->WriteProfileString(section, TopMargin,
         poutNoComma(getTopMargin(), 1, 2).c_str());
   if (saveLeftMargin)
      AfxGetApp()->WriteProfileString(section, LeftMargin,
         poutNoComma(getLeftMargin(), 1, 2).c_str());
   if (saveLongOutput) {
      int output = getLongOutput() ? 1 : 0;
      AfxGetApp()->WriteProfileInt(section, Output, output);
   }
   if (saveScreenPoints)
      AfxGetApp()->WriteProfileString(section, ScreenPoints,
         poutNoComma(getScreenPoints()).c_str());
   if (savePrinterPoints)
      AfxGetApp()->WriteProfileString(section, PrinterPoints,
         poutNoComma(getPrinterPoints()).c_str());
}
