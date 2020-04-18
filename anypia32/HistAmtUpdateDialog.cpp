// @doc HISTAMTUPDATEDIALOG
// $Id: HistAmtUpdateDialog.cpp 1.6.1.2 2017/12/12 08:19:43EST 277133 Development  $
// @module HistAmtUpdateDialog.cpp |
//
// Implementation of HistAmtUpdateDialog.

#include "stdafx.h"
#include "Anypia32.h"
#include "HistAmtUpdateDialog.h"
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
// HistAmtUpdateDialog dialog

// @mfunc Constructor.
//
// @parm Parent window (default NULL).

HistAmtUpdateDialog::HistAmtUpdateDialog( CWnd* pParent )
	: CDialog(HistAmtUpdateDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(HistAmtUpdateDialog)
	m_aw = 0.0;
	m_bi = 0.0;
	m_wb = 0.0;
	m_wbold = 0.0;
	//}}AFX_DATA_INIT
   m_wbhi = MAXEARN;
}

// @mfunc Exchange data with dialog.
//
// @parm Data to be exchanged.

void HistAmtUpdateDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(HistAmtUpdateDialog)
	DDX_Text2(pDX, IDC_UPDATEAW, m_aw);
	DDV_MinMaxDouble(pDX, m_aw, 0.0, MAXEARN);
	DDX_Text2(pDX, IDC_UPDATEBI, m_bi);
	DDV_MinMaxDouble(pDX, m_bi, 0.0, 99.9);
	DDX_Text2(pDX, IDC_UPDATEWB, m_wb);
	DDV_MinMaxDouble(pDX, m_wb, 0.0, MAXEARN);
	DDX_Text2(pDX, IDC_UPDATEWBOLD, m_wbold);
	DDV_MinMaxDouble(pDX, m_wbold, 0.0, MAXEARN);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// HistAmtUpdateDialog message handlers

BEGIN_MESSAGE_MAP(HistAmtUpdateDialog, CDialog)
	//{{AFX_MSG_MAP(HistAmtUpdateDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_HISTAMTUPDATEHELP, OnHistamtupdatehelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// @mfunc Initialize dialog.

BOOL HistAmtUpdateDialog::OnInitDialog() 
{
   CStatic* pS = (CStatic*) GetDlgItem(IDC_HISTAMTUPDATE);
   CString histamtstring;
   AfxFormatString1(histamtstring, PIA_IDS_HISTAMTUPDATE,
      poutNoComma(m_year).c_str());
   pS->SetWindowText(histamtstring);
   pS = (CStatic*) GetDlgItem(IDC_UPDATEWBTEXT);
   AfxFormatString1(histamtstring, PIA_IDS_UPDATEWB,
      poutNoComma(m_year, 1).c_str());
   pS->SetWindowText(histamtstring);
   pS = (CStatic*) GetDlgItem(IDC_UPDATEWBOLDTEXT);
   AfxFormatString1(histamtstring, PIA_IDS_UPDATEWBOLD,
      poutNoComma(m_year).c_str());
   pS->SetWindowText(histamtstring);
   pS = (CStatic*) GetDlgItem(IDC_UPDATEBITEXT);
   AfxFormatString1(histamtstring, PIA_IDS_UPDATEBI,
      poutNoComma(m_year - 1).c_str());
   pS->SetWindowText(histamtstring);
   pS = (CStatic*) GetDlgItem(IDC_UPDATEAWTEXT);
   AfxFormatString1(histamtstring, PIA_IDS_UPDATEAW,
      poutNoComma(m_year - 2).c_str());
   pS->SetWindowText(histamtstring);
   CDialog::OnInitDialog();
	
   return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// @mfunc Handles context-sensitive help.
//
// @parm Structure containing context when help was called.

BOOL HistAmtUpdateDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
   HtmlHelp(pHelpInfo->dwContextId);
   return TRUE;
}

// @mfunc Handles Help button click.

void HistAmtUpdateDialog::OnHistamtupdatehelp() 
{
   HtmlHelp((DWORD_PTR)"/html/Properties/properties_histamt_upd.html",
      HH_DISPLAY_TOPIC);
}
