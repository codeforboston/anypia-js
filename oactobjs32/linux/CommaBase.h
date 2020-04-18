// $Id: CommaBase.h 1.2 2009/02/17 07:13:31EST 729915 Development  $
//
// The Comma functions can use the stringstream functions or the strstream
// functions.

#pragma once
#ifndef __COMMABASE_H
#define __COMMABASE_H    // Prevent multiple #includes

// Use str streams for systems without stringstreams.
#include <strstream>
/// <summary>Use ostrstream for formatting output.</summary>
#define OSTREAM std::ostrstream
/// <summary>End of ostrstream designated by ends.</summary>
#define ENDS start << ends
/// <summary>Use freeze function to freeze the string.</summary>
#define FREEZE(strm) strm.freeze(false)

#endif  // __COMMABASE_H
