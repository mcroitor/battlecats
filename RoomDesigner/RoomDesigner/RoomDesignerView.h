
// RoomDesignerView.h : interface of the CRoomDesignerView class
//

#pragma once
#include "Room.h"


class CRoomDesignerView : public CView
{
protected: // create from serialization only
	CRoomDesignerView();
	DECLARE_DYNCREATE(CRoomDesignerView)

// Attributes
public:
	CRoomDesignerDoc* GetDocument() const;
	bool showgrid;
	bool showvalues;

	CImage sprite[4];

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
	virtual ~CRoomDesignerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEditBasket();
	afx_msg void OnEditPlate();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnContextAddplate();
	afx_msg void OnContextAddbasket();
	coord clickPos;
	afx_msg void OnViewShowgrid();
	afx_msg void OnIdcRemove();
	afx_msg void OnViewShowvalues();
};

#ifndef _DEBUG  // debug version in RoomDesignerView.cpp
inline CRoomDesignerDoc* CRoomDesignerView::GetDocument() const
   { return reinterpret_cast<CRoomDesignerDoc*>(m_pDocument); }
#endif

