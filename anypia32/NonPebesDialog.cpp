// $Id: NonPebesDialog.cpp 1.22.1.2 2017/12/12 08:19:43EST 277133 Development  $
//
// Implementation of NonPebesDialog.

#include "stdafx.h"
#include "Anypia32.h"
#include "NonPebesDialog.h"
#include "pia.h"
#include "PiaException.h"
#include "EarnProject.h"
#include "Htmlhelp.h"
#include "TextFloatFormatPatch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Description: NonPebesDialog dialog.
//
// Arguments:
//   pParent: Parent window (default is NULL).
NonPebesDialog::NonPebesDialog( CWnd* pParent )
	: CDialog(NonPebesDialog::IDD, pParent)
   , M_nonpendate(_T(""))
{
	//{{AFX_DATA_INIT(NonPebesDialog)
	m_bendate = _T("");
	m_ent = _T("");
	m_begin = 0;
	m_end = 0;
	m_backperc = 0.0;
	m_backyear = 0;
	m_fwrdperc = 0.0;
	m_fwrdyear = 0;
	m_valdi = 0;
	m_nonpen = 0.0;
	m_backtype = -1;
	m_fwrdtype = -1;
	m_recalc = FALSE;
	//}}AFX_DATA_INIT
	m_backyear = 1937;
	m_fwrdyear = 2100;
}

// Description: Exchanges data between variables and dialog boxes.
//
// Arguments:
//   pDX: Context information for the exchange.
void NonPebesDialog::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(NonPebesDialog)
   DDX_Text(pDX, IDC_BENDATE, m_bendate);
   DDV_MaxChars(pDX, m_bendate, 7);
   DDX_Text(pDX, IDC_ENT, m_ent);
   DDV_MaxChars(pDX, m_ent, 7);
   DDX_Text(pDX, IDC_BEGIN, m_begin);
   DDV_MinMaxInt(pDX, m_begin, 0, 2100);
   DDX_Text(pDX, IDC_END, m_end);
   DDV_MinMaxInt(pDX, m_end, 0, 2100);
   DDX_Text2(pDX, IDC_BACKPERC, m_backperc);
   DDV_MinMaxDouble(pDX, m_backperc, -9.99, 9.99);
   DDX_Text(pDX, IDC_BACKYEAR, m_backyear);
   DDV_MinMaxInt(pDX, m_backyear, 1937, 2100);
   DDX_Text2(pDX, IDC_FWRDPERC, m_fwrdperc);
   DDV_MinMaxDouble(pDX, m_fwrdperc, -9.99, 9.99);
   DDX_Text(pDX, IDC_FWRDYEAR, m_fwrdyear);
   DDV_MinMaxInt(pDX, m_fwrdyear, 1937, 2100);
   DDX_Text(pDX, IDC_VALDI, m_valdi);
   DDV_MinMaxInt(pDX, m_valdi, 0, 2);
   DDX_Text2(pDX, IDC_NONPEN_NONPEBES, m_nonpen);
   DDV_MinMaxDouble(pDX, m_nonpen, 0.0, 999999.99);
   DDX_Radio(pDX, IDC_BACKNONE, m_backtype);
   DDX_Radio(pDX, IDC_FWRDNONE, m_fwrdtype);
   DDX_Check(pDX, IDC_RECALC, m_recalc);
   //}}AFX_DATA_MAP
   DDX_Text(pDX, IDC_NONPEBESNONPENDATE, M_nonpendate);
	DDV_MaxChars(pDX, M_nonpendate, 7);
}

/////////////////////////////////////////////////////////////////////////////
// NonPebesDialog message handlers

BEGIN_MESSAGE_MAP(NonPebesDialog, CDialog)
	//{{AFX_MSG_MAP(NonPebesDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_SUPP_HELP, OnSuppHelp)
	ON_BN_CLICKED(IDC_RECALC, OnRecalc)
	ON_BN_CLICKED(IDC_BACKNONE, OnBacknone)
	ON_BN_CLICKED(IDC_BACKAVGWAGE, OnBackavgwage)
	ON_BN_CLICKED(IDC_BACKCONSTANT, OnBackconstant)
	ON_BN_CLICKED(IDC_FWRDAVGWAGE, OnFwrdavgwage)
	ON_BN_CLICKED(IDC_FWRDCONSTANT, OnFwrdconstant)
	ON_BN_CLICKED(IDC_FWRDNONE, OnFwrdnone)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Description: Handles OK button click.
void NonPebesDialog::OnOK()
{
   CString temp;

   if (!UpdateData(TRUE))
      return;
   try {
      // do not use date of entitlement in survivor case
      if (m_joasdi != WorkerData::SURVIVOR) {
         try {
            enttemp = DateMoyr((const char *)m_ent);
         } catch (PiaException e) {
            throw PiaException(PIA_IDS_ENT4);
         }
         WorkerData::entCheck(enttemp);
      }
      // use date of benefit if recalculation or survivor
      if (m_recalc || m_joasdi == WorkerData::SURVIVOR) {
         try {
            bendttemp = DateMoyr((const char *)m_bendate);
         } catch (PiaException e) {
            throw PiaException(PIA_IDS_BENDATE5);
         }
         WorkerData::benefitDate1Check(bendttemp);
         // do not check against entitlement date if survivor
         if (m_joasdi != WorkerData::SURVIVOR) {
            WorkerData::benefitDate2Check(enttemp, bendttemp);
         }
      }
      if (m_indearn) {
         WorkerData::ibegin2Check(m_begin);
         WorkerData::iendCheck(m_end);
         if (m_bback) {
            WorkerData::ibegin2Check(m_backyear);
         }
         else {
            m_backyear = m_begin;
         }
         if (m_bfwrd) {
            WorkerData::iendCheck(m_fwrdyear);
         }
         else {
            m_fwrdyear = m_end;
         }
         // Check for consistency among years
         EarnProject::ibeginCheck(m_backyear, m_begin);
         WorkerData::ibeginCheck(m_backyear, m_birthyear);
         EarnProject::yearsCheck(m_backyear, m_begin, m_fwrdyear, m_end);
      }
      if (m_joasdi == WorkerData::DISABILITY)
         WorkerData::valdi2Check(m_valdi);
      if (m_nonpen > 0) {
         try {
            m_nonpendatetemp = DateMoyr((const char *)M_nonpendate);
            m_nonpendatetemp.check();
         } catch (PiaException&) {
            throw PiaException(PIA_IDS_NONPENDATE3);
         }
         WorkerData::pubpenDateCheck(m_nonpendatetemp, m_birthdate,
            m_deathdate);
      }
      else {
         m_nonpendatetemp = DateMoyr(0, 0);
      }
      EndDialog(IDOK);
   } catch (PiaException& e) {
      AfxMessageBox(e.getNumber());
      return;
   }
}

// Description: Initializes dialog.
//
// Returns: TRUE.
BOOL NonPebesDialog::OnInitDialog() 
{
   // Enable entitlement date and recalculation button unless a survivor
   CStatic* pS = (CStatic*) GetDlgItem(IDC_ENTTEXT);
   pS->EnableWindow(m_joasdi != WorkerData::SURVIVOR);
   CEdit* pE = (CEdit*) GetDlgItem(IDC_ENT);
   pE->EnableWindow(m_joasdi != WorkerData::SURVIVOR);
   CButton* pB = (CButton*) GetDlgItem(IDC_RECALC);
   pB->EnableWindow(m_joasdi != WorkerData::SURVIVOR);
   // Enable benefit date if a recalculation or a survivor
   pS = (CStatic*) GetDlgItem(IDC_BENDATETEXT);
   pS->EnableWindow(m_recalc || m_joasdi == WorkerData::SURVIVOR);
   pE = (CEdit*) GetDlgItem(IDC_BENDATE);
   pE->EnableWindow(m_recalc || m_joasdi == WorkerData::SURVIVOR);
   // Disable years of earnings if no earnings
   pS = (CStatic*) GetDlgItem(IDC_YEARSTEXT);
   pS->EnableWindow(m_indearn);
   pS = (CStatic*) GetDlgItem(IDC_BEGINTEXT);
   pS->EnableWindow(m_indearn);
   pS = (CStatic*) GetDlgItem(IDC_ENDTEXT);
   pS->EnableWindow(m_indearn);
   pE = (CEdit*) GetDlgItem(IDC_BEGIN);
   pE->EnableWindow(m_indearn);
   pE = (CEdit*) GetDlgItem(IDC_END);
   pE->EnableWindow(m_indearn);
   // Disable backwards projection if not projected back
   OnBacktype();
   // Disable forward projection if not projected forward
   OnFwrdtype();
   // Enable noncovered pension information if needed
   pE = (CEdit*) GetDlgItem(IDC_NONPEN_NONPEBES);
   pE->EnableWindow(m_bnonpen);
   pE = (CEdit*) GetDlgItem(IDC_NONPEBESNONPENDATE);
   pE->EnableWindow(m_bnonpen);
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
BOOL NonPebesDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
   HtmlHelp(pHelpInfo->dwContextId);
   return TRUE;
}

// Description: Handles Help button click.
void NonPebesDialog::OnSuppHelp() 
{
   HtmlHelp((DWORD_PTR)"/html/Forms/forms_supplemental_info.html",
      HH_DISPLAY_TOPIC);
}

// Description: Handles button to enable/disable benefit after entitlement.
void NonPebesDialog::OnRecalc() 
{
   UpdateData(TRUE);
   // Disable benefit date if not a recalculation
   CStatic* pS = (CStatic*) GetDlgItem(IDC_BENDATETEXT);
   pS->EnableWindow(m_recalc);
   CEdit* pE = (CEdit*) GetDlgItem(IDC_BENDATE);
   pE->EnableWindow(m_recalc);
}

void NonPebesDialog::OnBacknone() 
{
   m_bback = false;
   OnBacktype();
}

void NonPebesDialog::OnBackavgwage() 
{
   m_bback = true;
   OnBacktype();
}

void NonPebesDialog::OnBackconstant() 
{
   m_bback = true;
   OnBacktype();
}

void NonPebesDialog::OnFwrdavgwage() 
{
   m_bfwrd = true;
   OnFwrdtype();
}

void NonPebesDialog::OnFwrdconstant() 
{
   m_bfwrd = true;
   OnFwrdtype();
}

void NonPebesDialog::OnFwrdnone() 
{
   m_bfwrd = false;
   OnFwrdtype();
}

// Description: Handles enabling/disabling due to button-click on any
//   backward projection.
void NonPebesDialog::OnBacktype()
{
   // Disable backwards projection if not projected back
   CStatic* pS = (CStatic*) GetDlgItem(IDC_BACKYEARTEXT);
   pS->EnableWindow(m_bback);
   pS = (CStatic*) GetDlgItem(IDC_BACKPERCTEXT);
   pS->EnableWindow(m_bback);
   CEdit* pE = (CEdit*) GetDlgItem(IDC_BACKYEAR);
   pE->EnableWindow(m_bback);
   pE = (CEdit*) GetDlgItem(IDC_BACKPERC);
   pE->EnableWindow(m_bback);
}

// Description: Handles enabling/disabling due to button-click on any
//   forward projection.
void NonPebesDialog::OnFwrdtype()
{
   // Disable forwards projection if not projected forward
   CStatic* pS = (CStatic*) GetDlgItem(IDC_FWRDYEARTEXT);
   pS->EnableWindow(m_bfwrd);
   pS = (CStatic*) GetDlgItem(IDC_FWRDPERCTEXT);
   pS->EnableWindow(m_bfwrd);
   CEdit* pE = (CEdit*) GetDlgItem(IDC_FWRDYEAR);
   pE->EnableWindow(m_bfwrd);
   pE = (CEdit*) GetDlgItem(IDC_FWRDPERC);
   pE->EnableWindow(m_bfwrd);
}
