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
#include "EditorAnimation1D.h"
#include "EditorAnimation2D.h"
#include <vector>

using namespace ChromaSDK;


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
	~CMainViewDlg();

	void OpenOrCreateAnimation(const std::string& path);
	void PlayAnimationOnOpen();
	void LoadFile();
	void SaveFile();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_VIEW };
#endif

	virtual BOOL OnInitDialog();

	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

														// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSelChangeListTypes();
	afx_msg void OnBnClickedButtonImportOverrideTime();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonFill();
	afx_msg void OnBnClickedButtonFillBlank();
	afx_msg void OnBnClickedButtonDarken();
	afx_msg void OnBnClickedButtonLighten();
	afx_msg void OnBnClickedButtonRandom();
	afx_msg void OnBnClickedButtonCopy();
	afx_msg void OnBnClickedButtonPaste();
	afx_msg void OnBnClickedButtonPreview();
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonUnload();
	afx_msg void OnBnClickedButtonSetKey();
	afx_msg void OnBnClickedButtonSetLed();
	afx_msg void OnBnClickedButtonFirst();
	afx_msg void OnBnClickedButtonLast();
	afx_msg void OnBnClickedButtonPrevious();
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedButtonInsert();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDuplicate();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonSetDuration();
	afx_msg void OnBnClickedButtonLoop();
	afx_msg void OnTextChangeFrameIndex();
	afx_msg void OnTextChangeBrush();
	afx_msg void OnBnClickedButtonNthDelete();
	afx_msg void OnBnClickedMenuNew();
	afx_msg void OnBnClickedMenuOpen();
	afx_msg void OnBnClickedMenuSave();
	afx_msg void OnBnClickedMenuSaveAs();
	afx_msg void OnBnClickedMenuExit();
	afx_msg void OnBnClickedMenuImportImage();
	afx_msg void OnBnClickedMenuImportImageSequence();
	afx_msg void OnBnClickedMenuImportAnimation();

	// Avoid enter closing dialog
	virtual void OnOK();

	// Avoid esc closing dialog
	virtual void OnCancel();

	// Update preview when animation is playing
	virtual void OnTimer(UINT_PTR TimerVal);

	void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	void OnSliderBrushIntensity();

	void OnBnClickedButtonColor(UINT nID);

private:

	void UpdateWindowTitle();
	void SetPath(const std::string& path);

	EditorAnimationBase* GetEditor();
	AnimationBase* GetAnimation();

	int GetCurrentFrame();
	void SetCurrentFrame(unsigned int index);
	int GetFrameCount();

	std::string _mPath;
	bool _mPlayOnOpen;

	CStatic* GetControlVersion();
	CListBox* GetControlListTypes();
	CEdit* GetControlOverrideTime();
	CStatic* GetControlGridSize();
	CStatic* GetControlSetKeyLabel();
	CComboBox* GetControlSetKeyCombo();
	CButton* GetControlSetKeyButton();
	CStatic* GetControlSetLEDLabel();
	CComboBox* GetControlSetLEDCombo();
	CButton* GetControlSetLEDButton();
	CStatic* GetControlFrames();
	CEdit* GetControlFrameIndex();
	CEdit* GetControlDuration();
	CSliderCtrl* GetBrushSlider();
	CEdit* GetControlEditBrush();
	CEdit* GetControlEditDelete();

	void UpdateOverrideTime(float time);
	float GetOverrideTime();

	void UpdateDuration(float time);
	float GetDuration();

	void RefreshDevice();
	void RecreateGrid();
	void RefreshGrid();

	void RefreshFrames();

	std::vector<CColorButton*>& GetGridButtons();
	std::vector<CColorButton*>& GetColorButtons();

	COLORREF GetColor();
	void SetColor(COLORREF color);

	float _mOverrideTime;

	EChromaSDKDeviceTypeEnum _mDeviceType;

	std::vector<CColorButton*> _mGridButtons;
	std::vector<CColorButton*> _mColorButtons;
	COLORREF _mColor;

	// editors
	ChromaSDK::EditorAnimation1D _mEdit1D;
	ChromaSDK::EditorAnimation2D _mEdit2D;

	// keyboard input
	bool _mShiftModifier;
	bool _mControlModifier;

	float _mBrushIntensitity;

	UINT _mTimer;
	bool _mWasPlaying;

	bool _mDialogInitialized;

	int _mIndexLed;
	int _mIndexRow;
	int _mIndexColumn;
};
