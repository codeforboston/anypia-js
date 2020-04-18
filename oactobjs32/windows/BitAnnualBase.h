// Declarations for the <see cref="BitAnnual"/> class to manage an array of
// annual bits for Windows.
//
// $Id: BitAnnualBase.h 1.7 2011/08/11 15:21:15EDT 044579 Development  $

#pragma once

#include <bitset>

/// <summary>Size to use for bit array in <see cref="BitAnnual"/> (from 1937 to
/// 2100).</summary>
const int MAX_BITSET_SIZE = 164;

/// <summary>Bit array used in <see cref="BitAnnual"/> (a std::bitset).
/// </summary>
typedef std::bitset< MAX_BITSET_SIZE > BitAnnualData;
