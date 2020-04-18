// $Id: BiprojIni.cpp 1.14.1.2 2016/12/07 08:10:33EST 277133 Development  $
//
// Functions to handle projected benefit increases in an ini file

#include "stdafx.h"
#include "BiprojIni.h"
#include "Resource.h"
#include "comma.h"
#include "PiaException.h"
#include "BiprojNonFile.h"

using namespace std;

const char *BiprojIni::sectionTitle = "Title";

// Description: Initializes projected benefit increase info
//
// Arguments:
//   newIstart: Starting year of benefit increases.
//   newMaxyears: Maximum number of years of benefit increases
BiprojIni::BiprojIni( int newIstart, int newMaxyears ) :
Biproj(newIstart, newMaxyears)
{ }

// Description: Sets projected benefit increase info from another Biproj.
//
// Arguments:
//   newBiproj: New benefit increase info.
BiprojIni::BiprojIni( const Biproj& newBiproj ) : Biproj(newBiproj)
{ }

// Description: Read benefit increases from an ini file.
//
// Throws: PiaException of type PIA_IDS_CPIINC3 if there are no (or not enough)
//   benefit increases.
//
// Arguments:
//   altNum: Desired alternative number (1-4).
void BiprojIni::read( int altNum )
{
   CString temp;  // temporary string

   setData(altNum);
   for (int i = 0; i <= BiprojNonFile::NUMPROJYEARS; i++) {
      AfxFormatString1(entry, PIA_IDS_YEAR, poutNoComma(i + 1).c_str());
      temp = AfxGetApp()->GetProfileString(section, entry);
      if (temp.IsEmpty())
         throw PiaException(PIA_IDS_CPIINC3);
      theData[getFirstYear() + i] = atof(temp);
   }
   for (int i = getFirstYear() + BiprojNonFile::NUMPROJYEARS + 1; i <= theData.getLastYear(); i++){
     theData[i] = theData[getFirstYear() + BiprojNonFile::NUMPROJYEARS];
   }
   biprojTitle = AfxGetApp()->GetProfileString(section, sectionTitle);
}

// Description: Write benefit increases to registry or an ini file.
void BiprojIni::write( int )
{
   for (int i = 0; i <= BiprojNonFile::NUMPROJYEARS; i++) {
      AfxFormatString1(entry, PIA_IDS_YEAR, poutNoComma(i + 1).c_str());
      AfxGetApp()->WriteProfileString(section, entry,
         poutNoComma(theData[getFirstYear() + i], 1, 1).c_str());
   }
   AfxGetApp()->WriteProfileString(section, sectionTitle,
      CString(biprojTitle.c_str()));
}

// Description: Sets section name.
//
// Arguments:
//   altNum: Desired alternative number (1-4).
void BiprojIni::setData( int altNum )
{
   AfxFormatString1(section, PIA_IDS_BIPROJTTL, poutNoComma(altNum).c_str());
}

// Description: Sets data for one alternative, then updates the current data.
//
// Arguments:
//   altNum: Desired alternative number (1-4).
//   newData: Data to use.
void BiprojIni::setData( int altNum, const DoubleAnnual& newData )
{
  setData(altNum);
  for (int i = getFirstYear();
    i <= getFirstYear() + BiprojNonFile::NUMPROJYEARS; i++) {
    theData[i] = newData[i];
  }
  for (int i = getFirstYear() + BiprojNonFile::NUMPROJYEARS + 1; i <= theData.getLastYear(); i++){
    theData[i] = theData[getFirstYear() + BiprojNonFile::NUMPROJYEARS];
  }
}

// Description: Dummy function.
void BiprojIni::setTitle( int )
{ }

// Description: Sets title for one alternative.
//
// Arguments:
//   altNum: Desired alternative number (1-4).
//   newTitle: Title to use.
void BiprojIni::setTitle( int altNum, const std::string& newTitle )
{
   biprojTitle = newTitle;
}

// Description: Clears all entries from registry.
void BiprojIni::clear()
{
   CString temp;  // temporary string

   for (int i = 0; i <= BiprojNonFile::NUMPROJYEARS; i++) {
      AfxFormatString1(entry, PIA_IDS_YEAR, poutNoComma(i + 1).c_str());
      AfxGetApp()->WriteProfileString(section, entry, NULL);
      // clear values in memory
      theData[getFirstYear() + i] = 0.0;
   }
   for (int i = getFirstYear() + BiprojNonFile::NUMPROJYEARS + 1; i <= theData.getLastYear(); i++){
     theData[i] = 0.0;
   }
   AfxGetApp()->WriteProfileString(section, sectionTitle, NULL);
   biprojTitle = "";
}
