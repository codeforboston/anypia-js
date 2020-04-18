// $Id: WageBaseDialog.cpp 1.10.1.2 2017/12/12 08:19:44EST 277133 Development  $
//
// Implementation of WageBaseDialog.

#include <sstream>
#include "stdafx.h"
#include "Anypia32.h"
#include "WageBaseDialog.h"
#include "pia.h"
#include "Htmlhelp.h"
#include "oactcnst.h"
#include "TextFloatFormatPatch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// WageBaseDialog dialog

// Description: Constructor.
//
// Arguments:
//   pParent: Parent window (default NULL).
WageBaseDialog::WageBaseDialog( CWnd* pParent /*=NULL*/ ) :
   CDialog(WageBaseDialog::IDD, pParent),
   m_DAplwb(YEAR37, WorkerData::getMaxyear()),
   m_DAolwb(YEAR37, WorkerData::getMaxyear())
{
	//{{AFX_DATA_INIT(WageBaseDialog)
	m_olwb = 0.0;
	m_plwb = 0.0;
	//}}AFX_DATA_INIT
}

// @mfunc Exchange data with dialog.
//
// @parm Data to be exchanged.

void WageBaseDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(WageBaseDialog)
	DDX_Text2(pDX, IDC_OLWB, m_olwb);
	DDV_MinMaxDouble(pDX, m_olwb, 0., MAXEARN);
	DDX_Text2(pDX, IDC_PLWB, m_plwb);
	DDV_MinMaxDouble(pDX, m_plwb, 0., MAXEARN);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// WageBaseDialog message handlers

BEGIN_MESSAGE_MAP(WageBaseDialog, CDialog)
	//{{AFX_MSG_MAP(WageBaseDialog)
	ON_BN_CLICKED(IDC_WBNEXTYEAR, OnWbnextyear)
	ON_BN_CLICKED(IDC_WBPREVYEAR, OnWbprevyear)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_WAGEBASEHELP, OnWagebasehelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// @mfunc Handle Next Year button.

void WageBaseDialog::OnWbnextyear()
{
   if (check())
      return;
   if (m_year < m_ilastyear)
      m_year++;
   setupdata();
   UpdateData(FALSE);
}

// @mfunc Handle Previous Year button.

void WageBaseDialog::OnWbprevyear()
{
   if (check())
      return;
   if (m_year > m_istartyear)
      m_year--;
   setupdata();
   UpdateData(FALSE);
}

// @mfunc Handle OK button click.

void WageBaseDialog::OnOK()
{
   if (check())
      return;
   EndDialog(IDOK);
}

// @mfunc Initialize dialog.

BOOL WageBaseDialog::OnInitDialog()
{
   m_year = m_istartyear;
   setupdata();
   CDialog::OnInitDialog();

   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

// @mfunc Handles context-sensitive help.
//
// @parm Structure containing context when help was called.

BOOL WageBaseDialog::OnHelpInfo(HELPINFO* pHelpInfo)
{
   HtmlHelp(pHelpInfo->dwContextId);
   return TRUE;
}

// @mfunc Set up data to be displayed for one year.

void WageBaseDialog::setupdata()
{
   CStatic* pS = (CStatic*) GetDlgItem(IDC_WBTEXT);
   CString wagebasestring;
   ostringstream strm;
   strm << m_year;
   AfxFormatString1(wagebasestring, PIA_IDS_WAGEBASE,
      strm.str().c_str());
   pS->SetWindowText(wagebasestring);
   m_plwb = m_DAplwb[m_year];
   m_olwb = m_DAolwb[m_year];
}

// @mfunc Checks data for inconsistencies.

bool WageBaseDialog::check()
{
   if (!UpdateData(TRUE))
      return(true);
   m_DAplwb[m_year] = m_plwb;
   m_DAolwb[m_year] = m_olwb;
   return(false);
}

// @mfunc Handles Help button click.

void WageBaseDialog::OnWagebasehelp() 
{
   HtmlHelp((DWORD_PTR)"/html/Forms/forms_wage_bases.html",
      HH_DISPLAY_TOPIC);
}
