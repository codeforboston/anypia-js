// $Id: BiprojIni.h 1.9.1.1 2012/03/08 06:55:16EST 277133 Development 277133(2012/03/08 06:55:49EST) $
//
// Declarations for class to manage projected benefit increases in ini file.

#pragma once
#ifndef __BIPROJINI_H
#define __BIPROJINI_H

#include "biproj.h"

// Description: Manages the file of projected benefit increases
//   in the registry or an ini file.
//
// Remarks: Manages the file of projected benefit increases
//   in the registry or an ini file.
class BiprojIni : public Biproj
{
   protected:
      // Ini section heading.
      CString section;
      // Name of yearly entry.
      CString entry;
      // Name of title entry.
      static const char *sectionTitle;
   public:
      BiprojIni( int newIstart, int newMaxyears );
      BiprojIni( const Biproj& newBiproj );
      void clear();
      void read( int altNum );
      void setData ( int altNum );
      void setData ( int altNum, const DoubleAnnual& newData );
      void setTitle( int altNum );
      void setTitle( int altNum, const std::string& newTitle );
      void write( int );
};

#endif  // __BIPROJINI_H
