
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
	bool CRead(const CString &buffer);
	
	void COutput();
	void CFillThisWeekArr();
	void CFillNextWeekArr();
	void CFillWorkerArr();
	void CFillWorkerPresArr();
	CString CPointChange(const CString &buffer);
	std::list<CString> m_arrThisWeek;
	std::list<CString> m_arrNextWeek;
	std::list<CString> m_arrWorker;
	std::list<CString> m_arrWorkerPres;
	std::list<CPlan> m_arr;
	std::list<CString> CSort();
	
private:

	c_m_WorkerPres m_listWorkerPres;
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
