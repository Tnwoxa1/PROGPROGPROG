
// RSADlg.h: файл заголовка
//

#pragma once
#include "rs.h"

// Диалоговое окно CRSADlg
class CRSADlg : public CDialogEx
{
// Создание
public:
	CRSADlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RSA_DIALOG };
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
	afx_msg void OnBnClickedButton2();
	unsigned int d;
	unsigned int e;
	unsigned int n;
	CEdit ctrE;
	CButton coding;
	CEdit ctrD;
	CEdit ctrN;
	CEdit DKey;
	afx_msg void OnBnClickedButton3();
	CString fpath1;
	CString fpath2;
	CString PubText;
	CString ClosedText;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
};
