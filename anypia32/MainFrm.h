// @doc MAINFRAME
// $Id: MainFrm.h 1.2.1.1 2012/03/08 06:55:02EST 277133 Development 277133(2012/03/08 06:55:46EST) $
// @module MainFrm.h |
//
// Interface of CMainFrame.

#if !defined(AFX_MAINFRM_H__560E66F8_2E0D_11D1_B873_00A0249F5E63__INCLUDED_)
#define AFX_MAINFRM_H__560E66F8_2E0D_11D1_B873_00A0249F5E63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// @class CMainFrame is the viewable window used in Anypia32.
//
// @base public | CFrameWnd

class CMainFrame : public CFrameWnd
{
   // @access Protected Members
   protected:
      // @cmember Constructor (create from serialization only).
      CMainFrame();
      DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

   // @access Public Members
   public:
      // @cmember Destructor.
      virtual ~CMainFrame();
#ifdef _DEBUG
      virtual void AssertValid() const;
      virtual void Dump(CDumpContext& dc) const;
#endif

   // @access Protected Members
   protected:
      // @cmember Status bar.
      CStatusBar  m_wndStatusBar;
      // @cmember Toolbar.
      CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__560E66F8_2E0D_11D1_B873_00A0249F5E63__INCLUDED_)
