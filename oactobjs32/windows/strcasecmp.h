// $Id: strcasecmp.h 1.2 2009/01/13 08:47:50EST 729915 Development  $
//
// Declarations needed for gnu string functions not included in MSVC.

#pragma once
#if !defined __STRCASECMP_H
#define __STRCASECMP_H

#if defined(__cplusplus)
extern "C" {
#endif

/// <summary>Compare S1 and S2, ignoring case, returning less than, equal
/// to or greater than zero if S1 is lexicographically less than, equal to,
/// or greater than S2.</summary>
int strcasecmp( const char *s1, const char *s2 );
/// <summary>Compare S1 and S2, ignoring case, returning less than, equal
/// to or greater than zero if S1 is lexicographically less than, equal to,
/// or greater than S2.  Limited to first n characters.</summary>
int strncasecmp( const char *s1, const char *s2, unsigned n );

#if defined(__cplusplus)
}
#endif

#endif  // __STRCASECMP_H
