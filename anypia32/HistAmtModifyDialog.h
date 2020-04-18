// $Id: HistAmtModifyDialog.h 1.4.1.1 2012/03/08 06:55:09EST 277133 Development 277133(2012/03/08 06:55:48EST) $
//
// Declaration of HistAmtModifyDialog.

#if !defined(AFX_HISTAMTMODIFYDIALOG_H__B42FEA87_365B_11D1_B875_00A0249F5E63__INCLUDED_)
#define AFX_HISTAMTMODIFYDIALOG_H__B42FEA87_365B_11D1_B875_00A0249F5E63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "dbleann.h"

// Description: Allows the modification of stored historical amounts.
//
// Remarks: Allows the modification of stored historical amounts.
class HistAmtModifyDialog : public CDialog
{
   public:
      HistAmtModifyDialog( CWnd* pParent = NULL );

// Dialog Data
	//{{AFX_DATA(HistAmtModifyDialog)
	enum { IDD = IDD_HISTAMTMODIFY };
	double	m_aw;
	double	m_bi;
	double	m_wb;
	double	m_wbold;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(HistAmtModifyDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

   // @access Public Members
   public:
      // @cmember First year to display.
      int m_istartyear;
      // @cmember Last year to display.
      int m_ilastyear;
      // @cmember Year being displayed.
      int m_year;
      // @cmember Annual wage bases.
      DoubleAnnual m_DAwb;
      // @cmember Annual old-law wage bases.
      DoubleAnnual m_DAwbold;
      // @cmember Average wages.
      DoubleAnnual m_DAaw;
      // @cmember Benefit increases.
      DoubleAnnual m_FAbi;
      // @cmember Set up data to be displayed for one year.
      void setupdata();
      // @cmember Checks data for inconsistencies.
      bool check();
        
protected:

	// Generated message map functions
	//{{AFX_MSG(HistAmtModifyDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnHistmodnextyear();
	afx_msg void OnHistmodprevyear();
	afx_msg void OnHistamtmodifyhelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTAMTMODIFYDIALOG_H__B42FEA87_365B_11D1_B875_00A0249F5E63__INCLUDED_)
