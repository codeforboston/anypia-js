// $Id: isspace.h 1.3 2009/01/13 08:47:50EST 729915 Development  $
//
// Functions to classify a character for Windows.

#pragma once
#ifndef __ISSPACE_H
#define __ISSPACE_H

#include <locale>
// Use the default locale.
static std::locale loc;

/// <summary>Returns true if argument is a space.</summary>
///
/// <returns>True if argument is a space.</returns>
///
/// <remarks>The Windows version uses the C++ isspace function.</remarks>
///
/// <param name="ch">The character to test.</param>
inline bool ISSPACE( char ch )
{ return std::isspace(ch, loc); }

#endif  // __ISSPACE_H
