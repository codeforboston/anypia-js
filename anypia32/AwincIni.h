// $Id: AwincIni.h 1.6.1.1 2012/03/08 06:55:15EST 277133 Development 277133(2012/03/08 06:55:49EST) $
//
// Declarations for class to manage average wage increases in ini file.

#pragma once
#ifndef __AWINCINI_H
#define __AWINCINI_H

#include "AwincDoc.h"

// Description: Manages the file of projected average wage
//   increases stored in the registry or an ini file.
//
// Remarks: Manages the file of projected average wage
//   increases stored in the registry or an ini file.
class AwincIni : public AwincDoc
{
   protected:
      // Ini section heading.
      CString section;
      // Name of yearly entry.
      CString entry;
      // Name of title entry.
      static const char *sectionTitle;
   public:
      AwincIni( int newIstart, int newMaxyears );
      AwincIni( const AwincDoc& newAwincDoc );
      const AwincIni& operator=( const AwincDoc& newAwincDoc );
      void clear();
      void read( int altnum );
      void setData( int altnum );
      void setData( int altNum, const DoubleAnnual& newData );
      void setTitle( int altNum );
      void setTitle( int altNum, const std::string& newTitle );
      void write( int );
};

#endif  // __AWINCINI_H
