
// RSA.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CRSAApp:
// Сведения о реализации этого класса: RSA.cpp
//

class CRSAApp : public CWinApp
{
public:
	CRSAApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CRSAApp theApp;
