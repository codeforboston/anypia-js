// $Id: PebesDialog.cpp 1.12.1.1 2012/03/08 06:55:07EST 277133 Development 277133(2012/03/08 06:55:47EST) $
//
// Implementation of PebesDialog.

#include <sstream>
#include "stdafx.h"
#include "Anypia32.h"
#include "PebesDialog.h"
#include "pia.h"
#include "PiaException.h"
#include "UserAssumptions.h"
#include "Htmlhelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// PebesDialog dialog

// Description: Constructor.
//
// Arguments:
//   pParent: Parent window (default NULL).
PebesDialog::PebesDialog( CWnd* pParent )
	: CDialog(PebesDialog::IDD, pParent)
   , m_nonpenpebesdate(_T(""))
{
	//{{AFX_DATA_INIT(PebesDialog)
	m_ageplan = 0;
	m_beginpebes = 0;
	m_month = _T("");
	m_nonpen = 0.0;
	//}}AFX_DATA_INIT
}

// Description: Exchange data with dialog.
//
// Arguments:
//   pDX: Data to be exchanged.
void PebesDialog::DoDataExchange( CDataExchange* pDX )
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(PebesDialog)
   DDX_Text(pDX, IDC_AGEPLAN, m_ageplan);
   DDV_MinMaxInt(pDX, m_ageplan, 0, 99);
   DDX_Text(pDX, IDC_BEGINPEBES, m_beginpebes);
   DDV_MinMaxInt(pDX, m_beginpebes, 1937, 2100);
   DDX_LBString(pDX, IDC_MONTH, m_month);
   DDX_Text(pDX, IDC_NONPEN_PEBES, m_nonpen);
   DDV_MinMaxDouble(pDX, m_nonpen, 0., 999999.99);
   //}}AFX_DATA_MAP
   DDX_Text(pDX, IDC_NONPENPEBESDATE, m_nonpenpebesdate);
	DDV_MaxChars(pDX, m_nonpenpebesdate, 7);
}

/////////////////////////////////////////////////////////////////////////////
// PebesDialog message handlers

BEGIN_MESSAGE_MAP(PebesDialog, CDialog)
	//{{AFX_MSG_MAP(PebesDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_PEBES_HELP, OnPebesHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Description: Initialize dialog.
//
// Returns: TRUE.
BOOL PebesDialog::OnInitDialog()
{
   // Fill out month box
   CListBox* pLB = (CListBox*) GetDlgItem(IDC_MONTH);
   pLB->InsertString(-1, "January");
   pLB->InsertString(-1, "February");
   pLB->InsertString(-1, "March");
   pLB->InsertString(-1, "April");
   pLB->InsertString(-1, "May");
   pLB->InsertString(-1, "June");
   pLB->InsertString(-1, "July");
   pLB->InsertString(-1, "August");
   pLB->InsertString(-1, "September");
   pLB->InsertString(-1, "October");
   pLB->InsertString(-1, "November");
   pLB->InsertString(-1, "December");
   pLB->SetCurSel(m_imonth);
   CString monthstring;
   ostringstream strm;
   strm << m_istart;
   AfxFormatString1(monthstring, PIA_IDS_MONTHTEXT, strm.str().c_str());
   CStatic* pS = (CStatic*) GetDlgItem(IDC_MONTHTEXT);
   pS->SetWindowText(monthstring);
   CDialog::OnInitDialog();

   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

// Description: Handle OK button click.
void PebesDialog::OnOK()
{
   if (!UpdateData(TRUE))
      return;
   try {
      WorkerData::ibegin1Check(m_beginpebes, UserAssumptions::getIstart());
      WorkerData::ibeginCheck(m_beginpebes, m_birthyear);
      if (m_nonpen > 0) {
         try {
            m_nonpendatetemp = DateMoyr((const char *)m_nonpenpebesdate);
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
      CListBox* pLB = (CListBox*) GetDlgItem(IDC_MONTH);
      if ((m_imonth = pLB->GetCurSel()) == LB_ERR) {
         throw PiaException(PIA_IDS_PEBESMONTH);
      }
      EndDialog(IDOK);
   } catch (PiaException& e) {
      AfxMessageBox(e.getNumber());
      return;
   }
}

// Description: Handles context-sensitive help.
//
// Arguments:
//   pHelpInfo: Structure containing context when help was called.
BOOL PebesDialog::OnHelpInfo( HELPINFO* pHelpInfo )
{
   HtmlHelp(pHelpInfo->dwContextId);
   return TRUE;
}

// Description: Handles Help button click.
void PebesDialog::OnPebesHelp() 
{
   HtmlHelp((DWORD_PTR)"/html/Forms/forms_statement_info.html",
      HH_DISPLAY_TOPIC);
}
