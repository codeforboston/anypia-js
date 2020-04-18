// @doc CONFIGDIALOG
// $Id: ConfigDialog.cpp 1.3.1.1 2012/03/08 06:55:07EST 277133 Development 277133(2012/03/08 06:55:47EST) $
// @module ConfigDialog.cpp |
//
// Implementation of ConfigDialog.

#include "stdafx.h"
#include "Anypia32.h"
#include "ConfigDialog.h"
#include "Htmlhelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ConfigDialog dialog

// @mfunc Constructor.
//
// @parm Parent window (default NULL).

ConfigDialog::ConfigDialog( CWnd* pParent )
	: CDialog(ConfigDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(ConfigDialog)
	m_leftmargin = 0.0f;
	m_topmargin = 0.0f;
	m_PrinterPoints = 0;
	//}}AFX_DATA_INIT
   longOutput = TRUE;
}

// @mfunc Exchange data with dialog.
//
// @parm Data to be exchanged.

void ConfigDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ConfigDialog)
	DDX_Text(pDX, IDC_LEFTMARGIN, m_leftmargin);
	DDV_MinMaxFloat(pDX, m_leftmargin, 0.f, 2.f);
	DDX_Text(pDX, IDC_TOPMARGIN, m_topmargin);
	DDV_MinMaxFloat(pDX, m_topmargin, 0.f, 2.f);
	DDX_Text(pDX, IDC_PRINTERPOINTS, m_PrinterPoints);
	DDV_MinMaxInt(pDX, m_PrinterPoints, 2, 30);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ConfigDialog message handlers

BEGIN_MESSAGE_MAP(ConfigDialog, CDialog)
	//{{AFX_MSG_MAP(ConfigDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_CONFIG_HELP, OnConfigHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// @mfunc Handle OK button click.

void ConfigDialog::OnOK() 
{
	CDialog::OnOK();
}

// @mfunc Initialize dialog.

BOOL ConfigDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// @mfunc Handles context-sensitive help.
//
// @parm Structure containing context when help was called.

BOOL ConfigDialog::OnHelpInfo( HELPINFO* pHelpInfo ) 
{
   HtmlHelp(pHelpInfo->dwContextId);
   return TRUE;
}

// @mfunc Handles Help button click.

void ConfigDialog::OnConfigHelp() 
{
   HtmlHelp((DWORD_PTR)"/html/File/file_page_setup.html",
      HH_DISPLAY_TOPIC);
}
