#include "ClockCtrl.h"

class CMainFrame : public CFrameWnd
{
public:
//Constructors / Destructors
	CMainFrame();
	virtual ~CMainFrame();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	DECLARE_DYNCREATE(CMainFrame)

	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMainFrame)
	afx_msg void OnFileTransparent();
	afx_msg void OnUpdateFileTransparent(CCmdUI* pCmdUI);
	afx_msg void OnFileAlwaysontop();
	afx_msg void OnUpdateFileAlwaysontop(CCmdUI* pCmdUI);
	afx_msg void OnFileCaption();
	afx_msg void OnUpdateFileCaption(CCmdUI* pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

  BOOL m_bTopMostWindow;
  CMenu m_MainMenu;
  CClockCtrl m_ctrlClock;
};

