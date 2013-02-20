#include "stdafx.h"
#include "PJClock.h"
#include "resource.h"
#include "MainFrm.h"

#define MOUSE_MOVE 0xF012

//In case you do not have the latest Platform SDK installed
#ifndef WS_EX_LAYERED
#define WS_EX_LAYERED           0x00080000
#endif
#ifndef LWA_COLORKEY
#define LWA_COLORKEY            0x00000001
#endif


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CMainFrame)
	ON_COMMAND(ID_FILE_TRANSPARENT, OnFileTransparent)
	ON_UPDATE_COMMAND_UI(ID_FILE_TRANSPARENT, OnUpdateFileTransparent)
	ON_COMMAND(ID_FILE_ALWAYSONTOP, OnFileAlwaysontop)
	ON_UPDATE_COMMAND_UI(ID_FILE_ALWAYSONTOP, OnUpdateFileAlwaysontop)
	ON_COMMAND(ID_FILE_CAPTION, OnFileCaption)
	ON_UPDATE_COMMAND_UI(ID_FILE_CAPTION, OnUpdateFileCaption)
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMainFrame::CMainFrame()
{
  m_bTopMostWindow = FALSE;
  VERIFY(m_MainMenu.LoadMenu(IDR_MAINFRAME));
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
  //Let the parent class do its thing
	BOOL bSuccess = CFrameWnd::PreCreateWindow(cs);

  //Remove the client edge
  cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
  return bSuccess;
}

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


void CMainFrame::OnFileTransparent() 
{
  CPJClockApp* pApp = GetApp();
  if (pApp->m_lpfnSetLayeredWindowAttributes)
  {
	  BOOL bLayered = GetWindowLong(m_hWnd, GWL_EXSTYLE) & WS_EX_LAYERED;
    if (!bLayered)
    {
      //Add the transparent style
      LONG nStyle = GetWindowLong(m_hWnd, GWL_EXSTYLE);
      SetWindowLong(m_hWnd, GWL_EXSTYLE, nStyle | WS_EX_LAYERED);

      //Make the Window transparent used the button face color
      pApp->m_lpfnSetLayeredWindowAttributes(m_hWnd, GetSysColor(COLOR_BTNFACE), 0, LWA_COLORKEY);
    }
    else
    {
      //Remove the layered style
      LONG nStyle = GetWindowLong(m_hWnd, GWL_EXSTYLE);
      nStyle &= ~WS_EX_LAYERED;
      SetWindowLong(m_hWnd, GWL_EXSTYLE, nStyle);

      //Ask the window and its children to repaint
      ::RedrawWindow(m_hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
    }
  }
  else
    AfxMessageBox(_T("Transparency support is not provided on this OS, Please try Windows 2000 or later"));
}

void CMainFrame::OnUpdateFileTransparent(CCmdUI* pCmdUI) 
{
  if (GetApp()->m_lpfnSetLayeredWindowAttributes) 
    pCmdUI->SetCheck(GetWindowLong(m_hWnd, GWL_EXSTYLE) & WS_EX_LAYERED);
  else
    pCmdUI->Enable(TRUE);
}

void CMainFrame::OnFileAlwaysontop() 
{
	m_bTopMostWindow = !m_bTopMostWindow;

  if (m_bTopMostWindow)
    SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
  else
  {
    SetRedraw(FALSE);
    SetWindowPos(&CWnd::wndBottom, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    BringWindowToTop();
    SetRedraw(TRUE);
  }
}

void CMainFrame::OnUpdateFileAlwaysontop(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_bTopMostWindow);
}

void CMainFrame::OnFileCaption() 
{
	BOOL bCaption = GetWindowLong(m_hWnd, GWL_STYLE) & WS_CAPTION;
  if (!bCaption)
  {
    //Add the caption and thick frame styles
    LONG nStyle = GetWindowLong(m_hWnd, GWL_STYLE);
    nStyle |= WS_CAPTION;
    nStyle |= WS_THICKFRAME;
    SetWindowLong(m_hWnd, GWL_STYLE, nStyle);

    //Hook up the menu again
    SetMenu(&m_MainMenu);
  }
  else
  {
    //Remove the caption and thick frame styles
    LONG nStyle = GetWindowLong(m_hWnd, GWL_STYLE);
    nStyle &= ~WS_CAPTION;
    nStyle &= ~WS_THICKFRAME;
    SetWindowLong(m_hWnd, GWL_STYLE, nStyle);

    //Also remove the menu
    SetMenu(NULL);
  }

  //Ask the window and its children to repaint
  ::RedrawWindow(m_hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
}

void CMainFrame::OnUpdateFileCaption(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(GetWindowLong(m_hWnd, GWL_STYLE) & WS_CAPTION);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
  //Let the parent class do its thing
	CFrameWnd::OnSize(nType, cx, cy);
	
  //Resize the clock control
  CRect rClient;
  GetClientRect(&rClient);
  m_ctrlClock.MoveWindow(rClient);
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
  //Create the clock control
  CRect rClient;
  GetClientRect(&rClient);
	if (!m_ctrlClock.Create(_T(""), WS_CHILD | WS_VISIBLE | SS_SIMPLE, rClient, this))
    return 0;

  // Let the parent class do its thing
	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::OnLButtonDown(UINT /*nFlags*/, CPoint /*point*/) 
{
  //Fake a Window drag
  SendMessage(WM_LBUTTONUP);
  SendMessage(WM_SYSCOMMAND, MOUSE_MOVE);
}

void CMainFrame::OnContextMenu(CWnd*, CPoint point)
{
	if (point.x == -1 && point.y == -1)
  {
		//keystroke invocation
		CRect rect;
		GetClientRect(rect);
		ClientToScreen(rect);

		point = rect.TopLeft();
		point.Offset(5, 5);
	}

	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_POPUP_MAINFRAME));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	CWnd* pWndPopupOwner = this;

	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,	pWndPopupOwner);
}

void CMainFrame::OnLButtonDblClk(UINT /*nFlags*/, CPoint /*point*/) 
{
  OnFileCaption();
}

