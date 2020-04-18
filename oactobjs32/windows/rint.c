// $Id: rint.c 1.2 2009/01/13 08:47:50EST 729915 Development  $
//
// Math functions from GNU compiler.

#pragma once
#include "gnumath.h"

/// <summary>Rounds to the nearest integer by adding 0.5 to a double
/// or floating point number and casting to an integer, truncating the
/// decimal.</summary>
///
/// <returns>The argument rounded to the nearest integer.</returns>
///
/// <param name="x">The value to be rounded.</param>
double rint( double x )
{
  return (double)((int)(x + 0.5));
}
