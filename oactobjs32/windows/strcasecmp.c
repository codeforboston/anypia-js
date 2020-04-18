// $Id: strcasecmp.c 1.2 2009/01/13 08:47:50EST 729915 Development  $
//
// Declarations needed for gnu string functions not included in MSVC.
//
// Copyright (C) 1991, 1992, 1995, 1996 Free Software Foundation, Inc.
// This file is part of the GNU C Library.

#include <ctype.h>
#include "strcasecmp.h"

/// <summary>Compare two strings, ignoring case.</summary>
///
/// <returns>Less than, equal to, or greater than zero if s1 is
/// lexicographically less than, equal to, or greater than s2.</returns>
///
/// <param name="s1">First string to compare.</param>
/// <param name="s2">Second string to compare.</param>
int strcasecmp( const char *s1, const char *s2 )
{
  register const unsigned char *p1 = (const unsigned char *) s1;
  register const unsigned char *p2 = (const unsigned char *) s2;
  unsigned char c1, c2;

  if (p1 == p2)
    return 0;

  do {
    c1 = tolower (*p1++);
    c2 = tolower (*p2++);
    if (c1 == '\0')
      break;
  // skip over matching letters
  } while (c1 == c2);

  return c1 - c2;
}

/// <summary>Compare two strings, ignoring case, limited to first n
/// characters.</summary>
///
/// <returns>Less than, equal to, or greater than zero if s1 is
/// lexicographically less than, equal to, or greater than s2.</returns>
///
/// <param name="s1">First string to compare.</param>
/// <param name="s2">Second string to compare.</param>
/// <param name="n">Limit on number of characters to compare.</param>
int strncasecmp( const char *s1, const char *s2, unsigned n )
{
  register const unsigned char *p1 = (const unsigned char *) s1;
  register const unsigned char *p2 = (const unsigned char *) s2;
  unsigned char c1, c2;
  unsigned count = 0;

  if (p1 == p2)
    return 0;

  do {
    c1 = tolower (*p1++);
    c2 = tolower (*p2++);
    if (c1 == '\0')
      break;
  // skip over matching letters
  } while (c1 == c2 && ++count < n);

  return c1 - c2;
}
