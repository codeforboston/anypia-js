// @doc FOINFODIALOG
// $Id: FoinfoDialog.h 1.2.1.1 2012/03/08 06:55:09EST 277133 Development 277133(2012/03/08 06:55:48EST) $
// @module FoinfoDialog.h |
//
// Declaration of FoinfoDialog.

#if !defined(AFX_FOINFODIALOG_H__B42FEA85_365B_11D1_B875_00A0249F5E63__INCLUDED_)
#define AFX_FOINFODIALOG_H__B42FEA85_365B_11D1_B875_00A0249F5E63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// @class FoinfoDialog updates the stored field office information.
//
// @base public | CDialog

class FoinfoDialog : public CDialog
{
   // @access Public Members
   public:
      // @cmember Standard constructor.
      FoinfoDialog(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(FoinfoDialog)
	enum { IDD = IDD_FOINFO };
	CString	m_foaddr1;
	CString	m_foaddr2;
	CString	m_foaddr3;
	CString	m_foaddr4;
	CString	m_foname;
	CString	m_fotitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FoinfoDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(FoinfoDialog)
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnFoinfohelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOINFODIALOG_H__B42FEA85_365B_11D1_B875_00A0249F5E63__INCLUDED_)
