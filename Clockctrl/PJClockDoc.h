class CPJClockDoc : public CDocument
{
public:
	virtual ~CPJClockDoc();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CPJClockDoc();
	DECLARE_DYNCREATE(CPJClockDoc)

	//{{AFX_VIRTUAL(CPJClockDoc)
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CPJClockDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

