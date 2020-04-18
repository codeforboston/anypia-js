// @doc CONFIGDIALOG
// $Id: ConfigDialog.h 1.2.1.1 2012/03/08 06:55:17EST 277133 Development 277133(2012/03/08 06:55:50EST) $
// @module ConfigDialog.h |
//
// Declaration of ConfigDialog.

#if !defined(AFX_CONFIGDIALOG_H__27152261_5C1A_11D1_855C_00A0249F5D27__INCLUDED_)
#define AFX_CONFIGDIALOG_H__27152261_5C1A_11D1_855C_00A0249F5D27__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// @class ConfigDialog implements the report configuration dialog (margins and 
// point size).
//
// @base public | CDialog

class ConfigDialog : public CDialog
{
   // @access Public Members
   public:
      // @cmember Standard constructor.
      ConfigDialog(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(ConfigDialog)
	enum { IDD = IDD_CONFIG };
	float	m_leftmargin;
	float	m_topmargin;
	int		m_PrinterPoints;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ConfigDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

   // @access Public Members
   public:
      // @cmember Indicator for long output.
      BOOL longOutput;

protected:

	// Generated message map functions
	//{{AFX_MSG(ConfigDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnConfigHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGDIALOG_H__27152261_5C1A_11D1_855C_00A0249F5D27__INCLUDED_)
