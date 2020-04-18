// $Id: CachupIni.h 1.4.1.1 2012/03/08 06:55:00EST 277133 Development 277133(2012/03/08 06:55:45EST) $
//
// Declarations needed for class to manage catch-up benefit increases in ini
// file.

#ifndef __CATCHUPINI_H
#define __CATCHUPINI_H

#include "cachupf.h"

// Description: Manages catch-up benefit increases in the registry or an ini
//   file.
//
// Remarks: Manages catch-up benefit increases in the registry or an ini file.
class CatchupIni : public CatchupDoc
{
   protected:
      // Ini section heading.
      CString section;
      // Name of yearly entry.
      CString entry;
   public:
      CatchupIni( int newcstart );
      CatchupIni( const CatchupDoc& newCatchupDoc );
      void clear();
      void read( int altNum );
      void setData( int altNum );
      void setData( int altNum, const Catchup& newCatchup );
      void write( int );
};

#endif  // __CATCHUPINI_H
