// $Id: WorkerDialog.cpp 1.18.1.2 2012/03/08 10:58:31EST 277133 Development  $
//
// Implementation of WorkerDialog.

#include "stdafx.h"
#include "Anypia32.h"
#include "WorkerDialog.h"
#include "pia.h"
#include "PiaException.h"
#include "UserAssumptions.h"
#include "Htmlhelp.h"
#include "boost/date_time/gregorian/parsers.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

// Description: Constructor of WorkerDialog dialog.
//
// Arguments:
//   pParent: Parent window (default is NULL).
WorkerDialog::WorkerDialog( CWnd* pParent ) :
CDialog(WorkerDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(WorkerDialog)
	m_dob = _T("");
	m_ssn1 = _T("");
	m_ssn2 = _T("");
	m_ssn3 = _T("");
	m_nhname = _T("");
	m_nhaddr1 = _T("");
	m_nhaddr2 = _T("");
	m_nhaddr3 = _T("");
	m_mqge = FALSE;
	m_totalize = FALSE;
	m_blind = FALSE;
	m_deemed = FALSE;
	m_indearn = FALSE;
	m_indrr = FALSE;
	m_rryear1 = 0;
	m_rryear2 = 0;
	m_mscount = 0;
	m_indms = FALSE;
	m_death = _T("");
	m_fammem = 0;
	m_bentype = -1;
	m_sex = -1;
	//}}AFX_DATA_INIT
}

// Description: Exchanges data between variables and dialog boxes.
//
// Arguments:
//   pDX: Context information for the exchange.
void WorkerDialog::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(WorkerDialog)
	DDX_Text(pDX, IDC_DOB, m_dob);
	DDV_MaxChars(pDX, m_dob, 10);
	DDX_Text(pDX, IDC_SSN1, m_ssn1);
	DDV_MaxChars(pDX, m_ssn1, 3);
	DDX_Text(pDX, IDC_SSN2, m_ssn2);
	DDV_MaxChars(pDX, m_ssn2, 2);
	DDX_Text(pDX, IDC_SSN3, m_ssn3);
	DDV_MaxChars(pDX, m_ssn3, 4);
	DDX_Text(pDX, IDC_WORKER, m_nhname);
	DDV_MaxChars(pDX, m_nhname, 40);
	DDX_Text(pDX, IDC_NHADDR1, m_nhaddr1);
	DDV_MaxChars(pDX, m_nhaddr1, 40);
	DDX_Text(pDX, IDC_NHADDR2, m_nhaddr2);
	DDV_MaxChars(pDX, m_nhaddr2, 40);
	DDX_Text(pDX, IDC_NHADDR3, m_nhaddr3);
	DDV_MaxChars(pDX, m_nhaddr3, 40);
	DDX_Check(pDX, IDC_MQGE, m_mqge);
	DDX_Check(pDX, IDC_TOTALIZE, m_totalize);
	DDX_Check(pDX, IDC_BLIND, m_blind);
	DDX_Check(pDX, IDC_DEEMED, m_deemed);
	DDX_Check(pDX, IDC_INDEARN, m_indearn);
	DDX_Check(pDX, IDC_INDRR, m_indrr);
	DDX_Text(pDX, IDC_RRYEAR1, m_rryear1);
	DDV_MinMaxInt(pDX, m_rryear1, 0, 2100);
	DDX_Text(pDX, IDC_RRYEAR2, m_rryear2);
	DDV_MinMaxInt(pDX, m_rryear2, 0, 2100);
	DDX_Text(pDX, IDC_MSCOUNT, m_mscount);
	DDV_MinMaxInt(pDX, m_mscount, 0, 15);
	DDX_Check(pDX, IDC_INDMS, m_indms);
	DDX_Text(pDX, IDC_DEATH, m_death);
	DDV_MaxChars(pDX, m_death, 10);
	DDX_Text(pDX, IDC_FAMMEM, m_fammem);
	DDV_MinMaxInt(pDX, m_fammem, 0, 15);
	DDX_Radio(pDX, IDC_OLDAGE, m_bentype);
	DDX_Radio(pDX, IDC_FEMALE, m_sex);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// WorkerDialog message handlers

BEGIN_MESSAGE_MAP(WorkerDialog, CDialog)
	//{{AFX_MSG_MAP(WorkerDialog)
	ON_BN_CLICKED(IDC_OLDAGE, OnOldage)
	ON_BN_CLICKED(IDC_DISABILITY, OnDisability)
	ON_BN_CLICKED(IDC_PEBES, OnPebes)
	ON_BN_CLICKED(IDC_SURVIVOR, OnSurvivor)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_INDRR, OnIndrr)
	ON_BN_CLICKED(IDC_INDMS, OnIndms)
	ON_BN_CLICKED(IDC_WORKER_HELP, OnWorkerHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Description: Initializes dialog.
//
// Returns: TRUE.
BOOL WorkerDialog::OnInitDialog()
{
   // Fill out type of benefit box
   CButton* pBoldage = (CButton*) GetDlgItem(IDC_OLDAGE);
   CButton* pBsurvivor = (CButton*) GetDlgItem(IDC_SURVIVOR);
   CButton* pBdisability = (CButton*) GetDlgItem(IDC_DISABILITY);
   //CButton* pBpebes = (CButton*) GetDlgItem(IDC_PEBES);
   pBoldage->SetCheck(0);
   pBsurvivor->SetCheck(0);
   pBdisability->SetCheck(0);
   //pBpebes->SetCheck(0);
   CEdit* pE = (CEdit*) GetDlgItem(IDC_RRYEAR1);
   pE->EnableWindow(m_indrr);
   pE = (CEdit*) GetDlgItem(IDC_RRYEAR2);
   pE->EnableWindow(m_indrr);
   pE = (CEdit*) GetDlgItem(IDC_MSCOUNT);
   pE->EnableWindow(m_indms);
   pE = (CEdit*) GetDlgItem(IDC_DEATH);
   pE->EnableWindow(m_bentype + 1 == WorkerData::SURVIVOR);
   CStatic* pS = (CStatic*) GetDlgItem(IDC_DEATHTEXT);
   pS->EnableWindow(m_bentype + 1 == WorkerData::SURVIVOR);
   CDialog::OnInitDialog();

   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

// Description: Handles Old Age button click.
void WorkerDialog::OnOldage()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_DEATH);
   pE->EnableWindow(FALSE);
   CStatic* pS = (CStatic*) GetDlgItem(IDC_DEATHTEXT);
   pS->EnableWindow(FALSE);
}

// Description: Handles Disability button click.
void WorkerDialog::OnDisability()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_DEATH);
   pE->EnableWindow(FALSE);
   CStatic* pS = (CStatic*) GetDlgItem(IDC_DEATHTEXT);
   pS->EnableWindow(FALSE);
}

// Description: Handles Social Security Statement button click.
void WorkerDialog::OnPebes()
{
   //CEdit* pE = (CEdit*) GetDlgItem(IDC_DEATH);
   //pE->EnableWindow(FALSE);
   //CStatic* pS = (CStatic*) GetDlgItem(IDC_DEATHTEXT);
   //pS->EnableWindow(FALSE);
}

// Description: Handles Survivor button click.
void WorkerDialog::OnSurvivor()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_DEATH);
   pE->EnableWindow(TRUE);
   CStatic* pS = (CStatic*) GetDlgItem(IDC_DEATHTEXT);
   pS->EnableWindow(TRUE);
}

// Description: Handles context-sensitive help.
//
// Returns: TRUE.
//
// Arguments:
//   pHelpInfo: Structure containing context when help was called.
BOOL WorkerDialog::OnHelpInfo( HELPINFO* pHelpInfo )
{
   HtmlHelp(pHelpInfo->dwContextId);
   return TRUE;
}

// Description: Handles OK button click.
void WorkerDialog::OnOK()
{
   if (!UpdateData(TRUE))
      return;
   try {
      // check for any kind of earnings
      WorkerData::earningsCheck(m_indearn == FALSE, m_indrr == TRUE,
         m_mscount > 0);
      try {
         m_dobtemp = boost::gregorian::from_us_string((const char *)m_dob);
      } catch (boost::gregorian::bad_year) {
         throw PiaException(PIA_IDS_BIRTH2);
      } catch (boost::gregorian::bad_month) {
         throw PiaException(PIA_IDS_BIRTH3);
      } catch (boost::gregorian::bad_day_of_month) {
         throw PiaException(PIA_IDS_BIRTH4);
      } catch (exception&) {
         throw PiaException(PIA_IDS_BIRTH6);
      }
      if (m_bentype + 1 == WorkerData::SURVIVOR) {
         try {
            m_deathtemp = boost::gregorian::from_us_string((const char *)m_death);
            // check date of death for basic correctness
            WorkerData::deathCheck1(m_deathtemp,
               (WorkerData::ben_type)(m_bentype + 1));
            WorkerData::deathCheck2(m_deathtemp);
         } catch (exception&) {
            throw PiaException(PIA_IDS_DEATH6);
         }
      }
      if (m_bentype + 1 == WorkerData::PEBS_CALC) {
         WorkerData::birth1Check(m_dobtemp, UserAssumptions::getIstart());
      }
      else {
         WorkerData::birth2Check(m_dobtemp);
      }
   } catch (PiaException e) {
      AfxMessageBox(e.getNumber());
      return;
   }
   EndDialog(IDOK);
}

// Description: Handles Railroad button click.
void WorkerDialog::OnIndrr()
{
   UpdateData(TRUE);
   CEdit* pE = (CEdit*) GetDlgItem(IDC_RRYEAR1);
   pE->EnableWindow(m_indrr);
   pE = (CEdit*) GetDlgItem(IDC_RRYEAR2);
   pE->EnableWindow(m_indrr);
}

// Description: Handles Military Service button click.
void WorkerDialog::OnIndms()
{
   UpdateData(TRUE);
   CEdit* pE = (CEdit*) GetDlgItem(IDC_MSCOUNT);
   pE->EnableWindow(m_indms);
}

// Description: Handles Help button click.
void WorkerDialog::OnWorkerHelp() 
{
   HtmlHelp((DWORD_PTR)"/html/Forms/forms_worker_info.html",
      HH_DISPLAY_TOPIC);
}
