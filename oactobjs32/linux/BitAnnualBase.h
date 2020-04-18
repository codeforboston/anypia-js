// $Id: BitAnnualBase.h 1.2 2009/02/17 07:13:30EST 729915 Development  $
//
// Declarations needed for class to manage an array of annual bits for Linux.

#pragma once
#ifndef __BITANNUALBASE_H
#define __BITANNUALBASE_H   1   // Prevent multiple includes

#include <vector>
#include "BitPacked.h"
// Bit array.
typedef std::vector< BitPacked > BitAnnualData;

#endif    // __BITANNUALBASE_H
