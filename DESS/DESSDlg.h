
// DESSDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CDESSDlg
class CDESSDlg : public CDialogEx
{
// Создание
public:
	CDESSDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DESS_DIALOG };
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
	CString PlainText;
	CString CipherText;
	afx_msg void OnBnClickedEncrypButton();
	afx_msg void OnBnClickedDecrypbutton();
	CString FILEIN;
	CString FILEOUT;
	//CString FILEIN1;
	CString FILEOUT1;
	CFile OpenText;
	CFile OpenText1;
	CFile ShifrText1;
	CFile ShifrText;
	CFile OPT;
	CFile SHT;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	CButton rbt1;
	CButton rbt2;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	CEdit FileIn;
	CEdit FileOut;
	CString FILEIN1;
	int RSAn;
	int RSAe;
	int RSAd;
};
