
// CChromaEditor.h : main header file for the CChromaEditor application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include <vector>


// CCChromaEditorApp:
// See CChromaEditor.cpp for the implementation of this class
//

class CColorButton;

class CCChromaEditorApp : public CWinApp
{
public:
	CCChromaEditorApp();

	void OnBnClickedButtonColor(UINT nID);

// Overrides
public:
	virtual BOOL InitInstance();

	std::vector<CColorButton*>& GetButtons();

	COLORREF GetColor();
	void SetColor(COLORREF color);

// Implementation
	afx_msg void OnAppMainView();
	DECLARE_MESSAGE_MAP()

private:
	std::vector<CColorButton*> _mButtons;
	COLORREF _mColor;
};

extern CCChromaEditorApp theApp;
