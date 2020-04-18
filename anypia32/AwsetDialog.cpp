// $Id: AwsetDialog.cpp 1.13.1.3 2017/12/12 08:19:40EST 277133 Development  $
//
// Implementation of AwsetDialog.

#include "stdafx.h"
#include "Anypia32.h"
#include "AwsetDialog.h"
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
// AwsetDialog dialog

// Description: Constructor.
//
// Arguments:
//   pParent: Parent window (default NULL).
AwsetDialog::AwsetDialog( CWnd* pParent ) : CDialog(AwsetDialog::IDD, pParent),
m_awproj(YEAR37, WorkerData::getMaxyear())
{
	//{{AFX_DATA_INIT(AwsetDialog)
	m_awprojtitle = _T("");
	m_awprojult = 0.0;
	m_awprojyear1 = 0.0;
	m_awprojyear10 = 0.0;
	m_awprojyear11 = 0.0;
	m_awprojyear12 = 0.0;
	m_awprojyear13 = 0.0;
	m_awprojyear14 = 0.0;
	m_awprojyear15 = 0.0;
	m_awprojyear16 = 0.0;
	m_awprojyear2 = 0.0;
	m_awprojyear3 = 0.0;
	m_awprojyear4 = 0.0;
	m_awprojyear5 = 0.0;
	m_awprojyear6 = 0.0;
	m_awprojyear7 = 0.0;
	m_awprojyear8 = 0.0;
	m_awprojyear9 = 0.0;
	//}}AFX_DATA_INIT
}

// Description: Exchange data with dialog.
//
// Arguments:
//   pDX: Data to be exchanged.
void AwsetDialog::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AwsetDialog)
	DDX_Text(pDX, IDC_AWPROJTITLE, m_awprojtitle);
	DDX_Text2(pDX, IDC_AWPROJULT, m_awprojult);
	DDV_MinMaxDouble(pDX, m_awprojult, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWPROJYEAR1, m_awprojyear1);
	DDV_MinMaxDouble(pDX, m_awprojyear1, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWPROJYEAR10, m_awprojyear10);
	DDV_MinMaxDouble(pDX, m_awprojyear10, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWPROJYEAR11, m_awprojyear11);
	DDV_MinMaxDouble(pDX, m_awprojyear11, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWPROJYEAR12, m_awprojyear12);
	DDV_MinMaxDouble(pDX, m_awprojyear12, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWPROJYEAR13, m_awprojyear13);
	DDV_MinMaxDouble(pDX, m_awprojyear13, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWPROJYEAR14, m_awprojyear14);
	DDV_MinMaxDouble(pDX, m_awprojyear14, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWPROJYEAR15, m_awprojyear15);
	DDV_MinMaxDouble(pDX, m_awprojyear15, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWPROJYEAR16, m_awprojyear16);
	DDV_MinMaxDouble(pDX, m_awprojyear16, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWPROJYEAR2, m_awprojyear2);
	DDV_MinMaxDouble(pDX, m_awprojyear2, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWPROJYEAR3, m_awprojyear3);
	DDV_MinMaxDouble(pDX, m_awprojyear3, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWPROJYEAR4, m_awprojyear4);
	DDV_MinMaxDouble(pDX, m_awprojyear4, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWPROJYEAR5, m_awprojyear5);
	DDV_MinMaxDouble(pDX, m_awprojyear5, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWPROJYEAR6, m_awprojyear6);
	DDV_MinMaxDouble(pDX, m_awprojyear6, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWPROJYEAR7, m_awprojyear7);
	DDV_MinMaxDouble(pDX, m_awprojyear7, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWPROJYEAR8, m_awprojyear8);
	DDV_MinMaxDouble(pDX, m_awprojyear8, -9.99, 99.99);
	DDX_Text2(pDX, IDC_AWPROJYEAR9, m_awprojyear9);
	DDV_MinMaxDouble(pDX, m_awprojyear9, -9.99, 99.99);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// AwsetDialog message handlers

BEGIN_MESSAGE_MAP(AwsetDialog, CDialog)
	//{{AFX_MSG_MAP(AwsetDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_AWPROJSETHELP, OnAwprojsethelp)
	ON_BN_CLICKED(IDC_AWPROJCLEAR, OnAwprojclear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Description: Handles context-sensitive help.
//
// Returns: TRUE.
//
// Arguments:
//   pHelpInfo: Structure containing context when help was called.
BOOL AwsetDialog::OnHelpInfo( HELPINFO* pHelpInfo ) 
{
   HtmlHelp(pHelpInfo->dwContextId);
   return TRUE;
}

// Description: Initialize dialog.
//
// Returns: TRUE (focus is not set to a control).
BOOL AwsetDialog::OnInitDialog() 
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_AWPROJYEAR1TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() - 1).c_str());
   pE = (CEdit*) GetDlgItem(IDC_AWPROJYEAR2TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart()).c_str());
   pE = (CEdit*) GetDlgItem(IDC_AWPROJYEAR3TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 1).c_str());
   pE = (CEdit*) GetDlgItem(IDC_AWPROJYEAR4TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 2).c_str());
   pE = (CEdit*) GetDlgItem(IDC_AWPROJYEAR5TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 3).c_str());
   pE = (CEdit*) GetDlgItem(IDC_AWPROJYEAR6TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 4).c_str());
   pE = (CEdit*) GetDlgItem(IDC_AWPROJYEAR7TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 5).c_str());
   pE = (CEdit*) GetDlgItem(IDC_AWPROJYEAR8TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 6).c_str());
   pE = (CEdit*) GetDlgItem(IDC_AWPROJYEAR9TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 7).c_str());
   pE = (CEdit*) GetDlgItem(IDC_AWPROJYEAR10TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 8).c_str());
   pE = (CEdit*)GetDlgItem(IDC_AWPROJYEAR11TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 9).c_str());
   pE = (CEdit*)GetDlgItem(IDC_AWPROJYEAR12TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 10).c_str());
   pE = (CEdit*)GetDlgItem(IDC_AWPROJYEAR13TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 11).c_str());
   pE = (CEdit*)GetDlgItem(IDC_AWPROJYEAR14TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 12).c_str());
   pE = (CEdit*)GetDlgItem(IDC_AWPROJYEAR15TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 13).c_str());
   pE = (CEdit*)GetDlgItem(IDC_AWPROJYEAR16TEXT);
   pE->SetWindowText(poutNoComma(UserAssumptions::getIstart() + 14).c_str());
   CString temp;
   AfxFormatString1(temp, PIA_IDS_ANDLATER,
      poutNoComma(UserAssumptions::getIstart() + 15).c_str());
   pE = (CEdit*)GetDlgItem(IDC_AWPROJULTTEXT);
   pE->SetWindowText(temp);
   temp = "Set ";
   temp += poutNoComma(m_ialt).c_str();
   pE = (CEdit*)GetDlgItem(IDC_AWPROJLABEL);
   pE->SetWindowText(temp);
   CDialog::OnInitDialog();

   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

// Description: Handle OK button click.
void AwsetDialog::OnOK()
{
   if (!UpdateData(TRUE))
      return;
   m_awproj[UserAssumptions::getIstart() - 1] = m_awprojyear1;
   m_awproj[UserAssumptions::getIstart()] = m_awprojyear2;
   m_awproj[UserAssumptions::getIstart() + 1] = m_awprojyear3;
   m_awproj[UserAssumptions::getIstart() + 2] = m_awprojyear4;
   m_awproj[UserAssumptions::getIstart() + 3] = m_awprojyear5;
   m_awproj[UserAssumptions::getIstart() + 4] = m_awprojyear6;
   m_awproj[UserAssumptions::getIstart() + 5] = m_awprojyear7;
   m_awproj[UserAssumptions::getIstart() + 6] = m_awprojyear8;
   m_awproj[UserAssumptions::getIstart() + 7] = m_awprojyear9;
   m_awproj[UserAssumptions::getIstart() + 8] = m_awprojyear10;
   m_awproj[UserAssumptions::getIstart() + 9] = m_awprojyear11;
   m_awproj[UserAssumptions::getIstart() + 10] = m_awprojyear12;
   m_awproj[UserAssumptions::getIstart() + 11] = m_awprojyear13;
   m_awproj[UserAssumptions::getIstart() + 12] = m_awprojyear14;
   m_awproj[UserAssumptions::getIstart() + 13] = m_awprojyear15;
   m_awproj[UserAssumptions::getIstart() + 14] = m_awprojyear16;
   m_awproj[UserAssumptions::getIstart() + 15] = m_awprojult;
   for (int i = UserAssumptions::getIstart() + AwincNonFile::NUMPROJYEARS;
        i <= m_awproj.getLastYear(); i++) {
     m_awproj[i] = m_awprojult;
   }
   EndDialog(IDOK);
}

// Description: Handles Help button click.
void AwsetDialog::OnAwprojsethelp()
{
   HtmlHelp((DWORD_PTR)"/html/Properties/stored_avg_wage.html",
      HH_DISPLAY_TOPIC);
}

// Description: Clears corresponding ini file and resets to stored values.
void AwsetDialog::OnAwprojclear() 
{
   // point to correct section of ini file
   awincIni->setData(m_ialt);
   // clear that section
   awincIni->clear();
   // reset assumptions
   assumptions->awincProj.read(m_ialt);
   setdata();
   userAssumptions->zeroJalt();
   UpdateData(FALSE);
}

// Description: Sets data to stored values.
void AwsetDialog::setdata()
{
   // set displayed values
   m_awprojtitle = CString(assumptions->getAverageWage(m_ialt).c_str());
   assumptions->awincProj.setData(m_ialt);
   for (int i = -1; i < AwincNonFile::NUMPROJYEARS; i++) {
      int year = UserAssumptions::getIstart() + i;
      m_awproj[year] = assumptions->awincProj.awinc[year];
   }
   for (int i = UserAssumptions::getIstart() + AwincNonFile::NUMPROJYEARS; 
        i <= m_awproj.getLastYear(); i++) {
     m_awproj[i] = m_awproj[UserAssumptions::getIstart() + AwincNonFile::NUMPROJYEARS - 1];
   }
   m_awprojyear1 = m_awproj[UserAssumptions::getIstart() -1];
   m_awprojyear2 = m_awproj[UserAssumptions::getIstart()];
   m_awprojyear3 = m_awproj[UserAssumptions::getIstart() + 1];
   m_awprojyear4 = m_awproj[UserAssumptions::getIstart() + 2];
   m_awprojyear5 = m_awproj[UserAssumptions::getIstart() + 3];
   m_awprojyear6 = m_awproj[UserAssumptions::getIstart() + 4];
   m_awprojyear7 = m_awproj[UserAssumptions::getIstart() + 5];
   m_awprojyear8 = m_awproj[UserAssumptions::getIstart() + 6];
   m_awprojyear9 = m_awproj[UserAssumptions::getIstart() + 7];
   m_awprojyear10 = m_awproj[UserAssumptions::getIstart() + 8];
   m_awprojyear11 = m_awproj[UserAssumptions::getIstart() + 9];
   m_awprojyear12 = m_awproj[UserAssumptions::getIstart() + 10];
   m_awprojyear13 = m_awproj[UserAssumptions::getIstart() + 11];
   m_awprojyear14 = m_awproj[UserAssumptions::getIstart() + 12];
   m_awprojyear15 = m_awproj[UserAssumptions::getIstart() + 13];
   m_awprojyear16 = m_awproj[UserAssumptions::getIstart() + 14];
   m_awprojult = m_awproj[UserAssumptions::getIstart() + 15];
}
