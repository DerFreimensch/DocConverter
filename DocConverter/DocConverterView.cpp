
// DocConverterView.cpp: реализация класса CDocConverterView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "DocConverter.h"
#endif

#include "DocConverterDoc.h"
#include "CntrItem.h"
#include "resource.h"
#include "DocConverterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDocConverterView

IMPLEMENT_DYNCREATE(CDocConverterView, CRichEditView)

BEGIN_MESSAGE_MAP(CDocConverterView, CRichEditView)
	ON_WM_DESTROY()
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CRichEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

// Создание или уничтожение CDocConverterView

CDocConverterView::CDocConverterView() noexcept
{
	// TODO: добавьте код создания
	

}

CDocConverterView::~CDocConverterView()
{
}

BOOL CDocConverterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CDocConverterView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();


	// Задайте границы печати (720 твип = 1/2 дюйма)
	SetMargins(CRect(720, 720, 720, 720));
}


// Печать CDocConverterView

BOOL CDocConverterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}


void CDocConverterView::OnDestroy()
{
	// Деактивируйте элемент при удалении; это важно
	// в случае использования представления разделителя
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != nullptr && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == nullptr);
   }
   CRichEditView::OnDestroy();
}



// Диагностика CDocConverterView

#ifdef _DEBUG
void CDocConverterView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CDocConverterView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CDocConverterDoc* CDocConverterView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDocConverterDoc)));
	return (CDocConverterDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CDocConverterView
