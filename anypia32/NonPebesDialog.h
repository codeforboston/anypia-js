// $Id: NonPebesDialog.h 1.8.1.1 2012/03/08 06:55:18EST 277133 Development 277133(2012/03/08 06:55:50EST) $
//
// Header file for NonPebesDialog.

#if !defined(AFX_NONPEBESDIALOG_H__5BDE98F2_3025_11D1_B873_00A0249F5E63__INCLUDED_)
#define AFX_NONPEBESDIALOG_H__5BDE98F2_3025_11D1_B873_00A0249F5E63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "pia.h"

// Description: Dialog to handle worker information for other than a Social
// Security Statement.
//
// Remarks: Dialog to handle worker information for other than a Social
// Security Statement.
class NonPebesDialog : public CDialog
{
public:
   NonPebesDialog(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(NonPebesDialog)
	enum { IDD = IDD_NONPEBES };
	CString	m_bendate;
	CString	m_ent;
	int		m_begin;
	int		m_end;
	double	m_backperc;
	int		m_backyear;
	double	m_fwrdperc;
	int		m_fwrdyear;
	int		m_valdi;
	double	m_nonpen;
	int		m_backtype;
	int		m_fwrdtype;
	BOOL	m_recalc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(NonPebesDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
   // Description: Backwards projection indicator.
   bool m_bback;
   // Description: Backwards projection indicator.
   bool m_bfwrd;
   // Description: Noncovered pension indicator.
   bool m_bnonpen;
   // Description: Entitlement date.
   DateMoyr enttemp;
   // Description: Benefit date.
   DateMoyr bendttemp;
   // Description: Year of birth.
   int m_birthyear;
   // Description: Temporary type of calculation.
   int m_joasdi;
   // Description: True if any regular earnings.
   int m_indearn;
   // Description: Date of entitlement to noncovered pension.
   DateMoyr m_nonpendatetemp;
   // Description: Date of birth.
   boost::gregorian::date m_birthdate;
   // Description: Date of death.
   boost::gregorian::date m_deathdate;

protected:
   void OnBacktype();
   void OnFwrdtype();

	// Generated message map functions
	//{{AFX_MSG(NonPebesDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnSuppHelp();
	afx_msg void OnRecalc();
	afx_msg void OnBacknone();
	afx_msg void OnBackavgwage();
	afx_msg void OnBackconstant();
	afx_msg void OnFwrdavgwage();
	afx_msg void OnFwrdconstant();
	afx_msg void OnFwrdnone();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
   // Description: Date of entitlement to noncovered pension (string).
   CString M_nonpendate;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NONPEBESDIALOG_H__5BDE98F2_3025_11D1_B873_00A0249F5E63__INCLUDED_)
