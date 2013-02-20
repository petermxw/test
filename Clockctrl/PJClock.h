#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

typedef BOOL (WINAPI *lpfnSetLayeredWindowAttributes)(HWND, COLORREF, BYTE, DWORD);

class CPJClockApp : public CWinApp
{
public:
//Constructors / Destructors
	CPJClockApp();

//Member variables
  lpfnSetLayeredWindowAttributes m_lpfnSetLayeredWindowAttributes;

protected:
	//{{AFX_VIRTUAL(CPJClockApp)
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CPJClockApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//////////// Helper Functions
CPJClockApp* GetApp();
