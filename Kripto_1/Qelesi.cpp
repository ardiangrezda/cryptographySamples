// Qelesi.cpp : implementation file
//

#include "stdafx.h"
#include "Kripto_1.h"
#include "Qelesi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQelesi dialog


CQelesi::CQelesi(CWnd* pParent /*=NULL*/)
	: CDialog(CQelesi::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQelesi)
	m_uiQelesi = 0;
	//}}AFX_DATA_INIT
}


void CQelesi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQelesi)
	DDX_Text(pDX, IDC_EDIT_QELES, m_uiQelesi);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQelesi, CDialog)
	//{{AFX_MSG_MAP(CQelesi)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQelesi message handlers

void CQelesi::OnOK() 
{
	// TODO: Add extra validation here
	m_uiQelesi = GetDlgItemInt(IDC_EDIT_QELES);
	if (m_uiQelesi > 100 || m_uiQelesi == 0)
	{
		MessageBox("Vlerat e qelesit duhet te jene ne mes 1 dhe 100", "Te ipet vlera tjeter");
		return;
	}

	CDialog::OnOK();
}
