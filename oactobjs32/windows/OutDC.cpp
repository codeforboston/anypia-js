// Functions needed for the <see cref="OutDC80"/> class to write to a device
// context (DC).

// $Id: OutDC.cpp 1.6 2010/11/22 16:15:24ACT 044579 Development  $

#ifdef _DLL
/// <summary>Use the AFXDLL library, which contains MFC in a DLL.</summary>
#define _AFXDLL
#endif
#include <afxwin.h>
#include "OutDC.h"

using namespace std;

/// <summary>Initializes a new OutDC.</summary>
OutDC80::OutDC80() : Out80("", ""), ht(0), y(0), x(10), pDC(NULL)
{ }

/// <summary>Prints one line of text with a newline.</summary>
///
/// <param name="str">Line of text to print.</param>
void OutDC80::printLine( const std::string& str )
{
  pDC->TextOut(x, y, CString(str.c_str())); y += ht;
}

/// <summary>Prints one line of text with a newline.</summary>
///
/// <param name="temp">Line of text to print.</param>
void OutDC80::printLine( const char* temp )
{
  pDC->TextOut(x, y, CString(temp)); y += ht;
}

/// <summary>Prints one line of text without newline.</summary>
///
/// <param name="str">Line of text to print.</param>
void OutDC80::printLinena( const std::string& str )
{
  pDC->TextOut(x, y, CString(str.c_str()));
}

/// <summary>Prints one line of text without newline.</summary>
///
/// <param name="temp">Line of text to print.</param>
void OutDC80::printLinena( const char* temp )
{
  pDC->TextOut(x, y, CString(temp));
}
