
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
	void CPosSetting(const CString& buffer, int& m_posThis, int& m_posNext, int& m_posWrite, int& i);
	bool CFindWeek(const CString& buffer, const int& i, const int& m_posThis, const CString& elem);
	void CWriteInList(const CString& buffer, const int& m_posThis, const int& m_posNext, const int& m_posWrite, 
		const bool& m_flagThis, const bool& m_flagNext, const int& i);
	void COutput();
	void CFillThisWeekArr();
	void CFillNextWeekArr();
	void CFillWorkerArr();
	CString CPointChange(const CString &buffer); // выставляет правильные точки анализа текста
	void CViewWholeBuffer(int& pos, int& i, int& count, CString &buf); // просматриваем весь текст, внутри исполняется расстановка точек
	void CPointName(const CString& elem, int& pos, int&i, CString& buf);
	void CPointThis(const CString& elem, int& pos, int&i, CString& buf);
	void CPointNext(const CString& elem, int& pos, int&i, CString& buf);
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
