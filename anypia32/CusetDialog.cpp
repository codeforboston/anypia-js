// $Id: CusetDialog.cpp 1.7.1.2 2017/12/12 08:19:42EST 277133 Development  $
//
// Implementation of CusetDialog.

#include "stdafx.h"
#include "Anypia32.h"
#include "CusetDialog.h"
#include "comma.h"
#include "Htmlhelp.h"
#include "TextFloatFormatPatch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CusetDialog dialog

// Description: Constructor.
//
// Arguments:
//   pParent: Parent window (default NULL).
CusetDialog::CusetDialog( CWnd* pParent )
   : CDialog(CusetDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CusetDialog)
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

// Description: Exchange data with dialog.
//
// @parm Data to be exchanged.
void CusetDialog::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CusetDialog)
	DDX_Text2(pDX, IDC_CUPROJYEAR1, m_cuyear1);
	DDV_MinMaxDouble(pDX, m_cuyear1, 0., 99.9);
	DDX_Text2(pDX, IDC_CUPROJYEAR2, m_cuyear2);
	DDV_MinMaxDouble(pDX, m_cuyear2, 0., 99.9);
	DDX_Text2(pDX, IDC_CUPROJYEAR3, m_cuyear3);
	DDV_MinMaxDouble(pDX, m_cuyear3, 0., 99.9);
	DDX_Text2(pDX, IDC_CUPROJYEAR4, m_cuyear4);
	DDV_MinMaxDouble(pDX, m_cuyear4, 0., 99.9);
	DDX_Text2(pDX, IDC_CUPROJYEAR5, m_cuyear5);
	DDV_MinMaxDouble(pDX, m_cuyear5, 0., 99.9);
	DDX_Text2(pDX, IDC_CUPROJYEAR6, m_cuyear6);
	DDV_MinMaxDouble(pDX, m_cuyear6, 0., 99.9);
	DDX_Text2(pDX, IDC_CUPROJYEAR7, m_cuyear7);
	DDV_MinMaxDouble(pDX, m_cuyear7, 0., 99.9);
	DDX_Text2(pDX, IDC_CUPROJYEAR8, m_cuyear8);
	DDV_MinMaxDouble(pDX, m_cuyear8, 0., 99.9);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CusetDialog message handlers

BEGIN_MESSAGE_MAP(CusetDialog, CDialog)
	//{{AFX_MSG_MAP(CusetDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_CUPROJNEXTYEAR, OnCuprojnextyear)
	ON_BN_CLICKED(IDC_CUPROJPREVYEAR, OnCuprojprevyear)
	ON_BN_CLICKED(IDC_CUPROJSETHELP, OnCuprojsethelp)
	ON_BN_CLICKED(IDC_CUPROJCLEAR, OnCuprojclear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Description: Handles context-sensitive help.
//
// @parm Structure containing context when help was called.
BOOL CusetDialog::OnHelpInfo( HELPINFO* pHelpInfo ) 
{
   HtmlHelp(pHelpInfo->dwContextId);
   return TRUE;
}

// Description: Initialize dialog.
//
BOOL CusetDialog::OnInitDialog()
{
   m_ieligyear = m_cachup.getCstart();
   CStatic *pS = (CStatic *)GetDlgItem(IDC_CUPROJYEAR1TEXT);
   pS->SetWindowText(poutNoComma(m_cachup.getCstart() + 2).c_str());
   pS = (CStatic *)GetDlgItem(IDC_CUPROJYEAR2TEXT);
   pS->SetWindowText(poutNoComma(m_cachup.getCstart() + 3).c_str());
   pS = (CStatic *)GetDlgItem(IDC_CUPROJYEAR3TEXT);
   pS->SetWindowText(poutNoComma(m_cachup.getCstart() + 4).c_str());
   pS = (CStatic *)GetDlgItem(IDC_CUPROJYEAR4TEXT);
   pS->SetWindowText(poutNoComma(m_cachup.getCstart() + 5).c_str());
   pS = (CStatic *)GetDlgItem(IDC_CUPROJYEAR5TEXT);
   pS->SetWindowText(poutNoComma(m_cachup.getCstart() + 6).c_str());
   pS = (CStatic *)GetDlgItem(IDC_CUPROJYEAR6TEXT);
   pS->SetWindowText(poutNoComma(m_cachup.getCstart() + 7).c_str());
   pS = (CStatic *)GetDlgItem(IDC_CUPROJYEAR7TEXT);
   pS->SetWindowText(poutNoComma(m_cachup.getCstart() + 8).c_str());
   pS = (CStatic *)GetDlgItem(IDC_CUPROJYEAR8TEXT);
   pS->SetWindowText(poutNoComma(m_cachup.getCstart() + 9).c_str());
   setupdata();
   CString temp = "Set ";
   temp += poutNoComma(m_ialt).c_str();
   CEdit *pE = (CEdit*) GetDlgItem(IDC_CUPROJLABEL);
   pE->SetWindowText(temp);
   CDialog::OnInitDialog();

   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

// Description: Handles Next Year button click.
void CusetDialog::OnCuprojnextyear()
{
   if (check())
      return;
   if (m_ieligyear < m_cachup.getCstart() + 9)
      m_ieligyear++;
   setupdata();
   UpdateData(FALSE);
}

// Description: Handles Previous Year button click.
void CusetDialog::OnCuprojprevyear()
{
   if (check())
      return;
   if (m_ieligyear > m_cachup.getCstart())
      m_ieligyear--;
   setupdata();
   UpdateData(FALSE);
}

// Description: Handles OK button click.
void CusetDialog::OnOK()
{
   if (check())
      return;
   EndDialog(IDOK);
}

// Description: Checks data and saves results to member array.
//
bool CusetDialog::check()
{
   if (!UpdateData(TRUE))
      return(TRUE);
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

// Description: Fills in strings in dialog box.
void CusetDialog::setupdata()
{
   CStatic *pS = (CStatic *)GetDlgItem(IDC_ELIGYEARSET);
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

// Description: Handles Help button click.
void CusetDialog::OnCuprojsethelp() 
{
   HtmlHelp((DWORD_PTR)"/html/Properties/stored_catchup.html",
      HH_DISPLAY_TOPIC);
}

// Description: Handles Restore Defaults button click.
void CusetDialog::OnCuprojclear() 
{
   // point to correct section of ini file
   cachupIni->setData(m_ialt);
   // clear that section from the registry
   cachupIni->clear();
   // reset assumptions
   assumptions->catchupDoc.read(m_ialt);
   setdata();
   setupdata();
   UpdateData(FALSE);
}

// Description: Sets data to stored values.
void CusetDialog::setdata()
{
   assumptions->catchupDoc.setData(m_ialt);
   m_cachup = assumptions->catchupDoc.catchup;
}
