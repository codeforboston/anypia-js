// $Id: DisabDialog.h 1.8.1.1 2012/03/08 06:55:04EST 277133 Development 277133(2012/03/08 06:55:46EST) $
//
// Declaration of DisabDialog.

#if !defined(AFX_DISABDIALOG_H__3F423311_30E9_11D1_B873_00A0249F5E63__INCLUDED_)
#define AFX_DISABDIALOG_H__3F423311_30E9_11D1_B873_00A0249F5E63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "pia.h"

// Description: Dialog to handle up to 2 periods of disability.
//
// Remarks: Dialog to handle up to 2 periods of disability.
class DisabDialog : public CDialog
{
   public:
      DisabDialog(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(DisabDialog)
	enum { IDD = IDD_DISAB };
	CString	m_dicess;
	CString	m_onset;
	CString	m_prrent;
	CString	m_waitpd;
	CString	m_dicess1;
	CString	m_onset1;
	CString	m_prrent1;
	CString	m_waitpd1;
	//}}AFX_DATA
      // Description: PIA at cessation, most recent period of disability.
      float m_pia;
      // Description: MFB at cessation, most recent period of disability.
      float m_mfb;
      // Description: PIA at cessation, next most recent period of disability.
      float m_pia1;
      // Description: MFB at cessation, next most recent period of disability.
      float m_mfb1;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DisabDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

   public:
      // Date of cessation, most recent period of disability.
      DateMoyr m_dicesstemp;
      // Date of onset, most recent period of disability.
      boost::gregorian::date m_onsettemp;
      // Date of prior entitlement, most recent period of disability.
      DateMoyr m_prrenttemp;
      // First month of waiting period, most recent period of disability.
      DateMoyr m_waitpdtemp;
      // Date of cessation, next most recent period of disability.
      DateMoyr m_dicess1temp;
      // Date of onset, next most recent period of disability.
      boost::gregorian::date m_onset1temp;
      // Date of prior entitlement, next most recent period of disability.
      DateMoyr m_prrent1temp;
      // First month of waiting period, next most recent period of disability.
      DateMoyr m_waitpd1temp;
      // Number of periods of disability.
      int m_valdi;
      // Type of benefit.
      WorkerData::ben_type m_ioasdi;
      // Date of birth.
      boost::gregorian::date m_birthDate;
      // Date of entitlement.
      DateMoyr m_entDate;
      // Date of benefit.
      DateMoyr m_benDate;
      // Date of death
      boost::gregorian::date m_deathDate;

protected:

	// Generated message map functions
	//{{AFX_MSG(DisabDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnDisabHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISABDIALOG_H__3F423311_30E9_11D1_B873_00A0249F5E63__INCLUDED_)
