// $Id: AwbidatIni.cpp 1.9.1.1 2012/03/08 06:55:14EST 277133 Development 277133(2012/03/08 06:55:49EST) $
//
// Functions to handle average wage and benefit increase in an ini file.

#include "stdafx.h"
#include "AwbidatIni.h"
#include "Resource.h"
#include "comma.h"
#include "PiaException.h"

const char *AwbiDataIni::BenefitIncrease = "BenefitIncrease";
const char *AwbiDataIni::AverageWage = "AverageWage";
const char *AwbiDataIni::WageBase = "WageBase";
const char *AwbiDataIni::OldLawWageBase = "OldLawWageBase";
const char *AwbiDataIni::HiWageBase = "HiWageBase";

// Description: Initializes average wage and benefit increase info.
//
// Arguments:
//   newLastYear: New last year of data.
//   newMaxyears: New maximum year of projection.
AwbiDataIni::AwbiDataIni( int newLastYear, int newMaxyears ) :
AwbiData(newLastYear, newMaxyears)
{ }

// Description: Reads average wage and benefit increase info from registry or
//   ini file.
void AwbiDataIni::read()
{
   CString temp;  // temporary string
   
   temp = AfxGetApp()->GetProfileString(section, BenefitIncrease);
   if (temp.IsEmpty())
      throw PiaException(PIA_IDS_AWBI1);
   cpiinc[getLastYear() - 1] = atof(temp);
   temp = AfxGetApp()->GetProfileString(section, AverageWage);
   if (temp.IsEmpty())
      throw PiaException(PIA_IDS_AWBI1);
   fq[getLastYear() - 2] = atof(temp);
   temp = AfxGetApp()->GetProfileString(section, WageBase);
   if (temp.IsEmpty())
      throw PiaException(PIA_IDS_AWBI1);
   baseOasdi[getLastYear()] = atof(temp);
   temp = AfxGetApp()->GetProfileString(section, OldLawWageBase);
   if (temp.IsEmpty())
      throw PiaException(PIA_IDS_AWBI1);
   base77[getLastYear()] = atof(temp);
   temp = AfxGetApp()->GetProfileString(section, HiWageBase);
   if (temp.IsEmpty())
      throw PiaException(PIA_IDS_AWBI1);
   baseHi[getLastYear()] = atof(temp);
}

// Description: Saves average wage and benefit increase info to registry or
//   ini file.
void AwbiDataIni::write()
{
   AfxGetApp()->WriteProfileString(section, BenefitIncrease,
      poutNoComma(cpiinc[getLastYear() - 1], 1, 1).c_str());
   AfxGetApp()->WriteProfileString(section, AverageWage,
      poutNoComma(fq[getLastYear() - 2], 3, 2).c_str());
   AfxGetApp()->WriteProfileString(section, WageBase,
      poutNoComma(baseOasdi[getLastYear()], 3, 2).c_str());
   AfxGetApp()->WriteProfileString(section, OldLawWageBase,
      poutNoComma(base77[getLastYear()], 3, 2).c_str());
   AfxGetApp()->WriteProfileString(section, HiWageBase,
      poutNoComma(baseHi[getLastYear()], 3, 2).c_str());
}

// Description: Dummy function for ini version.
void AwbiDataIni::setData()
{ }

// Description: Sets year to read or write.
//
// Arguments:
//   newYear: New year.
void AwbiDataIni::setLastYear( int newYear )
{
   AwbiData::setLastYear(newYear);
   AfxFormatString1(section, PIA_IDS_HISTAMTTL,
      poutNoComma(newYear).c_str());
}

// Description: Clears all entries from registry.
void AwbiDataIni::clear()
{
   AfxGetApp()->WriteProfileString(section, BenefitIncrease, NULL);
   AfxGetApp()->WriteProfileString(section, AverageWage, NULL);
   AfxGetApp()->WriteProfileString(section, WageBase, NULL);
   AfxGetApp()->WriteProfileString(section, OldLawWageBase, NULL);
   AfxGetApp()->WriteProfileString(section, HiWageBase, NULL);
}
