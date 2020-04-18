#if !defined(AFX_INTRODUCTION_H__CCDAC733_F042_11D3_B214_00105AC68D7E__INCLUDED_)
#define AFX_INTRODUCTION_H__CCDAC733_F042_11D3_B214_00105AC68D7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Introduction.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Introduction dialog

class Introduction : public CDialog
{
// Construction
public:
	Introduction(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Introduction)
	enum { IDD = IDD_INTRODUCTION };
	BOOL	m_nointro;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Introduction)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Introduction)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTRODUCTION_H__CCDAC733_F042_11D3_B214_00105AC68D7E__INCLUDED_)
