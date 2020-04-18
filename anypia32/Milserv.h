// @doc MILSERV
// $Id: Milserv.h 1.4.1.1 2012/03/08 06:55:19EST 277133 Development 277133(2012/03/08 06:55:50EST) $
// @module Milserv.h |
//
// Declaration of Milserv.

#if !defined(AFX_MILSERV_H__84861482_D5F8_11D1_857E_00A0249F5D27__INCLUDED_)
#define AFX_MILSERV_H__84861482_D5F8_11D1_857E_00A0249F5D27__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "msdates.h"

// @class Milserv allows the entry of up to 15 pairs of military service dates.

class Milserv : public CDialog
{
   // @access Public Members
   public:
      // @cmember Standard constructor.
      Milserv(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(Milserv)
	enum { IDD = IDD_MILSERV };
	CString	m_enddate1;
	CString	m_enddate2;
	CString	m_startdate1;
	CString	m_startdate2;
	CString	m_enddate3;
	CString	m_enddate4;
	CString	m_enddate5;
	CString	m_enddate6;
	CString	m_enddate7;
	CString	m_enddate8;
	CString	m_enddate9;
	CString	m_startdate3;
	CString	m_startdate4;
	CString	m_startdate5;
	CString	m_startdate6;
	CString	m_startdate7;
	CString	m_startdate8;
	CString	m_startdate9;
	CString	m_enddate10;
	CString	m_enddate11;
	CString	m_enddate12;
	CString	m_enddate13;
	CString	m_enddate14;
	CString	m_enddate15;
	CString	m_startdate10;
	CString	m_startdate11;
	CString	m_startdate12;
	CString	m_startdate13;
	CString	m_startdate14;
	CString	m_startdate15;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Milserv)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

   // @access Public Members
   public:
      // @cmember Pairs of starting and ending dates.
      MilServDates msdates[15];
      // @cmember Number of periods of military service.
      int m_mscount;
      // @cmember Set starting and ending dates from entered data.
      void setdata( int index, const char *startDate, const char *endDate );

protected:

	// Generated message map functions
	//{{AFX_MSG(Milserv)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnMilservHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MILSERV_H__84861482_D5F8_11D1_857E_00A0249F5D27__INCLUDED_)
