// Kripto_1.h : main header file for the KRIPTO_1 application
//

#if !defined(AFX_KRIPTO_1_H__BFE9D48A_5AEA_450B_A2C3_55B4C7BEDDC9__INCLUDED_)
#define AFX_KRIPTO_1_H__BFE9D48A_5AEA_450B_A2C3_55B4C7BEDDC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CKripto_1App:
// See Kripto_1.cpp for the implementation of this class
//

class CKripto_1App : public CWinApp
{
public:
	CKripto_1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKripto_1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CKripto_1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KRIPTO_1_H__BFE9D48A_5AEA_450B_A2C3_55B4C7BEDDC9__INCLUDED_)
