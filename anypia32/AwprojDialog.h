// $Id: AwprojDialog.h 1.3.1.1 2012/03/08 06:55:04EST 277133 Development 277133(2012/03/08 06:55:47EST) $
//
// Declaration of AwprojDialog.

#if !defined(AFX_AWPROJDIALOG_H__701746B1_34D7_11D1_B875_00A0249F5E63__INCLUDED_)
#define AFX_AWPROJDIALOG_H__701746B1_34D7_11D1_B875_00A0249F5E63__INCLUDED_

#pragma once

#include "dbleann.h"

// Description: The dialog to handle user-specified average wage increases.
//
// Remarks: The dialog to handle user-specified average wage increases.
class AwprojDialog : public CDialog
{
public:
   AwprojDialog( CWnd* pParent = NULL );

// Dialog Data
	//{{AFX_DATA(AwprojDialog)
	enum { IDD = IDD_AWPROJ };
	double	m_awult;
	double	m_awyear1;
	double	m_awyear10;
	double	m_awyear11;
	double	m_awyear12;
	double	m_awyear13;
	double	m_awyear14;
	double	m_awyear15;
	double	m_awyear16;
	double	m_awyear2;
	double	m_awyear3;
	double	m_awyear4;
	double	m_awyear5;
	double	m_awyear6;
	double	m_awyear7;
	double	m_awyear8;
	double	m_awyear9;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AwprojDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
   // Description: Projected average wage increases in this dialog.
   DoubleAnnual m_awproj;

protected:

	// Generated message map functions
	//{{AFX_MSG(AwprojDialog)
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAwprojhelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AWPROJDIALOG_H__701746B1_34D7_11D1_B875_00A0249F5E63__INCLUDED_)
