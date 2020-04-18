// Functions for the <see cref="BitAnnual"/> class to manage an array of
// annual bits for Windows.
//
// $Id: BitAnnualBase.cpp 1.10 2012/08/03 13:57:12EDT 044579 Development  $

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

/// <summary>Initializes the first and last years and sets all data values to
/// false.</summary>
///
/// <remarks>On the linux system, data is a vector of BitPacked's -- so the
/// constructor needs to know how many to create. On other systems (which
/// conform to the standard and have a std::bitset class built in), data is a
/// std::bitset and doesn't need parameters because the default
/// constructor initializes all of the bits to zero.</remarks>
///
/// <param name="newBaseYear">New base year.</param>
/// <param name="newLastYear">New last year.</param>
BitAnnual::BitAnnual( int newBaseYear, int newLastYear ) :
theData(), baseYear(newBaseYear), lastYear(newLastYear)
{ }

/// <summary>Copies all values from the BitAnnual argument to this instance.
/// </summary>
///
/// <remarks>On the linux system, data is a vector of BitPacked's -- so the
/// constructor needs to know how many to create. On other systems (which
/// conform to the standard and have a std::bitset class built in), data is a
/// std::bitset and doesn't need parameters because the default
/// constructor initializes all of the bits to zero.</remarks>
///
/// <param name="bitAnnual">The BitAnnual to copy from.</param>
BitAnnual::BitAnnual( const BitAnnual& bitAnnual ) :
theData(bitAnnual.theData), baseYear(bitAnnual.baseYear),
lastYear(bitAnnual.lastYear)
{ }
