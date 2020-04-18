// $Id: ConfigIni.h 1.4.1.1 2012/03/08 06:55:08EST 277133 Development 277133(2012/03/08 06:55:47EST) $
//
// Declarations for Config stored in ini file.

#pragma once

#include "config.h"

// Description: Manages the configuration information in
//   an ini file for a pia program.
//
// Remarks: Manages the configuration information in
//   an ini file for a pia program.
class ConfigIni : public Config
{
private:
   // Description: Section name.
   static const char *section;
   // Description: Top margin entry name.
   static const char *TopMargin;
   // Description: Screen points entry name.
   static const char *ScreenPoints;
   // Description: Printer points entry name.
   static const char *PrinterPoints;
   // Description: Left margin entry name.
   static const char *LeftMargin;
   // Description: Long output indicator entry name.
   static const char *Output;
public:
   // Description: Indicator to save long output indicator.
   bool saveLongOutput;
   // Description: Indicator to save screen output points.
   bool saveScreenPoints;
   // Description: Indicator to save printed report points.
   bool savePrinterPoints;
   // Description: Indicator to save top margin setting.
   bool saveTopMargin;
   // Description: Indicator to save left margin setting.
   bool saveLeftMargin;
public:
   ConfigIni();
   void read();
   void write();
};
