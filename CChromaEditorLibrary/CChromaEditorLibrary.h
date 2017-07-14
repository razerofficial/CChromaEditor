// CChromaEditorLibrary.h : main header file for the CChromaEditorLibrary DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "afxwinappex.h"
#include "afxdialogex.h"


// CCChromaEditorLibraryApp
// See CChromaEditorLibrary.cpp for the implementation of this class
//

class CCChromaEditorLibraryApp : public CWinApp
{
public:
	CCChromaEditorLibraryApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

// CMainViewDlg dialog used for App MainView

class CMainViewDlg : public CDialogEx
{
public:
	CMainViewDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_VIEW };
#endif

	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

														// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};
