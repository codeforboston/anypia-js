// $Id: getopt_long.c 1.3 2009/01/13 08:47:48EST 729915 Development  $ */
//
// getopt_long and getopt_long_only entry points for GNU getopt.
//
// Copyright (C) 1987,88,89,90,91,92,93,94,96,97,98
// Free Software Foundation, Inc.
// This file is part of the GNU C Library.
//
// The GNU C Library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public License as
// published by the Free Software Foundation; either version 2 of the
// License, or (at your option) any later version.
//
// The GNU C Library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with the GNU C Library; see the file COPYING.LIB.  If not,
// write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
// Boston, MA 02111-1307, USA.

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "getopt.h"
#include <stdio.h>
extern int _getopt_internal( int argc, char *const *argv,
  const char *optstring, const struct OptionStruct *longopts, int *longind,
  int long_only );

/* Comment out all this code if we are using the GNU C Library, and are not
   actually compiling the library itself.  This code is part of the GNU C
   Library, but also included in many other GNU distributions.  Compiling
   and linking in this code is a waste when using the GNU C library
   (especially if it is a shared library).  Rather than having every GNU
   program understand `configure --with-gnu-libc' and omit the object files,
   it is simpler to just do this in the source for each such file.  */

#define GETOPT_INTERFACE_VERSION 2
#if !defined _LIBC && defined __GLIBC__ && __GLIBC__ >= 2
#include <gnu-versions.h>
#if _GNU_GETOPT_INTERFACE_VERSION == GETOPT_INTERFACE_VERSION
#define ELIDE_CODE
#endif
#endif

#ifndef ELIDE_CODE


/* This needs to come after some library #include
   to get __GNU_LIBRARY__ defined.  */
#ifdef __GNU_LIBRARY__
#include <stdlib.h>
#endif

#ifndef NULL
#define NULL 0
#endif

/// <summary>Scan elements of argv (whose length is argc) for option
/// characters given in optstring.</summary>
///
/// <remarks>This simply calls _getopt_internal.</remarks>
///
/// <returns>An option character.</returns>
///
/// <param name="argc">Number of elements of argv.</param>
/// <param name="argv">Array of strings to parse.</param>
/// <param name="options">Options characters.</param>
/// <param name="long_options">Vector of `struct option' terminated by an
///     element containing a name which is zero.</param>
/// <param name="opt_index">Returns the index in LONGOPT of the long-named
///     option found. It is only valid when a long-named option has been
///     found by the most recent call.</param>
int getopt_long( int argc, char *const *argv, const char *options,
const struct OptionStruct *long_options, int *opt_index )
{
  return _getopt_internal(argc, argv, options, long_options, opt_index, 0);
}

/// <summary>Scan elements of argv (whose length is argc) for option
/// characters given in optstring.</summary>
///
/// <remarks>Like getopt_long, but '-' as well as '--' can indicate a long
/// option. If an option that starts with '-' (not '--') doesn't match a long
/// option, but does match a short option, it is parsed as a short option
/// instead. This simply calls _getopt_internal.</remarks>
///
/// <returns>An option character.</returns>
///
/// <param name="argc">Number of elements of argv.</param>
/// <param name="argv">Array of strings to parse.</param>
/// <param name="options">Options characters.</param>
/// <param name="long_options">Vector of OptionStruct's terminated by an
///     element containing a name which is zero.</param>
/// <param name="opt_index">Returns the index in long_options of the
///     long-named option found. It is only valid when a long-named option
///     has been found by the most recent call.</param>
int getopt_long_only( int argc, char *const *argv, const char *options,
const struct OptionStruct *long_options, int *opt_index )
{
  return _getopt_internal(argc, argv, options, long_options, opt_index, 1);
}


#endif	/* Not ELIDE_CODE.  */

#ifndef TEST
#else

#include <stdio.h>

int main( int argc, char **argv )
{
  int c;
  int digit_optind = 0;

  while (1)
    {
      int this_option_optind = optind ? optind : 1;
      int option_index = 0;
      static struct option long_options[] =
      {
	{"add", 1, 0, 0},
	{"append", 0, 0, 0},
	{"delete", 1, 0, 0},
	{"verbose", 0, 0, 0},
	{"create", 0, 0, 0},
	{"file", 1, 0, 0},
	{0, 0, 0, 0}
      };

      c = getopt_long (argc, argv, "abc:d:0123456789",
		       long_options, &option_index);
      if (c == -1)
	break;

      switch (c)
	{
	case 0:
	  printf ("option %s", long_options[option_index].name);
	  if (optarg)
	    printf (" with arg %s", optarg);
	  printf ("\n");
	  break;

	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	  if (digit_optind != 0 && digit_optind != this_option_optind)
	    printf ("digits occur in two different argv-elements.\n");
	  digit_optind = this_option_optind;
	  printf ("option %c\n", c);
	  break;

	case 'a':
	  printf ("option a\n");
	  break;

	case 'b':
	  printf ("option b\n");
	  break;

	case 'c':
	  printf ("option c with value `%s'\n", optarg);
	  break;

	case 'd':
	  printf ("option d with value `%s'\n", optarg);
	  break;

	case '?':
	  break;

	default:
	  printf ("?? getopt returned character code 0%o ??\n", c);
	}
    }

  if (optind < argc)
    {
      printf ("non-option ARGV-elements: ");
      while (optind < argc)
	printf ("%s ", argv[optind++]);
      printf ("\n");
    }

  exit (0);
}

#endif /* TEST */
