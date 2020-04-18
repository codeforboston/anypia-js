// $Id: AnypiaView.h 1.8.1.1 2012/03/08 06:55:11EST 277133 Development 277133(2012/03/08 06:55:48EST) $
//
// Interface of the CAnypia32View class.

#include "piaout/piaout.h"
#include "piaout/pebsout.h"
#include "piaout/AnypiaOut.h"

#if !defined(AFX_ANYPIA32VIEW_H__560E66FC_2E0D_11D1_B873_00A0249F5E63__INCLUDED_)
#define AFX_ANYPIA32VIEW_H__560E66FC_2E0D_11D1_B873_00A0249F5E63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Description: Provides the functions to draw the output results on
// the screen and on a printer.
class CAnypia32View : public CScrollView
{
private:
   // Description: Outfile used for screen output.
   OutDC80 outfiledraw;
   // Description: Outfile used for print output.
   OutDC80 outfileprint;
   // Description: Collection of all output pages.
   AnypiaOut* anypiaOut;
   // Description: Left margin in printer pixels.
   int leftMargin;
   // Description: Top margin in printer pixels.
   int topMargin;
   // Description: Font to use for printing.
   CFont printerFont;

protected:
   CAnypia32View();
   // create from serialization only
   DECLARE_DYNCREATE(CAnypia32View)

public:
   CAnypia32Doc* GetDocument();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnypia32View)
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC*, CPrintInfo*);
	//}}AFX_VIRTUAL

public:
   virtual ~CAnypia32View();
   virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CAnypia32View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Anypia32View.cpp
   // Description: Returns pointer to document.
   inline CAnypia32Doc* CAnypia32View::GetDocument()
      { return (CAnypia32Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANYPIA32VIEW_H__560E66FC_2E0D_11D1_B873_00A0249F5E63__INCLUDED_)
