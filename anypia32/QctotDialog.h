// $Id: QctotDialog.h 1.4.1.1 2012/03/08 06:55:10EST 277133 Development 277133(2012/03/08 06:55:48EST) $
//
// Declaration of QctotDialog.

#if !defined(AFX_QCTOTDIALOG_H__50EF9262_3106_11D1_B873_00A0249F5E63__INCLUDED_)
#define AFX_QCTOTDIALOG_H__50EF9262_3106_11D1_B873_00A0249F5E63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Description: Manages the dialog for the entry of the total quarters of
// coverage earned before 1978.
//
// Remarks: Manages the dialog for the entry of the total quarters of
// coverage earned before 1978.
class QctotDialog : public CDialog
{
public:
   QctotDialog( CWnd* pParent = NULL );

// Dialog Data
	//{{AFX_DATA(QctotDialog)
	enum { IDD = IDD_QCTOT };
	int		m_qc51td;
	int		m_qctd;
	int		m_qcann;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(QctotDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
   // Description: Indicator for needing qcs from 1951 to date.
   bool m_bqc51td;

protected:

	// Generated message map functions
	//{{AFX_MSG(QctotDialog)
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnQctotHelp();
	afx_msg void OnRadioQcann();
	afx_msg void OnRadioQctot();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QCTOTDIALOG_H__50EF9262_3106_11D1_B873_00A0249F5E63__INCLUDED_)
