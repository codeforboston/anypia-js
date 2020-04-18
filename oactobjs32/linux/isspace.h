// $Id: isspace.h 1.2 2009/02/17 07:13:31EST 729915 Development  $
//
// Functions to classify a character for linux.

#pragma once
#ifndef __ISSPACE_H
#define __ISSPACE_H

#include <cctype>

/// <summary>Returns true if argument is a space.</summary>
///
/// <returns>True if argument is a space.</returns>
///
/// <remarks>The linux version uses the C isspace function.</remarks>
inline bool ISSPACE( char a )
{ return isspace(a); }

#endif  // __ISSPACE_H
