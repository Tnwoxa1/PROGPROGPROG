
// Potential_pitDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include <algorithm>
#include <fstream>
#include <thread>
#include "Potential_pit.h"
#include "Potential_pitDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

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
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
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


// Диалоговое окно CPotentialpitDlg
//динамика волнового пакета
//начальное распределение - диффур в методичке
//считать на разных временных шагах (система линейных уравнений методом прогонки)


CPotentialpitDlg::CPotentialpitDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_POTENTIAL_PIT_DIALOG, pParent)
	, sigmaX(0.02)
	, muX(0.0)
	, sigmaY(0.02)
	, muY(0.0)
	, R(1.0)
	, x_dot(0)
	, dt(0.005)
	, dt_timer(0.03)
	, numWaves(256)
	, y_dot(0)
	, weightX(0)
	, weightY(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPotentialpitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_sigma_x, sigmaX);
	DDX_Text(pDX, IDC_mu_x, muX);
	DDX_Text(pDX, IDC_sigma_y, sigmaY);
	DDX_Text(pDX, IDC_mu_y, muY);
	DDX_Text(pDX, IDC_n_dot, x_dot);
	DDX_Control(pDX, IDC_slider_dot, slider_x);
	DDX_Text(pDX, IDC_R2, dt);
	DDX_Text(pDX, IDC_numWaves, numWaves);
	DDX_Text(pDX, IDC_y_dot, y_dot);
	DDX_Control(pDX, IDC_slider_dot_y, slider_y);
	//DDX_Text(pDX, IDC_k1, weightX);
	//DDX_Text(pDX, IDC_k2, weightY);
}

BEGIN_MESSAGE_MAP(CPotentialpitDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CPotentialpitDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_EN_UPDATE(IDC_n_dot, &CPotentialpitDlg::OnEnUpdatendot)
	ON_WM_HSCROLL()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_EN_UPDATE(IDC_y_dot, &CPotentialpitDlg::OnEnUpdateydot)
END_MESSAGE_MAP()


// Обработчики сообщений CPotentialpitDlg

BOOL CPotentialpitDlg::OnInitDialog()
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

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CPotentialpitDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPotentialpitDlg::OnPaint()
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
		if (wave0.size() > 0) {
			//DrawWave(wave0, IDC_phase);
		}
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CPotentialpitDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPotentialpitDlg::DrawWave(vector<vector <long double>> wave, int IDC = IDC_pits)
{
	//рисование модели
	CDC* dc = GetDlgItem(IDC)->GetDC();
	HDC hdc = *dc;
	Gdiplus::Graphics gr(hdc); //gr будет рисовать на IDC_Object
	CRect obj_rect; //прямоугольник области рисования
	GetDlgItem(IDC)->GetClientRect(&obj_rect); //получаем размеры прямоугольника
	Gdiplus::Bitmap myBitmap(obj_rect.Width(), obj_rect.Height()); //создаем битовый образ

	Gdiplus::Graphics* grr = Gdiplus::Graphics::FromImage(&myBitmap); //создаем дополнительный объект класса для рисования объектов
	grr->SetSmoothingMode(Gdiplus::SmoothingModeHighSpeed); //устанавливаем сглаживание в режиме наилучшего качества

	grr->Clear(Gdiplus::Color::WhiteSmoke);//очистим фон

	Gdiplus::Matrix mtx(1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);//создаем матрицу с осью у, направленной вверх

	long double x_max = R, y_max = R, x_min = -R, y_min = -R;
	if (IDC == IDC_spectrum) y_min = 0;

	mtx.Translate(obj_rect.Width() * 0.5, obj_rect.Height() * 0.5, Gdiplus::MatrixOrderAppend);//перенос начала координат
	if (IDC == IDC_spectrum) mtx.Translate(obj_rect.Width() * 0.0, obj_rect.Height() * 0.5, Gdiplus::MatrixOrderAppend);//перенос начала координат

	mtx.Scale(obj_rect.Width() / (x_max - x_min), obj_rect.Height() / (y_max - y_min)); //изменяем масштаб
	grr->SetTransform(&mtx); //применяем преобразования

	Gdiplus::Pen pGrid(Gdiplus::Color::Color(250, 250, 250), x_max/10.); //ручка для основной сетки
	
	//рисовка цветом 
	int step = 1;
	long double stepX = (x_max - x_min) / wave.size();
	long double stepY = (y_max - y_min) / wave.size();

	for (int i = 0; i < wave.size() - step - 1; i += step) 
	{
		for (int j = 0; j < wave[i].size() - step - 1; j += step) 
		{
			long double module = wave[i][j];
			Gdiplus::SolidBrush br(Gdiplus::Color(module * 0, module * 256, module * 256));
			long double x = i * stepX + x_min,
				   y = j * stepY + y_min;
			grr->FillRectangle(&br, Gdiplus::REAL(x), Gdiplus::REAL(y), Gdiplus::REAL(stepX), Gdiplus::REAL(stepY));
			//if (IDC == IDC_wave_in_time) 	gr.DrawImage(&myBitmap, 0, 0, obj_rect.Width(), obj_rect.Height());
		}
	}

	//рисовка из буфера
	gr.DrawImage(&myBitmap, 0, 0, obj_rect.Width(), obj_rect.Height());
	delete grr;//очистка памяти
}

void CPotentialpitDlg::DrawSpectrum(vector <long double> spectrum, int IDC = IDC_spectrum)
{
	//рисование модели
	CDC* dc = GetDlgItem(IDC)->GetDC();
	HDC hdc = *dc;
	Gdiplus::Graphics gr(hdc); //gr будет рисовать на IDC_Object
	CRect obj_rect; //прямоугольник области рисования
	GetDlgItem(IDC)->GetClientRect(&obj_rect); //получаем размеры прямоугольника
	Gdiplus::Bitmap myBitmap(obj_rect.Width(), obj_rect.Height()); //создаем битовый образ

	Gdiplus::Graphics* grr = Gdiplus::Graphics::FromImage(&myBitmap); //создаем дополнительный объект класса для рисования объектов
	grr->SetSmoothingMode(Gdiplus::SmoothingModeHighSpeed); //устанавливаем сглаживание в режиме наилучшего качества

	grr->Clear(Gdiplus::Color::WhiteSmoke);//очистим фон


	Gdiplus::Matrix mtx(1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);//создаем матрицу с осью у, направленной вверх

	long double spectrum_max = *max_element(spectrum.begin(), spectrum.end()),
				z_max = numWaves - 1,
				z_min = 0;

	mtx.Translate(obj_rect.Width() * 0.00, obj_rect.Height() * 0.95, Gdiplus::MatrixOrderAppend);//перенос начала координат
	mtx.Scale(obj_rect.Width() / (z_max), obj_rect.Height() / (1.1*spectrum_max)); //изменяем масштаб
	grr->SetTransform(&mtx); //применяем преобразования

	Gdiplus::Pen pGrid(Gdiplus::Color::Color(50, 50, 50), z_max / 5000); //ручка для основной сетки
	//Gdiplus::Pen pGrid2(Gdiplus::Color::Color(50, 50, 50), 5); //ручка для основной сетки

	grr->DrawLine(&pGrid, (Gdiplus::REAL)0, (Gdiplus::REAL)-spectrum_max, (Gdiplus::REAL)0, (Gdiplus::REAL)1.1*spectrum_max);
	grr->DrawLine(&pGrid, (Gdiplus::REAL)z_min, (Gdiplus::REAL)0, (Gdiplus::REAL)z_max, (Gdiplus::REAL)0);

	Gdiplus::Pen pObj(Gdiplus::Color::Green, z_max / 5000); //ручка для рисования объектов
	//Gdiplus::Pen pPits(Gdiplus::Color::BlueViolet, z_max / 900); //ручка для рисования объектов

	Gdiplus::SolidBrush brObj(Gdiplus::Color::Black); //ручка для рисования объектов


	for (int i = 0; i < spectrum.size() - 1; i++) 
	{
		grr->DrawLine(&pObj, (Gdiplus::REAL)i, (Gdiplus::REAL)abs(spectrum[i]), (Gdiplus::REAL)i+1, (Gdiplus::REAL)abs(spectrum[i + 1]));
	}


	//сбрасываем матрицу преобразования
	mtx.Reset();
	mtx.Translate(obj_rect.Width() * 0.00, obj_rect.Height() * 0.95, Gdiplus::MatrixOrderAppend);//перенос начала координат

	grr->SetTransform(&mtx); //применяем преобразования


	Gdiplus::REAL font_size = min((Gdiplus::REAL)(obj_rect.Width() / (2. * 20)), (Gdiplus::REAL)(obj_rect.Height() / (2. * 20)));
	//добавляем подписи
	Gdiplus::Font font(L"Arial", font_size, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel); //создаем шрифт
	Gdiplus::SolidBrush brText(Gdiplus::Color::Black); //кисть для шрифта
	grr->SetTextRenderingHint(Gdiplus::TextRenderingHintClearTypeGridFit); //сглаживание в стиле cleartype

	//подпись оси y
	long double y = 0;
	for (long double i = 0; i >= -obj_rect.Height(); i -= 0.1 * obj_rect.Height()) 
	{
		CString str;
		str.Format(_T("%.3f"), y);

		grr->DrawString(str, -1, &font, Gdiplus::PointF(0, i), &brText);
		y += spectrum_max * 0.1;

	}

	//рисовка из буфера
	gr.DrawImage(&myBitmap, 0, 0, obj_rect.Width(), obj_rect.Height());
	delete grr;//очистка памяти

}

void CPotentialpitDlg::OnBnClickedOk()
{
	BeginWaitCursor();
	ind_wave = 0;
	if (timer) KillTimer(1);
	//трехмерный вектор - волновые функции во времени - wave[t][x][y]
	wave.clear();
	//исходный гауссов купол (волновая функция) - двумерный вектор
	wave0.clear();
	timer = false;
	//работают ли потоки или нет
	thEvolutionDone = false; //просчитаны ли волновые функции во времени

	UpdateData(TRUE);
	if (pow(2, (int)log2(numWaves)) != numWaves || numWaves < 1) 
	{
		MessageBox(L"Количество волн должно быть больше 0\nи являться степенью 2!");
		Beep(5000,500);
		return;
	}

	//получаем начальное распределение
	wave0 = CreateWaveFunction(R, muX, sigmaX, muY, sigmaY);

	//запускаем в фоне вычисления
	//вычисление волновых функций
	thread thEvolution(CalculateWaveEvolution, wave0, &wave, R, numWaves, dt, &thEvolutionDone, weightX, weightY);
	thEvolution.join();
	

	slider_x.SetRange(0, int(255*R));
	slider_y.SetRange(0, int(255 * R));

	EndWaitCursor();
	wavefft = wave;
	for (int ix = 0; ix < wave[0].size(); ix++)
	{
		for (int iy = 0; iy < wave[0][ix].size(); iy++)
		{
			vector<complexld> spectr(numWaves);
			//берем точки для спектра по времени
			for (int i = 0; i < numWaves; i++)
			{
				spectr[i] = wave[i][ix][iy];
			}
			//берем фурье
			spectr = fft(spectr);

			for (int i = 0; i < numWaves; i++)
			{
				wavefft[i][ix][iy] = spectr[i];
			}
		}
	}
	//начальное распределение рисуем
	//DrawWave(wave0, IDC_phase);
	SetTimer(1, dt_timer*1000, NULL);
}

//отрисовка волновых функций во времени
void CPotentialpitDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (thEvolutionDone) 
	{
		if (ind_wave < numWaves - 2) ind_wave++;
		else ind_wave = 0; 
		//волновая функция - комплексная. Рисуем модуль
		vector<vector<long double>> wave_real = Cmplx2LDouble(wave[ind_wave]);

		//нормализуем для рисовки
		wave_real = Normalizate(wave_real);
		//рисуем
		DrawWave(wave_real, IDC_pits);
	}
	
	CDialogEx::OnTimer(nIDEvent);
}

//обновление точки
void CPotentialpitDlg::UpdateDot()
{
	UpdateData();
	if (!thEvolutionDone) 
	{
		MessageBox(L"Дождитесь конца вычислений!");
		return;
	}
	if (x_dot < 0) 
	{
		x_dot = 0;
	}
	else if (x_dot > wave[0].size() - 1) 
	{
		x_dot = wave[0].size() - 1;
	}

	if (y_dot < 0) 
	{
		y_dot = 0;
	}
	else if (y_dot > wave[0][0].size() - 1) 
	{
		y_dot = wave[0][0].size() - 1;
	}

	slider_x.SetPos(x_dot);
	slider_y.SetPos(y_dot);

	vector<complexld> spectr(numWaves);
	//берем точки для спектра по времени
	for (int i = 0; i < numWaves; i++) 
	{
		spectr[i] = wave[i][x_dot][y_dot];
	}
	//берем фурье
	spectr = fft(spectr);
	spectrumDouble = Cmplx2LDouble(spectr);
	DrawSpectrum(spectrumDouble, IDC_spectrum);
	
}

void CPotentialpitDlg::OnEnUpdateydot()
{
	UpdateDot();	
}

void CPotentialpitDlg::OnEnUpdatendot()
{
	UpdateDot();	
}

//слайдеры
void CPotentialpitDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (!thEvolutionDone) return;
	x_dot = slider_x.GetPos();
	y_dot = slider_y.GetPos();
	UpdateData(FALSE);
	OnEnUpdatendot();
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

// тык в спектр
void CPotentialpitDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CRect window_rect;
	GetDlgItem(IDC_spectrum)->GetWindowRect(&window_rect);
	ScreenToClient(&window_rect);
	//int x0 = , y0 = 281;
	if(window_rect.PtInRect(point))
	//if (point.x > x0 && point.y > y0)
		if (wave.size() != 0 && thEvolutionDone) 
		{
			int x0 = window_rect.left;
			UpdateDot();
			CDC* dc = GetDlgItem(IDC_spectrum)->GetDC();
			HDC hdc = *dc;
			CRect obj_rect; //прямоугольник области рисования
			GetDlgItem(IDC_spectrum)->GetClientRect(&obj_rect); //получаем размеры прямоугольника
			Gdiplus::Graphics gr(hdc); //gr будет рисовать на IDC_Object
			Gdiplus::Pen pGrid(Gdiplus::Color::Color(0, 0, 0), 2); //ручка для основной сетки
			
			gr.DrawLine(&pGrid, Gdiplus::PointF(point.x - x0, 0), Gdiplus::PointF(point.x -x0, 600));
			ind_fft = numWaves * (point.x - x0) / (obj_rect.Width() * 1.);
			

			auto spectr = wavefft[ind_fft];

			auto spectrum_real = Cmplx2LDouble(spectr);
			spectrum_real = Normalizate(spectrum_real);
			DrawWave(spectrum_real, IDC_wave_in_time);
		}
	CDialogEx::OnLButtonUp(nFlags, point);
}


