// $Id: Anypia32.h 1.3.1.1 2012/03/08 06:55:03EST 277133 Development  $
//
// Main header file for the ANYPIA32 application.

#if !defined(AFX_ANYPIA32_H__560E66F4_2E0D_11D1_B873_00A0249F5E63__INCLUDED_)
#define AFX_ANYPIA32_H__560E66F4_2E0D_11D1_B873_00A0249F5E63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

// Description: The Anypia32 application.
//
// Remarks: The Anypia32 application.
class CAnypia32App : public CWinApp
{
public:
   CAnypia32App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnypia32App)
	public:
	virtual BOOL InitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAnypia32App)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANYPIA32_H__560E66F4_2E0D_11D1_B873_00A0249F5E63__INCLUDED_)
