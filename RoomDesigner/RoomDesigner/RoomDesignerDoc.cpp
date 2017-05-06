
// RoomDesignerDoc.cpp : implementation of the CRoomDesignerDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "RoomDesigner.h"
#endif

#include "RoomDesignerDoc.h"
#include "InitRoomDlg.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRoomDesignerDoc

IMPLEMENT_DYNCREATE(CRoomDesignerDoc, CDocument)

BEGIN_MESSAGE_MAP(CRoomDesignerDoc, CDocument)
END_MESSAGE_MAP()


// CRoomDesignerDoc construction/destruction

CRoomDesignerDoc::CRoomDesignerDoc()
{
	// TODO: add one-time construction code here

}

CRoomDesignerDoc::~CRoomDesignerDoc()
{
}

BOOL CRoomDesignerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	CInitRoomDlg dlg;
	if (dlg.DoModal() == IDOK){
		room = CRoom(dlg.width, dlg.height);
	}
	return TRUE;
}




// CRoomDesignerDoc serialization

void CRoomDesignerDoc::Serialize(CArchive& ar)
{
	room.Serialize(ar);
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CRoomDesignerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CRoomDesignerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CRoomDesignerDoc::SetSearchContent(const CString& value)
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

// CRoomDesignerDoc diagnostics

#ifdef _DEBUG
void CRoomDesignerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRoomDesignerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CRoomDesignerDoc commands
