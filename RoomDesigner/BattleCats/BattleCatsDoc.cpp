
// BattleCatsDoc.cpp : implementation of the CBattleCatsDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "BattleCats.h"
#endif

#include "BattleCatsDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef ICat* (*createCat)(IRoom* /*room*/);;
// CBattleCatsDoc

IMPLEMENT_DYNCREATE(CBattleCatsDoc, CDocument)

BEGIN_MESSAGE_MAP(CBattleCatsDoc, CDocument)
END_MESSAGE_MAP()


// CBattleCatsDoc construction/destruction

CBattleCatsDoc::CBattleCatsDoc()
{
	// TODO: add one-time construction code here
	room = CRoom(10, 10);
	room.AddBasket(new CBasket(coord(0, 0)));

}

CBattleCatsDoc::~CBattleCatsDoc()
{
}

BOOL CBattleCatsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	room = CRoom(10, 10);
	room.AddBasket(new CBasket(coord(0, 0)));
	return TRUE;
}




// CBattleCatsDoc serialization

void CBattleCatsDoc::Serialize(CArchive& ar)
{
	room.Serialize(ar);
	LoadCats();
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

void CBattleCatsDoc::LoadCats() {
	// cant load cats if baskets does not exists.
	if (room.baskets()->size() == 0) {
		MessageBox(NULL, L"Cant load cats: no baskets for them", L"Oops Message", MB_ICONWARNING);
		return;
	}
	//remove cats if exists
	room.cats()->clear();

	// load cats dll
	CString pattern = L"./cats/*.dll";
	WIN32_FIND_DATA findData;
	HANDLE hFind = FindFirstFile(pattern, &findData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return;
	}

	do
	{
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			// directory is here!
		}
		else
		{
			HMODULE h = LoadLibrary(findData.cFileName);
			if (h != NULL) {
				//MessageBox(NULL, findData.cFileName, L"Loaded!", 0);
				createCat CreateCat = (createCat)GetProcAddress(h, "createCat");
				if (CreateCat != NULL) {
					ICat* cat = CreateCat(&room);
					room.AddCat(cat);
				}
				else {
					MessageBox(NULL, L"function CreateCat not found!", L"OOPS!", 0);
				}
			}
		}
	} while (FindNextFile(hFind, &findData) != 0);
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CBattleCatsDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CBattleCatsDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CBattleCatsDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CBattleCatsDoc diagnostics

#ifdef _DEBUG
void CBattleCatsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBattleCatsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CBattleCatsDoc commands
