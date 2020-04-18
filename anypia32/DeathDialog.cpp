// $Id: DeathDialog.cpp 1.19.1.1 2012/03/08 06:55:02EST 277133 Development 277133(2012/03/08 06:55:46EST) $
//
// Functions for dialog to ask for information about family members.

#include <sstream>
#include "stdafx.h"
#include "Anypia32.h"
#include "DeathDialog.h"
#include "PiaException.h"
#include "Htmlhelp.h"
#include "DateFormatter.h"
#include "boost/date_time/gregorian/parsers.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

// Description: DeathDialog constructor.
//
// Arguments:
//   pParent: Parent window (default is NULL).
DeathDialog::DeathDialog( CWnd* pParent ) :
CDialog(DeathDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(DeathDialog)
	m_jbirth = _T("");
	m_jonset = _T("");
	m_jent = _T("");
	m_lifetype = -1;
	m_survivortype = -1;
	//}}AFX_DATA_INIT
}

// Description: Exchange data between dialog widgets and class members.
//
// Arguments:
//   pDX: Context for data exchange.
void DeathDialog::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DeathDialog)
	DDX_Text(pDX, IDC_JBIRTH, m_jbirth);
	DDV_MaxChars(pDX, m_jbirth, 10);
	DDX_Text(pDX, IDC_JONSET, m_jonset);
	DDV_MaxChars(pDX, m_jonset, 10);
	DDX_Text(pDX, IDC_JENT, m_jent);
	DDV_MaxChars(pDX, m_jent, 7);
	DDX_Radio(pDX, IDC_CHILD_LIFE, m_lifetype);
	DDX_Radio(pDX, IDC_CHILD_SURV, m_survivortype);
	//}}AFX_DATA_MAP
}

// DeathDialog message handlers.

BEGIN_MESSAGE_MAP(DeathDialog, CDialog)
	//{{AFX_MSG_MAP(DeathDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_AGED_WID, OnAgedWid)
	ON_BN_CLICKED(IDC_DISAB_WID, OnDisabWid)
	ON_BN_CLICKED(IDC_MOTHER, OnMother)
	ON_BN_CLICKED(IDC_CHILD_SURV, OnChildSurv)
	ON_BN_CLICKED(IDC_AGEDSPOUSE, OnAgedspouse)
	ON_BN_CLICKED(IDC_CHILD_LIFE, OnChildLife)
	ON_BN_CLICKED(IDC_YOUNGSPOUSE, OnYoungspouse)
	ON_BN_CLICKED(IDC_PREVBENIE, OnPrevbenie)
	ON_BN_CLICKED(IDC_NEXTBENIE, OnNextbenie)
	ON_BN_CLICKED(IDC_DIV_AGED_WID, OnDivAgedWid)
	ON_BN_CLICKED(IDC_DIV_AGEDSPOUSE, OnDivAgedspouse)
	ON_BN_CLICKED(IDC_DIV_DISAB_WID, OnDivDisabWid)
	ON_BN_CLICKED(IDC_FAMILY_HELP, OnFamilyHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Description: Initialize dialog.
//
// Returns: TRUE.
BOOL DeathDialog::OnInitDialog()
{
   m_fammem = 0;
   setupdata();
   CDialog::OnInitDialog();

   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

// Description: Called when OK button clicked.
void DeathDialog::OnOK()
{
   if (check())
      return;
   EndDialog(IDOK);
}

// Description: Called when OK button clicked in survivor case.
void DeathDialog::survivorOK()
{
   switch (m_survivortype)
   {
   case 0:
      m_isurv[m_fammem] = 'C';
      break;
   case 1:
      m_isurv[m_fammem] = 'E';
      break;
   case 2:
      m_isurv[m_fammem] = 'W';
      m_young[m_fammem] = ' ';
      break;
   case 3:
      m_isurv[m_fammem] = 'W';
      m_young[m_fammem] = '6';
      break;
   case 4:
      m_isurv[m_fammem] = 'D';
      m_young[m_fammem] = ' ';
      break;
   case 5:
      m_isurv[m_fammem] = 'D';
      m_young[m_fammem] = '6';
      break;
   default:
      throw PiaException(PIA_IDS_JSURV);
   }
}

// Description: Called when OK button clicked in life case.
void DeathDialog::auxiliaryOK()
{
   switch (m_lifetype)
   {
   case 0:
      m_isurv[m_fammem] = 'C';
      break;
   case 1:
      m_isurv[m_fammem] = 'B';
      m_young[m_fammem] = '2';
      break;
   case 2:
      m_isurv[m_fammem] = 'B';
      m_young[m_fammem] = ' ';
      break;
   case 3:
      m_isurv[m_fammem] = 'B';
      m_young[m_fammem] = '6';
      break;
   default:
      throw PiaException(PIA_IDS_JSURV);
   }
}

// Description: Context-sensitive help.
//
// Returns: TRUE.
//
// Arguments:
//   pHelpInfo: Context when help was called.
BOOL DeathDialog::OnHelpInfo( HELPINFO* pHelpInfo )
{
   HtmlHelp(pHelpInfo->dwContextId);
   return TRUE;
}

// Description: Called when aged widow button clicked.
void DeathDialog::OnAgedWid()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_JONSET);
   pE->EnableWindow(FALSE);
   CStatic* pS = (CStatic*) GetDlgItem(IDC_JONSETTEXT);
   pS->EnableWindow(FALSE);
   pS = (CStatic*) GetDlgItem(IDC_WIDOWTEXT);
   pS->EnableWindow(FALSE);
}

// Description: Called when disabled widow button clicked.
void DeathDialog::OnDisabWid()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_JONSET);
   pE->EnableWindow(TRUE);
   CStatic* pS = (CStatic*) GetDlgItem(IDC_JONSETTEXT);
   pS->EnableWindow(TRUE);
   pS = (CStatic*) GetDlgItem(IDC_WIDOWTEXT);
   pS->EnableWindow(TRUE);
}

// Description: Called when mother/father button clicked.
void DeathDialog::OnMother()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_JONSET);
   pE->EnableWindow(FALSE);
   CStatic* pS = (CStatic*) GetDlgItem(IDC_JONSETTEXT);
   pS->EnableWindow(FALSE);
   pS = (CStatic*) GetDlgItem(IDC_WIDOWTEXT);
   pS->EnableWindow(FALSE);
}

// Description: Called when child survivor button clicked.
void DeathDialog::OnChildSurv()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_JONSET);
   pE->EnableWindow(FALSE);
   CStatic* pS = (CStatic*) GetDlgItem(IDC_JONSETTEXT);
   pS->EnableWindow(FALSE);
   pS = (CStatic*) GetDlgItem(IDC_WIDOWTEXT);
   pS->EnableWindow(FALSE);
}

// Description: Called when aged spouse button clicked.
void DeathDialog::OnAgedspouse()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_JONSET);
   pE->EnableWindow(FALSE);
   CStatic* pS = (CStatic*) GetDlgItem(IDC_JONSETTEXT);
   pS->EnableWindow(FALSE);
   pS = (CStatic*) GetDlgItem(IDC_WIDOWTEXT);
   pS->EnableWindow(FALSE);
}

// Description: Called when child life button clicked.
void DeathDialog::OnChildLife()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_JONSET);
   pE->EnableWindow(FALSE);
   CStatic* pS = (CStatic*) GetDlgItem(IDC_JONSETTEXT);
   pS->EnableWindow(FALSE);
   pS = (CStatic*) GetDlgItem(IDC_WIDOWTEXT);
   pS->EnableWindow(FALSE);
}

// Description: Called when young spouse button clicked.
void DeathDialog::OnYoungspouse()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_JONSET);
   pE->EnableWindow(FALSE);
   CStatic* pS = (CStatic*) GetDlgItem(IDC_JONSETTEXT);
   pS->EnableWindow(FALSE);
   pS = (CStatic*) GetDlgItem(IDC_WIDOWTEXT);
   pS->EnableWindow(FALSE);
}

// Description: Called when previous benie button clicked.
void DeathDialog::OnPrevbenie()
{
   if (check())
      return;
   if (m_fammem > 0)
      m_fammem--;
   setupdata();
   UpdateData(FALSE);
}

// Description: Called when next benie button clicked.
void DeathDialog::OnNextbenie()
{
   if (check())
      return;
   if (m_fammem < m_famsize - 1)
      m_fammem++;
   setupdata();
   UpdateData(FALSE);
}

// Description: Sets up data linked to dialog.
void DeathDialog::setupdata()
{
   CButton *pB1;

   CStatic *pS = (CStatic *)GetDlgItem(IDC_FAMMEMNUM);
   ostringstream strm;
   strm << m_fammem + 1;
   pS->SetWindowText(CString(strm.str().c_str()));
   m_jbirth = CString(DateFormatter::toString(
      m_jbirthtemp[m_fammem], "s").c_str());
   m_jonset = CString(DateFormatter::toString(
      m_jonsettemp[m_fammem], "s").c_str());
   m_jent = CString(DateFormatter::toString(
      m_jenttemp[m_fammem], "s").c_str());
   if (m_ioasdi == WorkerData::SURVIVOR) {
      switch (m_isurv[m_fammem])
      {
      case 'C':
         m_survivortype = 0;
         OnChildSurv();
         break;
      case 'E':
         m_survivortype = 1;
         OnMother();
         break;
      case 'W':
         if (m_young[m_fammem] == '6') {
            m_survivortype = 3;
            OnDivDisabWid();
         }
         else {
            m_survivortype = 2;
            OnDisabWid();
         }
         break;
      case 'D':
         if (m_young[m_fammem] == '6') {
            m_survivortype = 5;
            OnDivAgedWid();
         }
         else {
            m_survivortype = 4;
            OnAgedWid();
         }
         break;
      default:
         // Assume child survivor if not set
         m_survivortype = 0;
         OnChildSurv();
         break;
      }
      pB1 = (CButton*) GetDlgItem(IDC_CHILD_LIFE);
      pB1->EnableWindow(FALSE);
      pB1 = (CButton*) GetDlgItem(IDC_YOUNGSPOUSE);
      pB1->EnableWindow(FALSE);
      pB1 = (CButton*) GetDlgItem(IDC_AGEDSPOUSE);
      pB1->EnableWindow(FALSE);
      pB1 = (CButton*) GetDlgItem(IDC_DIV_AGEDSPOUSE);
      pB1->EnableWindow(FALSE);
      pS = (CStatic*) GetDlgItem(IDC_LIFETEXT);
      pS->EnableWindow(FALSE);
   }
   else {
      switch (m_isurv[m_fammem])
      {
      case 'C':
         m_lifetype = 0;
         OnChildLife();
         break;
      case 'B':
         if (m_young[m_fammem] == '2') {
            m_lifetype = 1;
            OnYoungspouse();
         }
         else if (m_young[m_fammem] == '6') {
            m_lifetype = 3;
            OnDivAgedspouse();
         }
         else {
            m_lifetype = 2;
            OnAgedspouse();
         }
         break;
      default:
         // Assume child life if not set
         m_lifetype = 0;
         OnChildLife();
         break;
      }
      pB1 = (CButton*) GetDlgItem(IDC_CHILD_SURV);
      pB1->EnableWindow(FALSE);
      pB1 = (CButton*) GetDlgItem(IDC_MOTHER);
      pB1->EnableWindow(FALSE);
      pB1 = (CButton*) GetDlgItem(IDC_DISAB_WID);
      pB1->EnableWindow(FALSE);
      pB1 = (CButton*) GetDlgItem(IDC_DIV_DISAB_WID);
      pB1->EnableWindow(FALSE);
      pB1 = (CButton*) GetDlgItem(IDC_AGED_WID);
      pB1->EnableWindow(FALSE);
      pB1 = (CButton*) GetDlgItem(IDC_DIV_AGED_WID);
      pB1->EnableWindow(FALSE);
      pS = (CStatic*) GetDlgItem(IDC_SURVTEXT);
      pS->EnableWindow(FALSE);
   }
   CButton* pB = (CButton*) GetDlgItem(IDC_PREVBENIE);
   pB->EnableWindow(m_fammem > 0);
   pB = (CButton*) GetDlgItem(IDC_NEXTBENIE);
   pB->EnableWindow(m_fammem < m_famsize - 1);
}

// Description: Checks data for inconsistencies.
//
// Returns: True or false.
bool DeathDialog::check()
{
   if (!UpdateData(TRUE))
      return(true);
   try {
      if (m_ioasdi == WorkerData::SURVIVOR)
         survivorOK();
      else
         auxiliaryOK();
      try {
         m_jbirthtemp[m_fammem] = boost::gregorian::from_us_string((const char *)m_jbirth);
      } catch (exception&) {
         throw PiaException(PIA_IDS_JBIRTH5);
      }
      try {
         m_jenttemp[m_fammem] = DateMoyr((const char *)m_jent);
         m_jenttemp[m_fammem].check();
      } catch (PiaException&) {
         throw PiaException(PIA_IDS_ENT4);
      }
      // check date of birth for general reasonableness
      WorkerData::birth2Check(m_jbirthtemp[m_fammem]);
      // check disabled widow(er)'s date of onset
      if (m_isurv[m_fammem] == 'W') {
         try {
            m_jonsettemp[m_fammem] = boost::gregorian::from_us_string((const char *)m_jonset);
         } catch (exception&) {
            throw PiaException(PIA_IDS_JONSET7);
         }
         DisabPeriod::onsetDateCheck(m_jonsettemp[m_fammem]);
         PiaCal::widowCheck(m_jonsettemp[m_fammem], m_jbirthtemp[m_fammem],
            m_jenttemp[m_fammem]);
      }
   } catch (PiaException& e) {
      AfxMessageBox(e.getNumber());
      return(true);
   }
   return(false);
}

// Description: Called when divorced aged widow button clicked.
void DeathDialog::OnDivAgedWid()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_JONSET);
   pE->EnableWindow(FALSE);
   CStatic* pS = (CStatic*) GetDlgItem(IDC_JONSETTEXT);
   pS->EnableWindow(FALSE);
   pS = (CStatic*) GetDlgItem(IDC_WIDOWTEXT);
   pS->EnableWindow(FALSE);
}

// Description: Called when divorced spouse button clicked.
void DeathDialog::OnDivAgedspouse()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_JONSET);
   pE->EnableWindow(FALSE);
   CStatic* pS = (CStatic*) GetDlgItem(IDC_JONSETTEXT);
   pS->EnableWindow(FALSE);
   pS = (CStatic*) GetDlgItem(IDC_WIDOWTEXT);
   pS->EnableWindow(FALSE);
}

// Description: Called when divorced disabled widow button clicked.
void DeathDialog::OnDivDisabWid()
{
   CEdit* pE = (CEdit*) GetDlgItem(IDC_JONSET);
   pE->EnableWindow(TRUE);
   CStatic* pS = (CStatic*) GetDlgItem(IDC_JONSETTEXT);
   pS->EnableWindow(TRUE);
   pS = (CStatic*) GetDlgItem(IDC_WIDOWTEXT);
   pS->EnableWindow(TRUE);
}

// Description: Handles Help button click.
void DeathDialog::OnFamilyHelp()
{
   HtmlHelp((DWORD_PTR)"/html/Forms/forms_family_members.html",
      HH_DISPLAY_TOPIC);
}
