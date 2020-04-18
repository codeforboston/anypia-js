// $Id: HistAmtClearDialog.cpp 1.2.1.1 2012/03/08 06:55:16EST 277133 Development 277133(2012/03/08 06:55:49EST) $
//
// HistAmtClearDialog.cpp : implementation file

#include <sstream>
#include "stdafx.h"
#include "Anypia32.h"
#include "HistAmtClearDialog.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// HistAmtClearDialog dialog

// Description: Default constructor.
HistAmtClearDialog::HistAmtClearDialog( CWnd* pParent /*=NULL*/ ) :
CDialog(HistAmtClearDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(HistAmtClearDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void HistAmtClearDialog::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(HistAmtClearDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(HistAmtClearDialog, CDialog)
	//{{AFX_MSG_MAP(HistAmtClearDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// HistAmtClearDialog message handlers

BOOL HistAmtClearDialog::OnInitDialog()
{
   ostringstream strm;
   strm << "You have entered data for year";
   if (m_istartyear == m_ilastyear) {
      strm << m_istartyear;
   }
   else {
      strm << "s" << m_istartyear << " through" << m_ilastyear;
   }
   strm << ". It is saved in the Registry, and overrides the default data ";
   strm << "stored in the Calculator.";
   CEdit* pE = (CEdit*) GetDlgItem(IDC_HISTAMTCLEARTEXT);
   pE->SetWindowText(strm.str().c_str());
   CDialog::OnInitDialog();
   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}
