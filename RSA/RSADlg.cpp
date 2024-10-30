
// RSADlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "RSA.h"
#include "RSADlg.h"
#include "afxdialogex.h"
#include<vector>
#include <string>

using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CRSADlg



CRSADlg::CRSADlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RSA_DIALOG, pParent)
	, d(0)
	, e(0)
	, n(0)
	, fpath1(_T(""))
	, fpath2(_T(""))
	, PubText(_T(""))
	, ClosedText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRSADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, d);
	DDX_Text(pDX, IDC_EDIT3, e);
	DDX_Text(pDX, IDC_EDIT4, n);
	DDX_Control(pDX, IDC_EDIT3, ctrE);
	DDX_Control(pDX, IDC_EDIT2, ctrD);
	DDX_Control(pDX, IDC_EDIT4, ctrN);
	DDX_Text(pDX, IDC_EDIT5, fpath1);
	DDX_Text(pDX, IDC_EDIT6, fpath2);
	DDX_Text(pDX, IDC_EDIT1, PubText);
	DDX_Text(pDX, IDC_EDIT7, ClosedText);
	DDX_Control(pDX, IDC_RADIO2, coding);

}

BEGIN_MESSAGE_MAP(CRSADlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CRSADlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CRSADlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CRSADlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &CRSADlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Обработчики сообщений CRSADlg

BOOL CRSADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок
	coding.SetCheck(BST_CHECKED);
	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CRSADlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CRSADlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
RSA r;

vector<char> ptext, cltext, chkey;
//true - of file; false - of wnd;
bool flag1 = false, flag2 = false, flag3 = false;
int sizepub, sizeclose;
// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CRSADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//сохранить в файл
void CRSADlg::OnBnClickedButton2()
{
	UpdateData(true);

	CFileDialog diag(0);
	CFile file;

	diag.DoModal();
	fpath2 = diag.GetPathName();

	file.Open(fpath2, file.modeCreate | file.modeWrite);


	int size = sizeclose;

	char csize[10];
	_itoa_s(size, csize, 10);
	for (int i = strlen(csize); i < 9; i++)csize[i] = ' ';
	csize[9] = '\0';

	char* buf = new char[size + 1];
	buf[size] = '\0';



	for (int i = 0; i < size; i++)
	{
		buf[i] = cltext[i];
	}

	file.Write(csize, strlen(csize));
	file.Write(buf, size);
	file.Close();
	UpdateData(0);
}

void CRSADlg::OnBnClickedButton3()
{
	UpdateData(true);
	srand(time(NULL));

	
		r.CreateKey();
		e = r.Gete();
		n = r.Getn();
		d = r.Getd();
		//f = r.Getf();
	
	UpdateData(false);
	// TODO: добавьте свой код обработчика уведомлений
}


void CRSADlg::OnBnClickedButton4()
{
	UpdateData(true);



	if (!coding.GetCheck()) coding.SetCheck(BST_UNCHECKED);
	
		r.Setd(d);
		r.Sete(e);
		r.Setn(n);
		//r.Setf(f);

		if (coding.GetCheck())
		{
			
			ClosedText = r.Shifr(ptext, cltext, true);
			sizeclose = cltext.size();
			sizepub = ptext.size();
		
			flag1 = false;
		}
		else
		{
			
			PubText = r.Shifr(cltext, ptext, false);
			sizeclose = cltext.size();
			sizepub = ptext.size();
		}
	

	UpdateData(false);
	// TODO: добавьте свой код обработчика уведомлений
}

//загрузить из файла
void CRSADlg::OnBnClickedButton1()
{
	CFileDialog diag(1);
	CFile file;

	diag.DoModal();
	fpath1 = diag.GetPathName();

	file.Open(fpath1, file.modeRead);

	int size = file.GetLength();
	char* buf = new char[size + 1];
	buf[size] = '\0';

	file.Read(buf, size);
	string str;



	flag1 = true;
	ptext.clear();

	for (int i = 0; i < size; i++)
	{
		ptext.push_back(buf[i]);
		str += buf[i];
	}

	PubText = str.c_str();
	file.Close();

	UpdateData(false);
	// TODO: добавьте свой код обработчика уведомлений
}
