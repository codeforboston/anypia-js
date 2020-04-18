// $Id: BiprojDialog.h 1.5.1.1 2012/03/08 06:55:04EST 277133 Development 277133(2012/03/08 06:55:47EST) $
//
// Declaration of BiprojDialog.

#if !defined(AFX_BIPROJDIALOG_H__71A0C012_337D_11D1_B874_00A0249F5E63__INCLUDED_)
#define AFX_BIPROJDIALOG_H__71A0C012_337D_11D1_B874_00A0249F5E63__INCLUDED_

#pragma once

#include "dbleann.h"

// Description: Handles the user-specified projected benefit increases.
//
// Remarks: Handles the user-specified projected benefit increases.
class BiprojDialog : public CDialog
{
public:
   BiprojDialog( CWnd* pParent = NULL );

// Dialog Data
	//{{AFX_DATA(BiprojDialog)
	enum { IDD = IDD_BIPROJ };
	double	m_biult;
	double	m_biyear1;
	double	m_biyear10;
	double	m_biyear11;
	double	m_biyear12;
	double	m_biyear13;
	double	m_biyear14;
	double	m_biyear15;
	double	m_biyear2;
	double	m_biyear3;
	double	m_biyear4;
	double	m_biyear5;
	double	m_biyear6;
	double	m_biyear7;
	double	m_biyear8;
	double	m_biyear9;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BiprojDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
   // Description: Projected benefit increases in this dialog.
   DoubleAnnual m_biproj;

protected:

	// Generated message map functions
	//{{AFX_MSG(BiprojDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnBiprojhelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnEnChangeEdit2();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BIPROJDIALOG_H__71A0C012_337D_11D1_B874_00A0249F5E63__INCLUDED_)
