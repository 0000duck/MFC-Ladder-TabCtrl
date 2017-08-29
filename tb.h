// tb.h : main header file for the TB application
//

#if !defined(AFX_TB_H__FDBA2DAB_7942_4026_8A55_AE5A47CD43AE__INCLUDED_)
#define AFX_TB_H__FDBA2DAB_7942_4026_8A55_AE5A47CD43AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTbApp:
// See tb.cpp for the implementation of this class
//

class CTbApp : public CWinApp
{
public:
	CTbApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTbApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTbApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TB_H__FDBA2DAB_7942_4026_8A55_AE5A47CD43AE__INCLUDED_)
