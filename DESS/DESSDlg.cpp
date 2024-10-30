
// DESSDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "DESS.h"
#include "DESSDlg.h"
#include "afxdialogex.h"
#include "Work.h"

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


// Диалоговое окно CDESSDlg



CDESSDlg::CDESSDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DESS_DIALOG, pParent)
	, PlainText(_T("Hello!!!!!"))
	, CipherText(_T(""))
	, FILEIN(_T(""))
	, FILEOUT(_T(""))
	, FILEIN1(_T(""))
	, FILEOUT1(_T(""))
	, RSAn(0)
	, RSAe(0)
	, RSAd(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDESSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, PlainText);
	DDX_Text(pDX, IDC_EDIT2, CipherText);
	DDX_Text(pDX, IDC_EDIT3, FILEIN);
	DDX_Text(pDX, IDC_EDIT6, FILEIN1);
	DDX_Text(pDX, IDC_EDIT4, FILEOUT);
	DDX_Text(pDX, IDC_EDIT5, FILEOUT1);
	DDX_Control(pDX, IDC_RADIO1, rbt1);
	DDX_Control(pDX, IDC_RADIO2, rbt2);
	DDX_Control(pDX, IDC_EDIT7, FileIn);
	DDX_Control(pDX, IDC_EDIT8, FileOut);
	DDX_Text(pDX, IDC_EDIT10, RSAn);
	DDX_Text(pDX, IDC_EDIT11, RSAe);
	DDX_Text(pDX, IDC_EDIT12, RSAd);
}

BEGIN_MESSAGE_MAP(CDESSDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ENCRYPBUTTON, &CDESSDlg::OnBnClickedEncrypButton)
	ON_BN_CLICKED(IDC_DECRYPBUTTON, &CDESSDlg::OnBnClickedDecrypbutton)
	ON_BN_CLICKED(IDC_BUTTON1, &CDESSDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CDESSDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CDESSDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CDESSDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// Обработчики сообщений CDESSDlg

BOOL CDESSDlg::OnInitDialog()
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

	rbt1.SetCheck(BST_CHECKED);
	rbt2.SetCheck(BST_UNCHECKED);
	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CDESSDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDESSDlg::OnPaint()
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

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CDESSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

string Key = "12345678";
int BlockNum1 = 0;
int BlockNum2 = 0;
int sIze = 8;
//RSA W2;
RSA W2;
vector<char> ptext, cltext;
void CDESSDlg::OnBnClickedEncrypButton()
{
//	MessageBox(L"Обработка выполнена!");

	UpdateData(TRUE);
	if (rbt1.GetCheck()) {
		MessageBox(L"DES");
		BlockNum1 = (PlainText.GetLength() % sIze == 0) ? (PlainText.GetLength() / sIze) : (PlainText.GetLength() / sIze + 1);
		CipherText = L"";

		CT2CA pszConvertedAnsiString(PlainText);
		string buf(pszConvertedAnsiString);
		CT2CA pszConvertedAnsiStringText(CipherText);
		string res(pszConvertedAnsiStringText);
		//res = ""
		//CipherText = FUNC(buf, res, Key, BlockNum1, sIze);
		DES W1;


		res = W1.encode(buf, Key);// это мы получили в 101001
		//теперь получим строку, которая даст шифрованный текст:
		string RESS = from2Tocharr(res);
		CipherText = RESS.c_str();
	}
	
	if (rbt2.GetCheck()) {
		MessageBox(L"RSA");
		// здесь хранится исходный текст
		CT2CA pszConvertedAnsiString(PlainText);
		string buf(pszConvertedAnsiString);
		//здесь будет наш зашифрованный
		CT2CA pszConvertedAnsiStringText(CipherText);
		string RESS(pszConvertedAnsiStringText);
		for (int i = 0; i < buf.size(); i++)
		{
			ptext.push_back(buf[i]);
		}
		for (int i = 0; i < RESS.size(); i++)
		{cltext.push_back(RESS[i]);
	}
		RSAn = 119;
		RSAe = 5;
		RSAd = 77;
		W2.Setd(RSAd);
		W2.Sete(RSAe);
		W2.Setn(RSAn);
		CipherText = W2.Shifr(ptext, cltext, true);
		
		/*CipherText = L"ha";*/
		
	}
	UpdateData(FALSE);
	// TODO: добавьте свой код обработчика уведомлений
}


void CDESSDlg::OnBnClickedDecrypbutton()
{
	UpdateData(TRUE);
	if (rbt1.GetCheck()) {
		BlockNum2 = ((BlockNum1 * sIze) % sIze == 0) ? ((BlockNum1 * sIze) / sIze) : ((BlockNum1 * sIze) / sIze + 1);
		PlainText = L"";
		CT2CA pszConvertedAnsiString(PlainText);
		string buf(pszConvertedAnsiString);
		CT2CA pszConvertedAnsiStringText(CipherText);
		string RESS(pszConvertedAnsiStringText);//здесь получим зашифррованный текст, из которого нужно получить 0 и 1, а потом уже отправлять в decode()
		DES W1;
		string res;//сюда запишем 0 и 1
		res = fromCharrTo2(RESS);
		//PlainText = FUNC(res, buf, Key, BlockNum2, sIze);
		////////////////////////////OpenText.GetBufferSetLength(BlockNum2 * sIze - counter);
		Key = "12345678";
		buf = W1.decode(res, Key);
		PlainText = buf.c_str();
	}
	if (rbt2.GetCheck()) {
		MessageBox(L"RSA");
		CT2CA pszConvertedAnsiString(PlainText);
		string buf(pszConvertedAnsiString);
		CT2CA pszConvertedAnsiStringText(CipherText);
		string RESS(pszConvertedAnsiStringText);//здесь получим зашифррованный текст, из которого нужно получить 0 и 1, а потом уже отправлять в decode()
	
	 PlainText = W2.Shifr(cltext, ptext, false);
	 for (int i = 0; i < buf.size(); i++)
	 {
		 ptext.push_back(buf[i]);
	 }
	 for (int i = 0; i < RESS.size(); i++)
	 {
		 ptext.push_back(RESS[i]);
	 }
	 PlainText = W2.Shifr(cltext, ptext, false);
		/*W2.cipher = RESS;
		W2.n = RSAn;
	    W2.e = RSAe;
		W2.d = RSAd;
		buf = W2.secondFunc(W2);

		PlainText = buf.c_str();*/

	
	}
	UpdateData(FALSE);
	MessageBox(L"Обработка выполнена!");
	//char* huf = new char[1000];
	// TODO: добавьте свой код обработчика уведомлений
}

string str;//записывает из открытого файла
string strcl;// то, что записывает в закрытый файл

int K;

// загружает простой текст
void CDESSDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	CFileDialog dialog(TRUE);

	dialog.DoModal();
	FILEIN = dialog.GetPathName();
	OpenText.Open(/*L"input.txt"*/FILEIN, CFile::modeRead);

	K = OpenText.GetLength();
	
	int i = 0;
	char ch;
	OpenText.SeekToBegin();
	while (i < K)//пока не дошли до конца
	{
		OpenText.Seek(i, CFile::begin);

		OpenText.Read(&ch, 1);
		str.push_back(ch);
		//OpenText.Seek(i,CFile::begin);

		i++;
	}
	
	OpenText.Close();
	
	//MessageBox(L"Файл прочитан");

	CString h
		;
	h = str.c_str();
	FileIn.SetWindowTextW(h);

	UpdateData(0);


	
}

// записывает зашифрованный текст
void CDESSDlg::OnBnClickedButton3()
{

	
	if (rbt1.GetCheck()) {
		MessageBox(L"DES");
		

		
		string res;
		//res = ""
		//CipherText = FUNC(buf, res, Key, BlockNum1, sIze);
		DES W1;


		res = W1.encode(str, Key);// это мы получили в 101001
		//теперь получим строку, которая даст шифрованный текст:
		strcl = from2Tocharr(res);
		
	}

	K = strcl.size();
	UpdateData(TRUE);
	CFileDialog dialog(TRUE);

	dialog.DoModal();
	FILEOUT = dialog.GetPathName();
	ShifrText.Open(FILEOUT, CFile::modeReadWrite);
	char cr;
	//str.resize(K);
	//ClosedText.Write(&cr, K);
	int i = 0;
	ShifrText.SeekToBegin();
	while (i < K)//пока не дошли до конца
	{
		cr = strcl[i];
		ShifrText.Seek(i, CFile::begin);

		ShifrText.Write(&cr, 1);


		//ClosedText.Seek(i, CFile::begin);

		i++;
	}
	
	ShifrText.Close();
	
	CString h;
	h = strcl.c_str();
	FileOut.SetWindowTextW(h);
	UpdateData(0);
	
	
}
/////////////////////////////////////////////////////////////////////////////////
string str1;
string strcl1;
int K1;

void CDESSDlg::OnBnClickedButton2()
{

	UpdateData(TRUE);
	CFileDialog dialog(TRUE);

	dialog.DoModal();
	FILEIN1 = dialog.GetPathName();
	OpenText1.Open(/*L"input.txt"*/FILEIN1, CFile::modeRead);

	K1 = OpenText1.GetLength();

	int i = 0;
	char ch;
	OpenText1.SeekToBegin();
	while (i < K1)//пока не дошли до конца
	{
		OpenText1.Seek(i, CFile::begin);

		OpenText1.Read(&ch, 1);
		str1.push_back(ch);
		//OpenText.Seek(i,CFile::begin);

		i++;
	}

	OpenText1.Close();

	//MessageBox(L"Файл прочитан");

	CString h
		;
	h = str1.c_str();
	FileIn.SetWindowTextW(L"");
	FileOut.SetWindowTextW(h);
    UpdateData(0);

}

// записывает простой текст
void CDESSDlg::OnBnClickedButton4()
{

	if (rbt1.GetCheck()) {
		
		;//здесь получим зашифррованный текст, из которого нужно получить 0 и 1, а потом уже отправлять в decode()
		DES W1;
		string res;//сюда запишем 0 и 1
		res = fromCharrTo2(str1);
	
		Key = "12345678";
		strcl1 = W1.decode(res, Key);
		
	}


	K1 = strcl1.size();
	UpdateData(TRUE);
	CFileDialog dialog(TRUE);

	dialog.DoModal();
	FILEOUT1 = dialog.GetPathName();
	ShifrText1.Open(FILEOUT1, CFile::modeWrite);
	char cr;
	//str.resize(K);
	//ClosedText.Write(&cr, K);
	int i = 0;
	ShifrText1.SeekToBegin();
	while (i < K1)//пока не дошли до конца
	{
		cr = strcl1[i];
		ShifrText1.Seek(i, CFile::begin);

		ShifrText1.Write(&cr, 1);


		//ClosedText.Seek(i, CFile::begin);

		i++;
	}

	ShifrText1.Close();

	CString h;
	h = strcl1.c_str();
	FileIn.SetWindowTextW(h);
	UpdateData(0);

}


void CDESSDlg::OnBnClickedButton6()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CDESSDlg::OnBnClickedButton7()
{
	// TODO: добавьте свой код обработчика уведомлений
}
