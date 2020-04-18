// $Id: BaseyearDialog.h 1.5.1.1 2012/03/08 06:55:18EST 277133 Development 277133(2012/03/08 06:55:50EST) $
//
// Declaration of BaseyearDialog.

#if !defined(AFX_BASEYEARDIALOG_H__B42FEA84_365B_11D1_B875_00A0249F5E63__INCLUDED_)
#define AFX_BASEYEARDIALOG_H__B42FEA84_365B_11D1_B875_00A0249F5E63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "BaseyearIni.h"
#include "BaseYearNonFile.h"

// Description: Dialog to handle the computation year.
//
// Remarks: Dialog to handle the computation year.
class BaseyearDialog : public CDialog
{
public:
   BaseyearDialog( CWnd* pParent = NULL );
   void setdata();

// Dialog Data
	//{{AFX_DATA(BaseyearDialog)
	enum { IDD = IDD_BASEYEAR };
	int		m_baseyear;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BaseyearDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
   // Description: Last possible year.
   int m_ilastyear;
   // Description: Pointer to ini data.
   BaseYearIni* baseyearIni;
   // Description: Computation year.
   BaseYearNonFile* baseyear;
   // Description: Indicator for resetting computation year.
   bool m_resetCompYear;

protected:

	// Generated message map functions
	//{{AFX_MSG(BaseyearDialog)
	virtual void OnOK();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnBaseyearhelp();
	afx_msg void OnBaseyearclear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASEYEARDIALOG_H__B42FEA84_365B_11D1_B875_00A0249F5E63__INCLUDED_)
