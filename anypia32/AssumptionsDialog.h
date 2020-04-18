// @doc ASSUMPTIONSDIALOG
// $Id: AssumptionsDialog.h 1.4.1.1 2012/03/08 06:55:11EST 277133 Development 277133(2012/03/08 11:07:34EST) $
// @module AssumptionsDialog.h |
//
// Header file for AssumptionsDialog.

#if !defined(AFX_ASSUMPTIONSDIALOG_H__71A0C011_337D_11D1_B874_00A0249F5E63__INCLUDED_)
#define AFX_ASSUMPTIONSDIALOG_H__71A0C011_337D_11D1_B874_00A0249F5E63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// @class The AssumptionsDialog class is the dialog for entering the type
//   of assumptions for projected average wages and benefit increases.
//
// @base public | CDialog

class AssumptionsDialog : public CDialog
{
// @access Public Members
public:
   // @cmember Standard constructor.
	AssumptionsDialog(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(AssumptionsDialog)
	enum { IDD = IDD_ASSUMPTIONS };
	CString	m_bitext;
	CString	m_awtext;
	BOOL	m_cachup;
	int		m_ialtaw;
	int		m_ialtbi;
	int		m_bases;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AssumptionsDialog)
   // @access Protected Members
	protected:
   // @cmember Exchanges data between variables and dialog boxes.
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// @access Public Members
public:
   // @cmember Description of benefit increase assumptions.
   CString m_beninc[7];
   // @cmember Descriptions of average wage increase assumptions.
   CString m_avgwage[7];
   // @cmember True if type of wage base projection is needed.
   bool m_bbases;
   // @cmember True if this is a Statement calculation.
   bool m_bpebes;
    
// @access Protected Members
protected:

	// Generated message map functions
	//{{AFX_MSG(AssumptionsDialog)
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAwFlat();
	afx_msg void OnAwI();
	afx_msg void OnAwIi();
	afx_msg void OnAwIia();
	afx_msg void OnAwIii();
	afx_msg void OnAwOther();
	afx_msg void OnAwPebs();
	afx_msg void OnBiFlat();
	afx_msg void OnBiI();
	afx_msg void OnBiIi();
	afx_msg void OnBiIia();
	afx_msg void OnBiIii();
	afx_msg void OnBiOther();
	afx_msg void OnBiPebs();
	afx_msg void OnAssumptionsHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASSUMPTIONSDIALOG_H__71A0C011_337D_11D1_B874_00A0249F5E63__INCLUDED_)
