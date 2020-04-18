// @doc FOINFOINI
// $Id: FoinfoIni.h 1.4.1.1 2012/03/08 06:55:16EST 277133 Development 277133(2012/03/08 06:55:49EST) $
// @module FoinfoIni.h |
//
// Declarations for field office info stored in ini file.

#ifndef __FOINFOINI_H
#define __FOINFOINI_H

#include "foinfo.h"

// @class The FieldOfficeInfoIni class manages the field office information in
//   an ini file for a pia program.
//
// @base public | FieldOfficeInfo

class FieldOfficeInfoIni : public FieldOfficeInfo
{
   // @access Private Members
   private:
      // @cmember Section title.
      static const char *section;
      // @cmember Field office name entry name.
      static const char *name;
      // @cmember Field office title entry name.
      static const char *title;
      // @cmember Field office address line 1 entry name.
      static const char *address1;
      // @cmember Field office address line 2 entry name.
      static const char *address2;
      // @cmember Field office address line 3 entry name.
      static const char *address3;
      // @cmember Field office address line 4 entry name.
      static const char *address4;
   // @access Public Members
   public:
      // @cmember Indicator for saving field office name.
      bool savename;
      // @cmember Indicator for saving field office title.
      bool savetitle;
      // @cmember Indicator for saving field office address line 1.
      bool saveaddress1;
      // @cmember Indicator for saving field office address line 1.
      bool saveaddress2;
      // @cmember Indicator for saving field office address line 1.
      bool saveaddress3;
      // @cmember Indicator for saving field office address line 1.
      bool saveaddress4;
   // @access Public Members
   public:
      // @cmember Constructor.
      FieldOfficeInfoIni();
      // @cmember Dummy function for ini version.
      void setData();
      // @cmember Reads field office info from ini file.
      void read  ();
      // @cmember Saves field office info to ini file.
      void write ();
};

#endif  // __FOINFOINI_H
