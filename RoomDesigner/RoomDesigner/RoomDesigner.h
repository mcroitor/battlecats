
// RoomDesigner.h : main header file for the RoomDesigner application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CRoomDesignerApp:
// See RoomDesigner.cpp for the implementation of this class
//

class CRoomDesignerApp : public CWinApp
{
public:
	CRoomDesignerApp();
	bool showgrid;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnViewShowgrid();
};

extern CRoomDesignerApp theApp;
