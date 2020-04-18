// $Id: BitPacked.cpp 1.2 2009/02/17 07:13:30EST 729915 Development  $
//
// Functions for BitPacked class.

#include "BitPacked.h"

/// <summary>Initialize all values to 0.</summary>
BitPacked::BitPacked() : bits(0u)
{ }

/// <summary>Returns true if any bit is set, false otherwise.</summary>
///
/// <returns>True if any bit is set, false otherwise.</returns>
bool BitPacked::any() const
{
   return (bits != 0u);
}

/// <summary>Sets all bits to zero.</summary>
void BitPacked::deleteContents()
{
   bits = 0u;
}

/// <summary>Return a bool.</summary>
///
/// <returns>One bool from the bitfield.</returns>
///
/// <param name="index">Index of bool (zero to U_NUMBITS-1).</param>
bool BitPacked::get( int index ) const
{
   unsigned mask = 1u << (U_NUMBITS - 1 - index);
   return static_cast<bool>(bits & mask);
}

/// <summary>Sets a bit.</summary>
///
/// <param name="index">Index of year.</param>
/// <param name="value">New value to use (0 = false, otherwise = true).</param>
void BitPacked::set( int index, int value )
{
   unsigned mask = 1u << (U_NUMBITS - 1 - index);
   if (value == 0)
      bits &= ~mask;
   else
      bits |= mask;
}
