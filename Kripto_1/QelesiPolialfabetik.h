#if !defined(AFX_QELESIPOLIALFABETIK_H__84E03AE2_E938_4B11_9699_5F4809AE9724__INCLUDED_)
#define AFX_QELESIPOLIALFABETIK_H__84E03AE2_E938_4B11_9699_5F4809AE9724__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QelesiPolialfabetik.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQelesiPolialfabetik dialog

class CQelesiPolialfabetik : public CDialog
{
// Construction
public:
	int * ArrayQelesave;
	UINT mNumriQelesave;
	CQelesiPolialfabetik(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CQelesiPolialfabetik)
	enum { IDD = IDD_DIALOG_QELESI_POLIALFABETIK };
	CListBox	m_List;
	CEdit	m_edtNdryshoQelesin;
	CButton	m_btnShtoQelesin;
	CButton	m_btnNdryshoQelesin;
	CButton	m_btnFshijeQelesin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQelesiPolialfabetik)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQelesiPolialfabetik)
	afx_msg void OnButtonFshijQelesin();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonNdryshoQelesin();
	afx_msg void OnButtonShtoQelesin();
	afx_msg void OnChangeEditShtoQelesin();
	afx_msg void OnChangeEditNdryshoQelesin();
	afx_msg void OnSelchangeList1();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QELESIPOLIALFABETIK_H__84E03AE2_E938_4B11_9699_5F4809AE9724__INCLUDED_)
