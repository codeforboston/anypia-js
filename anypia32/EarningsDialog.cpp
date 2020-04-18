// $Id: EarningsDialog.cpp 1.14.1.2 2017/12/12 08:19:42EST 277133 Development  $
//
// Implementation of EarningsDialog.

#include "stdafx.h"
#include "Anypia32.h"
#include "EarningsDialog.h"
#include "pia.h"
#include "comma.h"
#include "EarnProject.h"
#include "Htmlhelp.h"
#include "TextFloatFormatPatch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Description: EarningsDialog dialog.
//
// Arguments:
//   pParent: Parent window (default is NULL).
EarningsDialog::EarningsDialog(CWnd* pParent)
   : CDialog(EarningsDialog::IDD, pParent),
   m_DAoasdi(YEAR37, WorkerData::getMaxyear()),
   m_DAhi(YEAR37, WorkerData::getMaxyear()),
   m_DAbase(YEAR37, WorkerData::getMaxyear()),
   m_DAfq(YEAR37, WorkerData::getMaxyear()),
   m_DAwaghigh(YEAR37, WorkerData::getMaxyear()),
   m_DAwagmin(YEAR37, WorkerData::getMaxyear()),
   m_IAearntype(YEAR37, WorkerData::getMaxyear()),
   m_IAtaxtype(YEAR37, WorkerData::getMaxyear()),
   m_IAqc(YEAR37, WorkerData::getMaxyear()),
   m_BAchildcare(YEAR37, WorkerData::getMaxyear()),
   m_DArrearn(YEAR37, WorkerData::getMaxyear()),
   m_IArrqc(YEAR37, WorkerData::getMaxyear())
{
	//{{AFX_DATA_INIT(EarningsDialog)
	m_earnhi = 0.0;
	m_earnoasdi = 0.0;
	m_qcann = 0;
	m_rrqc = 0;
	m_rrearn = 0.0;
	m_childcare = FALSE;
	m_earntype = -1;
	m_taxtype = -1;
	//}}AFX_DATA_INIT
}

// @mfunc Exchange data between variables and dialog boxes.
//
// @parm Context information for the exchange.

void EarningsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(EarningsDialog)
	DDX_Text2(pDX, IDC_EARNHI, m_earnhi);
	DDV_MinMaxDouble(pDX, m_earnhi, 0., MAXEARN);
	DDX_Text2(pDX, IDC_EARNOASDI, m_earnoasdi);
	DDV_MinMaxDouble(pDX, m_earnoasdi, 0., MAXEARN);
	DDX_Text(pDX, IDC_QCANN, m_qcann);
	DDV_MinMaxInt(pDX, m_qcann, 0, 4);
	DDX_Text(pDX, IDC_RRQC, m_rrqc);
	DDV_MinMaxInt(pDX, m_rrqc, 0, 56);
	DDX_Text2(pDX, IDC_RREARN, m_rrearn);
	DDV_MinMaxDouble(pDX, m_rrearn, 0., MAXEARN);
	DDX_Check(pDX, IDC_CHILDCARE, m_childcare);
	DDX_Radio(pDX, IDC_ENTERED, m_earntype);
	DDX_Radio(pDX, IDC_TAXEMP, m_taxtype);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// EarningsDialog message handlers

BEGIN_MESSAGE_MAP(EarningsDialog, CDialog)
	//{{AFX_MSG_MAP(EarningsDialog)
	ON_BN_CLICKED(IDC_PREVYEAR, OnPrevyear)
	ON_BN_CLICKED(IDC_NEXTYEAR, OnNextyear)
	ON_BN_CLICKED(IDC_MAXIMUM, OnMaximum)
	ON_BN_CLICKED(IDC_LOW, OnLow)
	ON_BN_CLICKED(IDC_HIGH, OnHigh)
	ON_BN_CLICKED(IDC_ENTERED, OnEntered)
	ON_BN_CLICKED(IDC_AVERAGE, OnAverage)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_EARNINGSHELP, OnEarningshelp)
	ON_CBN_SELENDOK(IDC_COMBOEARNYEAR, OnSelendokComboearnyear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// @mfunc Handles OK button click.

void EarningsDialog::OnOK() 
{
   if (check())
      return;
   EndDialog(IDOK);
}

// @mfunc Handles Previous Year button click.

void EarningsDialog::OnPrevyear() 
{
   if (check())
      return;
   if (m_earnyear > m_istartyear1)
      m_earnyear--;
   setupdata();
   UpdateData(FALSE);
   CEdit* pE = (CEdit*) GetDlgItem(IDC_EARNOASDI);
   if (pE->IsWindowEnabled()) {
      pE->SetSel(0,-1);
	   pE->SetFocus();
	}
}

// @mfunc Handles Next Year button click.

void EarningsDialog::OnNextyear() 
{
   if (check())
      return;
   if (m_earnyear < m_ilastyear1)
      m_earnyear++;
   setupdata();
   UpdateData(FALSE);
   CEdit* pE = (CEdit*) GetDlgItem(IDC_EARNOASDI);
   if (pE->IsWindowEnabled()) {
      pE->SetSel(0,-1);
	   pE->SetFocus();
	}
}

// @mfunc Handles Maximum earnings button click.

void EarningsDialog::OnMaximum() 
{
    CEdit* pE = (CEdit*) GetDlgItem(IDC_EARNOASDI);
    pE->EnableWindow(FALSE);
}

// @mfunc Handles Low earnings button click.

void EarningsDialog::OnLow() 
{
    CEdit* pE = (CEdit*) GetDlgItem(IDC_EARNOASDI);
    pE->EnableWindow(FALSE);
}

// @mfunc Handles High earnings button click.

void EarningsDialog::OnHigh() 
{
    CEdit* pE = (CEdit*) GetDlgItem(IDC_EARNOASDI);
    pE->EnableWindow(FALSE);
}

// @mfunc Handles Entered earnings button click.

void EarningsDialog::OnEntered() 
{
    CEdit* pE = (CEdit*) GetDlgItem(IDC_EARNOASDI);
    pE->EnableWindow(TRUE);
}

// @mfunc Handles Average earnings button click.

void EarningsDialog::OnAverage() 
{
    CEdit* pE = (CEdit*) GetDlgItem(IDC_EARNOASDI);
    pE->EnableWindow(FALSE);
}

// @mfunc Handles context-sensitive help.
//
// @parm Structure containing context when help was called.

BOOL EarningsDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
   HtmlHelp(pHelpInfo->dwContextId);
   return TRUE;
}

// @mfunc Initializes dialog.

BOOL EarningsDialog::OnInitDialog() 
{
   if (m_indearn) {
      m_istartyear1 = m_istartyear;
      m_ilastyear1 = m_ilastyear;
      if (m_indrr && m_istartyear1 > m_istartyearrr)
         m_istartyear1 = m_istartyearrr;
      if (m_indrr && m_ilastyear1 < m_ilastyearrr)
         m_ilastyear1 = m_ilastyearrr;
   }
   else {
      m_istartyear1 = m_istartyearrr;
      m_ilastyear1 = m_ilastyearrr;
   }
   m_earnyear = m_istartyear1;
   // initialize the combo box with the year of earnings
   CComboBox* pCB = (CComboBox*) GetDlgItem(IDC_COMBOEARNYEAR);
   for (int i = m_istartyear1; i <= m_ilastyear1; i++) {
      pCB->AddString(poutNoComma(i).c_str());
   }
   pCB->SetCurSel(0);
   setupdata();
   CDialog::OnInitDialog();
   CEdit* pE = (CEdit*) GetDlgItem(IDC_EARNOASDI);
   if (pE -> IsWindowEnabled()) {
      pE->SetSel(0,-1);
      pE->SetFocus();
      return FALSE;
   }
   else
      return TRUE;
}

// @mfunc Checks data for inconsistencies.

bool EarningsDialog::check()
{
   if (!UpdateData(TRUE))
      return(TRUE);
   if (m_earnyear < m_istartyear1 || m_earnyear > m_ilastyear1) {
      AfxMessageBox("Year is out of range");
      return(true);
   }
   // save railroad amounts
   if (m_indrr && m_istartyearrr <= m_earnyear && m_earnyear <= m_ilastyearrr) {
      m_DArrearn[m_earnyear] = m_rrearn;
      m_IArrqc[m_earnyear] = m_rrqc;
   }
   // save regular earnings
   if (m_indearn && m_istartyear <= m_earnyear && m_earnyear <= m_ilastyear) {
      m_BAchildcare.setBit(m_earnyear, m_childcare);
      m_DAoasdi[m_earnyear] = m_earnoasdi;
      m_DAhi[m_earnyear] = m_earnhi;
      m_IAqc[m_earnyear] = m_qcann;
      m_IAearntype[m_earnyear] = m_earntype;
   }
   m_IAtaxtype[m_earnyear] = m_taxtype;
   return(false);
}

// @mfunc Fills in strings in dialog box, and enables/disables selections.

void EarningsDialog::setupdata()
{
   m_rrearn = m_DArrearn[m_earnyear];
   m_rrqc = m_IArrqc[m_earnyear];
   CComboBox* pCB = (CComboBox*) GetDlgItem(IDC_COMBOEARNYEAR);
   pCB->SetCurSel(m_earnyear - m_istartyear1);
   m_earnoasdi = m_DAoasdi[m_earnyear];
   m_earnhi = m_DAhi[m_earnyear];
   m_qcann = m_IAqc[m_earnyear];
   m_childcare = m_BAchildcare.getBit(m_earnyear);
   CButton* pB1 = (CButton*) GetDlgItem(IDC_ENTERED);
   CButton* pB2 = (CButton*) GetDlgItem(IDC_MAXIMUM);
   CButton* pB3 = (CButton*) GetDlgItem(IDC_HIGH);
   CButton* pB4 = (CButton*) GetDlgItem(IDC_AVERAGE);
   CButton* pB5 = (CButton*) GetDlgItem(IDC_LOW);
   CEdit* pE = (CEdit*) GetDlgItem(IDC_EARNOASDI);
   CStatic *pS = (CStatic *)GetDlgItem(IDC_EARNTYPE);
   if (m_indearn && m_istartyear <= m_earnyear && m_earnyear <= m_ilastyear) {
      pS->EnableWindow(TRUE);
      pB1->EnableWindow(TRUE);
      if (m_bpebes) {
         m_earntype = 0;
         pE->EnableWindow(TRUE);
         pB2->EnableWindow(FALSE);
         pB3->EnableWindow(FALSE);
         pB4->EnableWindow(FALSE);
         pB5->EnableWindow(FALSE);
      }
      else {
         m_earntype = m_IAearntype[m_earnyear];
         pB2->EnableWindow(TRUE);
         pB3->EnableWindow(TRUE);
         pB4->EnableWindow(TRUE);
         pB5->EnableWindow(TRUE);
         switch (m_earntype)
         {
         case EarnProject::ENTERED:
            pE->EnableWindow(TRUE);
            break;
         case EarnProject::MAXIMUM:
         case EarnProject::HIGH:
         case EarnProject::AVERAGE:
         case EarnProject::LOW:
            pE->EnableWindow(FALSE);
            break;
         default:
            pE->EnableWindow(FALSE);
            break;
         }
      }
   }
   // if no regular earnings in this year, disable windows
   else {
      pS->EnableWindow(FALSE);
      pE->EnableWindow(FALSE);
      pB1->EnableWindow(FALSE);
      pB2->EnableWindow(FALSE);
      pB3->EnableWindow(FALSE);
      pB4->EnableWindow(FALSE);
      pB5->EnableWindow(FALSE);
   }
   m_taxtype = m_IAtaxtype[m_earnyear];
   // Handle specified quarters of coverage
   bool indqc =
      m_qcbyyear && (m_earnyear < 1978) && (m_earnyear >= m_istartyear);
   pE = (CEdit*) GetDlgItem(IDC_QCANN);
   pE->EnableWindow(indqc);
   pS = (CStatic*) GetDlgItem(IDC_QCANNTEXT);
   pS->EnableWindow(indqc);
   // Handle Medicare earnings
   bool indmqge = m_mqge && m_earnyear >= m_istartyear && m_earnyear >= 1983
      && m_earnyear <= m_ilastyear;
   pE = (CEdit*) GetDlgItem(IDC_EARNHI);
   pE->EnableWindow(indmqge);
   pS = (CStatic*) GetDlgItem(IDC_EARNHITEXT);
   pS->EnableWindow(indmqge);
   // Handle railroad dialog
   bool indrr = (m_indrr && m_earnyear >= m_istartyearrr &&
      m_earnyear <= m_ilastyearrr);
   pE = (CEdit*) GetDlgItem(IDC_RREARN);
   pE->EnableWindow(indrr);
   pE = (CEdit*) GetDlgItem(IDC_RRQC);
   pE->EnableWindow(indrr && m_earnyear < 1978);
   pS = (CStatic*) GetDlgItem(IDC_RRTEXT);
   pS->EnableWindow(indrr);
   pS = (CStatic*) GetDlgItem(IDC_RREARNTEXT);
   pS->EnableWindow(indrr);
   pS = (CStatic*) GetDlgItem(IDC_RRQCTEXT);
   pS->EnableWindow(indrr && m_earnyear < 1978);
   // Handle type of earnings dialog
   pS = (CStatic*) GetDlgItem(IDC_MAXIMUM);
   CString highstring;
   AfxFormatString1(highstring, PIA_IDS_MAXIMUMTEXT,
      poutComma(m_DAbase[m_earnyear], 3, 2).c_str());
   pS->SetWindowText(highstring);
   pS = (CStatic*) GetDlgItem(IDC_HIGH);
   AfxFormatString1(highstring, PIA_IDS_HIGHTEXT,
      poutComma(m_DAwaghigh[m_earnyear], 3, 2).c_str());
   pS->SetWindowText(highstring);
   pS = (CStatic*) GetDlgItem(IDC_AVERAGE);
   AfxFormatString1(highstring, PIA_IDS_AVERAGETEXT,
      poutComma(m_DAfq[m_earnyear], 3, 2).c_str());
   pS->SetWindowText(highstring);
   pS = (CStatic*) GetDlgItem(IDC_LOW);
   AfxFormatString1(highstring, PIA_IDS_LOWTEXT,
      poutComma(m_DAwagmin[m_earnyear], 3, 2).c_str());
   pS->SetWindowText(highstring);
   CButton* pB = (CButton*) GetDlgItem(IDC_PREVYEAR);
   pB->EnableWindow(m_earnyear > m_istartyear1);
   pB = (CButton*) GetDlgItem(IDC_NEXTYEAR);
   pB->EnableWindow(m_earnyear < m_ilastyear1);
}

// @mfunc Handles Help button click.

void EarningsDialog::OnEarningshelp() 
{
   HtmlHelp((DWORD_PTR)"/html/Forms/forms_earnings_info.html",
      HH_DISPLAY_TOPIC);
}

// @mfunc Handles new selection in combo box displaying year of earnings.

void EarningsDialog::OnSelendokComboearnyear() 
{
   CComboBox* pCB = (CComboBox*) GetDlgItem(IDC_COMBOEARNYEAR);
   int curSel = pCB->GetCurSel();
   m_earnyear = m_istartyear1 + curSel;
   setupdata();
   UpdateData(FALSE);
}
