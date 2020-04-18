// $Id: CusetDialog.h 1.5.1.1 2012/03/08 06:55:05EST 277133 Development 277133(2012/03/08 06:55:47EST) $
//
// Declaration of CusetDialog.

#if !defined(AFX_CUSETDIALOG_H__BACAD683_3679_11D1_B875_00A0249F5E63__INCLUDED_)
#define AFX_CUSETDIALOG_H__BACAD683_3679_11D1_B875_00A0249F5E63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "pia.h"
#include "CachupIni.h"
#include "AssumptionsNonFile.h"

// Description: Displays and updates the stored sets of catch-up benefit 
//   increases.
//
// Remarks: Displays and updates the stored sets of catch-up benefit 
//   increases.
class CusetDialog : public CDialog
{
   public:
      CusetDialog( CWnd* pParent = NULL );

// Dialog Data
	//{{AFX_DATA(CusetDialog)
	enum { IDD = IDD_CUPROJSET };
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
	//{{AFX_VIRTUAL(CusetDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

   public:
      // Alternative number.
      int m_ialt;
      // Catch-up benefit increases in this dialog.
      Catchup m_cachup;
      // Current year of eligibility.
      int m_ieligyear;
      // Catch-up increases stored in the Registry.
      CatchupIni* cachupIni;
      // Projected average wage and benefit increases.
      AssumptionsNonFile* assumptions;
   public:
      bool check();
      void setdata();
      void setupdata();
    
protected:

	// Generated message map functions
	//{{AFX_MSG(CusetDialog)
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	virtual BOOL OnInitDialog();
	afx_msg void OnCuprojnextyear();
	afx_msg void OnCuprojprevyear();
	virtual void OnOK();
	afx_msg void OnCuprojsethelp();
	afx_msg void OnCuprojclear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSETDIALOG_H__BACAD683_3679_11D1_B875_00A0249F5E63__INCLUDED_)
