// @doc SCREENDIALOG
// $Id: ScreenDialog.cpp 1.4.1.1 2012/03/08 06:55:05EST 277133 Development 277133(2012/03/08 06:55:47EST) $
// @module ScreenDialog.cpp |
//
// Implementation of ScreenDialog.

#include "stdafx.h"
#include "Anypia32.h"
#include "ScreenDialog.h"
#include "Htmlhelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ScreenDialog dialog

// @mfunc Constructor.
//
// @parm Parent window (default NULL).

ScreenDialog::ScreenDialog( CWnd* pParent )
	: CDialog(ScreenDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(ScreenDialog)
	m_ScreenPoints = 0;
	//}}AFX_DATA_INIT
}

// @mfunc Exchange data with dialog.
//
// @parm Data to be exchanged.

void ScreenDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ScreenDialog)
	DDX_Text(pDX, IDC_SCREENPOINTS, m_ScreenPoints);
	DDV_MinMaxInt(pDX, m_ScreenPoints, 2, 30);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ScreenDialog, CDialog)
	//{{AFX_MSG_MAP(ScreenDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_SCREENHELP, OnScreenhelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// @mfunc Handles context-sensitive help.
//
// @parm Structure containing context when help was called.

BOOL ScreenDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
   HtmlHelp(pHelpInfo->dwContextId);
   return TRUE;
}

// @mfunc Handles Help button click.

void ScreenDialog::OnScreenhelp() 
{
   HtmlHelp((DWORD_PTR)"/html/View/view_screen_settings.html",
      HH_DISPLAY_TOPIC);
}
