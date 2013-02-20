#include "ClockCtrl.h"

class CPJClockView : public CView
{
public:
	CPJClockDoc* GetDocument();
	virtual ~CPJClockView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected: 
	CPJClockView();
	DECLARE_DYNCREATE(CPJClockView)

	//{{AFX_VIRTUAL(CPJClockView)
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CPJClockView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

  CClockCtrl m_ctrlClock;
};

#ifndef _DEBUG  // debug version in PJClockView.cpp
inline CPJClockDoc* CPJClockView::GetDocument()
   { return (CPJClockDoc*)m_pDocument; }
#endif

