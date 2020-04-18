// $Id: HistAmtClearDialog.h 1.2.1.1 2012/03/08 06:55:10EST 277133 Development 277133(2012/03/08 06:55:48EST) $
//
// HistAmtClearDialog.h : header file
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HISTAMTCLEARDIALOG_H__82B5CA69_D529_11D5_90EA_00B0D068B2C6__INCLUDED_)
#define AFX_HISTAMTCLEARDIALOG_H__82B5CA69_D529_11D5_90EA_00B0D068B2C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Description: Presents a dialog to inform the user of the historical amounts
// in the registry.
//
// Remarks: An instance of this class is created in
// CAnypia32Doc::OnSetupHistoricalamountsClear.
class HistAmtClearDialog : public CDialog
{
public:
   HistAmtClearDialog(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(HistAmtClearDialog)
	enum { IDD = IDD_HISTAMTCLEAR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(HistAmtClearDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
   // Description: First year to clear.
   int m_istartyear;
   // Description: Last year to clear.
   int m_ilastyear;

protected:

	// Generated message map functions
	//{{AFX_MSG(HistAmtClearDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTAMTCLEARDIALOG_H__82B5CA69_D529_11D5_90EA_00B0D068B2C6__INCLUDED_)
