// Inline functions for the <see cref="BitAnnual"/> class to manage an array
// of annual bits for Windows.
//
// $Id: BitAnnualInlines.h 1.7 2012/08/03 13:57:13EDT 044579 Development  $

#pragma once

/// <summary>Returns one constant value of data.</summary>
///
/// <returns>One constant value of data.</returns>
///
/// <exception cref="PiaException"><see cref="PiaException"/> of type
/// <see cref="PIA_IDS_BITANN1"/> if year is out of range (only in debug
/// mode).</exception>
///
/// <param name="year">Year for which data is desired.</param>
inline bool BitAnnual::getBit( int year ) const
{
#if !defined(NDEBUG)
  if (year < baseYear || year > lastYear) {
    throw PiaException(PIA_IDS_BITANN1);
  }
#endif
  return theData.test(year - baseYear);
}

/// <summary>Sets one value of data.</summary>
///
/// <exception cref="PiaException"><see cref="PiaException"/> of type
/// <see cref="PIA_IDS_BITANN1"/> if year is out of range (only in debug
/// mode).</exception>
///
/// <param name="year">Year for which data is to be set.</param>
/// <param name="bit">Value to set (0 for false, anything else for true).
/// </param>
inline void BitAnnual::setBit( int year, int bit )
{
#if !defined(NDEBUG)
  if (year < baseYear || year > lastYear) {
    throw PiaException(PIA_IDS_BITANN1);
  }
#endif
  theData.set(year - baseYear, (bit > 0));
}

/// <summary>Returns true if at least one bit is set, false otherwise.
/// </summary>
///
/// <returns>True if at least one bit is set, false otherwise.</returns>
inline bool BitAnnual::any() const
{ return theData.any(); }

/// <summary>Zeroes out all data values.</summary>
inline void BitAnnual::deleteContents()
{ theData.reset(); }
