#include "stdafx.h"
#include "PJClock.h"
#include "PJClockDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CPJClockDoc, CDocument)

BEGIN_MESSAGE_MAP(CPJClockDoc, CDocument)
	//{{AFX_MSG_MAP(CPJClockDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CPJClockDoc::CPJClockDoc()
{
}

CPJClockDoc::~CPJClockDoc()
{
}

BOOL CPJClockDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

void CPJClockDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef _DEBUG
void CPJClockDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPJClockDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

