// $Id: WageBaseDialog.h 1.3.1.1 2012/03/08 06:55:03EST 277133 Development 277133(2012/03/08 06:55:46EST) $
//
// Declaration of WageBaseDialog.

#if !defined(AFX_WAGEBASEDIALOG_H__701746B3_34D7_11D1_B875_00A0249F5E63__INCLUDED_)
#define AFX_WAGEBASEDIALOG_H__701746B3_34D7_11D1_B875_00A0249F5E63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "dbleann.h"

// Description: Handles the entry of user-specified wage bases.
//
// Remarks: Handles the entry of user-specified wage bases.
class WageBaseDialog : public CDialog
{
public:
   WageBaseDialog(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(WageBaseDialog)
	enum { IDD = IDD_WAGEBASE };
	double	m_olwb;
	double	m_plwb;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(WageBaseDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
   // Description: First year to display.
   int m_istartyear;
   // Description: Last year to display.
   int m_ilastyear;
   // Description: Year being displayed.
   int m_year;
   // Description: Present law wage bases.
   DoubleAnnual m_DAplwb;
   // Description: Old law wage bases.
   DoubleAnnual m_DAolwb;
   // Description: Set up data to be displayed for one year.
   void setupdata();
   // Description: Checks data for inconsistencies.
   bool check();

protected:

	// Generated message map functions
	//{{AFX_MSG(WageBaseDialog)
	afx_msg void OnWbnextyear();
	afx_msg void OnWbprevyear();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnWagebasehelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAGEBASEDIALOG_H__701746B3_34D7_11D1_B875_00A0249F5E63__INCLUDED_)
