// $Id: HistAmtReviewDialog.h 1.3.1.1 2012/03/08 06:55:05EST 277133 Development 277133(2012/03/08 06:55:47EST) $
//
// Implementation of HistAmtReviewDialog.

#if !defined(AFX_HISTAMTREVIEWDIALOG_H__B42FEA86_365B_11D1_B875_00A0249F5E63__INCLUDED_)
#define AFX_HISTAMTREVIEWDIALOG_H__B42FEA86_365B_11D1_B875_00A0249F5E63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "dbleann.h"

// Description: Allows the reviewing of historical data.
//
// Remarks: Allows the reviewing of historical data.
class HistAmtReviewDialog : public CDialog
{
   public:
      HistAmtReviewDialog( CWnd* pParent = NULL );

// Dialog Data
	//{{AFX_DATA(HistAmtReviewDialog)
	enum { IDD = IDD_HISTAMTREVIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(HistAmtReviewDialog)
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
      DoubleAnnual m_wb;
      // @cmember Annual old-law wage bases.
      DoubleAnnual m_wbold;
      // @cmember Average wages.
      DoubleAnnual m_fq;
      // @cmember Benefit increases.
      DoubleAnnual m_bi;
      // @cmember Set up data to be displayed for one year.
      void setupdata();
        
protected:

	// Generated message map functions
	//{{AFX_MSG(HistAmtReviewDialog)
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	virtual BOOL OnInitDialog();
	afx_msg void OnHistnextyear();
	afx_msg void OnHistprevyear();
	afx_msg void OnHistamtreviewhelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTAMTREVIEWDIALOG_H__B42FEA86_365B_11D1_B875_00A0249F5E63__INCLUDED_)
