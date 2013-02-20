#include "stdafx.h"
#include "PJClock.h"
#include "PJClockDoc.h"
#include "PJClockView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CPJClockView, CView)

BEGIN_MESSAGE_MAP(CPJClockView, CView)
	//{{AFX_MSG_MAP(CPJClockView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CPJClockView::CPJClockView()
{
}

CPJClockView::~CPJClockView()
{
}

BOOL CPJClockView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CPJClockView::OnDraw(CDC* /*pDC*/)
{
	CPJClockDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

#ifdef _DEBUG
void CPJClockView::AssertValid() const
{
	CView::AssertValid();
}

void CPJClockView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPJClockDoc* CPJClockView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPJClockDoc)));
	return (CPJClockDoc*)m_pDocument;
}
#endif //_DEBUG


int CPJClockView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
  //Create the clock control
  CRect rClient;
  GetClientRect(&rClient);
	if (!m_ctrlClock.Create(_T(""), WS_CHILD | WS_VISIBLE | SS_SIMPLE, rClient, this))
    return -1;
	
	return 0;
}

void CPJClockView::OnSize(UINT nType, int cx, int cy) 
{
  //Let the parent class do its thing
	CView::OnSize(nType, cx, cy);
	
  //Resize the clock control
  CRect rClient;
  GetClientRect(&rClient);
  m_ctrlClock.MoveWindow(rClient);
}
