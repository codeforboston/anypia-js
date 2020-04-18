// @doc CUPROJDIALOG
// $Id: CuprojDialog.h 1.4.1.1 2012/03/08 06:55:01EST 277133 Development 277133(2012/03/08 06:55:46EST) $
// @module CuprojDialog.h |
//
// Declaration of CuprojDialog.

#if !defined(AFX_CUPROJDIALOG_H__701746B2_34D7_11D1_B875_00A0249F5E63__INCLUDED_)
#define AFX_CUPROJDIALOG_H__701746B2_34D7_11D1_B875_00A0249F5E63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "pia.h"

// @class CuprojDialog handles the user-entered catch-up benefit increases.
//
// @base public | CDialog

class CuprojDialog : public CDialog
{
   // @access Public Members
   public:
      // @cmember Standard constructor.
      CuprojDialog(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CuprojDialog)
	enum { IDD = IDD_CUPROJ };
	double	m_cuyear1;
	double	m_cuyear2;
	double	m_cuyear3;
	double	m_cuyear4;
	double	m_cuyear5;
	double	m_cuyear6;
	double	m_cuyear7;
	double	m_cuyear8;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CuprojDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

   // @access Public Members
   public:
      // @cmember Projected catch-up benefit increases in this dialog.
      Catchup m_cachup;
      // @cmember Current year of eligibility.
      int m_ieligyear;
      // @cmember Checks data and saves results to member array.
      bool check();
      // @cmember Fills in strings in dialog box.
      void setupdata();
    
protected:

	// Generated message map functions
	//{{AFX_MSG(CuprojDialog)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnCunextyear();
	afx_msg void OnCuprevyear();
	virtual void OnOK();
	afx_msg void OnCuprojhelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUPROJDIALOG_H__701746B2_34D7_11D1_B875_00A0249F5E63__INCLUDED_)
