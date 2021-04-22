
// DocConverter.cpp: определяет поведение классов для приложения.
//

#include "pch.h"
#include "framework.h"
#include "DocConverter.h"
#include "DocConverterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDocConverterApp

BEGIN_MESSAGE_MAP(CDocConverterApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// Создание CDocConverterApp

CDocConverterApp::CDocConverterApp()
{
	// поддержка диспетчера перезагрузки
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
	setlocale(LC_ALL, "Russian");
	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}


// Единственный объект CDocConverterApp

CDocConverterApp theApp;


// Инициализация CDocConverterApp

BOOL CDocConverterApp::InitInstance()
{
	// InitCommonControlsEx() требуется для Windows XP, если манифест
	// приложения использует ComCtl32.dll версии 6 или более поздней версии для включения
	// стилей отображения.  В противном случае будет возникать сбой при создании любого окна.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Выберите этот параметр для включения всех общих классов управления, которые необходимо использовать
	// в вашем приложении.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Создать диспетчер оболочки, в случае, если диалоговое окно содержит
	// представление дерева оболочки или какие-либо его элементы управления.
	CShellManager *pShellManager = new CShellManager;

	// Активация визуального диспетчера "Классический Windows" для включения элементов управления MFC
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Стандартная инициализация
	// Если эти возможности не используются и необходимо уменьшить размер
	// конечного исполняемого файла, необходимо удалить из следующих
	// конкретных процедур инициализации, которые не требуются
	// Измените раздел реестра, в котором хранятся параметры
	// TODO: следует изменить эту строку на что-нибудь подходящее,
	// например на название организации
	SetRegistryKey(_T("Локальные приложения, созданные с помощью мастера приложений"));






	CDocConverterDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Введите код для обработки закрытия диалогового окна
		//  с помощью кнопки "ОК"
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Введите код для обработки закрытия диалогового окна
		//  с помощью кнопки "Отмена"
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Предупреждение. Не удалось создать диалоговое окно, поэтому работа приложения неожиданно завершена.\n");
		TRACE(traceAppMsg, 0, "Предупреждение. При использовании элементов управления MFC для диалогового окна невозможно #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Удалить диспетчер оболочки, созданный выше.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Поскольку диалоговое окно закрыто, возвратите значение FALSE, чтобы можно было выйти из
	//  приложения вместо запуска генератора сообщений приложения.
	return FALSE;
}

bool CDocConverterApp::Read(const CString &buffer) {
	bool m_flag = false, m_planFlag = false;
	int posThis = 0, posNext = 0, pos = 0;
	for (int i = 0; i < buffer.GetLength(); i++) {
		if (buffer[i] == '[') {
			m_flag = true;
			m_planFlag = true;
		}
		else if (buffer[i] == ']' && m_flag) {
			CPlan Node;
			i = Node.NameFunc(buffer, i);
			m_arr.push_back(Node);
			m_flag = false;
		}
		else if (m_planFlag && !m_flag) {
			bool m_flagThis = false;
			bool m_flagNext = false;
			int m_posThis, m_posNext, m_posWrite;
			m_posThis = buffer.Find(':', i+1);
			m_posNext = buffer.Find(':', m_posThis+1);
			m_posWrite = buffer.Find('[', i + 1);
			for (const auto& elem : m_arrThisWeek) {
				int k = buffer.Mid(i + 1, m_posThis - i).Find(elem);
				if (k != -1) {
					m_flagThis = true;
				}
			}
			for (const auto& elem : m_arrNextWeek) {
				int k = buffer.Mid(i+1, m_posThis - i).Find(elem);
				if (k != -1) {
					m_flagNext = true;
				}
			}
			if (m_flagThis) {
				int ptr;
				for (const auto& first : m_arrNextWeek) {
					ptr = buffer.Mid(m_posThis, m_posNext + 1 - m_posThis).Find(first);
					if (ptr != -1) {
						m_arr.back().This_WeekFunc(buffer.Mid(m_posThis+1, ptr-3));
						m_arr.back().Next_WeekFunc(buffer.Mid(m_posNext+1, m_posWrite - m_posNext - 3));
						break;
					}
				}	
				if (ptr == -1) {
					m_arr.back().This_WeekFunc(buffer.Mid(m_posThis + 1, m_posWrite - m_posThis - 3));
					TRACE(L"this week = %s\n", m_arr.back().GetThis_Week());
				}
			}
			else if (m_flagNext) {
				int ptr;
				for (const auto& first : m_arrThisWeek) {
					ptr = buffer.Mid(m_posThis, m_posNext+1 - m_posThis).Find(first);
					if (ptr != -1) {
						m_arr.back().Next_WeekFunc(buffer.Mid(m_posThis+1, ptr-3));
						m_arr.back().This_WeekFunc(buffer.Mid(m_posNext+1, m_posWrite - m_posNext -3));
						break;
					}
				}
				if (ptr == -1) {
					m_arr.back().This_WeekFunc(buffer.Mid(m_posThis + 1, m_posWrite - m_posThis - 3));
				}
			}
			else {
				m_arr.back().This_WeekFunc(buffer.Mid(i + 1, m_posWrite - i - 3));
			}
			i = m_posWrite-1;
			m_planFlag = false;
		}
	}
	return !m_arr.empty();
}
void CDocConverterApp::Output() {
	//std::ofstream out("C:\\Users\\MKD\\Desktop\\Output.csv");
	CStdioFile output;
	output.Open(L"C:\\Users\\MKD\\Desktop\\Output.csv", CFile::modeCreate|CFile::modeReadWrite|CFile::shareDenyWrite); //1) создаем файл 2) на чтение и запись 3) разрешаем запись
	for (const auto &elem: m_arr) { //для всех элементов из m_arr
		//output.WriteString(L"\"");
		output.WriteString(elem.GetName());
		output.WriteString(L";\"");
		for (int i = 0; i < elem.GetThis_Week().GetLength(); i++) {
			if (elem.GetThis_Week().GetAt(i) == '@') {
				elem.GetThis_Week().SetAt(i, '"');
			}
		}
		output.WriteString(elem.GetThis_Week());
		output.WriteString(L"\";\"");
		for (int i = 0; i < elem.GetNext_Week().GetLength(); i++) {
			if (elem.GetNext_Week().GetAt(i) == '@') {
				elem.GetNext_Week().SetAt(i, '"');
			}
		}
		output.WriteString(elem.GetNext_Week());
		output.WriteString(L"\";\n");
	}
	output.Close();
	ShellExecute(0, L"open", L"C:\\Users\\MKD\\Desktop\\Output.csv", 0, 0, SW_SHOW); //открытие .csv через устройство по умолчанию
}

void CDocConverterApp::FillThisWeekArr() {
	m_arrThisWeek.push_back(m_listThis.m_tw1);
	m_arrThisWeek.push_back(m_listThis.m_tw2);
	m_arrThisWeek.push_back(m_listThis.m_tw3);
}
void CDocConverterApp::FillNextWeekArr() {
	m_arrNextWeek.push_back(m_listNext.m_nw1);
	m_arrNextWeek.push_back(m_listNext.m_nw2);
	m_arrNextWeek.push_back(m_listNext.m_nw3);
	m_arrNextWeek.push_back(m_listNext.m_nw4);
	m_arrNextWeek.push_back(m_listNext.m_nw5);
	m_arrNextWeek.push_back(m_listNext.m_nw6);
	m_arrNextWeek.push_back(m_listNext.m_nw7);
	m_arrNextWeek.push_back(m_listNext.m_nw8);
}