// $Id: BiprojDialog.cpp 1.12.1.2 2017/12/12 08:19:40EST 277133 Development  $
//
// Implementation of BiprojDialog.

#include "stdafx.h"
#include "Anypia32.h"
#include "BiprojDialog.h"
#include "pia.h"
#include "comma.h"
#include "UserAssumptions.h"
#include "Htmlhelp.h"
#include "oactcnst.h"
#include "TextFloatFormatPatch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// BiprojDialog dialog

// Description: Constructor.
//
// Arguments:
//   pParent: Parent window (default NULL).
BiprojDialog::BiprojDialog( CWnd* pParent )
	: CDialog(BiprojDialog::IDD, pParent),
   m_biproj(YEAR51, WorkerData::getMaxyear())
{
	//{{AFX_DATA_INIT(BiprojDialog)
	m_biult = 0.0;
	m_biyear1 = 0.0;
	m_biyear10 = 0.0;
	m_biyear11 = 0.0;
	m_biyear12 = 0.0;
	m_biyear13 = 0.0;
	m_biyear14 = 0.0;
	m_biyear15 = 0.0;
	m_biyear2 = 0.0;
	m_biyear3 = 0.0;
	m_biyear4 = 0.0;
	m_biyear5 = 0.0;
	m_biyear6 = 0.0;
	m_biyear7 = 0.0;
	m_biyear8 = 0.0;
	m_biyear9 = 0.0;
	//}}AFX_DATA_INIT
}

// Description: Exchange data with dialog.
//
// Arguments:
//   pDX: Data to be exchanged.
void BiprojDialog::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BiprojDialog)
	DDX_Text2(pDX, IDC_BIULT, m_biult);
	DDV_MinMaxDouble(pDX, m_biult, 0.0, 99.9);
	DDX_Text2(pDX, IDC_BIYEAR1, m_biyear1);
	DDV_MinMaxDouble(pDX, m_biyear1, 0.0, 99.9);
	DDX_Text2(pDX, IDC_BIYEAR10, m_biyear10);
	DDV_MinMaxDouble(pDX, m_biyear10, 0.0, 99.9);
	DDX_Text2(pDX, IDC_BIYEAR11, m_biyear11);
	DDV_MinMaxDouble(pDX, m_biyear11, 0.0, 99.9);
	DDX_Text2(pDX, IDC_BIYEAR12, m_biyear12);
	DDV_MinMaxDouble(pDX, m_biyear12, 0.0, 99.9);
	DDX_Text2(pDX, IDC_BIYEAR13, m_biyear13);
	DDV_MinMaxDouble(pDX, m_biyear13, 0.0, 99.9);
	DDX_Text2(pDX, IDC_BIYEAR14, m_biyear14);
	DDV_MinMaxDouble(pDX, m_biyear14, 0.0, 99.9);
	DDX_Text2(pDX, IDC_BIYEAR15, m_biyear15);
	DDV_MinMaxDouble(pDX, m_biyear15, 0.0, 99.9);
	DDX_Text2(pDX, IDC_BIYEAR2, m_biyear2);
	DDV_MinMaxDouble(pDX, m_biyear2, 0.0, 99.9);
	DDX_Text2(pDX, IDC_BIYEAR3, m_biyear3);
	DDV_MinMaxDouble(pDX, m_biyear3, 0.0, 99.9);
	DDX_Text2(pDX, IDC_BIYEAR4, m_biyear4);
	DDV_MinMaxDouble(pDX, m_biyear4, 0.0, 99.9);
	DDX_Text(pDX, IDC_BIYEAR5, m_biyear5);
	DDV_MinMaxDouble(pDX, m_biyear5, 0.0, 99.9);
	DDX_Text2(pDX, IDC_BIYEAR6, m_biyear6);
	DDV_MinMaxDouble(pDX, m_biyear6, 0.0, 99.9);
	DDX_Text2(pDX, IDC_BIYEAR7, m_biyear7);
	DDV_MinMaxDouble(pDX, m_biyear7, 0.0, 99.9);
	DDX_Text2(pDX, IDC_BIYEAR8, m_biyear8);
	DDV_MinMaxDouble(pDX, m_biyear8, 0.0, 99.9);
	DDX_Text2(pDX, IDC_BIYEAR9, m_biyear9);
	DDV_MinMaxDouble(pDX, m_biyear9, 0.0, 99.9);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// BiprojDialog message handlers

BEGIN_MESSAGE_MAP(BiprojDialog, CDialog)
	//{{AFX_MSG_MAP(BiprojDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_BIPROJHELP, OnBiprojhelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Description: Handles OK button click.
void BiprojDialog::OnOK()
{
   if (!UpdateData(TRUE))
      return;
   m_biproj[UserAssumptions::getIstart()] = m_biyear1;
   m_biproj[UserAssumptions::getIstart() + 1] = m_biyear2;
   m_biproj[UserAssumptions::getIstart() + 2] = m_biyear3;
   m_biproj[UserAssumptions::getIstart() + 3] = m_biyear4;
   m_biproj[UserAssumptions::getIstart() + 4] = m_biyear5;
   m_biproj[UserAssumptions::getIstart() + 5] = m_biyear6;
   m_biproj[UserAssumptions::getIstart() + 6] = m_biyear7;
   m_biproj[UserAssumptions::getIstart() + 7] = m_biyear8;
   m_biproj[UserAssumptions::getIstart() + 8] = m_biyear9;
   m_biproj[UserAssumptions::getIstart() + 9] = m_biyear10;
   m_biproj[UserAssumptions::getIstart() + 10] = m_biyear11;
   m_biproj[UserAssumptions::getIstart() + 11] = m_biyear12;
   m_biproj[UserAssumptions::getIstart() + 12] = m_biyear13;
   m_biproj[UserAssumptions::getIstart() + 13] = m_biyear14;
   m_biproj[UserAssumptions::getIstart() + 14] = m_biyear15;
   m_biproj[UserAssumptions::getIstart() + 15] = m_biult;
   EndDialog(IDOK);
}

// Description: Initializes dialog.
BOOL BiprojDialog::OnInitDialog()
{
   const char *month = "Dec ";  // month of benefit increase

   CEdit* pE = (CEdit*) GetDlgItem(IDC_BIYEAR1TEXT);
   CString temp = month;
   temp += poutNoComma(UserAssumptions::getIstart()).c_str();
   pE->SetWindowText(temp);
   m_biyear1 = m_biproj[UserAssumptions::getIstart()];
   pE = (CEdit*) GetDlgItem(IDC_BIYEAR2TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 1).c_str();
   pE->SetWindowText(temp);
   m_biyear2 = m_biproj[UserAssumptions::getIstart() + 1];
   pE = (CEdit*) GetDlgItem(IDC_BIYEAR3TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 2).c_str();
   pE->SetWindowText(temp);
   m_biyear3 = m_biproj[UserAssumptions::getIstart() + 2];
   pE = (CEdit*) GetDlgItem(IDC_BIYEAR4TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 3).c_str();
   pE->SetWindowText(temp);
   m_biyear4 = m_biproj[UserAssumptions::getIstart() + 3];
   pE = (CEdit*) GetDlgItem(IDC_BIYEAR5TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 4).c_str();
   pE -> SetWindowText(temp);
   m_biyear5 = m_biproj[UserAssumptions::getIstart() + 4];
   pE = (CEdit*) GetDlgItem(IDC_BIYEAR6TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 5).c_str();
   pE -> SetWindowText(temp);
   m_biyear6 = m_biproj[UserAssumptions::getIstart() + 5];
   pE = (CEdit*) GetDlgItem(IDC_BIYEAR7TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 6).c_str();
   pE->SetWindowText(temp);
   m_biyear7 = m_biproj[UserAssumptions::getIstart() + 6];
   pE = (CEdit*) GetDlgItem(IDC_BIYEAR8TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 7).c_str();
   pE->SetWindowText(temp);
   m_biyear8 = m_biproj[UserAssumptions::getIstart() + 7];
   pE = (CEdit*) GetDlgItem(IDC_BIYEAR9TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 8).c_str();
   pE->SetWindowText(temp);
   m_biyear9 = m_biproj[UserAssumptions::getIstart() + 8];
   pE = (CEdit*) GetDlgItem(IDC_BIYEAR10TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 9).c_str();
   pE->SetWindowText(temp);
   m_biyear10 = m_biproj[UserAssumptions::getIstart() + 9];
   pE = (CEdit*) GetDlgItem(IDC_BIYEAR11TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 10).c_str();
   pE->SetWindowText(temp);
   m_biyear11 = m_biproj[UserAssumptions::getIstart() + 10];
   pE = (CEdit*) GetDlgItem(IDC_BIYEAR12TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 11).c_str();
   pE->SetWindowText(temp);
   m_biyear12 = m_biproj[UserAssumptions::getIstart() + 11];
   pE = (CEdit*) GetDlgItem(IDC_BIYEAR13TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 12).c_str();
   pE->SetWindowText(temp);
   m_biyear13 = m_biproj[UserAssumptions::getIstart() + 12];
   pE = (CEdit*) GetDlgItem(IDC_BIYEAR14TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 13).c_str();
   pE->SetWindowText(temp);
   m_biyear14 = m_biproj[UserAssumptions::getIstart() + 13];
   pE = (CEdit*) GetDlgItem(IDC_BIYEAR15TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 14).c_str();
   pE->SetWindowText(temp);
   m_biyear15 = m_biproj[UserAssumptions::getIstart() + 14];
   AfxFormatString1(temp, PIA_IDS_ANDLATER,
      poutNoComma(UserAssumptions::getIstart() + 15).c_str());
   pE = (CEdit*) GetDlgItem(IDC_BIULTTEXT);
   pE->SetWindowText(temp);
   m_biult = m_biproj[UserAssumptions::getIstart() + 15];
   CDialog::OnInitDialog();

   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

// Description: Handles context-sensitive help.
//
// Arguments:
//   pHelpInfo: Structure containing context when help was called.
BOOL BiprojDialog::OnHelpInfo( HELPINFO* pHelpInfo )
{
   HtmlHelp(pHelpInfo->dwContextId);
   return TRUE;
}

// Description: Handles Help button click.
void BiprojDialog::OnBiprojhelp()
{
   HtmlHelp((DWORD_PTR)"/html/Forms/forms_benefit_increases.html",
      HH_DISPLAY_TOPIC);
}
