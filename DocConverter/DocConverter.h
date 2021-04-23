﻿
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
	bool Read(const CString &buffer);
	void Output();
	void FillThisWeekArr();
	void FillNextWeekArr();
	void FillWorkerArr();
	void CPointChange(const CString &buffer);
private:
	std::list<CString> m_arrThisWeek;
	std::list<CString> m_arrNextWeek;
	std::list<CString> m_arrWorker;
	std::list<CPlan> m_arr;
	c_m_thisWeek m_listThis;
	c_m_nextWeek m_listNext;
	c_m_Worker m_listWorker;
	
// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CDocConverterApp theApp;
