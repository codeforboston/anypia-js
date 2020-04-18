// @doc FOINFODIALOG
// $Id: FoinfoDialog.cpp 1.3.1.1 2012/03/08 06:55:09EST 277133 Development 277133(2012/03/08 06:55:48EST) $
// @module FoinfoDialog.cpp |
//
// Implementation of FoinfoDialog.

#include "stdafx.h"
#include "Anypia32.h"
#include "FoinfoDialog.h"
#include "Htmlhelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FoinfoDialog dialog

// @mfunc Constructor.
//
// @parm Parent window (default NULL).

FoinfoDialog::FoinfoDialog( CWnd* pParent )
	: CDialog(FoinfoDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(FoinfoDialog)
	m_foaddr1 = _T("");
	m_foaddr2 = _T("");
	m_foaddr3 = _T("");
	m_foaddr4 = _T("");
	m_foname = _T("");
	m_fotitle = _T("");
	//}}AFX_DATA_INIT
}

// @mfunc Exchange data with dialog.
//
// @parm Data to be exchanged.

void FoinfoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FoinfoDialog)
	DDX_Text(pDX, IDC_FOADDR1, m_foaddr1);
	DDV_MaxChars(pDX, m_foaddr1, 40);
	DDX_Text(pDX, IDC_FOADDR2, m_foaddr2);
	DDV_MaxChars(pDX, m_foaddr2, 40);
	DDX_Text(pDX, IDC_FOADDR3, m_foaddr3);
	DDV_MaxChars(pDX, m_foaddr3, 40);
	DDX_Text(pDX, IDC_FOADDR4, m_foaddr4);
	DDV_MaxChars(pDX, m_foaddr4, 40);
	DDX_Text(pDX, IDC_FONAME, m_foname);
	DDV_MaxChars(pDX, m_foname, 40);
	DDX_Text(pDX, IDC_FOTITLE, m_fotitle);
	DDV_MaxChars(pDX, m_fotitle, 40);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// FoinfoDialog message handlers

BEGIN_MESSAGE_MAP(FoinfoDialog, CDialog)
	//{{AFX_MSG_MAP(FoinfoDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_FOINFOHELP, OnFoinfohelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// @mfunc Handles context-sensitive help.
//
// @parm Structure containing context when help was called.

BOOL FoinfoDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
   HtmlHelp(pHelpInfo->dwContextId);
   return TRUE;
}

// @mfunc Handles Help button click.

void FoinfoDialog::OnFoinfohelp() 
{
   HtmlHelp((DWORD_PTR)"/html/Properties/properties_foinfo.html",
      HH_DISPLAY_TOPIC);
}
