// $Id: anypiab.cpp 1.6 2007/05/22 09:34:14EDT 277133 Development  $
//
// This program reads a series of cases in standard anypia format, computes
// a primary insurance amount and associated data for each one, and prints
// the results to a file named "output".  The particular variables that are
// printed can be specified in function savecase, at the end of this file.

#include <iostream>
#include "AnypiabDoc.h"
#include "AnypiaTestDoc.h"
#include "Trace.h"
#include "TextWriterTraceListener.h"

using namespace std;

int main( int argc, char **argv )
{
   int ierr = 0;
   TextWriterTraceListener outputLog(&cout);
   Trace::getListeners().push_back(&outputLog);
#if defined(ANYPIAB)
   AnypiabDoc theDoc;
#else
   AnypiaTestDoc theDoc;
#endif
   ierr = theDoc.calculate();
   return(ierr);
}
