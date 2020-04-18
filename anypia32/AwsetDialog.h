// $Id: AwsetDialog.h 1.4.1.2 2016/12/07 08:11:57EST 277133 Development  $
//
// Declaration of AwsetDialog.

#if !defined(AFX_AWSETDIALOG_H__BACAD682_3679_11D1_B875_00A0249F5E63__INCLUDED_)
#define AFX_AWSETDIALOG_H__BACAD682_3679_11D1_B875_00A0249F5E63__INCLUDED_

#pragma once

#include "dbleann.h"
#include "AwincIni.h"
#include "AssumptionsNonFile.h"
#include "UserAssumptions.h"

// Description: Dialog to handle a set of stored average wage increases.
//
// Remarks: Dialog to handle a set of stored average wage increases.
class AwsetDialog : public CDialog
{
public:
   AwsetDialog( CWnd* pParent = NULL );
   void setdata();

// Dialog Data
	//{{AFX_DATA(AwsetDialog)
	enum { IDD = IDD_AWPROJSET };
	CString	m_awprojtitle;
	double	m_awprojult;
	double	m_awprojyear1;
	double	m_awprojyear10;
	double	m_awprojyear11;
	double	m_awprojyear12;
	double	m_awprojyear13;
	double	m_awprojyear14;
	double	m_awprojyear15;
	double	m_awprojyear16;
	double	m_awprojyear2;
	double	m_awprojyear3;
	double	m_awprojyear4;
	double	m_awprojyear5;
	double	m_awprojyear6;
	double	m_awprojyear7;
	double	m_awprojyear8;
	double	m_awprojyear9;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AwsetDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
   // Projected average wage increases in this dialog.
   DoubleAnnual m_awproj;
   // Alternative number.
   int m_ialt;
   // Pointer to ini data.
   AwincIni* awincIni;
   // Pointer to assumptions
   AssumptionsNonFile* assumptions;
   // Pointer to user assumptions
   UserAssumptions* userAssumptions;

protected:
	// Generated message map functions
	//{{AFX_MSG(AwsetDialog)
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAwprojsethelp();
	afx_msg void OnAwprojclear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AWSETDIALOG_H__BACAD682_3679_11D1_B875_00A0249F5E63__INCLUDED_)
