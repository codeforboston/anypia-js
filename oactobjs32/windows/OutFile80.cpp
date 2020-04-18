// Functions needed for the <see cref="OutFile80"/> class to manage print
// output to a file with 80-column lines.

// $Id: OutFile80.cpp 1.12 2011/08/12 08:47:02EDT 044579 Development  $

#include "OutFile80.h"
#include "Resource.h"
#include "PiaException.h"

using namespace std;

/// <summary>Initializes the core file name, using an extension of ".out".
/// </summary>
///
/// <param name="newCorename">New core file name.</param>
OutFile80::OutFile80( const std::string& newCorename ) :
Out80(newCorename, ".out"), cols(6)
{
  colstring = new char[cols + 1];
  for (int i = 0; i < cols; i++)
    colstring[i] = ' ';
  colstring[cols] = '\0';
}

/// <summary>Initializes the core file name and extension.</summary>
///
/// <param name="newCorename">New core file name.</param>
/// <param name="newExtension">New extension on the file name.</param>
OutFile80::OutFile80( const std::string& newCorename,
 const std::string& newExtension ) :
Out80(newCorename, newExtension), cols(6)
{
  colstring = new char[cols + 1];
  for (int i = 0; i < cols; i++)
    colstring[i] = ' ';
  colstring[cols] = '\0';
}

/// <summary>Destructor.</summary>
OutFile80::~OutFile80()
{
  delete [] colstring;
}

/// <summary>Sets number of columns on left-hand margin.</summary>
///
/// <param name="newCols">New number of columns.</param>
void OutFile80::setCols( int newCols )
{
  cols = newCols;
  delete colstring;
  colstring = new char[cols + 1];
  for (int i = 0; i < cols; i++)
    colstring[i] = ' ';
  colstring[cols] = '\0';
}
