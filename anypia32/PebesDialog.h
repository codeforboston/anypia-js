// $Id: PebesDialog.h 1.4.1.1 2012/03/08 06:55:11EST 277133 Development 277133(2012/03/08 06:55:48EST) $
//
// Declaration of PebesDialog.

#if !defined(AFX_PEBESDIALOG_H__5BDE98F1_3025_11D1_B873_00A0249F5E63__INCLUDED_)
#define AFX_PEBESDIALOG_H__5BDE98F1_3025_11D1_B873_00A0249F5E63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "pia.h"

// Description: Dialog to handle the entry of the data for the Social Security
// Statement.
//
// Remarks: Dialog to handle the entry of the data for the Social Security
// Statement.
class PebesDialog : public CDialog
{
public:
   PebesDialog(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(PebesDialog)
	enum { IDD = IDD_PEBES };
	int		m_ageplan;
	int		m_beginpebes;
	CString	m_month;
	double	m_nonpen;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PebesDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
   // Description: Year of birth.
   int m_birthyear;
   // Description: Month of processing as a zero-based integer.
   int m_imonth;
   // Description: Current year.
   int m_istart;
   // Description: Date of entitlement to noncovered pension.
   DateMoyr m_nonpendatetemp;
   // Description: Date of birth.
   boost::gregorian::date m_birthdate;
   // Description:Date of death.
   boost::gregorian::date m_deathdate;

protected:

	// Generated message map functions
	//{{AFX_MSG(PebesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnPebesHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
   // Description: Date of entitlement to noncovered pension (string).
   CString m_nonpenpebesdate;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PEBESDIALOG_H__5BDE98F1_3025_11D1_B873_00A0249F5E63__INCLUDED_)
