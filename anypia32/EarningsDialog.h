// @doc EARNINGSDIALOG
// $Id: EarningsDialog.h 1.4.1.1 2012/03/08 06:55:13EST 277133 Development 277133(2012/03/08 06:55:49EST) $
// @module EarningsDialog.h |
//
// Header file for EarningsDialog.

#if !defined(AFX_EARNINGSDIALOG_H__701746B4_34D7_11D1_B875_00A0249F5E63__INCLUDED_)
#define AFX_EARNINGSDIALOG_H__701746B4_34D7_11D1_B875_00A0249F5E63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "dbleann.h"
#include "intann.h"
#include "BitAnnual.h"

// @class The EarningsDialog class is the dialog for entering earnings, type
//   of taxes, quarters of coverage, and railroad earnings.
//
// @base public | CDialog

class EarningsDialog : public CDialog
{
// @access Public Members
public:
   // @cmember Standard constructor.
	EarningsDialog(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(EarningsDialog)
	enum { IDD = IDD_EARNINGS };
	double	m_earnhi;
	double	m_earnoasdi;
	int		m_qcann;
	int		m_rrqc;
	double	m_rrearn;
	BOOL	m_childcare;
	int		m_earntype;
	int		m_taxtype;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EarningsDialog)
   // @access Protected Members
	protected:
   // @cmember Exchange data between variables and dialog boxes.
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// @access Public Members
public:
   // @cmember First year of regular earnings.
   int m_istartyear;
   // @cmember Last year of regular earnings.
   int m_ilastyear;
   // @cmember First year of railroad earnings.
   int m_istartyearrr;
   // @cmember Last year of railroad earnings.
   int m_ilastyearrr;
   // @cmember First year of any earnings.
   int m_istartyear1;
   // @cmember Last year of any earnings.
   int m_ilastyear1;
   // @cmember Checks data for inconsistencies.
   bool check();
   // @cmember Fills in strings in dialog box, and enables/disables selections.
   void setupdata();
   // @cmember OASDI earnings.
   DoubleAnnual m_DAoasdi;
   // @cmember HI earnings.
   DoubleAnnual m_DAhi;
   // @cmember Type of earnings.
   IntAnnual m_IAearntype;
   // @cmember Type of taxes.
   IntAnnual m_IAtaxtype;
   // @cmember Regular quarters of coverage.
   IntAnnual m_IAqc;
   // @cmember Child care years.
   BitAnnual m_BAchildcare;
   // @cmember Indicator for annual quarters of coverage required.
   bool m_qcbyyear;
   // @cmember Indicator for Medicare earnings.
   bool m_mqge;
   // @cmember OASDI wage base.
   DoubleAnnual m_DAbase;
   // @cmember Average earnings.
   DoubleAnnual m_DAfq;
   // @cmember High earnings.
   DoubleAnnual m_DAwaghigh;
   // @cmember Low earnings.
   DoubleAnnual m_DAwagmin;
   // @cmember True if this is PEBES calculation.
   bool m_bpebes;
   // @cmember True if any railroad earnings.
   bool m_indrr;
   // @cmember True if any regular earnings.
   bool m_indearn;
   // @cmember Year currently being worked on.
   int m_earnyear;
   // @cmember Railroad earnings.
   DoubleAnnual m_DArrearn;
   // @cmember Railroad quarters of coverage.
   IntAnnual m_IArrqc;

// @access Protected Members
protected:

	// Generated message map functions
	//{{AFX_MSG(EarningsDialog)
	virtual void OnOK();
	afx_msg void OnPrevyear();
	afx_msg void OnNextyear();
	afx_msg void OnMaximum();
	afx_msg void OnLow();
	afx_msg void OnHigh();
	afx_msg void OnEntered();
	afx_msg void OnAverage();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	virtual BOOL OnInitDialog();
	afx_msg void OnEarningshelp();
	afx_msg void OnSelendokComboearnyear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EARNINGSDIALOG_H__701746B4_34D7_11D1_B875_00A0249F5E63__INCLUDED_)
