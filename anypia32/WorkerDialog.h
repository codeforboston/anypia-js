// $Id: WorkerDialog.h 1.7.1.1 2012/03/08 06:55:03EST 277133 Development 277133(2012/03/08 06:55:46EST) $
//
// Header file for WorkerDialog.

#if !defined(AFX_WORKERDIALOG_H__9ED74961_2F5C_11D1_B873_00A0249F5E63__INCLUDED_)
#define AFX_WORKERDIALOG_H__9ED74961_2F5C_11D1_B873_00A0249F5E63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "pia.h"

// Description: Dialog to handle the worker's personal information, such as
// name, Social Security number, and date of birth.
//
// Remarks: Dialog to handle the worker's personal information, such as
// name, Social Security number, and date of birth.
class WorkerDialog : public CDialog
{
public:
   WorkerDialog(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(WorkerDialog)
	enum { IDD = IDD_WORKER_DIALOG };
	CString	m_dob;
	CString	m_ssn1;
	CString	m_ssn2;
	CString	m_ssn3;
	CString	m_nhname;
	CString	m_nhaddr1;
	CString	m_nhaddr2;
	CString	m_nhaddr3;
	BOOL	m_mqge;
	BOOL	m_totalize;
	BOOL	m_blind;
	BOOL	m_deemed;
	BOOL	m_indearn;
	BOOL	m_indrr;
	int		m_rryear1;
	int		m_rryear2;
	int		m_mscount;
	BOOL	m_indms;
	CString	m_death;
	int		m_fammem;
	int		m_bentype;
	int		m_sex;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(WorkerDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

public:
   // Description: Temporary date of birth.
   boost::gregorian::date m_dobtemp;
   // Description: Temporary date of death.
   boost::gregorian::date m_deathtemp;

protected:

	// Generated message map functions
	//{{AFX_MSG(WorkerDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnOldage();
	afx_msg void OnDisability();
	afx_msg void OnPebes();
	afx_msg void OnSurvivor();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	virtual void OnOK();
	afx_msg void OnIndrr();
	afx_msg void OnIndms();
	afx_msg void OnWorkerHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKERDIALOG_H__9ED74961_2F5C_11D1_B873_00A0249F5E63__INCLUDED_)
