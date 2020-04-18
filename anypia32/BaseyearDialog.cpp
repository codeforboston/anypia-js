// $Id: BaseyearDialog.cpp 1.7.1.1 2012/03/08 06:55:05EST 277133 Development 277133(2012/03/08 06:55:47EST) $
//
// Implementation of BaseyearDialog.

#include "stdafx.h"
#include "Anypia32.h"
#include "BaseyearDialog.h"
#include "Resource.h"
#include "PiaException.h"
#include "Htmlhelp.h"
#include "oactcnst.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// BaseyearDialog dialog

// Description: Constructor.
//
// Arguments:
//   pParent: Parent window (default NULL).
BaseyearDialog::BaseyearDialog( CWnd* pParent )
	: CDialog(BaseyearDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(BaseyearDialog)
	m_baseyear = 0;
    m_resetCompYear = false;
	//}}AFX_DATA_INIT
}

// Description: Exchange data with dialog.
//
// Arguments:
//   pDX: Data to be exchanged.
void BaseyearDialog::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BaseyearDialog)
	DDX_Text(pDX, IDC_BASEYEAR, m_baseyear);
	DDV_MinMaxInt(pDX, m_baseyear, 1979, LASTYRSR);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// BaseyearDialog message handlers

BEGIN_MESSAGE_MAP(BaseyearDialog, CDialog)
	//{{AFX_MSG_MAP(BaseyearDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_BASEYEARHELP, OnBaseyearhelp)
	ON_BN_CLICKED(IDC_BASEYEARCLEAR, OnBaseyearclear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Description: Handle OK button click.
void BaseyearDialog::OnOK()
{
   if (!UpdateData(TRUE))
      return;
   try {
      BaseYear::yearCheck(m_baseyear);
      if (m_baseyear > m_ilastyear) {
         throw PiaException(PIA_IDS_BASEYR1);
      }
   } catch (PiaException& e) {
      AfxMessageBox(e.getNumber());
      return;
   }
   AfxMessageBox("Review stored benefit increases and average wage increases for consistency with new computation year!");
   EndDialog(IDOK);
}

// Description: Handles context-sensitive help.
//
// Returns: TRUE.
//
// Arguments:
//   pHelpInfo: Structure containing context when help was called.
BOOL BaseyearDialog::OnHelpInfo( HELPINFO* pHelpInfo ) 
{
   HtmlHelp(pHelpInfo->dwContextId);
   return TRUE;
}

// Description: Handles Help button click.
void BaseyearDialog::OnBaseyearhelp() 
{
   HtmlHelp((DWORD_PTR)"/html/Properties/comp_year.html",
      HH_DISPLAY_TOPIC);
}

// Description: Clears corresponding ini file and resets to stored value.
void BaseyearDialog::OnBaseyearclear() 
{
   // clear the ini file
   baseyearIni->clear();
   // reset base year
   baseyear->read();
   setdata();
   UpdateData(FALSE);
   m_resetCompYear = true;
}

// Description: Sets year to stored value.
void BaseyearDialog::setdata()
{
   m_baseyear = baseyear->getYear();
}
