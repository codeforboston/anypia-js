// $Id: HistAmtModifyDialog.cpp 1.10.1.2 2017/12/12 08:19:43EST 277133 Development  $
//
// Implementation of HistAmtModifyDialog.

#include "stdafx.h"
#include "Anypia32.h"
#include "HistAmtModifyDialog.h"
#include "pia.h"
#include "comma.h"
#include "Htmlhelp.h"
#include "oactcnst.h"
#include "TextFloatFormatPatch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// HistAmtModifyDialog dialog

// Description: Constructor.
//
// Arguments:
//   pParent: Parent window (default NULL).
HistAmtModifyDialog::HistAmtModifyDialog( CWnd* pParent )
   : CDialog(HistAmtModifyDialog::IDD, pParent),
   m_DAwb(YEAR37, WorkerData::getMaxyear()),
   m_DAwbold(YEAR37, WorkerData::getMaxyear()),
   m_DAaw(YEAR37, WorkerData::getMaxyear()),
   m_FAbi(YEAR51, WorkerData::getMaxyear())
{
	//{{AFX_DATA_INIT(HistAmtModifyDialog)
	m_aw = 0.0;
	m_bi = 0.0;
	m_wb = 0.0;
	m_wbold = 0.0;
	//}}AFX_DATA_INIT
}

// @mfunc Exchange data with dialog.
//
// @parm Data to be exchanged.

void HistAmtModifyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(HistAmtModifyDialog)
	DDX_Text2(pDX, IDC_MODIFYAW, m_aw);
	DDV_MinMaxDouble(pDX, m_aw, 0., MAXEARN);
	DDX_Text2(pDX, IDC_MODIFYBI, m_bi);
	DDV_MinMaxDouble(pDX, m_bi, 0., 99.9);
	DDX_Text2(pDX, IDC_MODIFYWB, m_wb);
	DDV_MinMaxDouble(pDX, m_wb, 0., MAXEARN);
	DDX_Text2(pDX, IDC_MODIFYWBOLD, m_wbold);
	DDV_MinMaxDouble(pDX, m_wbold, 0., MAXEARN);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// HistAmtModifyDialog message handlers

BEGIN_MESSAGE_MAP(HistAmtModifyDialog, CDialog)
	//{{AFX_MSG_MAP(HistAmtModifyDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_HISTMODNEXTYEAR, OnHistmodnextyear)
	ON_BN_CLICKED(IDC_HISTMODPREVYEAR, OnHistmodprevyear)
	ON_BN_CLICKED(IDC_HISTAMTMODIFYHELP, OnHistamtmodifyhelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// @mfunc Handle OK button click.

void HistAmtModifyDialog::OnOK() 
{
   if (check())
      return;
   EndDialog(IDOK);
}

// @mfunc Initialize dialog.

BOOL HistAmtModifyDialog::OnInitDialog() 
{
   m_year = m_istartyear;
   setupdata();
   CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// @mfunc Handles context-sensitive help.
//
// @parm Structure containing context when help was called.

BOOL HistAmtModifyDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
   HtmlHelp(pHelpInfo->dwContextId);
   return TRUE;
}

// @mfunc Handle Next Year button.

void HistAmtModifyDialog::OnHistmodnextyear() 
{
   if (check())
      return;
   if (m_year < m_ilastyear)
      m_year++;
   setupdata();
   UpdateData(FALSE);
}

// @mfunc Handle Previous Year button.

void HistAmtModifyDialog::OnHistmodprevyear() 
{
   if (check())
      return;
   if (m_year > m_istartyear)
      m_year--;
   setupdata();
   UpdateData(FALSE);
}

// @mfunc Set up data to be displayed for one year.

void HistAmtModifyDialog::setupdata()
{
   m_wb = m_DAwb[m_year];
   m_wbold = m_DAwbold[m_year];
   m_aw = m_DAaw[m_year - 2];
   m_bi = m_FAbi[m_year - 1];
   CStatic* pS = (CStatic*) GetDlgItem(IDC_HISTAMTMODIFY);
   CString histamtstring;
   AfxFormatString1(histamtstring, PIA_IDS_HISTAMTUPDATE,
      poutNoComma(m_year).c_str());
   pS->SetWindowText(histamtstring);
   // display descriptions
   pS = (CStatic*) GetDlgItem(IDC_MODIFYWBTEXT);
   AfxFormatString1(histamtstring, PIA_IDS_UPDATEWB,
      poutNoComma(m_year).c_str());
   pS->SetWindowText(histamtstring);
   pS = (CStatic*) GetDlgItem(IDC_MODIFYWBOLDTEXT);
   AfxFormatString1(histamtstring, PIA_IDS_UPDATEWBOLD,
      poutNoComma(m_year).c_str());
   pS->SetWindowText(histamtstring);
   pS = (CStatic*) GetDlgItem(IDC_MODIFYBITEXT);
   if (m_year > 1982) {
      AfxFormatString1(histamtstring, PIA_IDS_UPDATEBI,
         poutNoComma(m_year - 1).c_str());
   }
   else {
      AfxFormatString1(histamtstring, PIA_IDS_REVIEWBI,
         poutNoComma(m_year - 1).c_str());
   }
   pS->SetWindowText(histamtstring);
   pS = (CStatic*) GetDlgItem(IDC_MODIFYAWTEXT);
   AfxFormatString1(histamtstring, PIA_IDS_UPDATEAW,
      poutNoComma(m_year - 2).c_str());
   pS->SetWindowText(histamtstring);
   // display amounts
   pS = (CStatic*) GetDlgItem(IDC_MODIFYWB);
   histamtstring = poutComma(m_DAwb[m_year], 3).c_str();
   pS->SetWindowText(histamtstring);
   pS = (CStatic*) GetDlgItem(IDC_MODIFYWBOLD);
   histamtstring = poutComma(m_DAwbold[m_year], 3).c_str();
   pS->SetWindowText(histamtstring);
   pS = (CStatic*) GetDlgItem(IDC_MODIFYAW);
   histamtstring = poutComma(m_DAaw[m_year - 2], 3, 2).c_str();
   pS->SetWindowText(histamtstring);
   pS = (CStatic*) GetDlgItem(IDC_MODIFYBI);
   histamtstring = poutComma(m_FAbi[m_year - 1], 2, 1).c_str();
   pS->SetWindowText(histamtstring);
}

// @mfunc Checks data for inconsistencies.

bool HistAmtModifyDialog::check()
{
   if (!UpdateData(TRUE))
      return(true);
   if (m_year < m_istartyear || m_year > m_ilastyear) {
      AfxMessageBox("Year is out of range");
      return(true);
   }
   m_DAwb[m_year] = m_wb;
   m_DAwbold[m_year] = m_wbold;
   m_DAaw[m_year - 2] = m_aw;
   m_FAbi[m_year - 1] = m_bi;
   return(false);
}

// @mfunc Handles Help button click.

void HistAmtModifyDialog::OnHistamtmodifyhelp() 
{
   HtmlHelp((DWORD_PTR)"/html/Properties/properties_histamt_mod.html",
      HH_DISPLAY_TOPIC);
}
