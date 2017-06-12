
// BattleCatsView.h : interface of the CBattleCatsView class
//

#pragma once


class CBattleCatsView : public CView
{
protected: // create from serialization only
	CBattleCatsView();
	DECLARE_DYNCREATE(CBattleCatsView)

// Attributes
public:
	CBattleCatsDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CBattleCatsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BattleCatsView.cpp
inline CBattleCatsDoc* CBattleCatsView::GetDocument() const
   { return reinterpret_cast<CBattleCatsDoc*>(m_pDocument); }
#endif

