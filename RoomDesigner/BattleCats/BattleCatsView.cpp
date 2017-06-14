
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
#include "..\libicat\icat.h"

#include <strsafe.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const size_t SHIFT_POS = 200;


// CBattleCatsView

IMPLEMENT_DYNCREATE(CBattleCatsView, CView)

BEGIN_MESSAGE_MAP(CBattleCatsView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_LOADCATS, &CBattleCatsView::OnFileLoadcats)
END_MESSAGE_MAP()

// CBattleCatsView construction/destruction

CBattleCatsView::CBattleCatsView()
{
	// TODO: add construction code here
	sprite[BG].Load(L"images32/bg32.png");
	sprite[PLATE].Load(L"images32/plate32.png");
	sprite[FISH].Load(L"images32/fish32.png");
	sprite[BASKET].Load(L"images32/bed32.png");

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
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	int i, j;
	for (j = 0; j != room.height; ++j) {
		for (i = 0; i != room.width; ++i) {
			sprite[room.at(j, i)].Draw(*pDC, j * iw + SHIFT_POS, i * ih, iw, ih);

		}
	}

	// loaded cats
	CString text;
	text.Format(L"Loaded %d cats:", room.cats().size());
	pDC->TextOutW(10, 10, text);
	for (j = 0; j != room.cats().size(); ++j) {
		CString text;
		CatConfig& cfg = room.cats().at(j)->getConfig();
		text.Format(L"%s by %s", CString(cfg.name.c_str()), CString(cfg.author.c_str()));
		pDC->TextOutW(10, 30 + 20 * j, text);
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

void CBattleCatsView::LoadCats()
{
	typedef ICat* (*createCatFunc)(IRoom* /*room*/);
	CRoom& room = GetDocument()->room;
	//room.AddCat();
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	TCHAR szDir[MAX_PATH];
	size_t length_of_arg;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;

	StringCchCopy(szDir, MAX_PATH, L".\\cats\\*");
	hFind = FindFirstFile(szDir, &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		MessageBox(TEXT("FindFirstFile"));
		return;
	}

	// List all the files in the directory with some info about them.
	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			// _tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);
		}
		else
		{
			HMODULE handle = LoadLibrary(ffd.cFileName);
			if (handle != NULL) {
				createCatFunc createCat = (createCatFunc)GetProcAddress(handle, "createCat");
				ICat* cat = createCat((IRoom*)&room);
				room.AddCat(cat);
				//MessageBox(CString(cat->getConfig().name.c_str()));
			}
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES)
	{
		MessageBox(TEXT("No cats found"));
	}

	FindClose(hFind);
	RedrawWindow();
}


void CBattleCatsView::OnFileLoadcats()
{
	// TODO: Add your command handler code here
	LoadCats();
}
