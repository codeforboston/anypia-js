// Functions to mimic AfxFormatString using Standard C++ Library strings.

// $Id: FormatString.cpp 1.5.1.1 2012/03/08 06:55:13EST 277133 Development 277133(2012/03/08 06:55:49EST) $

//DOM-IGNORE-BEGIN
#include "stdafx.h"
//DOM-IGNORE-END
#include "FormatString.h"

using namespace std;

/// <summary>Loads the specified string resource and substitutes for the
/// characters "%1" the string referenced by filler.</summary>
///
/// <param name="result">A reference to a string that will contain the
/// resultant string after the substitution is performed.</param>
/// <param name="rsc">The resource ID of the template string on which the
/// substitution will be performed</param>
/// <param name="filler">A string that will replace the format characters "%1"
/// in the template string</param>
void AfxFormatString1(std::string& result, unsigned int rsc,
  const std::string& filler)
{
   CString cstring;
   AfxFormatString1(cstring, rsc, CString(filler.c_str()));
   result = string((const char *)cstring);
}

/// <summary>Loads the specified string resource and substitutes for the
/// characters "%1"and "%2" the strings referenced by filler1 and filler2.
/// </summary>
///
/// <param name="result">A reference to a string that will contain the
/// resultant string after the substitution is performed.</param>
/// <param name="rsc">The resource ID of the template string on which the
/// substitution will be performed</param>
/// <param name="filler1">A string that will replace the format characters "%1"
/// in the template string</param>
/// <param name="filler2">A string that will replace the format characters "%1"
/// in the template string</param>
void AfxFormatString2(std::string& result, unsigned int rsc,
  const std::string& filler1, const std::string& filler2)
{
   CString cstring;
   AfxFormatString2(cstring, rsc, CString(filler1.c_str()),
      CString(filler2.c_str()));
   result = string((const char *)cstring);
}
