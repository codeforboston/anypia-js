// $Id: CachupIni.cpp 1.6.1.1 2012/03/08 06:55:14EST 277133 Development 277133(2012/03/08 06:55:49EST) $
//
// Functions to handle catch-up benefit increases stored in an ini file.

#include "stdafx.h"
#include <math.h>
#include "CachupIni.h"
#include "Resource.h"
#include "comma.h"
#include "PiaException.h"

// Description: Initializes catch-up benefit increase file.
//
// Arguments:
//   newCstart: Starting year of catch-up benefit increases.
CatchupIni::CatchupIni( int newCstart ) : CatchupDoc(newCstart)
{
   for (int i = 0; i < 4; i++) {
      allownonzero[i] = false;
   }
}

// Arguments:
//   newCatchupDoc: New catch-up increases.
CatchupIni::CatchupIni( const CatchupDoc& newCatchupDoc ) :
CatchupDoc( newCatchupDoc )
{ }

// Description: Reads catch-up increases from registry or ini file.
//
// Arguments:
//   altNum: Desired alternative number (1-4).
void CatchupIni::read( int altNum )
{
   CString year[10], temp;  // temporary strings
   int i, j;  // loop counters

   setData(altNum);
   for (i = 0; i < 10; i++)
      year[i] = poutNoComma(i).c_str();
   for (i = 0; i < 10; i++) {
      for (j = 2; j < 10; j++) {
         AfxFormatString2(entry, PIA_IDS_2YEARS, year[i], year[j]);
         temp = AfxGetApp()->GetProfileString(section, entry);
         if (temp.IsEmpty())
            throw PiaException(PIA_IDS_READERR);
         catchup.set(catchup.getCstart() + i, catchup.getCstart() + j, 
            atof(temp));
      }
   }
}

// Description: Writes catch-up increases to registry or ini file.
void CatchupIni::write( int )
{
   CString year[10], temp;  // temporary strings
   int i, j;  // loop counters
   
   for (i = 0; i < 10; i++)
      year[i] = poutNoComma(i).c_str();
   for (i = 0; i < 10; i++) {
      for (j = 2; j < 10; j++) {
         AfxFormatString2(entry, PIA_IDS_2YEARS, year[i], year[j]);
         temp = poutNoComma(catchup.get(catchup.getCstart() + i,
            catchup.getCstart() + j), 1, 1).c_str();
         AfxGetApp()->WriteProfileString(section, entry, temp);
      }
   }
}

// Description: Deletes catch-up increases from registry or ini file.
void CatchupIni::clear()
{
   CString year[10];  // temporary strings
   int i, j;  // loop counters
   
   for (i = 0; i < 10; i++)
      year[i] = poutNoComma(i).c_str();
   for (i = 0; i < 10; i++) {
      for (j = 2; j < 10; j++) {
         AfxFormatString2(entry, PIA_IDS_2YEARS, year[i], year[j]);
         AfxGetApp()->WriteProfileString(section, entry, NULL);
      }
   }
}

// Description: Sets section name.
//
// Arguments:
//   altNum: Desired alternative number (1-4).
void CatchupIni::setData( int altNum )
{
   AfxFormatString1(section, PIA_IDS_CUPROJTTL,
      poutNoComma(altNum).c_str());
}

// Description: Sets catch-up increases from another Catchup.
//
// Arguments:
//   altNum: Desired alternative number (1-4)
//   newCatchup: The other Catchup.
void CatchupIni::setData( int altNum, const Catchup& newCatchup )
{
   setData(altNum);
   catchup = newCatchup;
}
