
// CntrItem.cpp: реализация класса CDocConverterCntrItem
//

#include "pch.h"
#include "framework.h"
#include "DocConverter.h"

#include "DocConverterDoc.h"
#include "DocConverterView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Реализация CDocConverterCntrItem

IMPLEMENT_SERIAL(CDocConverterCntrItem, CRichEditCntrItem, 0)

CDocConverterCntrItem::CDocConverterCntrItem(REOBJECT* preo, CDocConverterDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: добавьте код для одноразового вызова конструктора
}

CDocConverterCntrItem::~CDocConverterCntrItem()
{
	// TODO: добавьте код очистки
}


// Диагностика CDocConverterCntrItem

#ifdef _DEBUG
void CDocConverterCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CDocConverterCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

