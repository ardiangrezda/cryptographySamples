// Kripto_1Dlg.h : header file
//

#if !defined(AFX_KRIPTO_1DLG_H__14D40CF3_6A8C_406D_89EC_2C05F6FB507C__INCLUDED_)
#define AFX_KRIPTO_1DLG_H__14D40CF3_6A8C_406D_89EC_2C05F6FB507C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CKripto_1Dlg dialog

class CKripto_1Dlg : public CDialog
{
// Construction
public:
	int * ArrayQelesave;
	int mNumriQelesave;
	int DecryptedFunction();
	CString FileNameDecrypted;
	CString FileNameEncrypted;
	CString FileNameOriginal;
	int EncryptedFunction();
	UINT m_uiQelesiZevendesim;
	UINT m_uiQelesi;
	CKripto_1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CKripto_1Dlg)
	enum { IDD = IDD_KRIPTO_1_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKripto_1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CKripto_1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEncryptCesar();
	afx_msg void OnDecryptCesar();
	afx_msg void OnEncryptTransponim();
	afx_msg void OnDecryptTransponim();
	afx_msg void OnEncryptZevendesim();
	afx_msg void OnDecryptZevendesim();
	afx_msg void OnEncryptPolialfabetik();
	afx_msg void OnDecryptPolialfabetik();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KRIPTO_1DLG_H__14D40CF3_6A8C_406D_89EC_2C05F6FB507C__INCLUDED_)
