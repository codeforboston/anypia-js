// $Id: Floor.h 1.3 2009/01/13 08:47:50EST 729915 Development  $
//
// Declarations needed for floor function for Windows.

#pragma once
#ifndef __FLOOR_H
#define __FLOOR_H

/// <summary>Calls the floor function.</summary>
///
/// <returns>The greatest integer in the argument.</returns>
///
/// <param name="amount">Amount to be floored.</param>
inline double FLOOR( double amount )
{ return floor(amount); }

#endif  // __FLOOR_H
