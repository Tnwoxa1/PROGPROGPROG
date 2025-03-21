
// PuasonDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Puason.h"
#include "PuasonDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CPuasonDlg



CPuasonDlg::CPuasonDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PUASON_DIALOG, pParent)
	, my_q(1)
	, my_error(1e-3)
	, my_width(55)
	, my_height(55)
	, my_num_izoline(11)
	, my_step(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPuasonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT5, my_q);
	DDX_Text(pDX, IDC_EDIT4, my_error);
	DDX_Text(pDX, IDC_EDIT6, my_width);
	DDX_Text(pDX, IDC_EDIT7, my_height);
	DDX_Control(pDX, IDC_SHEMA, my_shema);
	DDX_Control(pDX, IDC_EDIT8, my_cur_error);
	DDX_Control(pDX, IDOK, but_ok);
	DDX_Control(pDX, IDC_SLIDER1, my_power_line);
	DDX_Control(pDX, IDC_SLIDER2, my_sl_izoline);
}

BEGIN_MESSAGE_MAP(CPuasonDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CPuasonDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPuasonDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CPuasonDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON2, &CPuasonDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CPuasonDlg::OnBnClickedButton3)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// Обработчики сообщений CPuasonDlg

BOOL CPuasonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	InitializeCriticalSection(&cs);
	but_ok.EnableWindow(TRUE);
	my_power_line.SetRange(-10, -1, TRUE);
	my_sl_izoline.SetRange(10, 50);
	my_power_line.SetPos(-1);
	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CPuasonDlg::OnPaint()
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
HCURSOR CPuasonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPuasonDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	//CDialogEx::OnOK();
	UpdateData();
	condensator.SetParametr(0, 0, 0 + 2, my_q, my_num_izoline, 0);
	if (!condensator.Initialize(my_width, my_height)) return;
	num_power = my_step;
	try_er = my_error;
	my_shema.my_e_line = condensator.E_line;
	my_shema.draw = true;
	my_shema.setka = condensator.GetFi();
	my_shema.my_const = condensator.fi_const;
	my_shema.step_e_line = my_step;
	Invalidate(FALSE);
	but_ok.EnableWindow(TRUE);

	if (my_timer != NULL) KillTimer(my_timer);
	stop = false;
	my_shema.izoline = true;
	my_shema.power_line = true;
	CreateThread(NULL, NULL, rasprostranenie, this, NULL, NULL);
	my_timer = SetTimer(123, 16, NULL);
}

DWORD __stdcall rasprostranenie(PVOID p)
{
	CPuasonDlg* dlg = (CPuasonDlg*)p;
	double cur_error;
	do
	{
		EnterCriticalSection(&dlg->cs);
		cur_error = dlg->condensator.error();
		dlg->condensator.Iteration();
		dlg->str_error = cur_error = dlg->condensator.error();
		dlg->my_shema.SetPower(dlg->condensator.GetPowerL());
		LeaveCriticalSection(&dlg->cs);
		Sleep(5);
	} while (cur_error >= dlg->try_er && !dlg->stop);
	dlg->KillTimer(dlg->my_timer);
	return 0;
}


void CPuasonDlg::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	DeleteCriticalSection(&cs);
	CDialogEx::OnCancel();
}


void CPuasonDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData();
	condensator.SetParametr(0, 0, 0 + 2, my_q, my_num_izoline, 0);
	if (!condensator.Initialize(my_width, my_height)) return; 
	num_power = my_step;
	try_er = my_error;
	my_shema.my_e_line = condensator.E_line;
	my_shema.draw = true;
	my_shema.setka = condensator.GetFi();
	my_shema.my_const = condensator.fi_const;
	my_shema.step_e_line = my_step;
	Invalidate(FALSE);
	but_ok.EnableWindow(TRUE);
}


void CPuasonDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	UpdateData();
	CString str;
	str.Format(L"%.2f", str_error / my_error);
	my_cur_error.SetWindowTextW(str);

	EnterCriticalSection(&cs);
	my_shema.setka = condensator.GetFi();
	Invalidate(FALSE);
	LeaveCriticalSection(&cs);

	CDialogEx::OnTimer(nIDEvent);
}


void CPuasonDlg::OnBnClickedButton2()
{
	// TODO: добавьте свой код обработчика уведомлений
	stop = true;
	KillTimer(my_timer);
	Invalidate(FALSE);
}


void CPuasonDlg::OnBnClickedButton3()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData();
	KillTimer(my_timer);
	my_shema.step_e_line = my_step;
	my_shema.power_line = true;
	Invalidate(FALSE);
}


void CPuasonDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	EnterCriticalSection(&cs);
	my_step = fabs(my_power_line.GetPos());
	if ((int)my_step != 1) my_step = (2 * my_step - 1);
	my_shema.step_e_line = my_step;
	my_num_izoline = my_sl_izoline.GetPos();
	condensator.SetParametr(0, 0, 0 + 2, my_q, my_num_izoline, 0);
	my_shema.my_const = condensator.fi_const;
	Invalidate(FALSE);
	LeaveCriticalSection(&cs);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
