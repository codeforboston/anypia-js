// $Id: HistAmtReviewDialog.cpp 1.8.1.1 2012/03/08 06:55:02EST 277133 Development 277133(2018/10/15 09:57:19EDT) $
//
// Implementation of HistAmtReviewDialog.

#include "stdafx.h"
#include "Anypia32.h"
#include "HistAmtReviewDialog.h"
#include "pia.h"
#include "comma.h"
#include "Htmlhelp.h"
#include "oactcnst.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// HistAmtReviewDialog dialog

// Description: Constructor.
//
// Arguments:
//   pParent: Parent window (default NULL).
HistAmtReviewDialog::HistAmtReviewDialog( CWnd* pParent )
   : CDialog(HistAmtReviewDialog::IDD, pParent),
   m_wb(YEAR37, WorkerData::getMaxyear()),
   m_wbold(YEAR37, WorkerData::getMaxyear()),
   m_fq(YEAR37, WorkerData::getMaxyear()),
   m_bi(YEAR51, WorkerData::getMaxyear())
{
	//{{AFX_DATA_INIT(HistAmtReviewDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

// @mfunc Exchange data with dialog.
//
// @parm Data to be exchanged.

void HistAmtReviewDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(HistAmtReviewDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// HistAmtReviewDialog message handlers

BEGIN_MESSAGE_MAP(HistAmtReviewDialog, CDialog)
	//{{AFX_MSG_MAP(HistAmtReviewDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_HISTNEXTYEAR, OnHistnextyear)
	ON_BN_CLICKED(IDC_HISTPREVYEAR, OnHistprevyear)
	ON_BN_CLICKED(IDC_HISTAMTREVIEWHELP, OnHistamtreviewhelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// @mfunc Handles context-sensitive help.
//
// @parm Structure containing context when help was called.

BOOL HistAmtReviewDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
   HtmlHelp(pHelpInfo->dwContextId);
   return TRUE;
}

// @mfunc Initialize dialog.

BOOL HistAmtReviewDialog::OnInitDialog() 
{
   m_year = m_istartyear;
   setupdata();
   CDialog::OnInitDialog();
	
   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

// @mfunc Handle Next Year button.

void HistAmtReviewDialog::OnHistnextyear() 
{
   if (m_year < m_ilastyear)
      m_year++;
   setupdata();
   UpdateData(FALSE);
}

// @mfunc Handle Previous Year button.

void HistAmtReviewDialog::OnHistprevyear() 
{
   if (m_year > m_istartyear)
      m_year--;
   setupdata();
   UpdateData(FALSE);
}

// @mfunc Set up data to be displayed for one year.

void HistAmtReviewDialog::setupdata()
{
   CStatic* pS = (CStatic*) GetDlgItem(IDC_HISTAMTREVIEW);
   CString histamtstring;
   AfxFormatString1(histamtstring, PIA_IDS_HISTAMTUPDATE,
      poutNoComma(m_year).c_str());
   pS->SetWindowText(histamtstring);
   // display descriptions
   pS = (CStatic*) GetDlgItem(IDC_REVIEWWBTEXT);
   AfxFormatString1(histamtstring, PIA_IDS_UPDATEWB,
      poutNoComma(m_year).c_str());
   pS->SetWindowText(histamtstring);
   pS = (CStatic*) GetDlgItem(IDC_REVIEWWBOLDTEXT);
   AfxFormatString1(histamtstring, PIA_IDS_UPDATEWBOLD,
      poutNoComma(m_year).c_str());
   pS->SetWindowText(histamtstring);
   pS = (CStatic*) GetDlgItem(IDC_REVIEWBITEXT);
   if (m_year > 1983) {
      AfxFormatString1(histamtstring, PIA_IDS_UPDATEBI,
         poutNoComma(m_year - 1).c_str());
   }
   else {
      AfxFormatString1(histamtstring, PIA_IDS_REVIEWBI,
         poutNoComma(m_year - 1).c_str());
   }
   pS->SetWindowText(histamtstring);
   pS = (CStatic*) GetDlgItem(IDC_REVIEWAWTEXT);
   AfxFormatString1(histamtstring, PIA_IDS_UPDATEAW,
      poutNoComma(m_year - 2).c_str());
   pS->SetWindowText(histamtstring);
   // display amounts
   pS = (CStatic*) GetDlgItem(IDC_REVIEWWB);
   histamtstring = poutComma(m_wb[m_year], 3).c_str();
   pS->SetWindowText(histamtstring);
   pS = (CStatic*) GetDlgItem(IDC_REVIEWWBOLD);
   histamtstring = poutComma(m_wbold[m_year], 3).c_str();
   pS->SetWindowText(histamtstring);
   pS = (CStatic*) GetDlgItem(IDC_REVIEWAW);
   histamtstring = poutComma(m_fq[m_year - 2], 3, 2).c_str();
   pS->SetWindowText(histamtstring);
   pS = (CStatic*) GetDlgItem(IDC_REVIEWBI);
   histamtstring = poutNoComma(m_bi[m_year - 1], 2, 1).c_str();
   pS->SetWindowText(histamtstring);
}

// @mfunc Handles Help button click.

void HistAmtReviewDialog::OnHistamtreviewhelp() 
{
   HtmlHelp((DWORD_PTR)"/html/Properties/properties_histamt_rev.html",
      HH_DISPLAY_TOPIC);
}
