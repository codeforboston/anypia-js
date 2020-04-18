// @doc CUPROJDIALOG
// $Id: CuprojDialog.cpp 1.6.1.2 2017/12/12 08:19:41EST 277133 Development  $
// @module CuprojDialog.cpp |
//
// Implementation of CuprojDialog.

#include "stdafx.h"
#include "Anypia32.h"
#include "CuprojDialog.h"
#include "comma.h"
#include "Htmlhelp.h"
#include "TextFloatFormatPatch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CuprojDialog dialog

// @mfunc Constructor.
//
// @parm Parent window (default NULL).

CuprojDialog::CuprojDialog( CWnd* pParent )
	: CDialog(CuprojDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CuprojDialog)
	m_cuyear1 = 0.0;
	m_cuyear2 = 0.0;
	m_cuyear3 = 0.0;
	m_cuyear4 = 0.0;
	m_cuyear5 = 0.0;
	m_cuyear6 = 0.0;
	m_cuyear7 = 0.0;
	m_cuyear8 = 0.0;
	//}}AFX_DATA_INIT
}

// @mfunc Exchange data with dialog.
//
// @parm Data to be exchanged.

void CuprojDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CuprojDialog)
	DDX_Text2(pDX, IDC_CUYEAR1, m_cuyear1);
	DDV_MinMaxDouble(pDX, m_cuyear1, 0., 99.9);
	DDX_Text2(pDX, IDC_CUYEAR2, m_cuyear2);
	DDV_MinMaxDouble(pDX, m_cuyear2, 0., 99.9);
	DDX_Text2(pDX, IDC_CUYEAR3, m_cuyear3);
	DDV_MinMaxDouble(pDX, m_cuyear3, 0., 99.9);
	DDX_Text2(pDX, IDC_CUYEAR4, m_cuyear4);
	DDV_MinMaxDouble(pDX, m_cuyear4, 0., 99.9);
	DDX_Text2(pDX, IDC_CUYEAR5, m_cuyear5);
	DDV_MinMaxDouble(pDX, m_cuyear5, 0., 99.9);
	DDX_Text2(pDX, IDC_CUYEAR6, m_cuyear6);
	DDV_MinMaxDouble(pDX, m_cuyear6, 0., 99.9);
	DDX_Text2(pDX, IDC_CUYEAR7, m_cuyear7);
	DDV_MinMaxDouble(pDX, m_cuyear7, 0., 99.9);
	DDX_Text2(pDX, IDC_CUYEAR8, m_cuyear8);
	DDV_MinMaxDouble(pDX, m_cuyear8, 0., 99.9);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CuprojDialog message handlers

BEGIN_MESSAGE_MAP(CuprojDialog, CDialog)
	//{{AFX_MSG_MAP(CuprojDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_CUNEXTYEAR, OnCunextyear)
	ON_BN_CLICKED(IDC_CUPREVYEAR, OnCuprevyear)
	ON_BN_CLICKED(IDC_CUPROJHELP, OnCuprojhelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// @mfunc Initialize dialog.

BOOL CuprojDialog::OnInitDialog() 
{
   m_ieligyear = m_cachup.getCstart();
   CStatic *pS = (CStatic *)GetDlgItem(IDC_CUYEAR1TEXT);
   pS->SetWindowText(poutNoComma(m_cachup.getCstart() + 2).c_str());
   pS = (CStatic *)GetDlgItem(IDC_CUYEAR2TEXT);
   pS->SetWindowText(poutNoComma(m_cachup.getCstart() + 3).c_str());
   pS = (CStatic *)GetDlgItem(IDC_CUYEAR3TEXT);
   pS->SetWindowText(poutNoComma(m_cachup.getCstart() + 4).c_str());
   pS = (CStatic *)GetDlgItem(IDC_CUYEAR4TEXT);
   pS->SetWindowText(poutNoComma(m_cachup.getCstart() + 5).c_str());
   pS = (CStatic *)GetDlgItem(IDC_CUYEAR5TEXT);
   pS->SetWindowText(poutNoComma(m_cachup.getCstart() + 6).c_str());
   pS = (CStatic *)GetDlgItem(IDC_CUYEAR6TEXT);
   pS->SetWindowText(poutNoComma(m_cachup.getCstart() + 7).c_str());
   pS = (CStatic *)GetDlgItem(IDC_CUYEAR7TEXT);
   pS->SetWindowText(poutNoComma(m_cachup.getCstart() + 8).c_str());
   pS = (CStatic *)GetDlgItem(IDC_CUYEAR8TEXT);
   pS->SetWindowText(poutNoComma(m_cachup.getCstart() + 9).c_str());
   setupdata();
   CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// @mfunc Handles context-sensitive help.
//
// @parm Structure containing context when help was called.

BOOL CuprojDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
   HtmlHelp(pHelpInfo->dwContextId);
   return TRUE;
}

// @mfunc Handles Next Year button click.

void CuprojDialog::OnCunextyear() 
{
   if (check())
      return;
   if (m_ieligyear < m_cachup.getCstart() + 9)
      m_ieligyear++;
   setupdata();
   UpdateData(FALSE);
}

// @mfunc Handles Previous Year button click.

void CuprojDialog::OnCuprevyear() 
{
   if (check())
      return;
   if (m_ieligyear > m_cachup.getCstart())
      m_ieligyear--;
   setupdata();
   UpdateData(FALSE);
}

// @mfunc Handles OK button click.

void CuprojDialog::OnOK() 
{
    if (check())
        return;
    EndDialog(IDOK);
}

// @mfunc Checks data and saves results to member array.

bool CuprojDialog::check()
{
   if (!UpdateData(TRUE))
      return(true);
   m_cachup.set(m_ieligyear, m_cachup.getCstart() + 2, m_cuyear1);
   m_cachup.set(m_ieligyear, m_cachup.getCstart() + 3, m_cuyear2);
   m_cachup.set(m_ieligyear, m_cachup.getCstart() + 4, m_cuyear3);
   m_cachup.set(m_ieligyear, m_cachup.getCstart() + 5, m_cuyear4);
   m_cachup.set(m_ieligyear, m_cachup.getCstart() + 6, m_cuyear5);
   m_cachup.set(m_ieligyear, m_cachup.getCstart() + 7, m_cuyear6);
   m_cachup.set(m_ieligyear, m_cachup.getCstart() + 8, m_cuyear7);
   m_cachup.set(m_ieligyear, m_cachup.getCstart() + 9, m_cuyear8);
   return(false);
}

// @mfunc Fills in strings in dialog box.

void CuprojDialog::setupdata()
{
   CStatic *pS = (CStatic *)GetDlgItem(IDC_ELIGYEAR);
   pS->SetWindowText(CString(poutNoComma(m_ieligyear).c_str()));
   m_cuyear1 = m_cachup.get(m_ieligyear, m_cachup.getCstart() + 2);
   m_cuyear2 = m_cachup.get(m_ieligyear, m_cachup.getCstart() + 3);
   m_cuyear3 = m_cachup.get(m_ieligyear, m_cachup.getCstart() + 4);
   m_cuyear4 = m_cachup.get(m_ieligyear, m_cachup.getCstart() + 5);
   m_cuyear5 = m_cachup.get(m_ieligyear, m_cachup.getCstart() + 6);
   m_cuyear6 = m_cachup.get(m_ieligyear, m_cachup.getCstart() + 7);
   m_cuyear7 = m_cachup.get(m_ieligyear, m_cachup.getCstart() + 8);
   m_cuyear8 = m_cachup.get(m_ieligyear, m_cachup.getCstart() + 9);
}

// @mfunc Handles Help button click.

void CuprojDialog::OnCuprojhelp() 
{
   HtmlHelp((DWORD_PTR)"/html/Forms/forms_catchup_increases.html",
      HH_DISPLAY_TOPIC);
}
