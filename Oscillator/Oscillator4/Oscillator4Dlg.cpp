
// Oscillator4Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Oscillator4.h"
#include "Oscillator4Dlg.h"
#include "afxdialogex.h"
#include <cmath>
#include <sstream>
#include <corecrt_math_defines.h>

// цвета
#define BK_COLOR RGB(255, 255, 255)		// фон
#define M_COLOR RGB(167, 167, 167)		// тело
#define TR_COLOR RGB(255, 0, 0)			// траектория
#define TXT_COLOR RGB(0, 0, 0)			// надписи
#define OSI_COLOR RGB(167, 167, 167)    // оси
#define EF_COLOR RGB(255, 0, 0)			// полная Е
#define EP_COLOR RGB(0, 255, 0)			// потенциальная Е
#define EK_COLOR RGB(0, 0, 255)			// кинетическая Е
#define SP_COLOR RGB(100, 100, 100)     // пружиноки
#define VX_COLOR RGB(255, 0, 0)         // скорость по X
#define VY_COLOR RGB(0, 0, 255)         // скорость по Y
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// начальные координаты
#define Y0 0.05
#define X0 0.075

// начальная жесткость пружин (Н/м)
#define KX 30
#define KY 60

const int sTimer = 1;	// таймер срабатывает через указанное количество миллисекунд
const int mR = 20;		// радиус тела
const int sR = 10;		// диаметр пружинки

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


// Диалоговое окно COscillator4Dlg



COscillator4Dlg::COscillator4Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Oscillator4_DIALOG, pParent)
	, m(0.3)	// масса груза 300 граммов 
	, l0(0.15)	// длина пружинок 15 см
	, x0(X0)
	, y0(Y0)
	, Vx(0)
	, Vy(0)
	, t(0)
	, dt(sTimer/1000.)
	, mT(3)
	, ifVGraf(TRUE)
	, ifTGraf(TRUE)
	, ifXGraf(TRUE)
	, ifYGraf(TRUE)
	, ifEGraf(TRUE)
	, mX(1)
	, V0x(0)
	, V0y(0)
	, kx(KX)	// жесткость пружин
	, ky(KY)	// жесткость пружин
	, friction(0)
	, ViscousK(0.01)
{
	x = ox = x0;
	y = oy = y0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COscillator4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MASS, m);
	DDX_Text(pDX, IDC_L, l0);
	DDX_Text(pDX, IDC_X0, x0);
	DDX_Text(pDX, IDC_Y0, y0);
	DDX_Text(pDX, IDC_CX, x);
	DDX_Text(pDX, IDC_CY, y);
	DDX_Text(pDX, IDC_CVX, Vx);
	DDX_Text(pDX, IDC_CVY, Vy);
	DDX_Text(pDX, IDC_TIME, t);
	DDX_Text(pDX, IDC_VX0, V0x);
	DDX_Text(pDX, IDC_VY0, V0y);
	DDX_Text(pDX, IDC_KX, kx);
	DDX_Text(pDX, IDC_KY, ky);
	DDX_Text(pDX, IDC_FRICTION, friction);
	DDX_Text(pDX, IDC_VISC, ViscousK);
}

BEGIN_MESSAGE_MAP(COscillator4Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &COscillator4Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &COscillator4Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &COscillator4Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_Bpkx1, &COscillator4Dlg::OnBnClickedBpkx1)
	ON_BN_CLICKED(IDC_Bpkx2, &COscillator4Dlg::OnBnClickedBpkx2)
	ON_BN_CLICKED(IDC_Bpky1, &COscillator4Dlg::OnBnClickedBpky1)
	ON_BN_CLICKED(IDC_Bpky2, &COscillator4Dlg::OnBnClickedBpky2)
END_MESSAGE_MAP()


// Обработчики сообщений COscillator4Dlg

BOOL COscillator4Dlg::OnInitDialog()
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

	// TODO: добавьте дополнительную инициализацию

	CWnd* Wnd;		// фрейм окна

	// главное окно
	Wnd = GetDlgItem(IDC_MAIN);
	A_Dc = Wnd->GetDC();
	Wnd->GetClientRect(&A_rect);

	A_mDc.CreateCompatibleDC(A_Dc);
	A_bmp.CreateCompatibleBitmap(A_Dc, A_rect.Width(), A_rect.Height());
	A_tmp = A_mDc.SelectObject(&A_bmp);

	// график скорости
	Wnd = GetDlgItem(IDC_VX);
	V_Dc = Wnd->GetDC();
	Wnd->GetClientRect(&V_rect);

	V_mDc.CreateCompatibleDC(V_Dc);
	V_bmp.CreateCompatibleBitmap(V_Dc, V_rect.Width(), V_rect.Height());
	V_tmp = V_mDc.SelectObject(&V_bmp);

	// график траектории
	Wnd = GetDlgItem(IDC_XY);
	T_Dc = Wnd->GetDC();
	Wnd->GetClientRect(&T_rect);

	T_mDc.CreateCompatibleDC(T_Dc);
	T_bmp.CreateCompatibleBitmap(T_Dc, T_rect.Width(), T_rect.Height());
	T_tmp = T_mDc.SelectObject(&T_bmp);

	// график координаты X
	Wnd = GetDlgItem(IDC_X);
	X_Dc = Wnd->GetDC();
	Wnd->GetClientRect(&X_rect);

	X_mDc.CreateCompatibleDC(X_Dc);
	X_bmp.CreateCompatibleBitmap(X_Dc, X_rect.Width(), X_rect.Height());
	X_tmp = X_mDc.SelectObject(&X_bmp);

	// график координаты Y
	Wnd = GetDlgItem(IDC_Y);
	Y_Dc = Wnd->GetDC();
	Wnd->GetClientRect(&Y_rect);

	Y_mDc.CreateCompatibleDC(Y_Dc);
	Y_bmp.CreateCompatibleBitmap(Y_Dc, Y_rect.Width(), Y_rect.Height());
	Y_tmp = Y_mDc.SelectObject(&Y_bmp);

	// график энергии от времени
	Wnd = GetDlgItem(IDC_EN);
	E_Dc = Wnd->GetDC();
	Wnd->GetClientRect(&E_rect);

	E_mDc.CreateCompatibleDC(E_Dc);
	E_bmp.CreateCompatibleBitmap(E_Dc, E_rect.Width(), E_rect.Height());
	E_tmp = E_mDc.SelectObject(&E_bmp);

	UpdateData(TRUE);

	X = (int)(xCenter + x / mX);
	Y = (int)(yCenter - y / mX);
	oX = X;
	oY = Y;
	t = Vx = Vy = V_max = E_max = 0;

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void COscillator4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void COscillator4Dlg::MyOnPaint()
{
	xCenter = (int)((A_rect.Width()) * 0.5);
	yCenter = (int)((A_rect.Height()) * 0.5);
	mX = (2 * l0) / A_rect.Width();

	X = (int)(xCenter + x / mX);
	Y = (int)(yCenter - y / mX);

	// траектория
	DrawTraectory(&T_mDc, T_rect);
	T_Dc->BitBlt(0, 0, T_rect.Width(), T_rect.Height(), &T_mDc, 0, 0, SRCCOPY);

	// координаты
	DrawX(&X_mDc, X_rect);
	X_Dc->BitBlt(0, 0, X_rect.Width(), X_rect.Height(), &X_mDc, 0, 0, SRCCOPY);
	DrawY(&Y_mDc, Y_rect);
	Y_Dc->BitBlt(0, 0, Y_rect.Width(), Y_rect.Height(), &Y_mDc, 0, 0, SRCCOPY);

	// график зависимости скорости от времени
	DrawVGraf(&V_mDc, V_rect);
	V_Dc->BitBlt(0, 0, V_rect.Width(), V_rect.Height(), &V_mDc, 0, 0, SRCCOPY);

	// график зависимости энергии от времени
	DrawEGraf(&E_mDc, E_rect);
	E_Dc->BitBlt(0, 0, E_rect.Width(), E_rect.Height(), &E_mDc, 0, 0, SRCCOPY);

	// основное окно анимации
	DrawOscillator4(&A_mDc, A_rect);
	A_Dc->BitBlt(0, 0, A_rect.Width(), A_rect.Height(), &A_mDc, 0, 0, SRCCOPY);
}

void COscillator4Dlg::OnPaint()
{
	UpdateData(TRUE);
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
		MyOnPaint();

	}
	UpdateData(FALSE);
}

void COscillator4Dlg::DrawTraectory(CDC *pDc, CRect r)
{
	int xC = (int)((r.Width()) * 0.5);
	int yC = (int)((r.Height()) * 0.5);

	if (ifTGraf) {
		pDc->Rectangle(0, 0, r.Width(), r.Height());
		ifTGraf = FALSE;
		pen.CreatePen(2, 1, OSI_COLOR);
		oldpen = pDc->SelectObject(&pen);
		// оси
		pDc->MoveTo(r.left, yC);
		pDc->LineTo(r.right, yC);
		pDc->MoveTo(xC, r.top);
		pDc->LineTo(xC, r.bottom);

		pDc->TextOutW(r.right - 20, yC + 10, _T("x"));
		pDc->TextOutW(xC - 20, 2, _T("y"));

		pDc->SelectObject(oldpen);
		pen.DeleteObject();
	}

	// текущие координаты на графике
	int c_x = (int)(0.95 * x * r.Width() / (2 * l0));
	int c_y = (int)(0.95 * y * r.Height() / (2 * l0));

	pDc->SetPixel(xC + c_x, yC - c_y, TR_COLOR);

	pDc->MoveTo(xC, yC);
}

void COscillator4Dlg::DrawSpringX(CDC *pDc, CRect r, int x1, int y1, int x2, int y2)
{
	int k = -1;
	if (y2 < y1) k = 1;
	const int R = 5;	// радиус шарнира
	const int N = 20;	// количество "витков" пружинки
	double co = abs(y1 - y2) / sqrt(pow(abs(x1 - x2), 2) + pow(abs(y1 - y2), 2));
	double si = abs(x1 - x2) / sqrt(pow(abs(x1 - x2), 2) + pow(abs(y1 - y2), 2));
	pDc->MoveTo(x1, y1);
	int dx = (x2 - x1) / N;
	int i = 0, ix, iy;
	for (ix = x1; ix < x2; ix += dx) {
		iy = ix * (y2 - y1) / (x2 - x1) + y1 - x1 * (y2 - y1) / (x2 - x1);
		if (i > 1 && i < N)
			if (i % 2)
				pDc->LineTo(ix + k * (int)(sR * co), iy + sR);
			else
				pDc->LineTo(ix - k * (int)(sR * co), iy - sR);
		else
			pDc->LineTo(ix, iy);
		i++;
	}
	pDc->LineTo(x2, y2);
	pDc->Ellipse(x1 - R, y1 - R, x1 + R, y1 + R);
	pDc->Ellipse(x2 - R, y2 - R, x2 + R, y2 + R);
	pDc->MoveTo(xCenter, yCenter);
}

void COscillator4Dlg::DrawSpringY(CDC* pDc, CRect r, int x1, int y1, int x2, int y2)
{
	int k = -1;
	if (x2 < x1) k = 1;
	const int R = 5;	// радиус шарнира
	const int N = 20;	// количество "витков" пружинки
	double co = abs(x1 - x2) / sqrt(pow(abs(x1 - x2), 2) + pow(abs(y1 - y2), 2));
	double si = abs(y1 - y2) / sqrt(pow(abs(x1 - x2), 2) + pow(abs(y1 - y2), 2));
	pDc->MoveTo(x1, y1);
	int dy = (y2 - y1) / N;
	int i = 0, ix, iy;
	for (iy = y1; iy < y2; iy += dy) {
		ix = iy * (x2 - x1) / (y2 - y1) + x1 - y1 * (x2 - x1) / (y2 - y1);
		if (i > 1 && i < N)
			if (i % 2)
				pDc->LineTo(ix + sR, iy + k * (int)(sR * co));// -(int)(sR * si));
			else
				pDc->LineTo(ix - sR, iy - k * (int)(sR * co));// -(int)(sR * si));
		else
			pDc->LineTo(ix, iy);
		i++;
	}
	pDc->LineTo(x2, y2);
	pDc->Ellipse(x1 - R, y1 - R, x1 + R, y1 + R);
	pDc->Ellipse(x2 - R, y2 - R, x2 + R, y2 + R);
	pDc->MoveTo(xCenter, yCenter);
}

void COscillator4Dlg::DrawOscillator4(CDC *pDc, CRect r)
{
	brush.CreateSolidBrush(BK_COLOR);
	oldbrush = pDc->SelectObject(&brush);
	pDc->Rectangle(0, 0, r.Width(), r.Height());
	pDc->SelectObject(oldbrush);
	brush.DeleteObject();
	pen.CreatePen(2, 1, OSI_COLOR);
	oldpen = pDc->SelectObject(&pen);

	// оси
	pDc->MoveTo(r.left, yCenter);
	pDc->LineTo(r.right, yCenter);
	pDc->MoveTo(xCenter, r.top);
	pDc->LineTo(xCenter, r.bottom);

	pDc->SelectObject(oldpen);
	pen.DeleteObject();

	// пружинки	
	pen.CreatePen(0, 1, SP_COLOR);
	oldpen = pDc->SelectObject(&pen);
	DrawSpringX(pDc, r, r.left, yCenter, X - mR, Y);
	DrawSpringX(pDc, r, X + mR, Y, r.right, yCenter);
	DrawSpringY(pDc, r, xCenter, r.top, X, Y - mR);
	DrawSpringY(pDc, r, X, Y + mR, xCenter, r.bottom);
	pDc->SelectObject(oldpen);
	pen.DeleteObject();

	// тело
	brush.CreateSolidBrush(M_COLOR);
	oldbrush = pDc->SelectObject(&brush);
	pDc->Ellipse(X - mR, Y - mR, X + mR, Y + mR);
	pDc->SelectObject(oldbrush);
	brush.DeleteObject();
	pDc->MoveTo(xCenter, yCenter);
}

// график скорости от времени
void COscillator4Dlg::DrawVGraf(CDC *pDc, CRect r)
{
	if (osi_V >= r.Width()*mT)
	{
		osi_V = 0;
		ifVGraf = TRUE;
	}

	int yCenter = (int)(r.Height() * 0.5);
	double coef = r.Height() / V_max * 0.35;
//	double coef = 10;

	if (ifVGraf)
	{
		pDc->Rectangle(&r);

		pDc->MoveTo(0, yCenter);
		pDc->LineTo(r.right, yCenter);

		pDc->TextOutW(2, 2, _T("Скорость"));
		pDc->TextOutW(r.right - 26, 2, _T("Vx"));
		pDc->TextOutW(r.right - 26, 20, _T("Vy"));
		for (int i = 35; i > 30; i--) {
			pDc->SetPixel(r.right - i, 10, VX_COLOR);
			pDc->SetPixel(r.right - i, 28, VY_COLOR);
		}
		pDc->TextOutW(r.right - 12, yCenter + 2, _T("t"));

		ifVGraf = FALSE;
	}

	pDc->MoveTo(1, 0);
	pDc->LineTo(1, r.bottom);
	
	// точка в соответствующем месте
	pDc->SetPixel(int(osi_V / mT), yCenter - int(Vx * coef), VX_COLOR);
	pDc->SetPixel(int(osi_V / mT), yCenter - int(Vy * coef), VY_COLOR);

	pDc->SelectObject(oldpen);
	pen.DeleteObject();
}

// график X от времени
void COscillator4Dlg::DrawX(CDC* pDc, CRect r)
{
	if (osi_X >= r.Width() * mT)
	{
		osi_X = 0;
		ifXGraf = TRUE;
	}

	int yCenter = (int)(r.Height() * 0.5);
	double coef = r.Height() / l0 * 0.75;
	//	double coef = 10;

	if (ifXGraf)
	{
		pDc->Rectangle(&r);

		pDc->MoveTo(0, yCenter);
		pDc->LineTo(r.right, yCenter);


		// сетка
		pen.CreatePen(2, 1, OSI_COLOR);
		oldpen = pDc->SelectObject(&pen);
		for (int i = 1; i < 10; i++) {
			double k = 0.05 * r.Height();
			pDc->MoveTo(r.left, yCenter - k * i);
			pDc->LineTo(r.right, yCenter - k * i);
			pDc->MoveTo(r.left, yCenter + k * i);
			pDc->LineTo(r.right, yCenter + k * i);
		}
		pDc->SelectObject(oldpen);
		pen.DeleteObject();
		CString s;
		s.Format(_T("%.2f"), l0);
		pDc->TextOutW(2, 2, s);
		pDc->TextOutW(2, r.Height() - 18, '-' + s);
		pDc->TextOutW(2, yCenter + 2, _T("0"));
		pDc->TextOutW(r.right - 26, 2, _T("X,м"));
		pDc->TextOutW(r.right - 12, yCenter + 2, _T("t"));

		ifXGraf = FALSE;
	}

	pDc->MoveTo(1, 0);
	pDc->LineTo(1, r.bottom);

	// точка в соответствующем месте
	pDc->SetPixel(int(osi_X / mT), yCenter - int(x * coef), VX_COLOR);

	pDc->SelectObject(oldpen);
	pen.DeleteObject();
}

// график Y от времени
void COscillator4Dlg::DrawY(CDC* pDc, CRect r)
{
	if (osi_Y >= r.Width() * mT)
	{
		osi_Y = 0;
		ifYGraf = TRUE;
	}

	int yCenter = (int)(r.Height() * 0.5);
	double coef = r.Height() / l0 * 0.75;

	if (ifYGraf)
	{
		pDc->Rectangle(&r);

		pDc->MoveTo(0, yCenter);
		pDc->LineTo(r.right, yCenter);

		// сетка
		pen.CreatePen(2, 1, OSI_COLOR);
		oldpen = pDc->SelectObject(&pen);
		for (int i = 1; i < 10; i++) {
			double k = 0.05 * r.Height();
			pDc->MoveTo(r.left, yCenter - k * i);
			pDc->LineTo(r.right, yCenter - k * i);
			pDc->MoveTo(r.left, yCenter + k * i);
			pDc->LineTo(r.right, yCenter + k * i);
		}
		pDc->SelectObject(oldpen);
		pen.DeleteObject();
		CString s;
		s.Format(_T("%.2f"), l0);
		pDc->TextOutW(2, 2, s);
		pDc->TextOutW(2, r.Height() - 18, '-'+s);
		pDc->TextOutW(2, yCenter + 2, _T("0"));
		pDc->TextOutW(r.right - 26, 2, _T("Y,м"));
		pDc->TextOutW(r.right - 12, yCenter + 2, _T("t"));

		ifYGraf = FALSE;
	}

	pDc->MoveTo(1, 0);
	pDc->LineTo(1, r.bottom);

	// точка в соответствующем месте
	pDc->SetPixel(int(osi_Y / mT), yCenter - int(y * coef), VY_COLOR);

	pDc->SelectObject(oldpen);
	pen.DeleteObject();
}

// график энергии от времени
void COscillator4Dlg::DrawEGraf(CDC *pDc, CRect r)
{
	if (osi_E >= r.Width()*mT)
	{
		osi_E = 0;
		ifEGraf = TRUE;
	}

	int yCenter = (int)(r.Height() - 1);
	double coef = r.Height() / E_max * 0.7;

	if (ifEGraf)
	{
		pDc->Rectangle(&r);

		pDc->MoveTo(0, yCenter);
		pDc->LineTo(r.right, yCenter);

		pDc->TextOutW(2, 2, _T("Энергия"));
		pDc->TextOutW(r.right - 26, 2, _T("Eп"));
		pDc->TextOutW(r.right - 26, 20, _T("Eк"));
		pDc->TextOutW(r.right - 26, 38, _T("E"));
		for (int i = 35; i > 30; i--) {
			pDc->SetPixel(r.right - i, 10, EP_COLOR);
			pDc->SetPixel(r.right - i, 28, EK_COLOR);
			pDc->SetPixel(r.right - i, 46, EF_COLOR);
		}
		pDc->TextOutW(r.right - 12, yCenter - 18, _T("t"));

		ifEGraf = FALSE;
	}

	pDc->MoveTo(1, 0);
	pDc->LineTo(1, r.bottom);

	pDc->SetPixel(int(osi_E / mT), int(yCenter - Ep * coef), EP_COLOR);
	pDc->SetPixel(int(osi_E / mT), int(yCenter - Ek * coef), EK_COLOR);
	pDc->SetPixel(int(osi_E / mT), int(yCenter - (E) * coef), EF_COLOR);//pDc->SetPixel(int(osi_E / mT), int(yCenter - (Ek + Ep) * coef), EF_COLOR);

	pDc->SelectObject(oldpen);
	pen.DeleteObject();
}

HCURSOR COscillator4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int sign(double value)
{
	return (value > 0) - (value < 0);
}





//double COscillator4Dlg::Fx(double t, double x, double y, double vx, double vy)
//{
//	// левая пружина
//	double dl1 = sqrt(pow(l0 + x, 2) + pow(y, 2)) - l0;
//	double F1 = kx * dl1;
//	double F1x = F1 * (l0 + x) / sqrt(pow(l0 + x, 2) + pow(y, 2));
//	// правая пружина
//	double dl2 = l0 - sqrt(pow(l0 - x, 2) + pow(y, 2));
//	double F2 = kx * dl2;
//	double F2x = F2 * (l0 - x) / sqrt(pow(l0 - x, 2) + pow(y, 2));
//	// нижняя пружина
//	double dl3 = sqrt(pow(l0 + y, 2) + pow(x, 2)) - l0;
//	double F3 = ky * dl3;
//	double F3x = F3 * x / sqrt(pow(l0 + y, 2) + pow(x, 2));
//	// верхняя пружина
//	double dl4 = l0 - sqrt(pow(l0 - y, 2) + pow(x, 2));
//	double F4 = ky * dl4;
//	double F4x = F4 * x / sqrt(pow(l0 - y, 2) + pow(x, 2));
//	//double fric_x = friction * m * g * sign(vx);//-----------------------------------
//	return -(F1x + F2x + F3x - F4x);//return -(F1x + F2x + F3x - F4x) / m;
//}
//
//
//
//
//
//
//double COscillator4Dlg::Fy(double t, double x, double y, double vx, double vy)
//{
//
//	// левая пружина
//	double dl1 = sqrt(pow(l0 + x, 2) + pow(y, 2)) - l0;
//	double F1 = kx * dl1;
//	double F1y = F1 * y / sqrt(pow(l0 + x, 2) + pow(y, 2));
//	// правая пружина
//	double dl2 = l0 - sqrt(pow(l0 - x, 2) + pow(y, 2));
//	double F2 = kx * dl2;
//	double F2y = F2 * y / sqrt(pow(l0 - x, 2) + pow(y, 2));
//	// нижняя пружина
//	double dl3 = sqrt(pow(l0 + y, 2) + pow(x, 2)) - l0;
//	double F3 = ky * dl3;
//	double F3y = F3 * (l0 + y) / sqrt(pow(l0 + y, 2) + pow(x, 2));
//	// верхняя пружина
//	double dl4 = l0 - sqrt(pow(l0 - y, 2) + pow(x, 2));
//	double F4 = ky * dl4;
//	double F4y = F4 * (l0 - y) / sqrt(pow(l0 - y, 2) + pow(x, 2));
//	double fric_y = friction * m * g * sign(vy);//-----------------------------------
//	return -(-F1y + F2y + F3y + F4y);//return -(F1y - F2y + F3y + F4y) / m;
//
//}
//double COscillator4Dlg::F(double t, double x, double y, double vx, double vy)
//{
//	double F = sqrt(pow(Fx(t, x, y, vx, vy), 2) + pow(Fy(t, x, y, vx, vy),2));
//}









//---------------------------================================================================







double COscillator4Dlg::ax(double t, double x, double y, double vx, double vy)
{

	//здесь я добавил kx1,ky1,kx2,ky2
	kx1 = kx + kx1m;
	ky1 = ky + ky1m;
	kx2 = ky + kx2m;
	ky2 = ky + ky2m;

	// левая пружина
	double dl1 = sqrt(pow(l0 + x, 2) + pow(y, 2)) - l0;
	double F1 = kx1 * dl1;//double F1 = kx * dl1;
	double F1x = F1 * (l0 + x) / sqrt(pow(l0 + x, 2) + pow(y, 2));
	// правая пружина
	double dl2 = l0 - sqrt(pow(l0 - x, 2) + pow(y, 2));
	double F2 = kx2 * dl2;
	double F2x = F2 * (l0 - x) / sqrt(pow(l0 - x, 2) + pow(y, 2));
	// нижняя пружина
	double dl3 = sqrt(pow(l0 + y, 2) + pow(x, 2)) - l0;
	double F3 = ky1 * dl3;
	double F3x = F3 * x / sqrt(pow(l0 + y, 2) + pow(x, 2));
	// верхняя пружина
	double dl4 = l0 - sqrt(pow(l0 - y, 2) + pow(x, 2));
	double F4 = ky2 * dl4;
	double F4x = F4 * x / sqrt(pow(l0 - y, 2) + pow(x, 2));
	// модуль скорости
	double v_mag = sqrt(vx * vx + vy * vy);
	double fric_x = 0;
	if (v_mag > 0) 
	{
		 fric_x = friction * m * g * vx / v_mag;  // сила трения по оси X
	}

	viscous_x = ViscousK * vx;  // сила вязкого трения по оси X
	//double fric_x = friction * m * g * sign(vx);//-----------------------------------
	return -(F1x + F2x + F3x - F4x + fric_x + viscous_x) / m;//return -(F1x + F2x + F3x - F4x) / m;
}

double COscillator4Dlg::ay(double t, double x, double y, double vx, double vy)
{
	kx1 = kx + kx1m;
	ky1 = ky + ky1m;
	kx2 = ky + kx2m;
	ky2 = ky + ky2m;
	
	// левая пружина
	dl1 = sqrt(pow(l0 + x, 2) + pow(y, 2)) - l0;
	double F1 = kx1 * dl1;
	double F1y = F1 * y / sqrt(pow(l0 + x, 2) + pow(y, 2));
	// правая пружина
	dl2 = l0 - sqrt(pow(l0 - x, 2) + pow(y, 2));
	double F2 = kx2 * dl2;
	double F2y = F2 * y / sqrt(pow(l0 - x, 2) + pow(y, 2));
	// нижняя пружина
	dl3 = sqrt(pow(l0 + y, 2) + pow(x, 2)) - l0;
	double F3 = ky1 * dl3;
	double F3y = F3 * (l0 + y) / sqrt(pow(l0 + y, 2) + pow(x, 2));
	// верхняя пружина
	dl4 = l0 - sqrt(pow(l0 - y, 2) + pow(x, 2));
	double F4 = ky2 * dl4;
	double F4y = F4 * (l0 - y) / sqrt(pow(l0 - y, 2) + pow(x, 2));
	double v_mag2 = sqrt(vx * vx + vy * vy);
	double fric_y = 0;
	if (v_mag2 > 0)
	{
		fric_y = friction * m * g * vy / v_mag2;  // сила трения по оси X
	}
	viscous_y = ViscousK * vy;//вязкое трение льда
	//double fric_y = friction * m * g  * sign(vy);//-----------------------------------
	return -(-F1y + F2y + F3y + F4y + fric_y + viscous_y) / m;//return -(F1y - F2y + F3y + F4y) / m;
	
}

RKresult COscillator4Dlg::RKMethod(double t, double x, double y, double vx, double vy)
{
	double k1x, k1y, k2x, k2y, k3x, k3y, k4x, k4y;

	k1x = ax(t, x, y, vx, vy) * dt;
	k1y = ay(t, x, y, vx, vy) * dt;
	k2x = ax(t + dt / 2, x + vx * dt / 2, y + vy * dt / 2, vx + k1x / 2, vy + k1y / 2) * dt;
	k2y = ay(t + dt / 2, x + vx * dt / 2, y + vy * dt / 2, vx + k1x / 2, vy + k1y / 2) * dt;
	k3x = ax(t + dt / 2, x + vx * dt / 2 + k1x / 4 * dt, y + vy * dt / 2 + k1y / 4 * dt, vx + k2x / 2, vy + k2y / 2) * dt;
	k3y = ay(t + dt / 2, x + vx * dt / 2 + k1x / 4 * dt, y + vy * dt / 2 + k1y / 4 * dt, vx + k2x / 2, vy + k2y / 2) * dt;
	k4x = ax(t + dt, x + vx * dt + k2x * dt / 2, y + vy * dt + k2y * dt / 2, vx + k3x, vy + k3y) * dt;
	k4y = ay(t + dt, x + vx * dt + k2x * dt / 2, y + vy * dt + k2y * dt / 2, vx + k3x, vy + k3y) * dt;

	double tNew = t + dt;
	double xNew = x + (vx * dt + ((k1x + k2x + k3x) / 16) * dt);
	double yNew = y + (vy * dt + ((k1y + k2y + k3y) / 16) * dt);
	double vxNew = vx + (k1x + 2 * k2x + 2 * k3x + k4x) / 16;
	double vyNew = vy + (k1y + 2 * k2y + 2 * k3y + k4y) / 16;

	RKresult koor4(tNew, xNew, yNew, vxNew, vyNew);
	return koor4;
}
//ВОТ ТУТ ЖЁСТКИЕ БЕДЫ=================================================================================================
//                                                                                                                    ||
//																													  V	
void COscillator4Dlg::OnTimer(UINT_PTR nIDEvent)
{
	UpdateData(TRUE);
	t += dt;
	osi_V++;
	osi_T++;
	osi_X++;
	osi_Y++;
	osi_E++;

	// метод Рунге-Кутта
	RKresult Coord = RKMethod(t, x, y, Vx, Vy);

	x = Coord.x;
	y = Coord.y;
	Vx = Coord.Vx;
	Vy = Coord.Vy;

	V = sqrt(pow(Vx, 2) + pow(Vy, 2));
	if (V > V_max * 1.05) {
		V_max = V * 1.1;
		ifVGraf = ifEGraf = TRUE;
		osi_V = osi_E = 0;
	}

	t = Coord.t;

	// Расчёт кинетической энергии
	Ek = m * (pow(Vx, 2) + pow(Vy, 2)) / 2.;
	// Потенциальная энергия (связана с пружинами)
	Ep = (kx1 * pow(dl1, 2) + kx2 * pow(dl2, 2) + ky1 * pow(dl3, 2) + ky2 * pow(dl4, 2)) / 2.0;
	// Обновление полной энергии (если кинетическая энергия больше текущей полной энергии)
	if (Ek > E) {
		E = Ek;
	}

	

	// Потери на сухое трение
	double fric_dry_loss = friction * m * g * V * dt; // сухое трение: F_fric * dx = μ * m * g * dx

	// Потери на вязкое трение
	double visc_friction = pow(viscous_y, 2) + pow(viscous_x, 2); // Коэффициент вязкого трения
	double fric_visc_loss = visc_friction * pow(V, 2) * dt; // Вязкое трение: b * V^2 * dt

	// Полная энергия с учётом потерь на трение
	E = Ek + Ep/* - fric_dry_loss - fric_visc_loss*/;
	//Ep = E - Ek;
	// Обновление максимальной энергии
	if (E > E_max) {
		E_max = E * 1.1;
		ifVGraf = ifEGraf = TRUE;
		osi_V = osi_E = 0;
	}
	
	// Энергия для графика
	/*Ep = E - Ek;*/





	//Ek = m * pow(pow(Vx, 2) + pow(Vy, 2), 2) / 2.;
	//if (Ek > E) {
	//	E = Ek;
	//}
	//if (E > E_max) {
	//	E_max = E * 1.1;
	//	ifVGraf = ifEGraf = TRUE;
	//	osi_V = osi_E = 0;
	//}
	//Ep = E - Ek;//Ep = E - Ek
	//// Потери на сухое трение
	//double fric_dry_loss = friction * m * g * V * dt; // сухое трение: F_fric * dx = μ * m * g * dx
	//// Потери на вязкое трение
	//double visc_friction = pow(viscous_y, 2) + pow(viscous_x, 2);
	//double fric_visc_loss = visc_friction * pow(V, 2) * dt; // вязкое трение: b * V^2 * dt
	//// Полная энергия с учётом потерь на трение
	//E = Ek + Ep - fric_dry_loss - fric_visc_loss;







	/*if (Ek > E) { 
		E = Ek;
	}*/

	/*if (E > E_max) {
		E_max = E * 1.1;
		ifVGraf = ifEGraf = TRUE;
		osi_V = osi_E = 0;
	}*/

	//Ep = E - Ek;//Ep = E - Ek
	

	ox = Coord.xOld;
	oy = Coord.yOld;

	oX = X;
	oY = Y;
	X = (int)(xCenter + x / mX);
	Y = (int)(yCenter - y / mX);

	MyOnPaint();
	UpdateData(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}


void COscillator4Dlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	// проверим ограничение начальных координат
	// от центра не далее чем на 0.75 от длины пружинок
	if (sqrt(pow(x0, 2) + pow(y0, 2)) > l0 * 0.75) {
		MessageBoxW(L"Неверно заданы начальные координаты", L"Внимание!", MB_OK);
		return;
	}
	// прикинем максимальную начальную скорость
	double V0max = l0 / (M_PI * sqrt(m / kx));
	// и проверим ограничение
	if (abs(V0x) > V0max || abs(V0y) > V0max) {
		std::ostringstream strs;
		strs << V0max;
		std::string str = "Начальные скорость\n не должна превышать " + strs.str();
		MessageBoxW(CA2W(str.c_str()), L"Внимание!", MB_OK);
		return;
	}

	CEdit* pEdit;
	pEdit = (CEdit*)GetDlgItem(IDC_MASS);
	pEdit->SetReadOnly(TRUE);
	pEdit = (CEdit*)GetDlgItem(IDC_L);
	pEdit->SetReadOnly(TRUE);
	pEdit = (CEdit*)GetDlgItem(IDC_X0);
	pEdit->SetReadOnly(TRUE);
	pEdit = (CEdit*)GetDlgItem(IDC_Y0);
	pEdit->SetReadOnly(TRUE);
	pEdit = (CEdit*)GetDlgItem(IDC_KX);
	pEdit->SetReadOnly(TRUE);
	pEdit = (CEdit*)GetDlgItem(IDC_KY);
	pEdit->SetReadOnly(TRUE);
	pEdit = (CEdit*)GetDlgItem(IDC_VX0);
	pEdit->SetReadOnly(TRUE);
	pEdit = (CEdit*)GetDlgItem(IDC_VY0);
	pEdit->SetReadOnly(TRUE);

	x = x0;
	y = y0;
	Vx = V0x;
	Vy = V0y;
	// начальная скорость
	V = V_max = sqrt(pow(Vx, 2) + pow(Vy, 2));
	// энергии
	E = Ep = Ek = E_max = 0;
	t = 0;
	X = (int)(xCenter + x / mX);
	Y = (int)(yCenter - y / mX);
	osi_V = osi_T = osi_X = osi_Y = osi_E = 0;
	ifVGraf = ifTGraf = ifXGraf = ifYGraf = ifEGraf = TRUE;
	UpdateData(FALSE);
	nTimer = SetTimer(ID_TIMER1, ntimeout, NULL);
}


void COscillator4Dlg::OnBnClickedButton2()
{
	KillTimer(nTimer);

	CEdit* pEdit;
	pEdit = (CEdit*)GetDlgItem(IDC_MASS);
	pEdit->SetReadOnly(FALSE);
	pEdit = (CEdit*)GetDlgItem(IDC_L);
	pEdit->SetReadOnly(FALSE);
	pEdit = (CEdit*)GetDlgItem(IDC_X0);
	pEdit->SetReadOnly(FALSE);
	pEdit = (CEdit*)GetDlgItem(IDC_Y0);
	pEdit->SetReadOnly(FALSE);
	pEdit = (CEdit*)GetDlgItem(IDC_KX);
	pEdit->SetReadOnly(FALSE);
	pEdit = (CEdit*)GetDlgItem(IDC_KY);
	pEdit->SetReadOnly(FALSE);
	pEdit = (CEdit*)GetDlgItem(IDC_VX0);
	pEdit->SetReadOnly(FALSE);
	pEdit = (CEdit*)GetDlgItem(IDC_VY0);
	pEdit->SetReadOnly(FALSE);

}


void COscillator4Dlg::OnBnClickedButton3()
{
	exit(0);
}


void COscillator4Dlg::OnBnClickedBpkx1()//Модификация жёсткости kx1
{
	// TODO: добавьте свой код обработчика уведомлений
	kx1m += 15;

}


void COscillator4Dlg::OnBnClickedBpkx2()//Модификация жёсткости kx2
{
	// TODO: добавьте свой код обработчика уведомлений
	kx2m += 15;
}

void COscillator4Dlg::OnBnClickedBpky1()//Модификация жёсткости ky1
{
	// TODO: добавьте свой код обработчика уведомлений
	ky1m += 15;
}


void COscillator4Dlg::OnBnClickedBpky2()//Модификация жёсткости ky2
{
	// TODO: добавьте свой код обработчика уведомлений
	ky2m += 15;
}
