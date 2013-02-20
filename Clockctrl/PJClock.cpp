#include "stdafx.h"
#include "PJClock.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CPJClockApp* GetApp()
{
  CPJClockApp* pApp = (CPJClockApp*) AfxGetApp();
  ASSERT(pApp);
  return pApp;
}

BEGIN_MESSAGE_MAP(CPJClockApp, CWinApp)
	//{{AFX_MSG_MAP(CPJClockApp)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
END_MESSAGE_MAP()

CPJClockApp::CPJClockApp()
{
}

CPJClockApp theApp;

BOOL CPJClockApp::InitInstance()
{
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

  //Determine if the OS supports layered windows
  HINSTANCE hUser32 = GetModuleHandle(_T("USER32.DLL"));
  if (hUser32)
    m_lpfnSetLayeredWindowAttributes = (lpfnSetLayeredWindowAttributes) GetProcAddress(hUser32, "SetLayeredWindowAttributes");

  //Bring up the mainframe window
  CMainFrame* pFrameWnd = new CMainFrame();
  VERIFY(pFrameWnd->LoadFrame(IDR_MAINFRAME));
  m_pMainWnd = pFrameWnd;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


