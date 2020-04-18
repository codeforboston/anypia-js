// $Id: AnypiaView.cpp 1.14.1.1 2012/03/08 06:55:02EST 277133 Development 277133(2012/03/08 06:55:46EST) $
//
// Implementation of the CAnypia32View class.

#include "stdafx.h"
#include "Anypia32.h"

#include "AnypiaDoc.h"
#include "AnypiaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnypia32View

IMPLEMENT_DYNCREATE(CAnypia32View, CScrollView)

BEGIN_MESSAGE_MAP(CAnypia32View, CScrollView)
	//{{AFX_MSG_MAP(CAnypia32View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

// Description: CAnypia32View construction.
CAnypia32View::CAnypia32View() : CScrollView(),
leftMargin(0), topMargin(0), printerFont()
{
   SetScrollSizes(MM_TEXT, CSize(700,10000));
   anypiaOut = new AnypiaOut();
}

// Description: CAnypia32View destruction.
CAnypia32View::~CAnypia32View()
{
   delete anypiaOut;
}

// Description: Modify the Window class or styles.
BOOL CAnypia32View::PreCreateWindow( CREATESTRUCT& cs )
{
   // TODO: Modify the Window class or styles here by modifying
   //  the CREATESTRUCT cs

   return CView::PreCreateWindow(cs);
}

// Description: CAnypia32View drawing.
//
// Arguments:
//   pDC: Device context to use.
void CAnypia32View::OnDraw( CDC* pDC )
{
   CAnypia32Doc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);
   Config* config = pDoc->config;
   //lawchgout = new Lawchgout(*pDoc -> lawchg);
   TEXTMETRIC metric;  // text metric
   CString separator(
      "_________________________________________________________________________");
   CFont courier;

   courier.CreatePointFont(10 * config->getScreenPoints(), "Courier New");
   pDC->SelectObject(&courier);
   pDC->GetTextMetrics(&metric);
   outfiledraw.setHeight(metric.tmHeight);
   outfiledraw.setDC(pDC);
   outfiledraw.setx(10);
   outfiledraw.sety(5);
   anypiaOut->setWorkerData(pDoc->workerData);
   anypiaOut->setPiaData(pDoc->piadata);
   anypiaOut->setPiaCal(pDoc->piacal);
   anypiaOut->setPiaOut(pDoc->pPiaOut);
   anypiaOut->setPebsOut(pDoc->pebsOut);
   anypiaOut->fillPageSlots(GetDocument()->isValid(),
      config->getLongOutput());
   for (unsigned int i = 0u; i < anypiaOut->getPageCount(); i++) {
      anypiaOut->getPage(i)->print(outfiledraw);
      if (pDoc->workerData->getJoasdi() != WorkerData::PEBS_CALC) {
         outfiledraw.printLine(separator);
         outfiledraw.printLine("");
      }
   }
   //delete lawchgout;
}

// Description: Begin CAnypia32View printing.
//
// Arguments:
//   pInfo: Printer information.
BOOL CAnypia32View::OnPreparePrinting( CPrintInfo* pInfo )
{
   pInfo->SetMaxPage(anypiaOut->getPageCount());
   pInfo->m_bContinuePrinting = TRUE;
   return DoPreparePrinting(pInfo);
}

// Description: Begin CAnypia32View printing, after OnPreparePrinting.
//
// Arguments:
//   pDC: Device context to use.
//   pInfo: Printer information.
void CAnypia32View::OnBeginPrinting( CDC* pDC, CPrintInfo* /*pInfo*/ )
{
   TEXTMETRIC metric;  // text metric
   CAnypia32Doc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);
   Config* config = pDoc->config;
   // first argument to CreatePointFont is in tenths of points
   printerFont.CreatePointFont(10 * config->getPrinterPoints(), "Courier New",
      pDC);
   pDC->SelectObject(&printerFont);
   pDC->GetTextMetrics(&metric);
   outfileprint.setHeight(metric.tmHeight);
   int pixelsPerInch = pDC->GetDeviceCaps(LOGPIXELSX);
   leftMargin = (int)(pixelsPerInch * config->getLeftMargin());
   pixelsPerInch = pDC->GetDeviceCaps(LOGPIXELSY);
   topMargin = (int)(pixelsPerInch * config->getTopMargin());
}

// Description: End CAnypia32View printing.
//
// Remarks: Unused arguments are pDC and pInfo.
void CAnypia32View::OnEndPrinting( CDC*, CPrintInfo* )
{
   // TODO: add cleanup after printing
}

// Description: Print one page.
//
// Arguments:
//   pDC: Device context to use.
//   pInfo: Printer information.
void CAnypia32View::OnPrint( CDC* pDC, CPrintInfo* pInfo )
{
   CAnypia32Doc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);
   //lawchgout = new Lawchgout(*pDoc->lawchg);
   outfileprint.setDC(pDC);
   outfileprint.setx(leftMargin);
   outfileprint.sety(topMargin);
   anypiaOut->setWorkerData(pDoc->workerData);
   anypiaOut->setPiaData(pDoc->piadata);
   anypiaOut->setPiaCal(pDoc->piacal);
   anypiaOut->setPiaOut(pDoc->pPiaOut);
   anypiaOut->setPebsOut(pDoc->pebsOut);
   anypiaOut->getPage(pInfo->m_nCurPage - 1)->print(outfileprint);
   //delete lawchgout;
}

/////////////////////////////////////////////////////////////////////////////
// CAnypia32View diagnostics

#ifdef _DEBUG
void CAnypia32View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CAnypia32View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CAnypia32Doc* CAnypia32View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAnypia32Doc)));
	return (CAnypia32Doc*)m_pDocument;
}
#endif //_DEBUG
