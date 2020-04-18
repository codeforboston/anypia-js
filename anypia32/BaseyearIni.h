// $Id: BaseyearIni.h 1.4.1.1 2012/03/08 06:55:06EST 277133 Development 277133(2012/03/08 06:55:47EST) $
//
// Declarations for baseyear stored in ini file.

#ifndef __BASEYEARINI_H
#define __BASEYEARINI_H

#include "baseyear.h"

// Description: Manages the computation year in an ini file
//   for a pia program.
//
// Remarks: Manages the computation year in an ini file
//   for a pia program.
class BaseYearIni : public BaseYear
{
   protected:
      // Ini section heading.
      static const char *section;
      // Name of entry.
      static const char *entry;
   public:
      BaseYearIni();
      void clear();
      void read();
      void write();
};

#endif  // __BASEYEARINI_H
