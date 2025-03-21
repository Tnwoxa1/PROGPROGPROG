
// Potential_pitDlg.h: файл заголовка
//

#pragma once



// Диалоговое окно CPotentialpitDlg
class CPotentialpitDlg : public CDialogEx
{
// Создание
public:
	CPotentialpitDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POTENTIAL_PIT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:

	double sigmaX; //ширина купола по х
	double sigmaY;
	double muY; // смещение
	double muX; 
	double R; 
	int numWaves; //кол-во волн
	double dt;
	double dt_timer;
	bool timer; 
	bool thEvolutionDone;
	bool thCalculationDone;

	bool thUpdateDotDone;
	int x_dot;
	int y_dot;
	CSliderCtrl slider_y;
	CSliderCtrl slider_x;
	double weightX;
	double weightY;

	//???//
	int ind_wave;
	int ind_fft;


	//z -УДАЛИТЬ ЕСЛИ НЕ ПОНАДОБИТСЯ

	std::vector<std::vector<std::vector <complexld>>> wave; //волновые функции
	std::vector<std::vector<std::vector <complexld>>> wavefft; //волновые функции
	std::vector<std::vector <long double>> wave0; //волновые функции
	std::vector<std::vector<std::vector <complexld>>> spectrumCmplx; //спектр
	std::vector <long double> spectrumDouble; //модуль спектра
	void DrawWave(std::vector<std::vector <long double>> wave, int IDC);
	void DrawSpectrum(std::vector <long double> spectrum, int IDC);
	void UpdateDot();

	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent); //ЛОМАЕТ ПРОГРАММУ, ЧМОШНИК
	afx_msg void OnEnUpdatendot();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	
	
	afx_msg void OnEnUpdateydot();
	
};



