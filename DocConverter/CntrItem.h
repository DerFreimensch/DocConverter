
// CntrItem.h: интерфейс класса CDocConverterCntrItem
//

#pragma once

class CDocConverterDoc;
class CDocConverterView;

class CDocConverterCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CDocConverterCntrItem)

// Конструкторы
public:
	CDocConverterCntrItem(REOBJECT* preo = nullptr, CDocConverterDoc* pContainer = nullptr);
		// Примечание. pContainer может иметь значение NULL для разрешения IMPLEMENT_SERIALIZE
		//  IMPLEMENT_SERIALIZE требует наличия у класса конструктора с
		//  нулевым аргументами.  Обычно элементы OLE создаются с
		//  указателями на документ, не равными NULL

// Атрибуты
public:
	CDocConverterDoc* GetDocument()
		{ return reinterpret_cast<CDocConverterDoc*>(CRichEditCntrItem::GetDocument()); }
	CDocConverterView* GetActiveView()
		{ return reinterpret_cast<CDocConverterView*>(CRichEditCntrItem::GetActiveView()); }

// Реализация
public:
	~CDocConverterCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

