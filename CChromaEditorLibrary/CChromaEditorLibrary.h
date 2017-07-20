// CChromaEditorLibrary.h : main header file for the CChromaEditorLibrary DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "ChromaSDKPlugin.h"
#include "ChromaSDKEditorAnimation1D.h"
#include "ChromaSDKEditorAnimation2D.h"
#include <vector>


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

class CColorButton;

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
public:
	afx_msg void OnBnClickedButtonImportImage();
	afx_msg void OnCbnSelchangeComboType();
	afx_msg void OnBnClickedButtonImportAnimation();
	afx_msg void OnEnChangeOverrideTime2();
	afx_msg void OnBnClickedButtonImportOverrideTime();
	afx_msg void OnCbnSelchangeComboDevices();
	afx_msg void OnBnClickedButtonSetDevice();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonFill();
	afx_msg void OnBnClickedButtonRandom();
	afx_msg void OnBnClickedButtonCopy();
	afx_msg void OnBnClickedButtonPaste();
	afx_msg void OnBnClickedButtonPreview();
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonUnload();
	afx_msg void OnCbnSelchangeComboKeys();
	afx_msg void OnBnClickedButtonSetKey();
	afx_msg void OnCbnSelchangeComboLeds();
	afx_msg void OnBnClickedButtonSetLed();
	afx_msg void OnEnChangeOverrideTime();
	afx_msg void OnBnClickedButtonPrevious();
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonColor();
	afx_msg void OnBnClickedButtonSetDeviceType();

	void OnBnClickedButtonColor(UINT nID);

private:

	CComboBox* GetControlDeviceType();
	CComboBox* GetControlDevice();
	CStatic* GetControlGridSize();

	void RefreshDevice();
	void RefreshGrid();

	std::vector<CColorButton*>& GetGridButtons();
	std::vector<CColorButton*>& GetColorButtons();

	COLORREF GetColor();
	void SetColor(COLORREF color);

	ChromaSDKPlugin _mPlugin;

	EChromaSDKDeviceTypeEnum _mDeviceType;

	std::vector<CColorButton*> _mGridButtons;
	std::vector<CColorButton*> _mColorButtons;
	COLORREF _mColor;

	// editors
	ChromaSDKEditorAnimation1D _mEdit1D;
	ChromaSDKEditorAnimation2D _mEdit2D;

};
