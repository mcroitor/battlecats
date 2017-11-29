
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
#include "StartDlg.h"
#include "..\libicat\icat.h"

#include <strsafe.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const size_t X_SHIFT = 250;
const size_t Y_SHIFT = 50;


// CBattleCatsView

IMPLEMENT_DYNCREATE(CBattleCatsView, CView)

BEGIN_MESSAGE_MAP(CBattleCatsView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_OPTIONS_LOADCATS, &CBattleCatsView::OnOptionsLoadcats)
	ON_COMMAND(ID_OPTIONS_START, &CBattleCatsView::OnOptionsStart)
END_MESSAGE_MAP()

// CBattleCatsView construction/destruction

CBattleCatsView::CBattleCatsView()
{
	// TODO: add construction code here
	sprite[BG].Load(L"images32/bg32.png");
	sprite[PLATE].Load(L"images32/plate32.png");
	sprite[FISH].Load(L"images32/fish32.png");
	sprite[BASKET].Load(L"images32/bed32.png");
	sprite[CAT].Load(L"images32/cat32.png");
	stage = 0;
	isPaused = false;
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

void CBattleCatsView::OnDraw(CDC* pDC)
{
	CBattleCatsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CRoom& room = pDoc->room;
	int iw = sprite[BG].GetWidth();
	int ih = sprite[BG].GetHeight();
	int i, j;
	CDC dc;
	CString text;
	dc.CreateCompatibleDC(pDC);
	// common info about room:
	text.Format(L"plates: %d", room.plates()->size());
	pDC->TextOutW(iw*room.width + 10 + X_SHIFT, 10, text);
	text.Format(L"baskets: %d", room.baskets()->size());
	pDC->TextOutW(iw*room.width + 10 + X_SHIFT, 30, text);
	text.Format(L"cats: %d", room.cats()->size());
	pDC->TextOutW(iw*room.width + 10 + X_SHIFT, 50, text);


	if (stage != 0) {
		text.Format(L"Stage %d", stage);
		text += L"     " + message;
		pDC->TextOutW(10, 10, text);
	}

	// loaded cats		
	text.Format(L"Loaded %d cats:", room.cats()->size());
	pDC->TextOutW(10, 10 + Y_SHIFT, text);
	for (j = 0; j != room.cats()->size(); ++j) {
		CString text;
		CatConfig& cfg = room.cats()->at(j)->getConfig();
		text.Format(L"%hs by %hs", cfg.name.c_str(), cfg.author.c_str());
		pDC->TextOutW(10, 30 + 20 * j + Y_SHIFT, text);
	}

	text.Format(L"Score:");
	pDC->TextOutW(190, 10 + Y_SHIFT, text);
	// draw room here
	// 1. background
	for (j = 0; j != room.height; ++j) {
		for (i = 0; i != room.width; ++i) {
			sprite[room.at(j, i)].Draw(*pDC, j * iw + X_SHIFT, i * ih + Y_SHIFT, iw, ih);
		}
	}
	// draw cats
	for (j = 0; j != room.cats()->size(); ++j) {
		coord& aux = room.cats()->at(j)->position;
		sprite[CAT].Draw(*pDC, aux.col * iw + X_SHIFT, aux.row * ih + Y_SHIFT, iw, ih);
	}
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

void CBattleCatsView::OnOptionsLoadcats()
{
	// TODO: Add your command handler code here
	this->GetDocument()->LoadCats();
	RedrawWindow();
}

void CBattleCatsView::SetCats() {
	CRoom& room = GetDocument()->room;
	//room.SetCats();
}

void CBattleCatsView::OnOptionsStart()
{
	// TODO: Add your command handler code here
	CRoom& room = GetDocument()->room;
	if (room.baskets()->size() == 0) {
		MessageBox(L"Cant start game no baskets found", L"Oops Message", MB_ICONWARNING);
		return;
	}
	if (room.cats()->size() == 0) {
		MessageBox(L"Cant start game no cats found", L"Oops Message", MB_ICONWARNING);
		return;
	}
	if (room.plates()->size() == 0) {
		MessageBox(L"Cant start game no plates found", L"Oops Message", MB_ICONWARNING);
		return;
	}
	CStartDlg dlg;

	if (dlg.DoModal() == IDOK) {
		UINT it = dlg.nr_it;
		//room = GetDocument()->room;
		cats_type cats = room.cats();
		actions_type actions;
		actions.resize(cats->size(), nullptr);

		while (stage != it) {
			++stage;

			for (size_t j = 0; j != cats->size(); ++j) {
				IAction* tmp = (*cats)[j]->Next(actions[j]);
				if (tmp != nullptr) {
					actions[j] = tmp;
				}
				message.Format(L"cat %hs does action %d", (*cats)[j]->getConfig().name.c_str(), actions[j]->type());
				actions[j]->doAction();
				if (actions[j]->type() != ACTION_T::COMPOSED || 
					( ((ComposedAction*)actions[j])->actions().size() == 0)) {
					actions[j] = nullptr;
				}
				//message.Format(L"cat %s do action", CString((*cats)[j]->getConfig().name.c_str()));
				Sleep(1000);
				RedrawWindow();
			}
			
			Sleep(100);
		}
	}
}