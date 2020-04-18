// $Id: Anypia32.cpp 1.9.1.1 2012/03/08 06:55:00EST 277133 Development  $
//
// Defines the class behaviors for the ANYPIA32 application.

#pragma warning(disable:4786)
#include "stdafx.h"
#include "Anypia32.h"

#include "MainFrm.h"
#include "AnypiaDoc.h"
#include "AnypiaView.h"
#include "Introduction.h"
#include "Htmlhelp.h"
#include "DebugCase.h"
#if defined(DEBUGCASE)
#include <fstream>
#include "Trace.h"
#include "TextWriterTraceListener.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if defined(DEBUGCASE)
   std::ofstream outputFile("output");
   TextWriterTraceListener outputLog(&outputFile);
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnypia32App

BEGIN_MESSAGE_MAP(CAnypia32App, CWinApp)
	//{{AFX_MSG_MAP(CAnypia32App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

// Description: CAnypia32App construction.
CAnypia32App::CAnypia32App()
{
  EnableHtmlHelp();
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAnypia32App object
CAnypia32App theApp;

// Description: CAnypia32App initialization.
BOOL CAnypia32App::InitInstance()
{
  InitCommonControls();
  CoInitialize(NULL);
  CWinApp::InitInstance();
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

//#ifdef _AFXDLL
	//Enable3dControls();			// Call this when using MFC in a shared DLL
//#else
	//Enable3dControlsStatic();	// Call this when linking to MFC statically
//#endif

	// Set the registry key under which our settings are stored.
	SetRegistryKey(_T("Social Security Administration"));

	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CAnypia32Doc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CAnypia32View));
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

#if defined(DEBUGCASE)
   Trace::getListeners().push_back(&outputLog);
#endif

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

   const char *section = "Settings";
   const char *sectitle = "No Introduction";
   int nointro = AfxGetApp()->GetProfileInt(section, sectitle, 0);
   // show introductory dialog if not turned off
   if (nointro == 0) {
      Introduction dlg;
      dlg.m_nointro = nointro;
      int ret = (int)dlg.DoModal();
      AfxGetApp()->WriteProfileInt(section, sectitle, dlg.m_nointro);
   }

	return TRUE;
}

// @class CAboutDlg dialog used for App About.
//
// @base public | CDialog

class CAboutDlg : public CDialog
{
   // @access Public Members
   public:
      // @cmember Constructor.
	   CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

// @mfunc void | CAboutDlg | CAboutDlg | Constructor.

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

// @mfunc Exchange data with dialog.
//
// @parm Data to be exchanged.

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// @mfunc App command to run the dialog.

void CAnypia32App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// @mfunc Handle a request for help, using HtmlHelp.
//
// @parm Context-sensitive help number.
// @parm Type of help.<nl>
//   HELP_CONTEXT: context-sensitive<nl>
//   HELP_FINDER: regular help.

void CAnypia32App::WinHelp(DWORD dwData, UINT nCmd) 
{
	//CWinApp::WinHelp(dwData, nCmd);
  switch (nCmd)
  {
  case HELP_CONTEXT:
    HtmlHelp(dwData);
    break;
  case HELP_FINDER:
    HtmlHelp(0, HH_DISPLAY_TOPIC);
    break;
  }
}
