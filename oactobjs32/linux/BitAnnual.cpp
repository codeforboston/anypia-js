// $Id: BitAnnual.cpp 1.2 2009/02/17 07:13:29ACT 729915 Development 277133(2011/04/06 09:48:11ACT) $
//
// Functions to handle BitAnnual arrays for linux.

#include "oactcnst.h"
#include "BitAnnual.h"

using namespace std;

// GENERAL NOTE:
// When adding functions to this class, or changing the implementation
// of existing functions, be careful not to use square brackets ( [] )
// to access 'data' unless you're really sure of what you're doing.
// This is because there are different implementations of this class
// depending on whether you're using NT or Linux. Instead, use the
// setBit() and getBit() functions.

/// <summary>Initializes first and last years.</summary>
///
/// <param name="newBaseYear">New base year.</param>
/// <param name="newLastYear">New last year.</param>
///
/// <remarks>On the linux system, data is a vector of BitPacked's -- so the
/// constructor needs to know how many to create. On other systems (which
/// conform to the standard and have a BitSet class built in), data is a
/// BitSet and doesn't need any parameters because the default constructor
/// initializes all of the bits to zero.</remarks>
BitAnnual::BitAnnual( int newBaseYear, int newLastYear ) :
data((newLastYear - newBaseYear) / U_NUMBITS + 1),
baseYear(newBaseYear), lastYear(newLastYear)
{ }

/// <summary>Returns true if any bit is set, false otherwise.</summary>
///
/// <returns>True if any bit is set, false otherwise.</returns>
bool BitAnnual::any() const
{
   for (unsigned i = 0; i < data.size(); i++) {
      if (data[i].any())
         return true;
   }
   return false;
}

/// <summary>Zeroes out all data values.</summary>
void BitAnnual::deleteContents()
{
   for (unsigned i = 0; i < data.size(); i++)
      data[i].deleteContents();
}
