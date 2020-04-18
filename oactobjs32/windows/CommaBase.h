// Definitions used by the <see cref="pcomma"/> function on a Windows machine.
//
// $Id: CommaBase.h 1.5 2011/08/11 15:21:18EDT 044579 Development  $

#pragma once

// Use stringstreams for systems that have them.
#include <sstream>

/// <summary>Use ostringstream for formatting output.</summary>
#define OSTREAM std::ostringstream

/// <summary>No special character for end of ostringstream.</summary>
#define ENDS

/// <summary>No special function to freeze the string.</summary>
///
/// <param name="strm">Stream to freeze.</param>
#define FREEZE(strm)
