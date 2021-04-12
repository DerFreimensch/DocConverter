
// DocConverterDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CDocConverterDlg
class CDocConverterDlg : public CDialogEx
{
// Создание
public:
	CDocConverterDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DOCCONVERTER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// Кнопка конвертирования текста в окне ввода
	CButton m_button_convert;
	afx_msg void OnBnClickedButton1();
	CEdit m_textbox;
	afx_msg void OnEnChangeEdit1();
	CString m_text;
};
