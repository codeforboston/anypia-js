// $Id: AwprojDialog.cpp 1.10.1.2 2017/12/12 08:19:39EST 277133 Development  $
//
// Implementation of AwprojDialog.

#include "stdafx.h"
#include "Anypia32.h"
#include "AwprojDialog.h"
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
// AwprojDialog dialog

// Description: Constructor.
//
// Arguments:
//   pParent: Parent window (default NULL).
AwprojDialog::AwprojDialog( CWnd* pParent ) :
CDialog(AwprojDialog::IDD, pParent), m_awproj(YEAR37, WorkerData::getMaxyear())
{
	//{{AFX_DATA_INIT(AwprojDialog)
	m_awult = 0.0;
	m_awyear1 = 0.0;
	m_awyear10 = 0.0;
	m_awyear11 = 0.0;
	m_awyear12 = 0.0;
	m_awyear13 = 0.0;
	m_awyear14 = 0.0;
	m_awyear15 = 0.0;
	m_awyear16 = 0.0;
	m_awyear2 = 0.0;
	m_awyear3 = 0.0;
	m_awyear4 = 0.0;
	m_awyear5 = 0.0;
	m_awyear6 = 0.0;
	m_awyear7 = 0.0;
	m_awyear8 = 0.0;
	m_awyear9 = 0.0;
	//}}AFX_DATA_INIT
}

// Description: Exchange data with dialog.
//
// Arguments:
//   pDX: Data to be exchanged.
void AwprojDialog::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AwprojDialog)
	DDX_Text2(pDX, IDC_AWULT, m_awult);
	DDV_MinMaxDouble(pDX, m_awult, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWYEAR1, m_awyear1);
	DDV_MinMaxDouble(pDX, m_awyear1, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWYEAR10, m_awyear10);
	DDV_MinMaxDouble(pDX, m_awyear10, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWYEAR11, m_awyear11);
	DDV_MinMaxDouble(pDX, m_awyear11, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWYEAR12, m_awyear12);
	DDV_MinMaxDouble(pDX, m_awyear12, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWYEAR13, m_awyear13);
	DDV_MinMaxDouble(pDX, m_awyear13, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWYEAR14, m_awyear14);
	DDV_MinMaxDouble(pDX, m_awyear14, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWYEAR15, m_awyear15);
	DDV_MinMaxDouble(pDX, m_awyear15, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWYEAR16, m_awyear16);
	DDV_MinMaxDouble(pDX, m_awyear16, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWYEAR2, m_awyear2);
	DDV_MinMaxDouble(pDX, m_awyear2, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWYEAR3, m_awyear3);
	DDV_MinMaxDouble(pDX, m_awyear3, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWYEAR4, m_awyear4);
	DDV_MinMaxDouble(pDX, m_awyear4, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWYEAR5, m_awyear5);
	DDV_MinMaxDouble(pDX, m_awyear5, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWYEAR6, m_awyear6);
	DDV_MinMaxDouble(pDX, m_awyear6, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWYEAR7, m_awyear7);
	DDV_MinMaxDouble(pDX, m_awyear7, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWYEAR8, m_awyear8);
	DDV_MinMaxDouble(pDX, m_awyear8, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWYEAR9, m_awyear9);
	DDV_MinMaxDouble(pDX, m_awyear9, -9.99, 99.99);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// AwprojDialog message handlers

BEGIN_MESSAGE_MAP(AwprojDialog, CDialog)
	//{{AFX_MSG_MAP(AwprojDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_AWPROJHELP, OnAwprojhelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Description: Handles context-sensitive help.
//
// Returns: TRUE.
//
// Arguments:
//   pHelpInfo: Structure containing context when help was called.
BOOL AwprojDialog::OnHelpInfo( HELPINFO* pHelpInfo )
{
   HtmlHelp(pHelpInfo->dwContextId);
   return TRUE;
}

// Description: Initialize dialog.
//
// Returns: TRUE.
BOOL AwprojDialog::OnInitDialog()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_AWYEAR1TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() - 1).c_str());
   m_awyear1 = m_awproj[UserAssumptions::getIstart() - 1];
   pE = (CEdit*) GetDlgItem(IDC_AWYEAR2TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart()).c_str());
   m_awyear2 = m_awproj[UserAssumptions::getIstart()];
   pE = (CEdit*) GetDlgItem(IDC_AWYEAR3TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 1).c_str());
   m_awyear3 = m_awproj[UserAssumptions::getIstart() + 1];
   pE = (CEdit*) GetDlgItem(IDC_AWYEAR4TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 2).c_str());
   m_awyear4 = m_awproj[UserAssumptions::getIstart() + 2];
   pE = (CEdit*) GetDlgItem(IDC_AWYEAR5TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 3).c_str());
   m_awyear5 = m_awproj[UserAssumptions::getIstart() + 3];
   pE = (CEdit*) GetDlgItem(IDC_AWYEAR6TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 4).c_str());
   m_awyear6 = m_awproj[UserAssumptions::getIstart() + 4];
   pE = (CEdit*) GetDlgItem(IDC_AWYEAR7TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 5).c_str());
   m_awyear7 = m_awproj[UserAssumptions::getIstart() + 5];
   pE = (CEdit*) GetDlgItem(IDC_AWYEAR8TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 6).c_str());
   m_awyear8 = m_awproj[UserAssumptions::getIstart() + 6];
   pE = (CEdit*) GetDlgItem(IDC_AWYEAR9TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 7).c_str());
   m_awyear9 = m_awproj[UserAssumptions::getIstart() + 7];
   pE = (CEdit*) GetDlgItem(IDC_AWYEAR10TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 8).c_str());
   m_awyear10 = m_awproj[UserAssumptions::getIstart() + 8];
   pE = (CEdit*)GetDlgItem(IDC_AWYEAR11TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 9).c_str());
   m_awyear11 = m_awproj[UserAssumptions::getIstart() + 9];
   pE = (CEdit*)GetDlgItem(IDC_AWYEAR12TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 10).c_str());
   m_awyear12 = m_awproj[UserAssumptions::getIstart() + 10];
   pE = (CEdit*)GetDlgItem(IDC_AWYEAR13TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 11).c_str());
   m_awyear13 = m_awproj[UserAssumptions::getIstart() + 11];
   pE = (CEdit*)GetDlgItem(IDC_AWYEAR14TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 12).c_str());
   m_awyear14 = m_awproj[UserAssumptions::getIstart() + 12];
   pE = (CEdit*)GetDlgItem(IDC_AWYEAR15TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 13).c_str());
   m_awyear15 = m_awproj[UserAssumptions::getIstart() + 13];
   pE = (CEdit*)GetDlgItem(IDC_AWYEAR16TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 14).c_str());
   m_awyear16 = m_awproj[UserAssumptions::getIstart() + 14];
   CString temp;
   AfxFormatString1(temp, PIA_IDS_ANDLATER,
      poutNoComma(UserAssumptions::getIstart() + 15).c_str());
   pE = (CEdit*)GetDlgItem(IDC_AWULTTEXT);
   pE->SetWindowText(temp);
   m_awult = m_awproj[UserAssumptions::getIstart() + 15];
   CDialog::OnInitDialog();

   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

// Description: Handle OK button click.
void AwprojDialog::OnOK()
{
   if (!UpdateData(TRUE))
      return;
   m_awproj[UserAssumptions::getIstart() - 1] = m_awyear1;
   m_awproj[UserAssumptions::getIstart()] = m_awyear2;
   m_awproj[UserAssumptions::getIstart() + 1] = m_awyear3;
   m_awproj[UserAssumptions::getIstart() + 2] = m_awyear4;
   m_awproj[UserAssumptions::getIstart() + 3] = m_awyear5;
   m_awproj[UserAssumptions::getIstart() + 4] = m_awyear6;
   m_awproj[UserAssumptions::getIstart() + 5] = m_awyear7;
   m_awproj[UserAssumptions::getIstart() + 6] = m_awyear8;
   m_awproj[UserAssumptions::getIstart() + 7] = m_awyear9;
   m_awproj[UserAssumptions::getIstart() + 8] = m_awyear10;
   m_awproj[UserAssumptions::getIstart() + 9] = m_awyear11;
   m_awproj[UserAssumptions::getIstart() + 10] = m_awyear12;
   m_awproj[UserAssumptions::getIstart() + 11] = m_awyear13;
   m_awproj[UserAssumptions::getIstart() + 12] = m_awyear14;
   m_awproj[UserAssumptions::getIstart() + 13] = m_awyear15;
   m_awproj[UserAssumptions::getIstart() + 14] = m_awyear16;
   m_awproj[UserAssumptions::getIstart() + 15] = m_awult;
   EndDialog(IDOK);
}

// Description: Handles Help button click.
void AwprojDialog::OnAwprojhelp()
{
   HtmlHelp((DWORD_PTR)"/html/Forms/forms_avg_wage_increases.html",
      HH_DISPLAY_TOPIC);
}
