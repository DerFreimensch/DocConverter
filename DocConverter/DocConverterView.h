
// DocConverterView.h: интерфейс класса CDocConverterView
//

#pragma once

class CDocConverterCntrItem;

class CDocConverterView : public CRichEditView
{
protected: // создать только из сериализации
	CDocConverterView() noexcept;
	DECLARE_DYNCREATE(CDocConverterView)

// Атрибуты
public:
	CDocConverterDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // вызывается в первый раз после конструктора
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CDocConverterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // версия отладки в DocConverterView.cpp
inline CDocConverterDoc* CDocConverterView::GetDocument() const
   { return reinterpret_cast<CDocConverterDoc*>(m_pDocument); }
#endif

