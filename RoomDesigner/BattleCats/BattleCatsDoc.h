
// BattleCatsDoc.h : interface of the CBattleCatsDoc class
//


#pragma once
#include "..\libroom\Room.h"

class CBattleCatsDoc : public CDocument
{
protected: // create from serialization only
	CBattleCatsDoc();
	DECLARE_DYNCREATE(CBattleCatsDoc)

// Attributes
public:
	CRoom room;
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	void LoadCats();
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CBattleCatsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
