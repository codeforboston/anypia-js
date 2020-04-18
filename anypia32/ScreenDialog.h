// @doc SCREENDIALOG
// $Id: ScreenDialog.h 1.3.1.1 2012/03/08 06:55:14EST 277133 Development 277133(2012/03/08 06:55:49EST) $
// @module ScreenDialog.h |
//
// Declaration of ScreenDialog.

#if !defined(AFX_SCREENDIALOG_H__DD1EA815_E374_11D2_B3E9_00104B256866__INCLUDED_)
#define AFX_SCREENDIALOG_H__DD1EA815_E374_11D2_B3E9_00104B256866__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// @class ScreenDialog handles the screen font characteristics.
//
// @base public | CDialog

class ScreenDialog : public CDialog
{
   // @access Public Members
   public:
      // @cmember Standard constructor.
	   ScreenDialog(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(ScreenDialog)
	enum { IDD = IDD_SCREEN };
	int		m_ScreenPoints;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ScreenDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ScreenDialog)
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnScreenhelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCREENDIALOG_H__DD1EA815_E374_11D2_B3E9_00104B256866__INCLUDED_)
