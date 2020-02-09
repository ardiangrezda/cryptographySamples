#if !defined(AFX_QELESI_H__328BE8DE_3D15_4D8C_BB06_462D443DC354__INCLUDED_)
#define AFX_QELESI_H__328BE8DE_3D15_4D8C_BB06_462D443DC354__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Qelesi.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQelesi dialog

class CQelesi : public CDialog
{
// Construction
public:
	CQelesi(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CQelesi)
	enum { IDD = IDD_DIALOG_QELESI };
	UINT	m_uiQelesi;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQelesi)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQelesi)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QELESI_H__328BE8DE_3D15_4D8C_BB06_462D443DC354__INCLUDED_)
