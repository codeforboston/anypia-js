// $Id: Milserv.cpp 1.7.1.1 2012/03/08 06:55:01EST 277133 Development 277133(2012/03/08 06:55:46EST) $
//
// Implementation of Milserv.

#include "stdafx.h"
#include "Anypia32.h"
#include "Milserv.h"
#include "PiaException.h"
#include "Htmlhelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Milserv dialog

// Description: Constructor.
//
// Arguments:
//   pParent: Parent window (default NULL).
Milserv::Milserv( CWnd* pParent ) :
CDialog( Milserv::IDD, pParent )
{
	//{{AFX_DATA_INIT(Milserv)
	m_enddate1 = _T("");
	m_enddate2 = _T("");
	m_startdate1 = _T("");
	m_startdate2 = _T("");
	m_enddate3 = _T("");
	m_enddate4 = _T("");
	m_enddate5 = _T("");
	m_enddate6 = _T("");
	m_enddate7 = _T("");
	m_enddate8 = _T("");
	m_enddate9 = _T("");
	m_startdate3 = _T("");
	m_startdate4 = _T("");
	m_startdate5 = _T("");
	m_startdate6 = _T("");
	m_startdate7 = _T("");
	m_startdate8 = _T("");
	m_startdate9 = _T("");
	m_enddate10 = _T("");
	m_enddate11 = _T("");
	m_enddate12 = _T("");
	m_enddate13 = _T("");
	m_enddate14 = _T("");
	m_enddate15 = _T("");
	m_startdate10 = _T("");
	m_startdate11 = _T("");
	m_startdate12 = _T("");
	m_startdate13 = _T("");
	m_startdate14 = _T("");
	m_startdate15 = _T("");
	//}}AFX_DATA_INIT
}

// Description: Exchange data with dialog.
//
// Arguments:
//   pDX: Data to be exchanged.
void Milserv::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Milserv)
	DDX_Text(pDX, IDC_MSENDDATE1, m_enddate1);
	DDV_MaxChars(pDX, m_enddate1, 7);
	DDX_Text(pDX, IDC_MSENDDATE2, m_enddate2);
	DDV_MaxChars(pDX, m_enddate2, 7);
	DDX_Text(pDX, IDC_MSSTARTDATE1, m_startdate1);
	DDV_MaxChars(pDX, m_startdate1, 7);
	DDX_Text(pDX, IDC_MSSTARTDATE2, m_startdate2);
	DDV_MaxChars(pDX, m_startdate2, 7);
	DDX_Text(pDX, IDC_MSENDDATE3, m_enddate3);
	DDV_MaxChars(pDX, m_enddate3, 7);
	DDX_Text(pDX, IDC_MSENDDATE4, m_enddate4);
	DDV_MaxChars(pDX, m_enddate4, 7);
	DDX_Text(pDX, IDC_MSENDDATE5, m_enddate5);
	DDV_MaxChars(pDX, m_enddate5, 7);
	DDX_Text(pDX, IDC_MSENDDATE6, m_enddate6);
	DDV_MaxChars(pDX, m_enddate6, 7);
	DDX_Text(pDX, IDC_MSENDDATE7, m_enddate7);
	DDV_MaxChars(pDX, m_enddate7, 7);
	DDX_Text(pDX, IDC_MSENDDATE8, m_enddate8);
	DDV_MaxChars(pDX, m_enddate8, 7);
	DDX_Text(pDX, IDC_MSENDDATE9, m_enddate9);
	DDV_MaxChars(pDX, m_enddate9, 7);
	DDX_Text(pDX, IDC_MSSTARTDATE3, m_startdate3);
	DDV_MaxChars(pDX, m_startdate3, 7);
	DDX_Text(pDX, IDC_MSSTARTDATE4, m_startdate4);
	DDV_MaxChars(pDX, m_startdate4, 7);
	DDX_Text(pDX, IDC_MSSTARTDATE5, m_startdate5);
	DDV_MaxChars(pDX, m_startdate5, 7);
	DDX_Text(pDX, IDC_MSSTARTDATE6, m_startdate6);
	DDV_MaxChars(pDX, m_startdate6, 7);
	DDX_Text(pDX, IDC_MSSTARTDATE7, m_startdate7);
	DDV_MaxChars(pDX, m_startdate7, 7);
	DDX_Text(pDX, IDC_MSSTARTDATE8, m_startdate8);
	DDV_MaxChars(pDX, m_startdate8, 7);
	DDX_Text(pDX, IDC_MSSTARTDATE9, m_startdate9);
	DDV_MaxChars(pDX, m_startdate9, 7);
	DDX_Text(pDX, IDC_MSENDDATE10, m_enddate10);
	DDV_MaxChars(pDX, m_enddate10, 7);
	DDX_Text(pDX, IDC_MSENDDATE11, m_enddate11);
	DDV_MaxChars(pDX, m_enddate11, 7);
	DDX_Text(pDX, IDC_MSENDDATE12, m_enddate12);
	DDV_MaxChars(pDX, m_enddate12, 7);
	DDX_Text(pDX, IDC_MSENDDATE13, m_enddate13);
	DDV_MaxChars(pDX, m_enddate13, 7);
	DDX_Text(pDX, IDC_MSENDDATE14, m_enddate14);
	DDV_MaxChars(pDX, m_enddate14, 7);
	DDX_Text(pDX, IDC_MSENDDATE15, m_enddate15);
	DDV_MaxChars(pDX, m_enddate15, 7);
	DDX_Text(pDX, IDC_MSSTARTDATE10, m_startdate10);
	DDV_MaxChars(pDX, m_startdate10, 7);
	DDX_Text(pDX, IDC_MSSTARTDATE11, m_startdate11);
	DDV_MaxChars(pDX, m_startdate11, 7);
	DDX_Text(pDX, IDC_MSSTARTDATE12, m_startdate12);
	DDV_MaxChars(pDX, m_startdate12, 7);
	DDX_Text(pDX, IDC_MSSTARTDATE13, m_startdate13);
	DDV_MaxChars(pDX, m_startdate13, 7);
	DDX_Text(pDX, IDC_MSSTARTDATE14, m_startdate14);
	DDV_MaxChars(pDX, m_startdate14, 7);
	DDX_Text(pDX, IDC_MSSTARTDATE15, m_startdate15);
	DDV_MaxChars(pDX, m_startdate15, 7);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// Milserv message handlers

BEGIN_MESSAGE_MAP(Milserv, CDialog)
	//{{AFX_MSG_MAP(Milserv)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_MILSERV_HELP, OnMilservHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Description: Handle OK button click.
void Milserv::OnOK()
{
   if (!UpdateData(TRUE))
      return;
   try {
      setdata(0, (const char *)m_startdate1, (const char *)m_enddate1);
      if (m_mscount > 1) {
         setdata(1, (const char *)m_startdate2, (const char *)m_enddate2);
      }
      if (m_mscount > 2) {
         setdata(2, (const char *)m_startdate3, (const char *)m_enddate3);
      }
      if (m_mscount > 3) {
         setdata(3, (const char *)m_startdate4, (const char *)m_enddate4);
      }
      if (m_mscount > 4) {
         setdata(4, (const char *)m_startdate5, (const char *)m_enddate5);
      }
      if (m_mscount > 5) {
         setdata(5, (const char *)m_startdate6, (const char *)m_enddate6);
      }
      if (m_mscount > 6) {
         setdata(6, (const char *)m_startdate7, (const char *)m_enddate7);
      }
      if (m_mscount > 7) {
         setdata(7, (const char *)m_startdate8, (const char *)m_enddate8);
      }
      if (m_mscount > 8) {
         setdata(8, (const char *)m_startdate9, (const char *)m_enddate9);
      }
      if (m_mscount > 9) {
         setdata(9, (const char *)m_startdate10, (const char *)m_enddate10);
      }
      if (m_mscount > 10) {
         setdata(10, (const char *)m_startdate11, (const char *)m_enddate11);
      }
      if (m_mscount > 11) {
         setdata(11, (const char *)m_startdate12, (const char *)m_enddate12);
      }
      if (m_mscount > 12) {
         setdata(12, (const char *)m_startdate13, (const char *)m_enddate13);
      }
      if (m_mscount > 13) {
         setdata(13, (const char *)m_startdate14, (const char *)m_enddate14);
      }
      if (m_mscount > 14) {
         setdata(14, (const char *)m_startdate15, (const char *)m_enddate15);
      }
   } catch (PiaException e) {
      AfxMessageBox(e.getNumber());
      return;
   }
   EndDialog(IDOK);
}

// Description: Set starting and ending dates from entered data.
void Milserv::setdata( int index, const char *startDate, const char *endDate )
{
   msdates[index].startDate = DateMoyr(startDate);
   MilServDates::startDateCheck(msdates[index].startDate);
   msdates[index].endDate = DateMoyr(endDate);
   MilServDates::endDateCheck(msdates[index].endDate);
   msdates[index].check();
}

// Description: Initialize dialog.
//
// Returns: TRUE.
BOOL Milserv::OnInitDialog()
{
   // Disable inapplicable dates
   CStatic* pS = (CStatic*) GetDlgItem(IDC_MSTEXT2);
   pS -> EnableWindow(m_mscount > 1);
   CEdit* pE = (CEdit*) GetDlgItem(IDC_MSSTARTDATE2);
   pE -> EnableWindow(m_mscount > 1);
   pE = (CEdit*) GetDlgItem(IDC_MSENDDATE2);
   pE -> EnableWindow(m_mscount > 1);
   pS = (CStatic*) GetDlgItem(IDC_MSTEXT3);
   pS -> EnableWindow(m_mscount > 2);
   pE = (CEdit*) GetDlgItem(IDC_MSSTARTDATE3);
   pE -> EnableWindow(m_mscount > 2);
   pE = (CEdit*) GetDlgItem(IDC_MSENDDATE3);
   pE -> EnableWindow(m_mscount > 2);
   pS = (CStatic*) GetDlgItem(IDC_MSTEXT4);
   pS -> EnableWindow(m_mscount > 3);
   pE = (CEdit*) GetDlgItem(IDC_MSSTARTDATE4);
   pE -> EnableWindow(m_mscount > 3);
   pE = (CEdit*) GetDlgItem(IDC_MSENDDATE4);
   pE -> EnableWindow(m_mscount > 3);
   pS = (CStatic*) GetDlgItem(IDC_MSTEXT5);
   pS -> EnableWindow(m_mscount > 4);
   pE = (CEdit*) GetDlgItem(IDC_MSSTARTDATE5);
   pE -> EnableWindow(m_mscount > 4);
   pE = (CEdit*) GetDlgItem(IDC_MSENDDATE5);
   pE -> EnableWindow(m_mscount > 4);
   pS = (CStatic*) GetDlgItem(IDC_MSTEXT6);
   pS -> EnableWindow(m_mscount > 5);
   pE = (CEdit*) GetDlgItem(IDC_MSSTARTDATE6);
   pE -> EnableWindow(m_mscount > 5);
   pE = (CEdit*) GetDlgItem(IDC_MSENDDATE6);
   pE -> EnableWindow(m_mscount > 5);
   pS = (CStatic*) GetDlgItem(IDC_MSTEXT7);
   pS -> EnableWindow(m_mscount > 6);
   pE = (CEdit*) GetDlgItem(IDC_MSSTARTDATE7);
   pE -> EnableWindow(m_mscount > 6);
   pE = (CEdit*) GetDlgItem(IDC_MSENDDATE7);
   pE -> EnableWindow(m_mscount > 6);
   pS = (CStatic*) GetDlgItem(IDC_MSTEXT8);
   pS -> EnableWindow(m_mscount > 7);
   pE = (CEdit*) GetDlgItem(IDC_MSSTARTDATE8);
   pE -> EnableWindow(m_mscount > 7);
   pE = (CEdit*) GetDlgItem(IDC_MSENDDATE8);
   pE -> EnableWindow(m_mscount > 7);
   pS = (CStatic*) GetDlgItem(IDC_MSTEXT9);
   pS -> EnableWindow(m_mscount > 8);
   pE = (CEdit*) GetDlgItem(IDC_MSSTARTDATE9);
   pE -> EnableWindow(m_mscount > 8);
   pE = (CEdit*) GetDlgItem(IDC_MSENDDATE9);
   pE -> EnableWindow(m_mscount > 8);
   pS = (CStatic*) GetDlgItem(IDC_MSTEXT10);
   pS -> EnableWindow(m_mscount > 9);
   pE = (CEdit*) GetDlgItem(IDC_MSSTARTDATE10);
   pE -> EnableWindow(m_mscount > 9);
   pE = (CEdit*) GetDlgItem(IDC_MSENDDATE10);
   pE -> EnableWindow(m_mscount > 9);
   pS = (CStatic*) GetDlgItem(IDC_MSTEXT11);
   pS -> EnableWindow(m_mscount > 10);
   pE = (CEdit*) GetDlgItem(IDC_MSSTARTDATE11);
   pE -> EnableWindow(m_mscount > 10);
   pE = (CEdit*) GetDlgItem(IDC_MSENDDATE11);
   pE -> EnableWindow(m_mscount > 10);
   pS = (CStatic*) GetDlgItem(IDC_MSTEXT12);
   pS -> EnableWindow(m_mscount > 11);
   pE = (CEdit*) GetDlgItem(IDC_MSSTARTDATE12);
   pE -> EnableWindow(m_mscount > 11);
   pE = (CEdit*) GetDlgItem(IDC_MSENDDATE12);
   pE -> EnableWindow(m_mscount > 11);
   pS = (CStatic*) GetDlgItem(IDC_MSTEXT13);
   pS -> EnableWindow(m_mscount > 12);
   pE = (CEdit*) GetDlgItem(IDC_MSSTARTDATE13);
   pE -> EnableWindow(m_mscount > 12);
   pE = (CEdit*) GetDlgItem(IDC_MSENDDATE13);
   pE -> EnableWindow(m_mscount > 12);
   pS = (CStatic*) GetDlgItem(IDC_MSTEXT14);
   pS -> EnableWindow(m_mscount > 13);
   pE = (CEdit*) GetDlgItem(IDC_MSSTARTDATE14);
   pE -> EnableWindow(m_mscount > 13);
   pE = (CEdit*) GetDlgItem(IDC_MSENDDATE14);
   pE -> EnableWindow(m_mscount > 13);
   pS = (CStatic*) GetDlgItem(IDC_MSTEXT15);
   pS -> EnableWindow(m_mscount > 14);
   pE = (CEdit*) GetDlgItem(IDC_MSSTARTDATE15);
   pE -> EnableWindow(m_mscount > 14);
   pE = (CEdit*) GetDlgItem(IDC_MSENDDATE15);
   pE -> EnableWindow(m_mscount > 14);
   CDialog::OnInitDialog();
   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

// Description: Handles context-sensitive help.
//
// Arguments:
//   pHelpInfo: Structure containing context when help was called.
BOOL Milserv::OnHelpInfo( HELPINFO* pHelpInfo )
{
   HtmlHelp(pHelpInfo->dwContextId);
   return TRUE;
}

// Description: Handles Help button click.
void Milserv::OnMilservHelp()
{
   HtmlHelp((DWORD_PTR)"/html/Forms/forms_military_service.html",
      HH_DISPLAY_TOPIC);
}
