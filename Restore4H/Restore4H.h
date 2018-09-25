
// Restore4H.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CRestore4HApp:
// See Restore4H.cpp for the implementation of this class
//

class CRestore4HApp : public CWinApp
{
public:
	CRestore4HApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CRestore4HApp theApp;