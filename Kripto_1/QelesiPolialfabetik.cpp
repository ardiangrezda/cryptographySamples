// QelesiPolialfabetik.cpp : implementation file
//

#include "stdafx.h"
#include "Kripto_1.h"
#include "QelesiPolialfabetik.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQelesiPolialfabetik dialog


CQelesiPolialfabetik::CQelesiPolialfabetik(CWnd* pParent /*=NULL*/)
	: CDialog(CQelesiPolialfabetik::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQelesiPolialfabetik)
	//}}AFX_DATA_INIT
}


void CQelesiPolialfabetik::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQelesiPolialfabetik)
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_EDIT_NDRYSHO_QELESIN, m_edtNdryshoQelesin);
	DDX_Control(pDX, IDC_BUTTON_SHTO_QELESIN, m_btnShtoQelesin);
	DDX_Control(pDX, IDC_BUTTON_NDRYSHO_QELESIN, m_btnNdryshoQelesin);
	DDX_Control(pDX, IDC_BUTTON_FSHIJ_QELESIN, m_btnFshijeQelesin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQelesiPolialfabetik, CDialog)
	//{{AFX_MSG_MAP(CQelesiPolialfabetik)
	ON_BN_CLICKED(IDC_BUTTON_FSHIJ_QELESIN, OnButtonFshijQelesin)
	ON_BN_CLICKED(IDC_BUTTON_NDRYSHO_QELESIN, OnButtonNdryshoQelesin)
	ON_BN_CLICKED(IDC_BUTTON_SHTO_QELESIN, OnButtonShtoQelesin)
	ON_EN_CHANGE(IDC_EDIT_SHTO_QELESIN, OnChangeEditShtoQelesin)
	ON_EN_CHANGE(IDC_EDIT_NDRYSHO_QELESIN, OnChangeEditNdryshoQelesin)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQelesiPolialfabetik message handlers

void CQelesiPolialfabetik::OnButtonFshijQelesin() 
{
	// TODO: Add your control notification handler code here
		int CurrentPosition = m_List.GetCurSel();
	m_List.DeleteString(CurrentPosition);
	char szString[100], s1[100], s2[100];
	int NumriQelesit, Qelesi;

	for (int i = 0; i < mNumriQelesave - 1; i++)
	{
		m_List.GetText(i, szString);
		sscanf(szString, "%s %d %s %d", s1, &NumriQelesit, s2, &Qelesi);
		sprintf(szString, "Qelesi %d: %d", i, Qelesi);
		m_List.DeleteString(i);
		m_List.InsertString(i, szString);		
	}
	SetDlgItemText(IDC_EDIT_NDRYSHO_QELESIN, "");
	m_btnNdryshoQelesin.EnableWindow(FALSE);
	m_btnFshijeQelesin.EnableWindow(FALSE);
	m_edtNdryshoQelesin.EnableWindow(FALSE);

	mNumriQelesave--;
}

BOOL CQelesiPolialfabetik::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	mNumriQelesave = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CQelesiPolialfabetik::OnButtonNdryshoQelesin() 
{
	// TODO: Add your control notification handler code here
		if (m_List.GetCurSel() == -1)
	{
		m_btnNdryshoQelesin.EnableWindow(FALSE);
		m_btnFshijeQelesin.EnableWindow(FALSE);
		return;
	}
	char szString[100];
	char s1[100], s2[100];
	int NumriQelesit, Qelesi;
	m_List.GetText(m_List.GetCurSel(), szString);
	sscanf(szString, "%s %d %s %d", s1, &NumriQelesit, s2, &Qelesi);
	UINT VleraQelesit = GetDlgItemInt(IDC_EDIT_NDRYSHO_QELESIN);
	if (VleraQelesit > 26 || VleraQelesit == 0)
	{
		MessageBox("Qelesi duhet te jete prej 1-26", "Gabim!!");
		SetDlgItemText(IDC_EDIT_NDRYSHO_QELESIN, "");
		m_btnNdryshoQelesin.EnableWindow(FALSE);
		return;
	}	
	int CurrentPosition = m_List.GetCurSel();
	m_List.DeleteString(CurrentPosition);
	sprintf(szString, "Qelesi %d: %d", NumriQelesit, VleraQelesit);
	m_List.InsertString(CurrentPosition, szString);
	SetDlgItemText(IDC_EDIT_NDRYSHO_QELESIN, "");
	m_btnNdryshoQelesin.EnableWindow(FALSE);
	m_btnFshijeQelesin.EnableWindow(FALSE);
	m_edtNdryshoQelesin.EnableWindow(FALSE);
}

void CQelesiPolialfabetik::OnButtonShtoQelesin() 
{
	// TODO: Add your control notification handler code here
	UINT VleraQelesit = GetDlgItemInt(IDC_EDIT_SHTO_QELESIN);
	if (VleraQelesit > 26 || VleraQelesit == 0)
	{
		MessageBox("Qelesi duhet te jete prej 1-26", "Gabim!!");
		SetDlgItemText(IDC_EDIT_SHTO_QELESIN, "");
		m_btnShtoQelesin.EnableWindow(FALSE);
		return;
	}
	char szString[100];
	sprintf(szString, "Qelesi %d: %d", mNumriQelesave, VleraQelesit);
	m_List.InsertString(mNumriQelesave, szString);
	mNumriQelesave++;
	SetDlgItemText(IDC_EDIT_SHTO_QELESIN, "");
	m_btnShtoQelesin.EnableWindow(FALSE);

}

void CQelesiPolialfabetik::OnChangeEditShtoQelesin() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_btnShtoQelesin.EnableWindow(TRUE);
	m_List.SetCurSel(-1);
	m_edtNdryshoQelesin.EnableWindow(FALSE);
	m_btnFshijeQelesin.EnableWindow(FALSE);

	
}

void CQelesiPolialfabetik::OnChangeEditNdryshoQelesin() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_btnNdryshoQelesin.EnableWindow(TRUE);

}

void CQelesiPolialfabetik::OnSelchangeList1() 
{
	// TODO: Add your control notification handler code here
	m_btnFshijeQelesin.EnableWindow(TRUE);
	m_edtNdryshoQelesin.EnableWindow(TRUE);

}

void CQelesiPolialfabetik::OnOK() 
{
	// TODO: Add extra validation here
	char szString[100], s1[100], s2[100];
	int NumriQelesit, Qelesi;

	ArrayQelesave = new int[mNumriQelesave];
	for (int i = 0; i < mNumriQelesave; i++)
	{
		m_List.GetText(i, szString);
		sscanf(szString, "%s %d %s %d", s1, &NumriQelesit, s2, &Qelesi);
		ArrayQelesave[i] = Qelesi;
	}
	
	CDialog::OnOK();
}
