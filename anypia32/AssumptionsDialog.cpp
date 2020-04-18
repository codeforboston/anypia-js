// $Id: AssumptionsDialog.cpp 1.9.1.2 2012/03/12 14:21:16EDT 277133 Development  $
//
// Implementation of AssumptionsDialog.

#include "stdafx.h"
#include "Anypia32.h"
#include "AssumptionsDialog.h"
#include "pia.h"
#include "UserAssumptions.h"
#include "Htmlhelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Description: AssumptionsDialog dialog.
//
// Arguments:
//   pParent: Parent window (default is NULL).
AssumptionsDialog::AssumptionsDialog( CWnd* pParent )
	: CDialog(AssumptionsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(AssumptionsDialog)
	m_bitext = _T("");
	m_awtext = _T("");
	m_cachup = FALSE;
	m_ialtaw = -1;
	m_ialtbi = -1;
	m_bases = -1;
	//}}AFX_DATA_INIT
}

// Description: Exchanges data between variables and dialog boxes.
//
// Arguments:
//   pDX: Context information for the exchange.
void AssumptionsDialog::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AssumptionsDialog)
	DDX_Text(pDX, IDC_BI_TEXT, m_bitext);
	DDV_MaxChars(pDX, m_bitext, 65);
	DDX_Text(pDX, IDC_AW_TEXT, m_awtext);
	DDV_MaxChars(pDX, m_awtext, 65);
	DDX_Check(pDX, IDC_CACHUP, m_cachup);
	DDX_Radio(pDX, IDC_AW_I, m_ialtaw);
	DDX_Radio(pDX, IDC_BI_I, m_ialtbi);
	DDX_Radio(pDX, IDC_BASEAUTO, m_bases);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// AssumptionsDialog message handlers


BEGIN_MESSAGE_MAP(AssumptionsDialog, CDialog)
	//{{AFX_MSG_MAP(AssumptionsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_AW_FLAT, OnAwFlat)
	ON_BN_CLICKED(IDC_AW_I, OnAwI)
	ON_BN_CLICKED(IDC_AW_II, OnAwIi)
	ON_BN_CLICKED(IDC_AW_IIA, OnAwIia)
	ON_BN_CLICKED(IDC_AW_III, OnAwIii)
	ON_BN_CLICKED(IDC_AW_OTHER, OnAwOther)
	ON_BN_CLICKED(IDC_AW_PEBS, OnAwPebs)
	ON_BN_CLICKED(IDC_BI_FLAT, OnBiFlat)
	ON_BN_CLICKED(IDC_BI_I, OnBiI)
	ON_BN_CLICKED(IDC_BI_II, OnBiIi)
	ON_BN_CLICKED(IDC_BI_IIA, OnBiIia)
	ON_BN_CLICKED(IDC_BI_III, OnBiIii)
	ON_BN_CLICKED(IDC_BI_OTHER, OnBiOther)
	ON_BN_CLICKED(IDC_BI_PEBS, OnBiPebs)
	ON_BN_CLICKED(IDC_ASSUMPTIONS_HELP, OnAssumptionsHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Description: Handles context-sensitive help.
//
// Arguments:
//   pHelpInfo: Structure containing context when help was called.
BOOL AssumptionsDialog::OnHelpInfo( HELPINFO* pHelpInfo )
{
   HtmlHelp(pHelpInfo->dwContextId);
   return TRUE;
}

// Description: Initializes dialog.
BOOL AssumptionsDialog::OnInitDialog()
{
   CButton* pB = (CButton*) GetDlgItem(IDC_BASEAUTO);
   pB->EnableWindow(m_bbases);
   pB = (CButton*) GetDlgItem(IDC_BASEADHOC);
   pB->EnableWindow(m_bbases);
   pB = (CButton*) GetDlgItem(IDC_BASES);
   pB->EnableWindow(m_bbases);
   CButton* pB1 = (CButton*) GetDlgItem(IDC_BI_I);
   pB1->SetWindowText(m_beninc[0]);
   pB1->EnableWindow(!m_bpebes);
   CButton* pB2 = (CButton*) GetDlgItem(IDC_BI_II);
   pB2->SetWindowText(m_beninc[1]);
   pB2->EnableWindow(!m_bpebes);
   CButton* pB3 = (CButton*) GetDlgItem(IDC_BI_III);
   pB3->SetWindowText(m_beninc[2]);
   pB3->EnableWindow(!m_bpebes);
   //CButton* pB4 = (CButton*) GetDlgItem(IDC_BI_IIA);
   //pB4->SetWindowText(m_beninc[3]);
   //pB4->EnableWindow(!m_bpebes);
   CButton* pB5 = (CButton*) GetDlgItem(IDC_BI_FLAT);
   pB5->SetWindowText(m_beninc[4]);
   //CButton* pB6 = (CButton*) GetDlgItem(IDC_BI_PEBS);
   //pB6->SetWindowText(m_beninc[5]);
   CButton* pB7 = (CButton*) GetDlgItem(IDC_BI_OTHER);
   pB7->EnableWindow(!m_bpebes);
   CEdit* pEbi = (CEdit*) GetDlgItem(IDC_BI_TEXT);
   pB = (CButton*) GetDlgItem(IDC_CACHUP);
   pEbi->EnableWindow(m_ialtbi + 3 == AssumptionType::OTHER_ASSUM);
   pB->EnableWindow(m_ialtbi + 3 == AssumptionType::OTHER_ASSUM);
   pB1 = (CButton*) GetDlgItem(IDC_AW_I);
   pB1->SetWindowText(m_avgwage[0]);
   pB1->EnableWindow(!m_bpebes);
   pB2 = (CButton*) GetDlgItem(IDC_AW_II);
   pB2->SetWindowText(m_avgwage[1]);
   pB2->EnableWindow(!m_bpebes);
   pB3 = (CButton*) GetDlgItem(IDC_AW_III);
   pB3->SetWindowText(m_avgwage[2]);
   pB3->EnableWindow(!m_bpebes);
   //pB4 = (CButton*) GetDlgItem(IDC_AW_IIA);
   //pB4->SetWindowText(m_avgwage[3]);
   //pB4->EnableWindow(!m_bpebes);
   pB5 = (CButton*) GetDlgItem(IDC_AW_FLAT);
   pB5->SetWindowText(m_avgwage[4]);
   //pB6 = (CButton*) GetDlgItem(IDC_AW_PEBS);
   //pB6->SetWindowText(m_avgwage[5]);
   pB7 = (CButton*) GetDlgItem(IDC_AW_OTHER);
   pB7->EnableWindow(!m_bpebes);
   CEdit* pEaw = (CEdit*) GetDlgItem(IDC_AW_TEXT);
   pEaw->EnableWindow(m_ialtaw + 3 == AssumptionType::OTHER_ASSUM);
   CDialog::OnInitDialog();
   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

// Description: Handles OK button click.
void AssumptionsDialog::OnOK()
{
   if (!UpdateData(TRUE))
      return;
   EndDialog(IDOK);
}

// Description: Handles Flat average wage button click.
void AssumptionsDialog::OnAwFlat()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_AW_TEXT);
   pE->EnableWindow(FALSE);
}

// Description: Handles Alt I average wage button click.
void AssumptionsDialog::OnAwI()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_AW_TEXT);
   pE->EnableWindow(FALSE);
}

// Description: Handles Alt II average wage button click.
void AssumptionsDialog::OnAwIi()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_AW_TEXT);
   pE->EnableWindow(FALSE);
}

// Description: Handles Alt II-A average wage button click.
void AssumptionsDialog::OnAwIia()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_AW_TEXT);
   pE->EnableWindow(FALSE);
}

// Description: Handles Alt III average wage button click.
void AssumptionsDialog::OnAwIii()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_AW_TEXT);
   pE->EnableWindow(FALSE);
}

// Description:Handles Other average wage button click.
void AssumptionsDialog::OnAwOther()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_AW_TEXT);
   pE->EnableWindow(TRUE);
}

// Description: Handles Statement average wage button click.
void AssumptionsDialog::OnAwPebs()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_AW_TEXT);
   pE->EnableWindow(FALSE);
}

// Description: Handles Flat benefit increases button click.
void AssumptionsDialog::OnBiFlat()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_BI_TEXT);
   pE->EnableWindow(FALSE);
   CButton* pB = (CButton*) GetDlgItem(IDC_CACHUP);
   pB->EnableWindow(FALSE);
   pB->SetCheck(0);
}

// Description: Handles Alt I benefit increases button click.
void AssumptionsDialog::OnBiI()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_BI_TEXT);
   pE->EnableWindow(FALSE);
   CButton* pB = (CButton*) GetDlgItem(IDC_CACHUP);
   pB->EnableWindow(FALSE);
   pB->SetCheck(0);
}

// Description: Handles Alt II benefit increases button click.
void AssumptionsDialog::OnBiIi()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_BI_TEXT);
   pE->EnableWindow(FALSE);
   CButton* pB = (CButton*) GetDlgItem(IDC_CACHUP);
   pB->EnableWindow(FALSE);
   pB->SetCheck(0);
}

// Description: Handles Alt II-A benefit increases button click.
void AssumptionsDialog::OnBiIia()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_BI_TEXT);
   pE->EnableWindow(FALSE);
   CButton* pB = (CButton*) GetDlgItem(IDC_CACHUP);
   pB->EnableWindow(FALSE);
   pB->SetCheck(0);
}

// Description: Handles Alt III benefit increases button click.
void AssumptionsDialog::OnBiIii()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_BI_TEXT);
   pE->EnableWindow(FALSE);
   CButton* pB = (CButton*) GetDlgItem(IDC_CACHUP);
   pB->EnableWindow(FALSE);
   pB->SetCheck(0);
}

// Description: Handles Other benefit increases button click.
void AssumptionsDialog::OnBiOther()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_BI_TEXT);
   pE->EnableWindow(TRUE);
   CButton* pB = (CButton*) GetDlgItem(IDC_CACHUP);
   pB->EnableWindow(TRUE);
}

// Description: Handles Statement benefit increases button click.
void AssumptionsDialog::OnBiPebs()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_BI_TEXT);
   pE -> EnableWindow(FALSE);
   CButton* pB = (CButton*) GetDlgItem(IDC_CACHUP);
   pB->EnableWindow(FALSE);
   pB->SetCheck(0);
}

// Description: Handles Help button click.
void AssumptionsDialog::OnAssumptionsHelp()
{
   HtmlHelp((DWORD_PTR)"/html/Forms/forms_assumptions.html",
      HH_DISPLAY_TOPIC);
}
