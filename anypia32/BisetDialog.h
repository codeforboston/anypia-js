// $Id: BisetDialog.h 1.6.1.2 2016/12/07 08:11:58EST 277133 Development  $
//
// Declaration of BisetDialog.

#if !defined(AFX_BISETDIALOG_H__BACAD681_3679_11D1_B875_00A0249F5E63__INCLUDED_)
#define AFX_BISETDIALOG_H__BACAD681_3679_11D1_B875_00A0249F5E63__INCLUDED_

#pragma once

#include "dbleann.h"
#include "BiprojIni.h"
#include "AssumptionsNonFile.h"
#include "UserAssumptions.h"

// Description: Handles a set of stored projected benefit increases.
//
// Remarks: Handles a set of stored projected benefit increases.
class BisetDialog : public CDialog
{
   public:
      BisetDialog(CWnd* pParent = NULL);
      void setdata();

// Dialog Data
	//{{AFX_DATA(BisetDialog)
	enum { IDD = IDD_BIPROJSET };
	double	m_biprojult;
	double	m_biprojyear1;
	double	m_biprojyear10;
	double	m_biprojyear11;
	double	m_biprojyear12;
	double	m_biprojyear13;
	double	m_biprojyear14;
	double	m_biprojyear15;
	double	m_biprojyear2;
	double	m_biprojyear3;
	double	m_biprojyear4;
	double	m_biprojyear5;
	double	m_biprojyear6;
	double	m_biprojyear7;
	double	m_biprojyear8;
	double	m_biprojyear9;
	BOOL	m_cachup;
	CString	m_biprojtitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BisetDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

    public:
    // Projected benefit increases in this dialog.
    DoubleAnnual m_biproj;
    // Alternative number.
    int m_ialt;
    // Benefit increases stored in the Registry.
    BiprojIni* biprojIni;
    // Projected average wage and benefit increases.
    AssumptionsNonFile* assumptions;
    // Pointer to user assumptions
    UserAssumptions* userAssumptions;

protected:

	// Generated message map functions
	//{{AFX_MSG(BisetDialog)
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBiprojsethelp();
	afx_msg void OnBiprojclear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BISETDIALOG_H__BACAD681_3679_11D1_B875_00A0249F5E63__INCLUDED_)
