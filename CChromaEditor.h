
// CChromaEditor.h : main header file for the CChromaEditor application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CCChromaEditorApp:
// See CChromaEditor.cpp for the implementation of this class
//

class CCChromaEditorApp : public CWinApp
{
public:
	CCChromaEditorApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppMainView();
	DECLARE_MESSAGE_MAP()
};

extern CCChromaEditorApp theApp;
