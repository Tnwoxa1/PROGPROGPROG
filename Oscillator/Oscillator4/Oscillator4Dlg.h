
// Oscillator4Dlg.h: файл заголовка
//

#pragma once

#define ID_TIMER1 1000

// эта структура для метода Рунге-Кутты
struct RKresult
{
	double t;
	double x;
	double y;
	double Vx;
	double Vy;
	double xOld;
	double yOld;
	double oldVx;
	double oldVy;
	double curE;
	RKresult(double t_, double x_, double y_, double Vx_, double Vy_)
	{
		t = t_;
		x = x_;
		y = y_;
		Vx = Vx_;
		Vy = Vy_;

		xOld = x_;
		yOld = y_;
	};
};

// Диалоговое окно COscillator4Dlg
class COscillator4Dlg : public CDialogEx
{
// Создание
public:
	COscillator4Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

protected:
	CRect				// область для рисования
		A_rect,			// анимации
		V_rect,			// скорости
		T_rect,			// траектории
		X_rect,
		Y_rect,
		E_rect;			// графика энергии
	
	CDC					// контексты для рисования
		*A_Dc,			// анимации
		*V_Dc,			// скорости
		*T_Dc,			// траектории
		*X_Dc,			// 
		*Y_Dc,			// 
		*E_Dc,			// энергии
		A_mDc,			// анимации в памяти
		V_mDc,			// скорости в памяти
		T_mDc,			// траектории в памяти
		X_mDc,			// 
		Y_mDc,			// 
		E_mDc;			// энергии в памяти 

	CBitmap				// для хранения изображения
		A_bmp, *A_tmp,	// анимации	
		V_bmp, *V_tmp,	// скорости
		T_bmp, *T_tmp,	// траектории
		X_bmp, *X_tmp,	// 
		Y_bmp, *Y_tmp,	// 
		E_bmp, *E_tmp;	// энергии

	CBrush brush, brush1,
		*oldbrush;			// кисть для рисования
	CPen pen,
		*oldpen;			// перо для рисования

	long int
		xCenter,			// центр по Х
		yCenter,			// центр по Y
		osiT,				// ось t для графиков
		osi_V,				// ось t для графика скорости
		osi_T,				// ось t для графика траектории
		osi_X,				// 
		osi_Y,				// 
		osi_E,				// ось t для графика энергии
		ntimeout;			// для таймера
	UINT_PTR nTimer;		// для таймера

	bool ifMainGraf, ifVGraf, ifTGraf, ifYGraf, ifXGraf, ifEGraf;	// отрисовывать ли

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Oscillator4_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void MyOnPaint();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//Сила тяжести
	double g = 9.8;
	// масса тела
	double m;
	// длина пружинок
	double l0;
	// начальная скорость
	double V0x;
	double V0y;
	// жесткость пружин по y
	double ky;
	// жесткость пружин по x
	double kx;
	// модификация kx1
	double kx1m = 0;
	// модификация kx1
	double ky1m = 0;
	// модификация kx1
	double kx2m = 0;
	// модификация kx1
	double ky2m = 0;
	// начальная координата x, y
	double x0, y0;
	// текущая координата x, y 
	double x, y;
	// предыдущая координата x, y 
	double ox, oy;
	// текущая скорость Vx, Vy, V
	double Vx, Vy, V;
	// максимальная скорость
	double V_max;
	// время	
	double t, dt;
	// масштабные множетели
	double mX, mT;
	// масштабные координаты
	int X, Y;
	// масштабные координаты
	int oX, oY;
	// энергия потенциальная, кинетическая, полная
	double Ep, Ek, E;
	// максимальная энергия
	double E_max;
	// трение сухое
	double friction;
	//вязкое трение
	double viscous_x;
	double viscous_y;
	//коэф
	double kx1, kx2, ky1, ky2, dl1, dl2, dl3, dl4;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	//=====================================
	/*double Fx(double t, double x, double y, double vx, double vy);
	double Fy(double t, double x, double y, double vx, double vy);
	double Fy(double t, double x, double y, double vx, double vy);*/
	//===========================================
	double ax(double t, double x, double y, double vx, double vy);
	double ay(double t, double x, double y, double vx, double vy);
	RKresult RKMethod(double t, double x, double y, double vx, double vy);	// метод Рунге-Кутта для 1 и 2 случая
	void DrawTraectory(CDC *pDc, CRect r);
	void DrawOscillator4(CDC *pDc, CRect r);
	void DrawSpringX(CDC *pDc, CRect r, int x1, int y1, int  x2, int y2);
	void DrawSpringY(CDC* pDc, CRect r, int x1, int y1, int  x2, int y2);
	void DrawVGraf(CDC *pDc, CRect r);
	void DrawEGraf(CDC *pDc, CRect r);
	void DrawX(CDC* pDc, CRect r);
	void DrawY(CDC* pDc, CRect r);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnStnClickedMain();
	afx_msg void OnEnChangeX0();
	afx_msg void OnEnChangeVy0();
	
	afx_msg void OnBnClickedBpkx1();
	afx_msg void OnBnClickedBpkx2();
	afx_msg void OnBnClickedBpky1();
	afx_msg void OnBnClickedBpky2();
	// Кэф вязкого трения
	double ViscousK;
};
