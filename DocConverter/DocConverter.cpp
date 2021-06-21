
// DocConverter.cpp: определяет поведение классов для приложения.
//

#include "pch.h"
#include "framework.h"
#include "DocConverter.h"
#include "DocConverterDlg.h"
#include "Change.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
void CViewWholeBuffer(int& pos, int& i, int& count, CString &buf);
void CPointNameK(const CString& elem, int& pos, int&i, CString& buf);
void CPointThisK(const CString& elem, int& pos, int&i, CString& buf);
void CPointNextK(const CString& elem, int& pos, int&i, CString& buf);
void CPosSetting(const CString& buffer, int& m_posThis, int& m_posNext, int& m_posWrite, int& i);
bool CFindThisWeek(const CString& buffer, const int& i, const int& m_posThis);
bool CFindNextWeek(const CString& buffer, const int& i, const int& m_posThis);
void CWriteInList(const CString& buffer, const int& m_posThis, const int& m_posNext, const int& m_posWrite,
	const bool& m_flagThis, const bool& m_flagNext, const int& i, bool m_flagSame);
bool CThereIsTheSame(std::list <CPlan> m_arr, CString buffer, int i);
void EnoughPeople(std::list<CPlan> m_arr, std::list<CString> m_arrWorkerPres);
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

bool CDocConverterApp::CRead(const CString &buffer) {
	bool m_flag = false, m_planFlag = false, m_flagSame = false;
	int posThis = 0, posNext = 0, pos = 0;
	for (int i = 0; i < buffer.GetLength(); i++) { // новая запись
		if (buffer[i] == '[') {
			m_flag = true;
			m_planFlag = true;
		}
		else if (buffer[i] == ']' && m_flag) { //запись имени
			m_flagSame = CThereIsTheSame(m_arr, buffer, i);
			if (!m_flagSame) {
				CPlan Node;
				i = Node.NameFunc(buffer, i);
				m_arr.push_back(Node);
				m_flag = false;
			}
			else {
				i = buffer.Find('@', i + 1) + 1;
				m_flag = false;
			}
		}
		else if (m_planFlag && !m_flag) { // запись этой и след недели
			bool m_flagThis = false;
			bool m_flagNext = false;
			int m_posThis, m_posNext, m_posWrite;
			CPosSetting(buffer, m_posThis, m_posNext, m_posWrite, i);
			if (m_posThis < m_posWrite || m_posNext < m_posWrite) {
				m_flagThis = CFindThisWeek(buffer, i, m_posThis);
				m_flagNext = CFindNextWeek(buffer, i, m_posThis);
			}
			CWriteInList(buffer, m_posThis, m_posNext, m_posWrite, m_flagThis, m_flagNext, i, m_flagSame);
			i = m_posWrite-1;
			m_planFlag = false;
		}
	}
	for (const auto &elem : NodeList.DocName) { // add DocName list
		int flag = 0;
		for (const auto &element : m_arr) {
			if (elem == element.GetName()) {
				flag = 1;
			}	
		}
		if (flag == 0) {
			CPlan Node;
			Node.SetName(elem);
			Node.SetThis_Week(L" ");
			Node.SetNext_Week(L" ");
			m_arr.push_back(Node);
		}
	}
	return !m_arr.empty();
}

void CPosSetting(const CString& buffer, int& m_posThis, int& m_posNext, int& m_posWrite, int& i) {
	m_posThis = buffer.Find('@', i + 1);
	m_posNext = buffer.Find('@', m_posThis + 1);
	m_posWrite = buffer.Find('[', i + 1);
	if (m_posWrite == -1) {
		m_posWrite = buffer.GetLength();
	}
}
bool CFindThisWeek(const CString& buffer, const int& i, const int& m_posThis) {
	for (const auto& elem : theApp.NodeList.ThisWeek) { // add ThisWeek list
		int k = buffer.Mid(i + 1, m_posThis - i).Find(elem);
		if (k != -1) {
			return true;
		}
	}
	return false;
}
bool CFindNextWeek(const CString& buffer, const int& i, const int& m_posThis) {
	for (const auto& elem : theApp.NodeList.NextWeek) { //add NextWeek list
		int k = buffer.Mid(i + 1, m_posThis - i).Find(elem);
		if (k != -1) {
			return true;
		}
	}
	return false;
}

void CWriteInList(const CString& buffer, const int& m_posThis, const int& m_posNext, const int& m_posWrite, 
	const bool& m_flagThis, const bool& m_flagNext, const int& i, bool m_flagSame) {
	if (m_flagThis) {
		int ptr;
		for (const auto& first : theApp.NodeList.NextWeek) { // add NextWeek list
			ptr = buffer.Mid(m_posThis, m_posNext + 1 - m_posThis).Find(first);
			if (ptr != -1) {
				theApp.m_arr.back().This_WeekFunc(buffer.Mid(m_posThis + 1, ptr - 2));
				theApp.m_arr.back().Next_WeekFunc(buffer.Mid(m_posNext + 1, m_posWrite - m_posNext - 2));
				break;
			}
		}
		if (ptr == -1) {
			if (m_flagSame) {
				theApp.m_arr.back().This_WeekFunc(buffer.Mid(m_posThis + 1, m_posWrite - m_posThis - 2));
			}
			else {
				theApp.m_arr.back().Next_WeekFunc(L" ");
				theApp.m_arr.back().This_WeekFunc(buffer.Mid(m_posThis + 1, m_posWrite - m_posThis - 2));
			}
		}
	}
	else if (m_flagNext) {
		int ptr;
		for (const auto& first : theApp.NodeList.ThisWeek) { // add ThisWeek list
			ptr = buffer.Mid(m_posThis, m_posNext + 1 - m_posThis).Find(first);
			if (ptr != -1) {
				theApp.m_arr.back().Next_WeekFunc(buffer.Mid(m_posThis + 1, ptr - 2));
				theApp.m_arr.back().This_WeekFunc(buffer.Mid(m_posNext + 1, m_posWrite - m_posNext - 2));
				break;
			}
		}
		if (ptr == -1) {
			if (m_flagSame) {
				theApp.m_arr.back().Next_WeekFunc(buffer.Mid(m_posThis + 1, m_posWrite - m_posThis - 2));
			}
			else {
				theApp.m_arr.back().This_WeekFunc(L" ");
				theApp.m_arr.back().Next_WeekFunc(buffer.Mid(m_posThis + 1, m_posWrite - m_posThis - 2));
			}
		}
	}
	else {
		theApp.m_arr.back().This_WeekFunc(buffer.Mid(i + 1, m_posWrite - i - 2));
		theApp.m_arr.back().Next_WeekFunc(L" ");
	}
}



void CDocConverterApp::COutput() {
	CData newData;
	EnoughPeople(m_arr, NodeList.DocName); //add DocName list
	std::list<CString> m_temp = theApp.CSort();
	CStdioFile output;
	CString sFile, sPath, sNumber;
	int j = 0;
	GetModuleFileName(NULL, sFile.GetBufferSetLength(MAX_PATH), MAX_PATH);// поиск пути к файлу
	int pos = sFile.ReverseFind('\\');
	sPath = sFile.Left(pos + 1);
	sPath = sPath + _T("Отчет по работе отдела разработки ПО.rtf");
	output.Open(sPath, CFile::modeCreate|CFile::modeReadWrite|CFile::shareDenyWrite); //1) создаем файл 2) на чтение и запись 3) разрешаем запись
//	output.WriteString(L"№ ; Сотрудник; Темы этой недели; Темы следующей недели \n");
	output.WriteString(L"{\\rtf1 \n \\par ");
	output.WriteString(L"{\\viewkind4\\uc1 \\pard\\sa200\\sl276\\slmult1\\qc\\b Отдел разработки ПО\\par}");
	output.WriteString(L"{\\viewkind4\\uc1 \\pard\\sa200\\sl276\\slmult1\\qc Отчет по работе за неделю: ");
	output.WriteString(newData.MakeThisWeek());
	output.WriteString(L". План по работе на неделю: ");
	output.WriteString(newData.MakeNextWeek());
	output.WriteString(L".\\par}");
	output.WriteString(L"\\trowd \\trql\\trgaph108\\trrh280\\trleft36 \\clbrdrt\\brdrth \\clbrdrl\\brdrth \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx1036\\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx3536\\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx7036 \\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx10036\\pard\\intbl ");
	output.WriteString(L"№");
	output.WriteString(L" \\cell \\pard \\intbl ");
	output.WriteString(L"Сотрудник");
	output.WriteString(L" \\cell \\pard  \\intbl ");
	output.WriteString(L"Эта неделя");
	output.WriteString(L" \\cell \\pard  \\intbl ");
	output.WriteString(L"Следующая неделя");
	output.WriteString(L" \\cell \\pard  \\intbl \\row ");
	for (const auto& element : m_temp) {
		for (const auto &elem : m_arr) { //для всех элементов из m_arr
			if (element == elem.GetName()) {
				j++;
				output.WriteString(L"\\trowd \\trql\\trgaph108\\trrh280\\trleft36 \\clbrdrt\\brdrth \\clbrdrl\\brdrth \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx1036\\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx3536\\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx7036 \\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx10036\\pard\\intbl ");
				sNumber.Format(L"%d", j);
				output.WriteString(sNumber);
				output.WriteString(L" \\cell \\pard \\intbl ");
				output.WriteString(elem.GetName());
				output.WriteString(L" \\cell \\pard  \\intbl ");
				output.WriteString(elem.GetThis_Week());
				output.WriteString(L" \\cell \\pard  \\intbl ");
				output.WriteString(elem.GetNext_Week());
				output.WriteString(L" \\cell \\pard  \\intbl \\row ");
			}
		}
	}
	output.WriteString(L"\\pard }");
	output.Close();
	ShellExecute(0, L"open", sPath, 0, L"", SW_SHOW); //открытие .csv через устройство по умолчанию
}




CString CDocConverterApp::CPointChange(const CString &buffer){ 
	CString buf;
	buf = buffer;
	int i = 0, pos = 0;
	int count = buf.GetLength();
	pos = buf.Find('[', pos);
	CViewWholeBuffer(pos, i, count, buf);
	return buf;
}
void CViewWholeBuffer(int& pos, int& i, int& count, CString &buf) {
	while (pos < count - 1) {
		pos = buf.Find('[', pos + 1);
		for (const auto &elem : theApp.NodeList.Name) { //add Name list
			CPointNameK(elem, pos, i, buf);
		}
		for (const auto& elem : theApp.NodeList.ThisWeek) { // add ThisWeek list
			CPointThisK(elem, pos, i, buf);
		}
		for (const auto& element : theApp.NodeList.NextWeek) { //add NextWeek list
			CPointNextK(element, pos, i, buf);
		}
	}
	
}

void CPointNameK(const CString& elem, int& pos, int&i, CString& buf) {
		int j;
		j = buf.Find(elem, i);
		if (j != -1 && j < pos) {
			i = j + elem.GetLength();
			if (buf.GetAt(i) != '@') {
				if (buf.GetAt(i) != ' ') {
					buf.Delete(i);
				}
				buf.Insert(i, '@');
			}
			return;
	}
	return;
}
void CPointThisK(const CString& elem, int& pos, int&i, CString& buf) {
	int j;
	j = buf.Find(elem, i);
	if (j != -1 && j < pos) {
		i = j + elem.GetLength();
		int s = buf.Mid(i+1).FindOneOf(L"АБВГДЕЁЖЗИКЛМНОПРСТУФХЦШЩЬЪЫЭЮЯабвгдеёжзиклмнопрстуфхцчшщьыъэюя-123456789");
		for (int p = i; p <= s + i+1; p++) {
			if (buf.GetAt(p) == '\r') {
				buf.SetAt(p, ' ');
			}
		}
		if (buf.GetAt(i) != '@') {
			if (buf.GetAt(i) != ' ') {
				buf.Delete(i);
			}
			buf.Insert(i, '@');
		}
		return;
	}
	return;
}
void CPointNextK(const CString& elem, int& pos, int&i, CString& buf) {
	int j;
	j = buf.Find(elem, i);
	if (j != -1 && j < pos) {
		i = j + elem.GetLength();
		int s = buf.Mid(i+1).FindOneOf(L"АБВГДЕЁЖЗИКЛМНОПРСТУФХЦШЩЬЪЫЭЮЯабвгдеёжзиклмнопрстуфхцчшщьыъэюя-123456789");
		for (int p = i; p <= s + i+1; p++) {
			if (buf.GetAt(p) == '\r') {
				buf.SetAt(p, ' ');
			}
		}
		if (buf.GetAt(i) != '@') {
			if (buf.GetAt(i) != ' ') {
				buf.Delete(i);
			}
			buf.Insert(i, '@');
		}
		return;
	}
	return;
}


std::list<CString> CDocConverterApp::CSort() {
	std::list<CString> m_temp;
	for (int k = 0; k < NodeList.DocName.size(); k++) { //add DocName list
		m_temp.push_back(L"ЯЯ");
		for (auto& elem : NodeList.DocName) { //add DocName list
			if (m_temp.back() > elem) {
				m_temp.pop_back();
				m_temp.push_back(elem);
			}
		}
		std::list<CString>::iterator it;
		it = NodeList.DocName.begin(); //add DocName list
		while(it != NodeList.DocName.end()) { //add DocName list
			if (m_temp.back() == *it) {
				*it = L"ЯЯЯ";
			}
			it++;
		}
	}
	return m_temp;
}

bool CThereIsTheSame(std::list <CPlan> m_arr, CString buffer, int i) {
	int pos = buffer.Find('@', i + 1);
	int counter = 0;
	for (const auto& elem : theApp.NodeList.Name) { // add Name list
		int k = buffer.Mid(i + 1, pos - 1 - i).Find(elem);
		if (k != -1) {
			break;
		}
		counter++;
	}
	for (const auto& elem : theApp.NodeList.DocName) { // add DocName list
		if (counter == 0) {
			for (const auto& element : m_arr) {
				if (element.GetName() == elem) {
					return true;
				}
			}
		}
		counter--;
	}
	return false;
}
void EnoughPeople(std::list<CPlan> m_arr, std::list<CString> m_arrWorkerPres) {
	int flag = 1;
	for (const auto &elem : m_arrWorkerPres) {
		for (const auto &element : m_arr) {
			if (elem == element.GetName()) {
				flag = 0;
			}
			else if(elem != element.GetName() && flag == 1){
				flag = 1;
			}
		}
		if (flag == 1) {
			CPlan Node;
			Node.NameFunc(elem, elem.GetLength());
			m_arr.push_back(Node);
		}
	}
	return;
}