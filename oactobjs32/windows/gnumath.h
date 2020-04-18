// $Id: gnumath.h 1.1 2003/05/22 09:22:04EDT sfmckay Exp  $
//
// Math functions from GNU compiler.

#pragma once

#if defined(__cplusplus)
extern "C" {
#endif

double erf( double x );
double erfc( double x );
double rint( double x );

#if defined(__cplusplus)
}
#endif
