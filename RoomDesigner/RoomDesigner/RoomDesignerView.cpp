
// RoomDesignerView.cpp : implementation of the CRoomDesignerView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "RoomDesigner.h"
#endif

#include "RoomDesignerDoc.h"
#include "RoomDesignerView.h"

#include "AddBasketDlg.h"
#include "AddPlateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRoomDesignerView

IMPLEMENT_DYNCREATE(CRoomDesignerView, CView)

BEGIN_MESSAGE_MAP(CRoomDesignerView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_EDIT_BASKET, &CRoomDesignerView::OnEditBasket)
	ON_COMMAND(ID_EDIT_PLATE, &CRoomDesignerView::OnEditPlate)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CONTEXT_ADDPLATE, &CRoomDesignerView::OnContextAddplate)
	ON_COMMAND(ID_CONTEXT_ADDBASKET, &CRoomDesignerView::OnContextAddbasket)
	ON_COMMAND(ID_VIEW_SHOWGRID, &CRoomDesignerView::OnViewShowgrid)
	ON_COMMAND(ID_IDC_REMOVE, &CRoomDesignerView::OnIdcRemove)
	ON_COMMAND(ID_VIEW_SHOWVALUES, &CRoomDesignerView::OnViewShowvalues)
END_MESSAGE_MAP()

// CRoomDesignerView construction/destruction

CRoomDesignerView::CRoomDesignerView()
{
	// TODO: add construction code here
	sprite[BG].Load(L"images32/bg32.png");
	sprite[PLATE].Load(L"images32/plate32.png");
	sprite[FISH].Load(L"images32/fish32.png");
	sprite[BASKET].Load(L"images32/bed32.png");
	showgrid = true;
	showvalues = true;
}

CRoomDesignerView::~CRoomDesignerView()
{
}

BOOL CRoomDesignerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CRoomDesignerView drawing

void CRoomDesignerView::OnDraw(CDC* pDC)
{
	CRoomDesignerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CRoom& room = pDoc->room;
	int iw = sprite[BG].GetWidth();
	int ih = sprite[BG].GetHeight();
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	int i, j;
	for (j = 0; j != room.height; ++j){
		for (i = 0; i != room.width; ++i){
			sprite[room.at(j, i)].Draw(*pDC, j * iw, i * ih, iw, ih);
			
		}
	}

	//grid
	if (showgrid){
		for (i = 1; i != room.width; ++i){
			pDC->MoveTo(i * iw, 0);
			pDC->LineTo(i * iw, room.height * ih);
		}
		for (i = 1; i != room.height; ++i){
			pDC->MoveTo(0, i * ih);
			pDC->LineTo(room.width * iw, i * ih);
		}
	}
	if (showvalues){
		for (i = 0; i != room.plates()->size(); ++i){
			CPlate* plate = room.plates()->at(i);
			CString text;
			text.Format(L"%d", plate->num_fish);
			pDC->TextOut(plate->position.col * iw, plate->position.row * ih, text);
		}
	}

	CString info;
	info.Format(L"room size: (%d, %d)", room.width, room.height);
	pDC->TextOutW(iw*room.width + 10, 10, info);
	info.Format(L"plates total: %d", room.plates()->size());
	pDC->TextOutW(iw*room.width + 10, 30, info);
	info.Format(L"baskets total: %d", room.baskets()->size());
	pDC->TextOutW(iw*room.width + 10, 50, info);

	// debug
	int index = 0;
	for (plates_iterator it = room.plates()->begin(); it != room.plates()->end(); ++it) {
		info.Format(L"plate[ %d ]: (%d, %d)", index, (*it)->position.col, (*it)->position.row);
		pDC->TextOutW(iw*room.width + 10, 100 + 20*index, info);
		++index;
	}
	//pDC->BitBlt(0, 0, iw*room.width, ih*room.height, &dc, 0, 0, SRCCOPY);
}


// CRoomDesignerView printing

BOOL CRoomDesignerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRoomDesignerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRoomDesignerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CRoomDesignerView diagnostics

#ifdef _DEBUG
void CRoomDesignerView::AssertValid() const
{
	CView::AssertValid();
}

void CRoomDesignerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRoomDesignerDoc* CRoomDesignerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRoomDesignerDoc)));
	return (CRoomDesignerDoc*)m_pDocument;
}
#endif //_DEBUG


// CRoomDesignerView message handlers


void CRoomDesignerView::OnEditBasket()
{
	// TODO: Add your command handler code here
	CRoom& room = this->GetDocument()->room;

	CAddBasketDlg dlg;
	do{
		if (dlg.DoModal()){
			if (dlg.row >= room.width || dlg.col >= room.height){
				continue;
			}
			// do not change exists data
			if (room.at(dlg.row, dlg.col) != BG){
				continue;
			}
			// insert
			room.AddBasket(new CBasket(coord(dlg.row, dlg.col)));
			RedrawWindow();
		}
		return;
	} while (true);
}


void CRoomDesignerView::OnEditPlate()
{
	// TODO: Add your command handler code here
	CRoom& room = this->GetDocument()->room;

	CAddPlateDlg dlg;
	do{
		if (dlg.DoModal()){
			if (dlg.row >= room.width || dlg.col >= room.height){
				continue;
			}
			// do not change exists data
			if (room.at(dlg.row, dlg.col) != BG){
				continue;
			}
			// insert
			room.AddPlate(new CPlate(coord(dlg.row, dlg.col), dlg.nf));
			RedrawWindow();
		}
		return;
	} while (true);
}

void CRoomDesignerView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: Add your message handler code here
	CRoom& room = this->GetDocument()->room;
	UINT s = sprite[BG].GetWidth();
	CPoint p = point;
	ScreenToClient(&p);
	clickPos.col = p.x / s;
	clickPos.row = p.y / s;

	CMenu menu;
	UINT menu_id = IDR_CONTEXT;
	// do not modify data
	if (room.at(clickPos.col, clickPos.row) != BG){
		menu_id = IDR_CONTEXT_REMOVE;
	}

	menu.LoadMenuW(menu_id);

	CMenu *popupMenu = menu.GetSubMenu(0);
	ASSERT(popupMenu);
	popupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}


void CRoomDesignerView::OnContextAddplate()
{
	// TODO: Add your command handler code here
	CRoom& room = this->GetDocument()->room;

	CAddPlateDlg dlg;
	dlg.row = clickPos.row;
	dlg.col = clickPos.col;

	if (dlg.DoModal()){
		room.AddPlate(new CPlate(coord(dlg.row, dlg.col), dlg.nf));
		RedrawWindow();
	}
	RedrawWindow();
}


void CRoomDesignerView::OnContextAddbasket()
{
	// TODO: Add your command handler code here
	CRoom& room = this->GetDocument()->room;

	room.AddBasket(new CBasket(clickPos));
	RedrawWindow();
}


void CRoomDesignerView::OnViewShowgrid()
{
	// TODO: Add your command handler code here
	showgrid = !showgrid;
	RedrawWindow();	
}


void CRoomDesignerView::OnIdcRemove()
{
	// TODO: Add your command handler code here
	CRoom& room = this->GetDocument()->room;
	UINT type = room.at(clickPos.col, clickPos.row);
	if (type == BASKET){
		for (UINT i = 0; i != room.baskets()->size(); ++i){
			if ((*room.baskets())[i]->position == clickPos){
				room.RemoveBasket(i);
				break;
			}
		}		
	}
	else if (type == PLATE || type == FISH){
		for (UINT i = 0; i != room.plates()->size(); ++i){
			if ((*room.plates())[i]->position == clickPos){
				room.RemovePlate(i);
				break;
			}
		}
	}
	RedrawWindow();
}


void CRoomDesignerView::OnViewShowvalues()
{
	// TODO: Add your command handler code here
	showvalues = !showvalues;
	RedrawWindow();
}
