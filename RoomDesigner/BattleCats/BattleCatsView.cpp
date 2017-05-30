
// BattleCatsView.cpp : implementation of the CBattleCatsView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "BattleCats.h"
#endif

#include "BattleCatsDoc.h"
#include "BattleCatsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBattleCatsView

IMPLEMENT_DYNCREATE(CBattleCatsView, CView)

BEGIN_MESSAGE_MAP(CBattleCatsView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CBattleCatsView construction/destruction

CBattleCatsView::CBattleCatsView()
{
	// TODO: add construction code here

}

CBattleCatsView::~CBattleCatsView()
{
}

BOOL CBattleCatsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CBattleCatsView drawing

void CBattleCatsView::OnDraw(CDC* /*pDC*/)
{
	CBattleCatsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CBattleCatsView printing

BOOL CBattleCatsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBattleCatsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBattleCatsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CBattleCatsView diagnostics

#ifdef _DEBUG
void CBattleCatsView::AssertValid() const
{
	CView::AssertValid();
}

void CBattleCatsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBattleCatsDoc* CBattleCatsView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBattleCatsDoc)));
	return (CBattleCatsDoc*)m_pDocument;
}
#endif //_DEBUG


// CBattleCatsView message handlers
