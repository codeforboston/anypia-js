// $Id: DebugCase.cpp 1.6 2005/03/28 09:57:53EST djolson Exp  $
//
// Functions for specifying which ID (ssn or pid) to print out
// detailed debugging information for.

#include "DebugCase.h"

// Value of 999999 is reserved. It means print out for all pid's.
static const unsigned long DEBUGPID = 1;

// Description: Returns true if argument person id is the debug pid.
//
// Returns: True if argument person id is the debug pid.
//
// Arguments:
//   pid: Requested person id.
bool isDebugPid( unsigned long pid )
{
  return (pid == DEBUGPID) || (DEBUGPID == 999999);
}
