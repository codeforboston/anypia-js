// $Id: DisabDialog.cpp 1.16.1.2 2017/12/12 08:19:42EST 277133 Development  $
//
// Implementation of DisabDialog.

#include "stdafx.h"
#include "Anypia32.h"
#include "DisabDialog.h"
#include "pia.h"
#include "PiaException.h"
#include "Htmlhelp.h"
#include "boost/date_time/gregorian/parsers.hpp"
#include "TextFloatFormatPatch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// DisabDialog dialog

// Description: Constructor.
//
// Arguments:
//   pParent: Parent window (default NULL).
DisabDialog::DisabDialog( CWnd* pParent /*=NULL*/) :
CDialog(DisabDialog::IDD, pParent), m_dicesstemp(), m_onsettemp(),
m_prrenttemp(), m_waitpdtemp(), m_dicess1temp(), m_onset1temp(),
m_prrent1temp(), m_waitpd1temp(), m_valdi(0), m_ioasdi(WorkerData::NO_BEN),
m_birthDate(), m_entDate(), m_benDate(), m_deathDate(), m_pia(0.0f),
m_mfb(0.0f), m_pia1(0.0f), m_mfb1(0.0f)
{
	//{{AFX_DATA_INIT(DisabDialog)
	m_dicess = _T("");
	m_onset = _T("");
	m_prrent = _T("");
	m_waitpd = _T("");
	m_dicess1 = _T("");
	m_onset1 = _T("");
	m_prrent1 = _T("");
	m_waitpd1 = _T("");
	//}}AFX_DATA_INIT
}

// Description: Exchange data with dialog.
//
// Arguments:
//   pDX: Data to be exchanged.
void DisabDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DisabDialog)
	DDX_Text(pDX, IDC_DICESS, m_dicess);
	DDV_MaxChars(pDX, m_dicess, 7);
	DDX_Text(pDX, IDC_ONSET, m_onset);
	DDV_MaxChars(pDX, m_onset, 10);
	DDX_Text(pDX, IDC_PRRENT, m_prrent);
	DDV_MaxChars(pDX, m_prrent, 7);
	DDX_Text(pDX, IDC_WAITPD, m_waitpd);
	DDV_MaxChars(pDX, m_waitpd, 7);
	DDX_Text(pDX, IDC_DICESS1, m_dicess1);
	DDV_MaxChars(pDX, m_dicess1, 7);
	DDX_Text(pDX, IDC_ONSET1, m_onset1);
	DDV_MaxChars(pDX, m_onset1, 10);
	DDX_Text(pDX, IDC_PRRENT1, m_prrent1);
	DDV_MaxChars(pDX, m_prrent1, 7);
	DDX_Text(pDX, IDC_WAITPD1, m_waitpd1);
	DDV_MaxChars(pDX, m_waitpd1, 7);
	//}}AFX_DATA_MAP
   DDX_Text2(pDX, IDC_DIPIA, m_pia);
   DDV_MinMaxFloat(pDX, m_pia, 0.0f, 999999.99f);
   DDX_Text2(pDX, IDC_DIMFB, m_mfb);
   DDV_MinMaxFloat(pDX, m_mfb, 0.0f, 999999.99f);
   DDX_Text2(pDX, IDC_DIPIA1, m_pia1);
   DDV_MinMaxFloat(pDX, m_pia1, 0.0f, 999999.99f);
   DDX_Text2(pDX, IDC_DIMFB1, m_mfb1);
   DDV_MinMaxFloat(pDX, m_mfb1, 0.0f, 999999.99f);
}

/////////////////////////////////////////////////////////////////////////////
// DisabDialog message handlers

BEGIN_MESSAGE_MAP(DisabDialog, CDialog)
	//{{AFX_MSG_MAP(DisabDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_DISAB_HELP, OnDisabHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Description: Handle OK button click.
void DisabDialog::OnOK()
{
   if (!UpdateData(TRUE))
      return;
   try {
      try {
         m_onsettemp = boost::gregorian::from_us_string((const char *)m_onset);
      } catch (exception&) {
         throw PiaException(PIA_IDS_ONSET9);
      }
      DisabPeriod::onsetDateCheck(m_onsettemp);
      WorkerData::disBirthEntCheck(m_onsettemp, m_birthDate, m_ioasdi,
         m_entDate, m_benDate);
      try {
         m_waitpdtemp = DateMoyr((const char *)m_waitpd);
      } catch (PiaException&) {
         throw PiaException(PIA_IDS_WAITPD7);
      }
      DisabPeriod::waitperDateCheck(m_waitpdtemp);
      try {
         m_prrenttemp = DateMoyr((const char *)m_prrent);
      } catch (PiaException&) {
         throw PiaException(PIA_IDS_PRRENT6);
      }
      DisabPeriod::entDateCheck(m_prrenttemp);
      WorkerData::priorentCheck(m_prrenttemp, m_onsettemp, m_entDate,
         m_ioasdi);
      if (m_ioasdi != WorkerData::DISABILITY) {
         try {
            m_dicesstemp = DateMoyr((const char *)m_dicess);
         } catch (PiaException&) {
            throw PiaException(PIA_IDS_DICESS8);
         }
         DisabPeriod::cessationDateCheck(m_dicesstemp);
         WorkerData::cessationCheck2(m_dicesstemp, m_onsettemp, m_deathDate,
            m_entDate, m_ioasdi);
      }
      if (m_valdi > 1) {
         try {
            m_onset1temp = boost::gregorian::from_us_string((const char *)m_onset1);
         } catch (exception&) {
            throw PiaException(PIA_IDS_ONSET10);
         }
         DisabPeriod::onsetDateCheck(m_onset1temp);
         WorkerData::dis1Check(m_onset1temp, m_onsettemp, m_valdi,
            m_birthDate);
         try {
            m_waitpd1temp = DateMoyr((const char *)m_waitpd1);
         } catch (PiaException&) {
            throw PiaException(PIA_IDS_WAITPD7);
         }
         DisabPeriod::waitperDateCheck(m_waitpd1temp);
         try {
            m_prrent1temp = DateMoyr((const char *)m_prrent1);
         } catch (PiaException&) {
            throw PiaException(PIA_IDS_PRRENT6);
         }
         DisabPeriod::entDateCheck(m_prrent1temp);
         try {
            m_dicess1temp = DateMoyr((const char *)m_dicess1);
         } catch (PiaException&) {
            throw PiaException(PIA_IDS_DICESS8);
         }
         DisabPeriod::cessationDateCheck(m_dicess1temp);
         WorkerData::cessation1Check(m_dicess1temp, m_onset1temp, m_onsettemp);
      }
      EndDialog(IDOK);
   } catch (PiaException& e) {
      AfxMessageBox(e.getNumber());
      return;
   }
}

// Description: Initialize dialog.
//
// Returns: TRUE.
BOOL DisabDialog::OnInitDialog()
{
   // Enable fields for most recent period of disability
   CStatic* pS = (CStatic*) GetDlgItem(IDC_PRRENTTEXT);
   pS->EnableWindow(WorkerData::needDiCess(m_valdi, m_ioasdi));
   CEdit* pE = (CEdit*) GetDlgItem(IDC_PRRENT);
   pE->EnableWindow(WorkerData::needDiCess(m_valdi, m_ioasdi));
   pS = (CStatic*) GetDlgItem(IDC_WAITPDTEXT);
   pS->EnableWindow();
   pE = (CEdit*) GetDlgItem(IDC_WAITPD);
   pE->EnableWindow();
   pS = (CStatic*) GetDlgItem(IDC_DICESSTEXT);
   pS->EnableWindow(WorkerData::needDiCess(m_valdi, m_ioasdi));
   pE = (CEdit*) GetDlgItem(IDC_DICESS);
   pE->EnableWindow(WorkerData::needDiCess(m_valdi, m_ioasdi));
   pS = (CStatic*) GetDlgItem(IDC_DIPIATEXT);
   pS->EnableWindow(WorkerData::needDiCess(m_valdi, m_ioasdi));
   pE = (CEdit*) GetDlgItem(IDC_DIPIA);
   pE->EnableWindow(WorkerData::needDiCess(m_valdi, m_ioasdi));
   pS = (CStatic*) GetDlgItem(IDC_DIMFBTEXT);
   pS->EnableWindow(WorkerData::needDiCess(m_valdi, m_ioasdi));
   pE = (CEdit*) GetDlgItem(IDC_DIMFB);
   pE->EnableWindow(WorkerData::needDiCess(m_valdi, m_ioasdi));
   // Enable fields for next most recent period of disability
   pS = (CStatic*) GetDlgItem(IDC_ONSET1TEXT);
   pS->EnableWindow(m_valdi > 1);
   pE = (CEdit*) GetDlgItem(IDC_ONSET1);
   pE->EnableWindow(m_valdi > 1);
   pS = (CStatic*) GetDlgItem(IDC_WAITPD1TEXT);
   pS->EnableWindow(m_valdi > 1);
   pE = (CEdit*) GetDlgItem(IDC_WAITPD1);
   pE->EnableWindow(m_valdi > 1);
   pS = (CStatic*) GetDlgItem(IDC_DICESS1TEXT);
   pS->EnableWindow(m_valdi > 1);
   pE = (CEdit*) GetDlgItem(IDC_DICESS1);
   pE->EnableWindow(m_valdi > 1);
   pS = (CStatic*) GetDlgItem(IDC_DIPIA1TEXT);
   pS->EnableWindow(m_valdi > 1);
   pE = (CEdit*) GetDlgItem(IDC_DIPIA1);
   pE->EnableWindow(m_valdi > 1);
   pS = (CStatic*) GetDlgItem(IDC_DIMFB1TEXT);
   pS->EnableWindow(m_valdi > 1);
   pE = (CEdit*) GetDlgItem(IDC_DIMFB1);
   pE->EnableWindow(m_valdi > 1);
   pS = (CStatic*) GetDlgItem(IDC_PRRENT1TEXT);
   pS->EnableWindow(m_valdi > 1);
   pE = (CEdit*) GetDlgItem(IDC_PRRENT1);
   pE->EnableWindow(m_valdi > 1);
   pS = (CStatic*) GetDlgItem(IDC_DISAB1TEXT);
   pS->EnableWindow(m_valdi > 1);
   CDialog::OnInitDialog();

   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

// Description: Handles context-sensitive help.
//
// Returns: TRUE.
//
// Arguments:
//   pHelpInfo: Structure containing context when help was called.
BOOL DisabDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
   HtmlHelp(pHelpInfo->dwContextId);
   return TRUE;
}

// Description: Handles Help button click.
void DisabDialog::OnDisabHelp() 
{
   HtmlHelp((DWORD_PTR)"/html/Forms/forms_disability_info.html",
      HH_DISPLAY_TOPIC);
}
