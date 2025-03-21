
// MyDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Shashki.h"
#include "MyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно MyDlg



MyDlg::MyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHASHKI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void MyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_GAME_MODE, CBGameMode);
	DDX_Control(pDX, IDOK, OkCtr);
	//  DDX_Control(pDX, IDC_BESTSCORE, BSctr);
	//  DDX_Control(pDX, IDC_BESTSCORE2, ScoresList);
	//  DDX_Control(pDX, IDC_BUTTON2, but_save);
	DDX_Control(pDX, IDC_BUTTON2, but_load);
	DDX_Control(pDX, IDC_BUTTON3, but_save);
	DDX_Control(pDX, IDC_EDIT1, info_educate);
	DDX_Control(pDX, IDC_EDIT2, num_max_generation);
	DDX_Control(pDX, IDC_NUMGENER, str_50);
}

BEGIN_MESSAGE_MAP(MyDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &MyDlg::OnBnClickedOk)
	//ON_COMMAND(ID_32771, &MyDlg::On32771)
	//ON_COMMAND(ID_32773, &MyDlg::On32773)
	//ON_COMMAND(ID_MENU_LOAD, &MyDlg::OnMenuLoad)
	//ON_COMMAND(ID_32776, &MyDlg::OnSaveAll)
	//ON_COMMAND(ID_32777, &MyDlg::OnLoadAll)
	ON_WM_TIMER()
	//ON_MESSAGE(MS_FILLBOT, &MyDlg::OnMsFillBot)
	//ON_COMMAND(ID_FORCED_TRAIN, &MyDlg::OnForcedTrain)
	ON_BN_CLICKED(IDC_BUTTON3, &MyDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &MyDlg::OnBnClickedButton2)
	ON_CBN_SELCHANGE(IDC_COMBO_GAME_MODE, &MyDlg::OnCbnSelchangeComboGameMode)
END_MESSAGE_MAP()


// Обработчики сообщений MyDlg

BOOL MyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	CBGameMode.InsertString(-1, L"Игра человек-человек");
	CBGameMode.InsertString(-1, L"Игра человек-нейросеть");
	CBGameMode.InsertString(-1, L"Игра нейросеть-человек");
	CBGameMode.InsertString(-1, L"Обучение");
	CBGameMode.SetCurSel(0);

	but_load.ShowWindow(SW_HIDE);
	but_save.ShowWindow(SW_HIDE);
	OkCtr.SetWindowTextW(L"Начать игру");
	info_educate.ShowWindow(SW_HIDE);

	num_max_generation.SetWindowTextW(L"50");
	num_max_generation.ShowWindow(SW_HIDE);
	str_50.ShowWindow(SW_HIDE);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void MyDlg::OnPaint()
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
//HCURSOR MyDlg::OnQueryDragIcon()
//{
//	return static_cast<HCURSOR>(m_hIcon);
//}
//
//LRESULT MyDlg::OnMsFillBot(WPARAM wParam, LPARAM lParam)
//{
//	trainer.FillOut();
//
//	return LRESULT();
//}


void MyDlg::FillInfo()
{
	int curtime = (clock() - trainer.StartTime) / 1000;
	int h = curtime / 3600;
	int m = (curtime % 3600) / 60;
	int s = curtime % 60;
	CString str, str2;
	/*str.Format(L"Лучший счет: %d\r\nИгр сыграно: %d\r\nПоколение: %d\r\nХоды: %d\r\n Время: %d : %d : %d",
		trainer.BestScore, trainer.GamesCount, trainer.GenerationCount, trainer.hod, h, m, s);*/
	str.Format(L"Лучший счет: %d\r\nПоколение: %d",
		trainer.BestScore, trainer.GenerationCount);
	//BSctr.SetWindowTextW(str);
	info_educate.SetWindowTextW(str);

	str.Format(L"");
	for (int i = 0; i < 10; i++)
	{
		str2.Format(L"%d, ", trainer.scores[i]);
		str += str2;
	}
	str += L"\r\n";
	for (int i = 10; i < 20; i++)
	{
		str2.Format(L"%d, ", trainer.scores[i]);
		str += str2;
	}
	str += L"\r\n";
	for (int i = 20; i < 29; i++)
	{
		str2.Format(L"%d, ", trainer.scores[i]);
		str += str2;
	}
	str2.Format(L"%d ", trainer.scores[29]);
	str += str2;
	//ScoresList.SetWindowTextW(str);
}

DWORD WINAPI TrainingThreadFunc(LPVOID p)
{
	srand(time(NULL));
	MyDlg* dlg = (MyDlg*)p;
	dlg->OkCtr.EnableWindow(FALSE);
	dlg->trainer.train();
	dlg->KillTimer(dlg->timerid);
	dlg->OkCtr.EnableWindow(TRUE);
	dlg->SendMessage(MS_FILLBOT);
	dlg->FillInfo();
	return 0;
}

void MyDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	int id = CBGameMode.GetCurSel();
	if (id == -1)return;

	CString str;
	CBGameMode.GetLBText(id, str);

	GameDlg dlg;
	if (str == L"Игра человек-человек")
	{
		dlg.gm = pvp;
	}
	else
		if (str == L"Игра человек-нейросеть")
		{
			dlg.gm = pvn;
		}
		else
			if (str == L"Игра нейросеть-человек")
			{
				dlg.gm = nvp;
			}
			else 
				if (str == L"Обучение")
				{
					//if (ftd.DoModal() != IDOK)return;

					TerminateThread(TrainingThread, 0);
					CloseHandle(TrainingThread);
					KillTimer(timerid);

					num_max_generation.GetWindowTextW(str);
					int gener = _wtoi(str);
					if (gener <= 0)
					{
						MessageBox(L"Введите количество поколений больше 0", L"Error!");
						return;
					}
					trainer.ForceToTrain(gener);

					TrainingThread = CreateThread(NULL, NULL, TrainingThreadFunc, this, NULL, NULL);
					timerid = SetTimer(123, 25, NULL);
					return;
				}
	dlg.name = str;

	CRect rect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
	dlg.posx = rect.Width() / 2. - 400;
	dlg.posy = 50;
	dlg.bot = trainer.OutNW;
	

	dlg.DoModal();
}

//сохранить
//void MyDlg::On32771()
//{
//	// TODO: добавьте свой код обработчика команд
//	trainer.SaveBest();
//}

////обучение
//void MyDlg::On32773()
//{
//	// TODO: добавьте свой код обработчика команд
//	TerminateThread(TrainingThread, 0);
//	CloseHandle(TrainingThread);
//	KillTimer(timerid);
//
//	TrainingThread = CreateThread(NULL, NULL, TrainingThreadFunc, this, NULL, NULL);
//	timerid = SetTimer(123, 25, NULL);
//}
//
//
//void MyDlg::OnMenuLoad()
//{
//	// TODO: добавьте свой код обработчика команд
//	trainer.Load();
//}
//
//
//void MyDlg::OnSaveAll()
//{
//	// TODO: добавьте свой код обработчика команд
//	trainer.SaveAll();
//}
//
//
//void MyDlg::OnLoadAll()
//{
//	// TODO: добавьте свой код обработчика команд
//	trainer.LoadALL();
//}


void MyDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	FillInfo();
	CDialogEx::OnTimer(nIDEvent);
}


//void MyDlg::OnForcedTrain()
//{
//	// TODO: добавьте свой код обработчика команд
//	if (ftd.DoModal() != IDOK)return;
//
//	TerminateThread(TrainingThread, 0);
//	CloseHandle(TrainingThread);
//	KillTimer(timerid);
//
//	trainer.ForceToTrain(ftd.n);
//
//	TrainingThread = CreateThread(NULL, NULL, TrainingThreadFunc, this, NULL, NULL);
//	timerid = SetTimer(123, 25, NULL);
//}


void MyDlg::OnBnClickedButton3()
{
	// TODO: добавьте свой код обработчика уведомлений
	trainer.SaveBest();
}


void MyDlg::OnBnClickedButton2()
{
	// TODO: добавьте свой код обработчика уведомлений
	trainer.Load();
}


void MyDlg::OnCbnSelchangeComboGameMode()
{
	// TODO: добавьте свой код обработчика уведомлений
	int id = CBGameMode.GetCurSel();
	if (id == -1)return;

	CString str;
	CBGameMode.GetLBText(id, str);

	if (str == L"Игра человек-человек")
	{
		but_load.ShowWindow(SW_HIDE);
		but_save.ShowWindow(SW_HIDE);
		OkCtr.SetWindowTextW(L"Начать игру");
		info_educate.ShowWindow(SW_HIDE);
		num_max_generation.ShowWindow(SW_HIDE);
		str_50.ShowWindow(SW_HIDE);
	}
	else
		if (str == L"Игра человек-нейросеть")
		{
			but_load.ShowWindow(SW_SHOW);
			but_save.ShowWindow(SW_HIDE);
			OkCtr.SetWindowTextW(L"Начать игру");
			info_educate.ShowWindow(SW_HIDE);
			num_max_generation.ShowWindow(SW_HIDE);
			str_50.ShowWindow(SW_HIDE);
		}
		else
			if (str == L"Игра нейросеть-человек")
			{
				but_load.ShowWindow(SW_SHOW);
				but_save.ShowWindow(SW_HIDE);
				OkCtr.SetWindowTextW(L"Начать игру");
				info_educate.ShowWindow(SW_HIDE);
				num_max_generation.ShowWindow(SW_HIDE);
				str_50.ShowWindow(SW_HIDE);
			}
			else
				if (str == L"Обучение")
				{
					but_load.ShowWindow(SW_HIDE);
					but_save.ShowWindow(SW_SHOW);
					OkCtr.SetWindowTextW(L"Начать обучение");
					info_educate.ShowWindow(SW_SHOW);
					num_max_generation.ShowWindow(SW_SHOW);
					str_50.ShowWindow(SW_SHOW);
				}
}
