// Declarations needed for the <see cref="OutDC80"/> class to write to a device
// context (DC).

// $Id: OutDC.h 1.4 2010/11/22 16:15:25ACT 044579 Development  $

#pragma once

#include "outfile.h"
class CDC;

/// <summary>Handles output to a Windows window.</summary>
///
/// <remarks>Handles output to a Windows window.</remarks>
class OutDC80 : public Out80
{
private:
  /// <summary> Height of one line in pixels.</summary>
  int ht;
  /// <summary> Number of vertical pixels from top of page.</summary>
  int y;
  /// <summary> Number of horizontal pixels from left side of page.</summary>
  int x;
  /// <summary> Pointer to device context.</summary>
  CDC* pDC;
public:
  OutDC80();
  /// <summary>Advances one line.</summary>
  void advanceLine() { y += ht; }
  /// <summary>Dummy function.</summary>
  void formfeed() { }
  void printLine( const std::string& str );
  void printLine( const char* temp );
  void printLinena( const std::string& str );
  void printLinena( const char* temp );
  /// <summary>Sets device context to use.</summary>
  ///
  /// <param name="newDC"> New device context to use.</param>
  void setDC( CDC* newDC ) { pDC = newDC; }
  /// <summary>Sets height of one line.</summary>
  ///
  /// <param name="newht"> New height of one line.</param>
  void setHeight( int newht ) { ht = newht; }
  /// <summary>Sets horizontal margin.</summary>
  ///
  /// <param name="newx"> New horizontal margin.</param>
  void setx( int newx ) { x = newx; }
  /// <summary>Sets vertical margin.</summary>
  ///
  /// <param name="newy"> New vertical margin.</param>
  void sety( int newy ) { y = newy; }
};
