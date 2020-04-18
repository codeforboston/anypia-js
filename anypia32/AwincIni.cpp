// $Id: AwincIni.cpp 1.13.1.2 2016/12/07 08:10:33EST 277133 Development  $
//
// Functions to handle projected average wage increases in an ini file.

#include "stdafx.h"
#include "AwincIni.h"
#include "Resource.h"
#include "comma.h"
#include "PiaException.h"
#include "AwincNonFile.h"

using namespace std;

const char *AwincIni::sectionTitle = "Title";

// Description: Initializes projected average wage increase info.
//
// Arguments:
//   newIstart: Starting year of average wage increases.
//   newMaxyears: Maximum number of years of average wage increases.
AwincIni::AwincIni( int newIstart, int newMaxyears ) :
AwincDoc(newIstart, newMaxyears)
{ }

// Arguments:
//   newAwincDoc: New average wage increase info.
AwincIni::AwincIni( const AwincDoc& newAwincDoc ) : AwincDoc(newAwincDoc)
{ }

// Description: Reads average wage increases from registry or ini file.
//
// Throws: PiaException of type PIA_IDS_FQINC3 if any expected value is not
//   available.
void AwincIni::read( int altNum )
{
   CString temp;  // temporary string

   setData(altNum);
   for (int i = 0; i <= AwincNonFile::NUMPROJYEARS; i++) {
      AfxFormatString1(entry, PIA_IDS_YEAR, poutNoComma(i + 1).c_str());
      temp = AfxGetApp()->GetProfileString(section, entry);
      if (temp.IsEmpty())
         throw PiaException(PIA_IDS_FQINC3);
      awinc[getFirstYear() + i] = atof(temp);
   }
   for (int i = getFirstYear() + AwincNonFile::NUMPROJYEARS + 1; i <= awinc.getLastYear(); i++) {
     awinc[i] = awinc[getFirstYear() + AwincNonFile::NUMPROJYEARS];
   }
   awincTitle = AfxGetApp()->GetProfileString(section, sectionTitle);
}

// Description: Write data to registry or ini file.
void AwincIni::write( int )
{
   CString temp;  // temporary string

   for (int i = 0; i <= AwincNonFile::NUMPROJYEARS; i++) {
      AfxFormatString1(entry, PIA_IDS_YEAR, poutNoComma(i + 1).c_str());
      AfxGetApp()->WriteProfileString(section, entry,
         poutNoComma(awinc[getFirstYear() + i], 6, 6).c_str());
   }
   AfxGetApp()->WriteProfileString(section, sectionTitle,
      CString(awincTitle.c_str()));
}

// Description: Sets section name.
//
// Arguments:
//   altNum: Desired alternative number (1-4).
void AwincIni::setData( int altNum )
{
   AfxFormatString1(section, PIA_IDS_AVGWGTTL, poutNoComma(altNum).c_str());
}

// Description: Sets data for one alternative.
//
// Arguments:
//   altNum: Desired alternative number (1-4).
//   newData: Data to use.
void AwincIni::setData( int altNum, const DoubleAnnual& newData )
{
   setData(altNum);
   for (int i = getFirstYear();
     i <= getFirstYear() + AwincNonFile::NUMPROJYEARS; i++) {
      awinc[i] = newData[i];
   }
   for (int i = getFirstYear() + AwincNonFile::NUMPROJYEARS + 1; i <= awinc.getLastYear(); i++) {
     awinc[i] = newData[getFirstYear() + AwincNonFile::NUMPROJYEARS];
   }
}

// Description: Dummy function.
void AwincIni::setTitle( int )
{ }

// Description: Sets title for one alternative.
//
// Arguments:
//   newTitle: Title to use.
void AwincIni::setTitle( int, const std::string& newTitle )
{
   awincTitle = newTitle;
}

// Description: Clears all entries from registry.
void AwincIni::clear()
{
   CString temp;  // temporary string

   for (int i = 0; i <= AwincNonFile::NUMPROJYEARS; i++) {
      AfxFormatString1(entry, PIA_IDS_YEAR, poutNoComma(i + 1).c_str());
      AfxGetApp()->WriteProfileString(section, entry, NULL);
      // clear values in memory
      awinc[getFirstYear() + i] = 0.0;
   }
   for (int i = getFirstYear() + AwincNonFile::NUMPROJYEARS + 1; i <= awinc.getLastYear(); i++) {
      awinc[i] = 0.0;
   }
   AfxGetApp()->WriteProfileString(section, sectionTitle, NULL);
   awincTitle = "";
}
