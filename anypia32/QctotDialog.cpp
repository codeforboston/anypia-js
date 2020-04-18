// $Id: QctotDialog.cpp 1.8.1.1 2012/03/08 06:55:11EST 277133 Development 277133(2012/03/08 06:55:48EST) $
//
// Implementation of QctotDialog.

#include "stdafx.h"
#include "Anypia32.h"
#include "QctotDialog.h"
#include "pia.h"
#include "PiaException.h"
#include "Htmlhelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// QctotDialog dialog

// Description: Constructor.
//
// Arguments:
//   pParent: Parent window (default NULL).
QctotDialog::QctotDialog(CWnd* pParent /*=NULL*/)
	: CDialog(QctotDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(QctotDialog)
	m_qc51td = 0;
	m_qctd = 0;
	m_qcann = -1;
	//}}AFX_DATA_INIT
}

// Description: Exchange data with dialog.
//
// Arguments:
//   pDX: Data to be exchanged.
void QctotDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(QctotDialog)
	DDX_Text(pDX, IDC_QC51TD, m_qc51td);
	DDV_MinMaxInt(pDX, m_qc51td, 0, 108);
	DDX_Text(pDX, IDC_QCTD, m_qctd);
	DDV_MinMaxInt(pDX, m_qctd, 0, 164);
	DDX_Radio(pDX, IDC_RADIO_QCTOT, m_qcann);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// QctotDialog message handlers

BEGIN_MESSAGE_MAP(QctotDialog, CDialog)
	//{{AFX_MSG_MAP(QctotDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_QCTOT_HELP, OnQctotHelp)
	ON_BN_CLICKED(IDC_RADIO_QCANN, OnRadioQcann)
	ON_BN_CLICKED(IDC_RADIO_QCTOT, OnRadioQctot)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Description: Handles context-sensitive help.
//
// Arguments:
//   pHelpInfo: Structure containing context when help was called.
BOOL QctotDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
   HtmlHelp(pHelpInfo->dwContextId);
   return TRUE;
}

// Description: Initialize dialog.
BOOL QctotDialog::OnInitDialog() 
{
   bool bqctd = (m_qcann == 0);
   CEdit* pE = (CEdit*) GetDlgItem(IDC_QCTDTEXT);
   pE->EnableWindow(bqctd);
   pE = (CEdit*) GetDlgItem(IDC_QCTD);
   pE->EnableWindow(bqctd);
   pE = (CEdit*) GetDlgItem(IDC_QC51TDTEXT);
   pE->EnableWindow(m_bqc51td && bqctd);
   pE = (CEdit*) GetDlgItem(IDC_QC51TD);
   pE->EnableWindow(m_bqc51td && bqctd);
   CDialog::OnInitDialog();

   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

// Description: Handle OK button click.
void QctotDialog::OnOK()
{
   if (!UpdateData(TRUE))
      return;
   try {
      // if earnings started after 1950, total qcs must meet test for
      // all qcs after 1950
      if (!m_bqc51td) {
         WorkerData::qc51tdCheck(m_qctd);
         m_qc51td = m_qctd;
      }
      // check for consistency between the two amounts
      WorkerData::qcCheck(m_qctd, m_qc51td);
   } catch (PiaException e) {
      AfxMessageBox(e.getNumber());
      return;
   }
   EndDialog(IDOK);
}

// Description: Handles Help button click.
void QctotDialog::OnQctotHelp() 
{
   HtmlHelp((DWORD_PTR)"/html/Forms/forms_summary_qcs.html",
      HH_DISPLAY_TOPIC);
}

void QctotDialog::OnRadioQcann() 
{
   // Disable total quarters of coverage widgets
   CEdit* pE = (CEdit*) GetDlgItem(IDC_QCTDTEXT);
   pE->EnableWindow(FALSE);
   pE = (CEdit*) GetDlgItem(IDC_QCTD);
   pE->EnableWindow(FALSE);
   pE = (CEdit*) GetDlgItem(IDC_QC51TDTEXT);
   pE->EnableWindow(FALSE);
   pE = (CEdit*) GetDlgItem(IDC_QC51TD);
   pE->EnableWindow(FALSE);
}

void QctotDialog::OnRadioQctot() 
{
   // Enable total quarters of coverage widgets
   CEdit* pE = (CEdit*) GetDlgItem(IDC_QCTDTEXT);
   pE->EnableWindow(TRUE);
   pE = (CEdit*) GetDlgItem(IDC_QCTD);
   pE->EnableWindow(TRUE);
   pE = (CEdit*) GetDlgItem(IDC_QC51TDTEXT);
   pE->EnableWindow(m_bqc51td);
   pE = (CEdit*) GetDlgItem(IDC_QC51TD);
   pE->EnableWindow(m_bqc51td);
}
