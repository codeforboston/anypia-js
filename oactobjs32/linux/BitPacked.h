// $Id: BitPacked.h 1.2 2009/02/17 07:13:30EST 729915 Development  $
//
// Definition of class to manage 32 annual bits (one word) as bools.

#ifndef BITPACKED_H
#define BITPACKED_H

#include <climits>

/// <summary>Number of bits in an unsigned int.</summary>
const int U_NUMBITS = sizeof(unsigned int) * CHAR_BIT;

// {group:Miscellaneous Classes}
/// <summary>Holds 32 annual bits (as bools) in one word (4 bytes).</summary>
///
/// <remarks>This class is used in the Linux version of the library, where a
///   vector of BitPacked structures is used to hold the array of annual bits.
///   This class is unused in the NT version of the library.</remarks>
class BitPacked
{
   protected:
      // Array of bits (bools) as unsigned int.
      unsigned bits;
   public:
      BitPacked();
      bool any() const;
      void deleteContents();
      bool get( int index ) const;
      void set( int index, int value );
};

#endif   // BITPACKED_H
