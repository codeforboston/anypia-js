// $Id: BitAnnualInlines.h 1.2 2009/02/17 07:13:30EST 729915 Development  $
//
// Inline functions for class to manage an array of annual bits for Windows.

#pragma once
#ifndef __BITANNUALINLINES_H
#define __BITANNUALINLINES_H   1   // Prevent multiple includes

/// <summary>Returns one constant value of data.</summary>
///
/// <returns>One constant value of data.</returns>
///
/// <exception>PiaException of type PIA_IDS_BITANN1 if year is out of range
///   (only in debug mode).</exception>
///
/// <param name="year">Year for which data is desired.</param>
inline bool BitAnnual::getBit( int year ) const
{
#if !defined(NDEBUG)
   if (year < baseYear || year > lastYear) {
      throw PiaException(PIA_IDS_BITANN1);
   }
#endif
   int indexYear = year - baseYear;
   return data[indexYear / U_NUMBITS].get(indexYear % U_NUMBITS);
}

/// <summary>Sets one value of data.</summary>
///
/// <exception>PiaException of type PIA_IDS_BITANN1 if year is out of range
///   (only in debug mode).</exception>
///
/// <param name="year">Year for which data is to be set.</param>
/// <param name="bit">Value to set (0 for false, any other value for true).
/// </param>
inline void BitAnnual::setBit( int year, int bit )
{
#if !defined(NDEBUG)
   if (year < baseYear || year > lastYear) {
      throw PiaException(PIA_IDS_BITANN1);
   }
#endif
   int indexYear = year - baseYear;
   data[indexYear / U_NUMBITS].set(indexYear % U_NUMBITS, bit);
}

#endif    // __BITANNUALINLINES_H
