// $Id: HistAmtUpdateDialog.h 1.4.1.1 2012/03/08 06:55:07EST 277133 Development 277133(2012/03/08 06:55:47EST) $
//
// Implementation of HistAmtUpdateDialog.

#if !defined(AFX_HISTAMTUPDATEDIALOG_H__56B63261_3672_11D1_B875_00A0249F5E63__INCLUDED_)
#define AFX_HISTAMTUPDATEDIALOG_H__56B63261_3672_11D1_B875_00A0249F5E63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Description: Allows the addition of a new year to the historical data.
//
// Remarks: Allows the addition of a new year to the historical data.
class HistAmtUpdateDialog : public CDialog
{
   public:
      HistAmtUpdateDialog( CWnd* pParent = NULL );

// Dialog Data
	//{{AFX_DATA(HistAmtUpdateDialog)
	enum { IDD = IDD_HISTAMTUPDATE };
	double	m_aw;
	double	m_bi;
	double	m_wb;
	double	m_wbold;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(HistAmtUpdateDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

   // @access Public Members
   public:
      // @cmember Year of update.
      int m_year;
      // @cmember HI wage base as a double.
      double m_wbhi;

protected:

	// Generated message map functions
	//{{AFX_MSG(HistAmtUpdateDialog)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnHistamtupdatehelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTAMTUPDATEDIALOG_H__56B63261_3672_11D1_B875_00A0249F5E63__INCLUDED_)
