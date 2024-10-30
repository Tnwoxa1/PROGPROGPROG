
// Oscillator4.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// основные символы


// COscillator4App:
// Сведения о реализации этого класса: Oscillator4.cpp
//

class COscillator4App : public CWinApp
{
public:
	COscillator4App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern COscillator4App theApp;
