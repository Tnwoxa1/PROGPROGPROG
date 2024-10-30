
// DESS.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CDESSApp:
// Сведения о реализации этого класса: DESS.cpp
//

class CDESSApp : public CWinApp
{
public:
	CDESSApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CDESSApp theApp;
