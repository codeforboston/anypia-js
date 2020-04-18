// $Id: getopt.h 1.4 2009/01/22 16:53:08EST 044579 Development  $
//
// Declarations for getopt.
//
// Copyright (C) 1989,90,91,92,93,94,96,97 Free Software Foundation, Inc.
// This file is part of the GNU C Library.

#pragma once
#ifndef _GETOPT_H
#define _GETOPT_H 1

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>For communication from getopt to the caller.</summary>
///
/// <remarks>When getopt finds an option that takes an argument,
/// the argument value is returned here.
/// Also, when ordering is RETURN_IN_ORDER,
/// each non-option argv-element is returned here.</remarks>
extern char *optarg;

/// <summary>Index in argv of the next element to be scanned.</summary>
///
/// <remarks>This is used for communication to and from the caller
/// and for communication between successive calls to getopt.
///
/// On entry to getopt, zero means this is the first call; initialize.
///
/// When getopt returns -1, this is the index of the first of the
/// non-option elements that the caller should itself scan.
///
/// Otherwise, optind communicates from one call to the next
/// how much of argv has been scanned so far.</remarks>
extern int optind;

/// <summary>Callers store zero here to inhibit the error message getopt
/// prints for unrecognized options.</summary>
extern int opterr;

/// <summary>Set to an option character which was unrecognized.</summary>
extern int optopt;

/// <summary>Describe the long-named options requested by the application.
/// </summary>
///
/// <remarks>The long_options argument to getopt_long or getopt_long_only is a
/// vector of OptionStruct's terminated by an element containing a name which
/// is zero.
///
/// To have a long-named option do something other than set an int to a
/// compiled-in constant, such as set a value from optarg, set the option's
/// flag field to zero and its val field to a nonzero value (the equivalent
/// single-letter option character, if there is one).  For long options that
/// have a zero flag field, getopt returns the contents of the val field.
/// </remarks>
struct OptionStruct
{
  // Name of option.
  const char *name;
  // <summary>Indicator for required/optional argument.</summary>
  //
  // <remarks>no_argument (or 0) if the option does not take an argument.
  // required_argument (or 1) if the option requires an argument.
  // optional_argument (or 2) if the option takes an optional argument.
  // has_arg can't be an enum because some compilers complain about
  // type mismatches in all the code that assumes it is an int.</remarks>
  int has_arg;
  // <summary>If this field is not NULL, it points to a variable
  // that is set to the value given in the field val when the option is
  // found, but left unchanged if the option is not found.</summary>
  int *flag;
  // <summary>Value to use as described in remarks.</summary>
  int val;
};

// <summary>Indicator that the getopt option does not take an argument.
// </summary>
//
// <remarks>Used in the has_arg field of OptionStruct.</remarks>
#define no_argument       0
// <summary>Indicator that the getopt option requires an argument.</summary>
//
// <remarks>Used in the has_arg field of OptionStruct.</remarks>
#define required_argument 1
// <summary>Indicator that the getopt option takes an optional argument.
// </summary>
//
// <remarks>Used in the has_arg field of OptionStruct.</remarks>
#define optional_argument 2

extern int getopt( int argc, char *const *argv, const char *shortopts );
extern int getopt_long( int argc, char *const *argv, const char *shortopts,
  const struct OptionStruct *longopts, int *longind );
extern int getopt_long_only( int argc, char *const *argv,
  const char *shortopts, const struct OptionStruct *longopts, int *longind );

#ifdef __cplusplus
}
#endif

#endif /* _GETOPT_H */
