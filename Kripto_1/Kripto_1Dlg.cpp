// Kripto_1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Kripto_1.h"
#include "Kripto_1Dlg.h"
#include "Qelesi.h"
#include "QelesiPolialfabetik.h"
#include <io.h>
#include <fcntl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKripto_1Dlg dialog

CKripto_1Dlg::CKripto_1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKripto_1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKripto_1Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKripto_1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKripto_1Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CKripto_1Dlg, CDialog)
	//{{AFX_MSG_MAP(CKripto_1Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ENCRYPT_CESAR, OnEncryptCesar)
	ON_BN_CLICKED(IDC_DECRYPT_CESAR, OnDecryptCesar)
	ON_BN_CLICKED(IDC_ENCRYPT_TRANSPONIM, OnEncryptTransponim)
	ON_BN_CLICKED(IDC_DECRYPT_TRANSPONIM, OnDecryptTransponim)
	ON_BN_CLICKED(IDC_ENCRYPT_ZEVENDESIM, OnEncryptZevendesim)
	ON_BN_CLICKED(IDC_DECRYPT_ZEVENDESIM, OnDecryptZevendesim)
	ON_BN_CLICKED(IDC_ENCRYPT_POLIALFABETIK, OnEncryptPolialfabetik)
	ON_BN_CLICKED(IDC_DECRYPT_POLIALFABETIK, OnDecryptPolialfabetik)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKripto_1Dlg message handlers

BOOL CKripto_1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKripto_1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKripto_1Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKripto_1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CKripto_1Dlg::OnEncryptCesar() 
{
	// TODO: Add your control notification handler code here
	FILE *inputFile, *EncryptedFile;
	if (EncryptedFunction())
	{
		// mbyllet datoteken hyrese dhe datoteken e enkriptuar
		return;
	}
	if((inputFile = fopen(FileNameOriginal, "r+b" )) == NULL )
	{
		MessageBox("Datoteka origjinale nuk mund te hapet\n", "Gabim!!");
		return ;		
	}
	if ((EncryptedFile = fopen(FileNameEncrypted, "w+b")) == NULL)
	{
		MessageBox("Datoteka e encryptuar nuk mund te hapet\n", "Gabim!!");
		return;
	} 

	// ch eshte karakteri i datotekes hyrese
	// ch1 eshte karakteri i enkriptuar
	int ch, ch1;
	while (!feof(inputFile))
	{
		ch = fgetc(inputFile);
		if (ch != EOF)
		{
			// nese karakteri i lexuar i datotekes eshte shkronje
			if (ch1 = isalpha(ch))
			{
				switch(ch)
				{
				// nese karakteri hyres eshte 'X', karakteri dales do te jete 'A'
				case 88:
					ch1 = 65;
					break;
				// nese karakteri hyres eshte 'Y', karakteri dales do te jete 'B'
				case 89:
					ch1 = 66;
					break;
				// nese karakteri hyres eshte 'Z', karakteri dales do te jete 'C'
				case 90:
					ch1 = 67;
					break;
				// nese karakteri hyres eshte 'x', karakteri dales do te jete 'a'
				case 120:
					ch1 = 97;
					break;
				// nese karakteri hyres eshte 'y', karakteri dales do te jete 'b'
				case 121:
					ch1 = 98;
					break;
				// nese karakteri hyres eshte 'z', karakteri dales do te jete 'c'
				case 122:
					ch1 = 99;
					break;
				default:
					ch1 = ch + 3;
					break;
				}
			}
			// nese karakteri i lexuar i datotekes nuk eshte shkronje
			else
			{
				ch1 = ch;
			}
			// shkruaj ne datoteken dalese
			fputc(ch1, EncryptedFile);
		}
	}
	// mbyllet datoteken hyrese dhe datoteken e enkriptuar
	fclose(inputFile);
	fclose(EncryptedFile);
	
}

void CKripto_1Dlg::OnDecryptCesar() 
{
	// TODO: Add your control notification handler code here
	FILE *EncryptedFile, *DecryptedFile;
	if (DecryptedFunction())
	{
		return;
	}
	if((EncryptedFile = fopen(FileNameEncrypted, "r+b" )) == NULL )
	{
		MessageBox("Datoteka e enkriptuar nuk mund te hapet\n", "Gabim!!");
		return ;		
	}
	if ((DecryptedFile = fopen(FileNameDecrypted, "w+b")) == NULL)
	{
		MessageBox("Datoteka e dekriptuar nuk mund te hapet\n", "Gabim!!");
		return;
	}

	// ch- karakteri hyres, ch1- karakteri i dekriptuar
	int ch, ch1;
	while (!feof(EncryptedFile))
	{
		ch = fgetc(EncryptedFile);
		if (ch != EOF)
		{
			if (ch1 = isalpha(ch))
			{
				switch(ch)
				{
				case 65:
					ch1 = 88;
					break;
				case 66:
					ch1 = 89;
					break;
				case 67:
					ch1 = 90;
					break;
				case 97:
					ch1 = 120;
					break;
				case 98:
					ch1 = 121;
					break;
				case 99:
					ch1 = 122;
					break;
				default:
					ch1 = ch - 3;
					break;
				}
			}
			else
			{
				ch1 = ch;
			}
			fputc(ch1, DecryptedFile);
		}
	}
	fclose(EncryptedFile);
	fclose(DecryptedFile);
	
}


void CKripto_1Dlg::OnEncryptTransponim() 
{
	// TODO: Add your control notification handler code here
	CQelesi Qelesi;
	if (Qelesi.DoModal() == IDCANCEL)
		return;
	m_uiQelesi = Qelesi.m_uiQelesi;

	FILE *inputFile, *EncryptedFile;
	if (EncryptedFunction())
	{
		return;
	}
	if((inputFile = fopen(FileNameOriginal, "r+b" )) == NULL )
	{
		MessageBox("Datoteka origjinale nuk mund te hapet\n", "Gabim!!");
		return ;		
	}
	if ((EncryptedFile = fopen(FileNameEncrypted, "w+b")) == NULL)
	{
		MessageBox("Datoteka e encryptuar nuk mund te hapet\n", "Gabim!!");
		return;
	} 

	int ch, i;
	long position, fileSize;
	// percakto madhesine e file-it
	fseek(inputFile, 0, SEEK_END);
	fileSize = ftell(inputFile);

	if (m_uiQelesi > fileSize)
	{
		MessageBox("Vlera e qelesit duhet te jete me e vogel se madhesia e file-it", "Gabim!!");
		fclose(inputFile);
		fclose(EncryptedFile);
		return;
	}

	for (i = 0; i < m_uiQelesi; i++)
	{
		// zhvendos poziten e file-it prej fillimit + i (0, 1, 2, ...)
		fseek(inputFile, i, SEEK_SET);
		while (!feof(inputFile))
		{
			ch = fgetc(inputFile);
			fputc(ch, EncryptedFile);
			// zhvendose pointerin e file-it per m_uiQelesi - 1
			fseek(inputFile, m_uiQelesi - 1, SEEK_CUR);
			// trego poziten e file-it
			position = ftell(inputFile);
			// ne rast se pozita e pointerit te file-it 
			// eshte me e madhe se madhesia e file-it
			if (position >= fileSize)
			{
				break;
			}
		}
		fputc(32, EncryptedFile);
	}
	// mbyllet file-i hyres dhe file-i i enkriptuar
	fclose(inputFile);
	fclose(EncryptedFile);
	CWnd* EnableDecryptTransp = GetDlgItem(IDC_DECRYPT_TRANSPONIM);
	EnableDecryptTransp->EnableWindow(TRUE);
}

void CKripto_1Dlg::OnDecryptTransponim() 
{
	// TODO: Add your control notification handler code here
	FILE *EncryptedFile, *DecryptedFile;
	if (DecryptedFunction())
	{
		return;
	}
	if((EncryptedFile = fopen(FileNameEncrypted, "r+b" )) == NULL )
	{
		MessageBox("Datoteka e enkriptuar nuk mund te hapet\n", "Gabim!!");
		return ;		
	}
	if ((DecryptedFile = fopen(FileNameDecrypted, "w+b")) == NULL)
	{
		MessageBox("Datoteka e dekriptuar nuk mund te hapet\n", "Gabim!!");
		return;
	}

	int ch, i, j = 0;
	long position, fileSize;
	// shko ne fund te file-it
	fseek(EncryptedFile, 0, SEEK_END);
	// percakto madhesine e file-it hyres
	fileSize = ftell(EncryptedFile);
	// percakto numrin e rreshtave ne matrice
	long NumriRreshave = fileSize / m_uiQelesi;
	// Per tekstin e enkriptuar disa rreshta jane me
	// te medha, e disa me te vogla
	long ZhvendosjaPointeritFile;

	for (i = 0; i < NumriRreshave; i++)
	{
		// zhvendos poziten e file-it prej fillimit + i (0, 1, 2, ...)
		fseek(EncryptedFile, i, SEEK_SET);
		// j percakton per sa duhet zhvendosur pointerin
		// e file-it, varesisht sa eshte madhesia 
		// e nje rreshti
		j = 0;
		while (!feof(EncryptedFile))
		{
			ch = fgetc(EncryptedFile);
			fputc(ch, DecryptedFile);
			j++;
			if (j > fileSize % m_uiQelesi)
				ZhvendosjaPointeritFile = NumriRreshave - 1;
			else
				ZhvendosjaPointeritFile = NumriRreshave;
			fseek(EncryptedFile, ZhvendosjaPointeritFile, SEEK_CUR);
			// tregon poziten e pointerit te file-it
			// ne pointer
			position = ftell(EncryptedFile);

			if (position >= fileSize)
			{
				break;
			}
		}
	}
	fclose(DecryptedFile);
	// ne fund kane mbetur disa zbraztesira ne file-in e 
	// dekriptuar. Ato duhet te fshihen. Kete e bejme
	// duke e zvogluar madhesine e file-it te enkriptuar
	int fh;
	if( fh = _open( FileNameDecrypted, _O_RDWR )  != -1 )
	{
		int AAS = _chsize( _fileno(DecryptedFile), fileSize - m_uiQelesi);
	}
	_close(fh);
	fclose(EncryptedFile);

}

void CKripto_1Dlg::OnEncryptZevendesim() 
{
	// TODO: Add your control notification handler code here
	CQelesi Qelesi;
	if (Qelesi.DoModal() == IDCANCEL)
		return;
	m_uiQelesiZevendesim = Qelesi.m_uiQelesi;	
	if (m_uiQelesiZevendesim > 26)
		m_uiQelesiZevendesim = m_uiQelesiZevendesim % 26;
	FILE *inputFile, *EncryptedFile;
	if (EncryptedFunction())
	{
		return;
	}
	if((inputFile = fopen(FileNameOriginal, "r+b" )) == NULL )
	{
		MessageBox("Datoteka origjinale nuk mund te hapet\n", "Gabim!!");
		return ;		
	}
	if ((EncryptedFile = fopen(FileNameEncrypted, "w+b")) == NULL)
	{
		MessageBox("Datoteka e encryptuar nuk mund te hapet\n", "Gabim!!");
		return;
	} 

	// ch eshte karakteri i datotekes hyrese
	// ch1 eshte karakteri i enkriptuar
	int ch, ch1;
	// ch eshte karakteri i datotekes hyrese
	// ch1 eshte karakteri i enkriptuar
	while (!feof(inputFile))
	{
		ch = fgetc(inputFile);
		if (ch != EOF)
		{
			// nese karakteri i lexuar i datotekes eshte shkronje
			if (isalpha(ch))
			{
				if (isupper(ch))
					ch1 = 'A' + (ch % 65 + m_uiQelesiZevendesim) % 26 ;
				else
					ch1 = 'a' + (ch % 97 + m_uiQelesiZevendesim) % 26 ;
			}
			else
			{
				ch1 = ch;
			}
			// shkruaj ne datoteken dalese
			fputc(ch1, EncryptedFile);
		}
	}
	// mbyllet datoteken hyrese dhe datoteken e enkriptuar
	fclose(inputFile);
	fclose(EncryptedFile);
	CWnd* EnableDecryptTransp = GetDlgItem(IDC_DECRYPT_ZEVENDESIM);
	EnableDecryptTransp->EnableWindow(TRUE);
}

void CKripto_1Dlg::OnDecryptZevendesim() 
{
	// TODO: Add your control notification handler code here
	FILE *EncryptedFile, *DecryptedFile;
	if (DecryptedFunction())
	{
		return;
	}
	if((EncryptedFile = fopen(FileNameEncrypted, "r+b" )) == NULL )
	{
		MessageBox("Datoteka e enkriptuar nuk mund te hapet\n", "Gabim!!");
		return ;		
	}
	if ((DecryptedFile = fopen(FileNameDecrypted, "w+b")) == NULL)
	{
		MessageBox("Datoteka e dekriptuar nuk mund te hapet\n", "Gabim!!");
		return;
	}
	// ch eshte karakteri i datotekes hyrese
	// ch1 eshte karakteri i enkriptuar
	int ch, ch1;
	while (!feof(EncryptedFile))
	{
		ch = fgetc(EncryptedFile);
		if (ch != EOF)
		{
			// nese karakteri i lexuar i datotekes eshte shkronje
			if (isalpha(ch))
			{
				if (isupper(ch))
					ch1 = 'A' + (26 + ch % 65 - m_uiQelesiZevendesim) % 26;
				else
					ch1 = 'a' + (26 + ch % 97 - m_uiQelesiZevendesim) % 26;
			}
			else
			{
				ch1 = ch;
			}
			// shkruaj ne datoteken dalese
			fputc(ch1, DecryptedFile);
		}
	}
	fclose(EncryptedFile);
	fclose(DecryptedFile);
}

int CKripto_1Dlg::EncryptedFunction()
{
	static char szFilter[] = "File-t tekstuale (*.txt)|*.txt|";
	CFileDialog dlg(TRUE, "*.txt", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT ,szFilter);
	if (dlg.DoModal() == IDCANCEL)
	{
		return 1;
	}
	CString Extension, FileNameOnly;
	FileNameOriginal = dlg.GetPathName();

	// Gjen paraqitjen e fundit te pikes ne emrin e datotekes 
	int Position = FileNameOriginal.ReverseFind('.');
	Extension = FileNameOriginal.Right(FileNameOriginal.GetLength() - Position);
	// nese variabla Extension eshte .ENC atehere ky funksion i kthehet funksionit main()
	if (!strcmp(Extension, ".ENC"))
	{
		MessageBox("Datoteka hyrese duhet te mos kete ekstenzion .ENC!\n", "Gabim!!");
		return 1;
	}
	FileNameOnly = FileNameOriginal.Left(Position);
	FileNameEncrypted = FileNameOnly + ".enc";

	return 0;
}

int CKripto_1Dlg::DecryptedFunction()
{
	static char szFilter[] = "Filet e enkriptuara (*.enc)|*.enc|";
	CFileDialog dlg(TRUE, "*.enc", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT ,szFilter);
	if (dlg.DoModal() == IDCANCEL)
	{
		return 1;
	}
	CString Extension, FileNameOnly;
	FileNameEncrypted = dlg.GetPathName();

	// Gjen paraqitjen e fundit te pikes ne emrin e datotekes 
	int Position = FileNameEncrypted.ReverseFind('.');
	Extension = FileNameEncrypted.Right(FileNameEncrypted.GetLength() - Position);
	Extension.MakeUpper();
	if (Extension.Compare(".ENC"))
	{
		MessageBox("Datoteka hyrese e enkriptuar duhet te kete ekstenzionin .ENC!\n", "Gabim!!");
		return 1;
	}
	FileNameOnly = FileNameEncrypted.Left(Position);
	FileNameDecrypted = FileNameOnly + ".dcp";
	return 0;
}

void CKripto_1Dlg::OnEncryptPolialfabetik() 
{
	// TODO: Add your control notification handler code here
	CQelesiPolialfabetik QelesiPolialfabetik;
	if (QelesiPolialfabetik.DoModal() == IDCANCEL)
		return;

	mNumriQelesave = QelesiPolialfabetik.mNumriQelesave; 
	ArrayQelesave = QelesiPolialfabetik.ArrayQelesave;
	FILE *inputFile, *EncryptedFile;
	if (EncryptedFunction())
	{
		return;
	}
	if((inputFile = fopen(FileNameOriginal, "r+b" )) == NULL )
	{
		MessageBox("Datoteka origjinale nuk mund te hapet\n", "Gabim!!");
		return ;		
	}
	if ((EncryptedFile = fopen(FileNameEncrypted, "w+b")) == NULL)
	{
		MessageBox("Datoteka e encryptuar nuk mund te hapet\n", "Gabim!!");
		return;
	} 

	// ch eshte karakteri i datotekes hyrese
	// ch1 eshte karakteri i enkriptuar
	int ch, ch1, ReadCh;
	ReadCh = 0;
	// ch eshte karakteri i datotekes hyrese
	// ch1 eshte karakteri i enkriptuar
	while (!feof(inputFile))
	{
		ch = fgetc(inputFile);
		if (ch != EOF)
		{
			// nese karakteri i lexuar i datotekes eshte shkronje
			if (isalpha(ch))
			{
				if (isupper(ch))
				{
					ch1 = 'A' + (ch % 65 + ArrayQelesave[ReadCh]) % 26 ;
				}
				else
				{
					ch1 = 'a' + (ch % 97 + ArrayQelesave[ReadCh]) % 26 ;
				}
				ReadCh++;
				ReadCh = ReadCh % mNumriQelesave;
			}
			else
			{
				ch1 = ch;
			}
			// shkruaj ne datoteken dalese
			fputc(ch1, EncryptedFile);
		}
	}
	// mbyllet file-i hyres dhe file-i i enkriptuar
	fclose(inputFile);
	fclose(EncryptedFile);
	CWnd* EnableDecryptTransp = GetDlgItem(IDC_DECRYPT_POLIALFABETIK);
	EnableDecryptTransp->EnableWindow(TRUE);
}

void CKripto_1Dlg::OnDecryptPolialfabetik() 
{
	// TODO: Add your control notification handler code here
	FILE *EncryptedFile, *DecryptedFile;
	if (DecryptedFunction())
	{
		return;
	}
	if((EncryptedFile = fopen(FileNameEncrypted, "r+b" )) == NULL )
	{
		MessageBox("Datoteka e enkriptuar nuk mund te hapet\n", "Gabim!!");
		return ;		
	}
	if ((DecryptedFile = fopen(FileNameDecrypted, "w+b")) == NULL)
	{
		MessageBox("Datoteka e dekriptuar nuk mund te hapet\n", "Gabim!!");
		return;
	}
	// ch eshte karakteri i datotekes hyrese
	// ch1 eshte karakteri i enkriptuar
	int ch, ch1, ReadCh;
	ReadCh = 0;
	while (!feof(EncryptedFile))
	{
		ch = fgetc(EncryptedFile);
		if (ch != EOF)
		{
			if (isalpha(ch))
			{
				if (isupper(ch))
				{
					ch1 = 'A' + (26 + ch % 65 - ArrayQelesave[ReadCh]) % 26;
				}
				else
				{
					ch1 = 'a' + (26 + ch % 97 - ArrayQelesave[ReadCh]) % 26;
				}
				ReadCh++;
				ReadCh = ReadCh % mNumriQelesave;
			}
			else
			{
				ch1 = ch;
			}
			fputc(ch1, DecryptedFile);
		}
	}
	fclose(EncryptedFile);
	fclose(DecryptedFile);
	
}
