// $Id: AwbidatIni.h 1.6.1.1 2012/03/08 06:55:16EST 277133 Development 277133(2012/03/08 06:55:50EST) $
//
// Declarations for class to manage AwbiData in an ini file.

#pragma once

#include "awbidat.h"

// Description: Manages the average wage and benefit increase
//   information in the registry or an ini file for a pia program.
//
// Remarks: Manages the average wage and benefit increase
//   information in the registry or an ini file for a pia program.
class AwbiDataIni : public AwbiData
{
protected:
   // Description: Section name.
   CString section;
   // Description: Benefit increase entry name.
   static const char *BenefitIncrease;
   // Description: Average wage increase entry name.
   static const char *AverageWage;
   // Description: Wage base increase entry name.
   static const char *WageBase;
   // Description: Old law wage base increase entry name.
   static const char *OldLawWageBase;
   // Description: HI wage base increase entry name.
   static const char *HiWageBase;
public:
   AwbiDataIni( int newLastYear, int newMaxyears );
   void clear();
   void read();
   void setData();
   void setLastYear( int newYear );
   void write();
};
