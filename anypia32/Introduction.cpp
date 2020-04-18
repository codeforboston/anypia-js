// Introduction.cpp : implementation file
//

#include "stdafx.h"
#include "Anypia32.h"
#include "Introduction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Introduction dialog


Introduction::Introduction(CWnd* pParent /*=NULL*/)
	: CDialog(Introduction::IDD, pParent)
{
	//{{AFX_DATA_INIT(Introduction)
	m_nointro = FALSE;
	//}}AFX_DATA_INIT
}


void Introduction::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Introduction)
	DDX_Check(pDX, IDC_NOINTRO, m_nointro);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Introduction, CDialog)
	//{{AFX_MSG_MAP(Introduction)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Introduction message handlers
