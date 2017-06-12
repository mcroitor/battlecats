
// BattleCats.h : main header file for the BattleCats application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CBattleCatsApp:
// See BattleCats.cpp for the implementation of this class
//

class CBattleCatsApp : public CWinApp
{
public:
	CBattleCatsApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBattleCatsApp theApp;
