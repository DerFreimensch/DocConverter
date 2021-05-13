
// DocConverterDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "DocConverter.h"
#include "DocConverterDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CDocConverterDlg



CDocConverterDlg::CDocConverterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DOCCONVERTER_DIALOG, pParent)
	, m_text(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_DOC);
}

void CDocConverterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_button_convert);
	DDX_Control(pDX, IDC_EDIT1, m_textbox);
	DDX_Text(pDX, IDC_EDIT1, m_text);
}

BEGIN_MESSAGE_MAP(CDocConverterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDocConverterDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CDocConverterDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// Обработчики сообщений CDocConverterDlg

BOOL CDocConverterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CDocConverterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CDocConverterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CDocConverterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void  CDocConverterDlg::OnSize(UINT nType, int cx, int cy) {
	CDialog::OnSize(nType, cx, cy);
	CRect m_cbutton;
	CRect m_ctext;
	if (m_button_convert.GetSafeHwnd() != 0 && m_textbox.GetSafeHwnd()!= 0) {
		m_button_convert.GetWindowRect(m_cbutton);
		m_textbox.GetWindowRect(m_ctext);
		//MoveWindow(cr.left, cr.top, cr.right-cr.left, cr.bottom - cr.top);
		m_button_convert.MoveWindow(10, cy - 10 - m_cbutton.Height(), cx - 30, m_cbutton.Height());
		m_textbox.MoveWindow(10, 10, cx - 30, cy - 40 - m_cbutton.Height());
	}
}


void CDocConverterDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	//GetDlgItemText(IDC_EDIT1, m_text);
	UpdateData(TRUE);
	m_text += '[';
	m_text.Replace('\n', ' ');
	m_text.Replace('"', '\'');
	theApp.CFillThisWeekArr();
	theApp.CFillNextWeekArr();
	theApp.CFillWorkerArr();
	theApp.CFillWorkerPresArr();
	//CDialogEx::OnOK();
	if (theApp.CRead(theApp.CPointChange(m_text))) {
		theApp.COutput();
		AfxMessageBox(L"Готово!"); 
	}
	else {
		AfxMessageBox(L"Что то не так!");
	}

	//UpdateData(FALSE);
}


void CDocConverterDlg::OnEnChangeEdit1()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
	
}

