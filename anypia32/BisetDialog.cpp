// $Id: BisetDialog.cpp 1.13.1.3 2017/12/12 08:19:41EST 277133 Development  $
//
// Implementation of BisetDialog.

#include "stdafx.h"
#include "Anypia32.h"
#include "BisetDialog.h"
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
// BisetDialog dialog

// Description: Constructor.
//
// Arguments:
//   pParent: Parent window (default NULL).
BisetDialog::BisetDialog( CWnd* pParent )
   : CDialog(BisetDialog::IDD, pParent),
   m_biproj(YEAR51, WorkerData::getMaxyear())
{
	//{{AFX_DATA_INIT(BisetDialog)
	m_biprojult = 0.0;
	m_biprojyear1 = 0.0;
	m_biprojyear10 = 0.0;
	m_biprojyear11 = 0.0;
	m_biprojyear12 = 0.0;
	m_biprojyear13 = 0.0;
	m_biprojyear14 = 0.0;
	m_biprojyear15 = 0.0;
	m_biprojyear2 = 0.0;
	m_biprojyear3 = 0.0;
	m_biprojyear4 = 0.0;
	m_biprojyear5 = 0.0;
	m_biprojyear6 = 0.0;
	m_biprojyear7 = 0.0;
	m_biprojyear8 = 0.0;
	m_biprojyear9 = 0.0;
	m_cachup = FALSE;
	m_biprojtitle = _T("");
	//}}AFX_DATA_INIT
}

// Description: Exchange data with dialog.
//
// Arguments:
//   pDX: Data to be exchanged.
void BisetDialog::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BisetDialog)
	DDX_Text2(pDX, IDC_BIPROJULT, m_biprojult);
	DDV_MinMaxDouble(pDX, m_biprojult, 0., 99.9);
	DDX_Text2(pDX, IDC_BIPROJYEAR1, m_biprojyear1);
	DDV_MinMaxDouble(pDX, m_biprojyear1, 0., 99.9);
	DDX_Text2(pDX, IDC_BIPROJYEAR10, m_biprojyear10);
	DDV_MinMaxDouble(pDX, m_biprojyear10, 0., 99.9);
	DDX_Text2(pDX, IDC_BIPROJYEAR11, m_biprojyear11);
	DDV_MinMaxDouble(pDX, m_biprojyear11, 0., 99.9);
	DDX_Text2(pDX, IDC_BIPROJYEAR12, m_biprojyear12);
	DDV_MinMaxDouble(pDX, m_biprojyear12, 0., 99.9);
	DDX_Text2(pDX, IDC_BIPROJYEAR13, m_biprojyear13);
	DDV_MinMaxDouble(pDX, m_biprojyear13, 0., 99.9);
	DDX_Text2(pDX, IDC_BIPROJYEAR14, m_biprojyear14);
	DDV_MinMaxDouble(pDX, m_biprojyear14, 0., 99.9);
	DDX_Text2(pDX, IDC_BIPROJYEAR15, m_biprojyear15);
	DDV_MinMaxDouble(pDX, m_biprojyear15, 0., 99.9);
	DDX_Text2(pDX, IDC_BIPROJYEAR2, m_biprojyear2);
	DDV_MinMaxDouble(pDX, m_biprojyear2, 0., 99.9);
	DDX_Text2(pDX, IDC_BIPROJYEAR3, m_biprojyear3);
	DDV_MinMaxDouble(pDX, m_biprojyear3, 0., 99.9);
	DDX_Text2(pDX, IDC_BIPROJYEAR4, m_biprojyear4);
	DDV_MinMaxDouble(pDX, m_biprojyear4, 0., 99.9);
	DDX_Text2(pDX, IDC_BIPROJYEAR5, m_biprojyear5);
	DDV_MinMaxDouble(pDX, m_biprojyear5, 0., 99.9);
	DDX_Text2(pDX, IDC_BIPROJYEAR6, m_biprojyear6);
	DDV_MinMaxDouble(pDX, m_biprojyear6, 0., 99.9);
	DDX_Text2(pDX, IDC_BIPROJYEAR7, m_biprojyear7);
	DDV_MinMaxDouble(pDX, m_biprojyear7, 0., 99.9);
	DDX_Text2(pDX, IDC_BIPROJYEAR8, m_biprojyear8);
	DDV_MinMaxDouble(pDX, m_biprojyear8, 0., 99.9);
	DDX_Text2(pDX, IDC_BIPROJYEAR9, m_biprojyear9);
	DDV_MinMaxDouble(pDX, m_biprojyear9, 0., 99.9);
	DDX_Check(pDX, IDC_CACHUPPROJ, m_cachup);
	DDX_Text(pDX, IDC_BIPROJTITLE, m_biprojtitle);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// BisetDialog message handlers

BEGIN_MESSAGE_MAP(BisetDialog, CDialog)
	//{{AFX_MSG_MAP(BisetDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_BIPROJSETHELP, OnBiprojsethelp)
	ON_BN_CLICKED(IDC_BIPROJCLEAR, OnBiprojclear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Description: Handles context-sensitive help.
//
// Arguments:
//   pHelpInfo: Structure containing context when help was called.
BOOL BisetDialog::OnHelpInfo( HELPINFO* pHelpInfo )
{
   HtmlHelp(pHelpInfo->dwContextId);
   return TRUE;
}

// Description: Initialize dialog.
//
// Returns: TRUE (focus is not set to a control).
BOOL BisetDialog::OnInitDialog() 
{
   const char *month = "Dec ";

   CEdit* pE = (CEdit*) GetDlgItem(IDC_BIPROJYEAR1TEXT);
   CString temp = month;
   temp += poutNoComma(UserAssumptions::getIstart()).c_str();
   pE->SetWindowText(temp);
   pE = (CEdit*) GetDlgItem(IDC_BIPROJYEAR2TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 1).c_str();
   pE->SetWindowText(temp);
   pE = (CEdit*) GetDlgItem(IDC_BIPROJYEAR3TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 2).c_str();
   pE -> SetWindowText(temp);
   pE = (CEdit*) GetDlgItem(IDC_BIPROJYEAR4TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 3).c_str();
   pE -> SetWindowText(temp);
   pE = (CEdit*) GetDlgItem(IDC_BIPROJYEAR5TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 4).c_str();
   pE -> SetWindowText(temp);
   pE = (CEdit*) GetDlgItem(IDC_BIPROJYEAR6TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 5).c_str();
   pE -> SetWindowText(temp);
   pE = (CEdit*) GetDlgItem(IDC_BIPROJYEAR7TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 6).c_str();
   pE -> SetWindowText(temp);
   pE = (CEdit*) GetDlgItem(IDC_BIPROJYEAR8TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 7).c_str();
   pE -> SetWindowText(temp);
   pE = (CEdit*) GetDlgItem(IDC_BIPROJYEAR9TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 8).c_str();
   pE->SetWindowText(temp);
   pE = (CEdit*)GetDlgItem(IDC_BIPROJYEAR10TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 9).c_str();
   pE->SetWindowText(temp);
   pE = (CEdit*)GetDlgItem(IDC_BIPROJYEAR11TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 10).c_str();
   pE->SetWindowText(temp);
   pE = (CEdit*)GetDlgItem(IDC_BIPROJYEAR12TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 11).c_str();
   pE->SetWindowText(temp);
   pE = (CEdit*)GetDlgItem(IDC_BIPROJYEAR13TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 12).c_str();
   pE->SetWindowText(temp);
   pE = (CEdit*)GetDlgItem(IDC_BIPROJYEAR14TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 13).c_str();
   pE->SetWindowText(temp);
   pE = (CEdit*)GetDlgItem(IDC_BIPROJYEAR15TEXT);
   temp = month;
   temp += poutNoComma(UserAssumptions::getIstart() + 14).c_str();
   pE->SetWindowText(temp);
   AfxFormatString1(temp, PIA_IDS_ANDLATER,
      poutNoComma(UserAssumptions::getIstart() + 15).c_str());
   pE = (CEdit*)GetDlgItem(IDC_BIPROJULTTEXT);
   pE->SetWindowText(temp);
   temp = "Set ";
   temp += poutNoComma(m_ialt).c_str();
   pE = (CEdit*)GetDlgItem(IDC_BIPROJLABEL);
   pE->SetWindowText(temp);
   CDialog::OnInitDialog();

   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

// Description: Handle OK button click.
void BisetDialog::OnOK() 
{
   if (!UpdateData(TRUE))
      return;
   m_biproj[UserAssumptions::getIstart()] = m_biprojyear1;
   m_biproj[UserAssumptions::getIstart() + 1] = m_biprojyear2;
   m_biproj[UserAssumptions::getIstart() + 2] = m_biprojyear3;
   m_biproj[UserAssumptions::getIstart() + 3] = m_biprojyear4;
   m_biproj[UserAssumptions::getIstart() + 4] = m_biprojyear5;
   m_biproj[UserAssumptions::getIstart() + 5] = m_biprojyear6;
   m_biproj[UserAssumptions::getIstart() + 6] = m_biprojyear7;
   m_biproj[UserAssumptions::getIstart() + 7] = m_biprojyear8;
   m_biproj[UserAssumptions::getIstart() + 8] = m_biprojyear9;
   m_biproj[UserAssumptions::getIstart() + 9] = m_biprojyear10;
   m_biproj[UserAssumptions::getIstart() + 10] = m_biprojyear11;
   m_biproj[UserAssumptions::getIstart() + 11] = m_biprojyear12;
   m_biproj[UserAssumptions::getIstart() + 12] = m_biprojyear13;
   m_biproj[UserAssumptions::getIstart() + 13] = m_biprojyear14;
   m_biproj[UserAssumptions::getIstart() + 14] = m_biprojyear15;
   m_biproj[UserAssumptions::getIstart() + 15] = m_biprojult;
   for (int i = UserAssumptions::getIstart() + 16; i <= m_biproj.getLastYear(); i++) {
     m_biproj[i] = m_biprojult;
   }
   EndDialog(IDOK);
}

// Description: Handles Help button click.
void BisetDialog::OnBiprojsethelp() 
{
   HtmlHelp((DWORD_PTR)"/html/Properties/stored_ben_inc.html",
      HH_DISPLAY_TOPIC);
}

// Description: Clears corresponding ini file and resets to stored values.
void BisetDialog::OnBiprojclear() 
{
   // point to correct section of ini file
   biprojIni->setData(m_ialt);
   // clear that section
   biprojIni->clear();
   // reset assumptions
   assumptions->biProj.read(m_ialt);
   setdata();
   userAssumptions->zeroJalt();
   UpdateData(FALSE);
}

// Description: Sets data to stored values.
void BisetDialog::setdata()
{
   // set displayed values
   m_biprojtitle = CString(assumptions->getBenefitInc(m_ialt).c_str());
   assumptions->biProj.setData(m_ialt);
   for (int i = 0; i <= BiprojNonFile::NUMPROJYEARS; i++) {
      int year = UserAssumptions::getIstart() + i;
      m_biproj[year] = assumptions->biProj.theData[year];
   }
   for (int i = UserAssumptions::getIstart() + BiprojNonFile::NUMPROJYEARS + 1;
        i <= m_biproj.getLastYear(); i++) {
     m_biproj[i] = m_biproj[UserAssumptions::getIstart() + BiprojNonFile::NUMPROJYEARS];
   }
   m_biprojyear1 = m_biproj[UserAssumptions::getIstart()];
   m_biprojyear2 = m_biproj[UserAssumptions::getIstart() + 1];
   m_biprojyear3 = m_biproj[UserAssumptions::getIstart() + 2];
   m_biprojyear4 = m_biproj[UserAssumptions::getIstart() + 3];
   m_biprojyear5 = m_biproj[UserAssumptions::getIstart() + 4];
   m_biprojyear6 = m_biproj[UserAssumptions::getIstart() + 5];
   m_biprojyear7 = m_biproj[UserAssumptions::getIstart() + 6];
   m_biprojyear8 = m_biproj[UserAssumptions::getIstart() + 7];
   m_biprojyear9 = m_biproj[UserAssumptions::getIstart() + 8];
   m_biprojyear10 = m_biproj[UserAssumptions::getIstart() + 9];
   m_biprojyear11 = m_biproj[UserAssumptions::getIstart() + 10];
   m_biprojyear12 = m_biproj[UserAssumptions::getIstart() + 11];
   m_biprojyear13 = m_biproj[UserAssumptions::getIstart() + 12];
   m_biprojyear14 = m_biproj[UserAssumptions::getIstart() + 13];
   m_biprojyear15 = m_biproj[UserAssumptions::getIstart() + 14];
   m_biprojult = m_biproj[UserAssumptions::getIstart() + 15];
}
