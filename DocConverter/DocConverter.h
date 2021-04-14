
// DocConverter.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// основные символы


// CDocConverterApp:
// Сведения о реализации этого класса: DocConverter.cpp
//

class CDocConverterApp : public CWinApp
{
public:
	CDocConverterApp();
	std::vector<Plan> Arr;

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CDocConverterApp theApp;
