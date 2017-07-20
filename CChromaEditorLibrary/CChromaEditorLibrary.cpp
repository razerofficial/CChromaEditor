// CChromaEditorLibrary.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "CChromaEditorLibrary.h"
#include "ColorButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_DYNAMIC_BUTTON_MIN 2000
#define ID_DYNAMIC_COLOR_MIN 2200
#define ID_DYNAMIC_BUTTON_MAX 2256

using namespace std;

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CCChromaEditorLibraryApp

BEGIN_MESSAGE_MAP(CCChromaEditorLibraryApp, CWinApp)
END_MESSAGE_MAP()


// CCChromaEditorLibraryApp construction

CCChromaEditorLibraryApp::CCChromaEditorLibraryApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CCChromaEditorLibraryApp object

CCChromaEditorLibraryApp theApp;


// CCChromaEditorLibraryApp initialization

BOOL CCChromaEditorLibraryApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

CMainViewDlg::CMainViewDlg() : CDialogEx(IDD_MAIN_VIEW)
{
}

BOOL CMainViewDlg::OnInitDialog()
{
	// setup dialog
	CComboBox* comboType = (CComboBox*)GetDlgItem(IDC_COMBO_TYPE);
	comboType->AddString(_T("1D"));
	comboType->AddString(_T("2D"));
	comboType->SetCurSel(0);

	// Setup defaults
	_mDeviceType = EChromaSDKDeviceTypeEnum::DE_2D;
	_mDevice1D = EChromaSDKDevice1DEnum::DE_ChromaLink;
	_mDevice2D = EChromaSDKDevice2DEnum::DE_Keyboard;

	COLORREF black = RGB(0, 0, 0);
	COLORREF red = RGB(255, 0, 0);

	// Create grid
	int width = 15;
	int height = 30;
	int y = 280;
	int id = ID_DYNAMIC_BUTTON_MIN;
	for (int j = 0; j < 6; ++j)
	{
		int x = 25;
		for (int i = 0; i < 22; ++i)
		{
			CColorButton* button = new CColorButton(black, black);
			const int flags = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON |
				BS_OWNERDRAW | BS_MULTILINE;
			button->Create(_T(""), flags, CRect(x, y, x + width, y + height), this, id);
			++id;
			GetGridButtons().push_back(button);
			x += width + 2;
		}

		y += height + 2;
	}

	//create color picker
	id = ID_DYNAMIC_COLOR_MIN;
	y = 550;
	int x = 85;
	width = 50;
	height = 50;
	if (true)
	{
		SetColor(red);
		CColorButton* button = new CColorButton(red, red);
		const int flags = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON |
			BS_OWNERDRAW | BS_MULTILINE;
		button->Create(_T(""), flags, CRect(x, y, x + width, y + height), this, id);
		++id;
		GetColorButtons().push_back(button);
		x += width + 2;
	}

	// create palette
	const float full = 255;
	const float half = 127;
	const float quater = 63;
	int colors[] =
	{
		RGB(full, 0, 0), RGB(half, 0, 0),
		RGB(full, half, 0), RGB(half, quater, 0),
		RGB(full, full, 0), RGB(half, half, 0),
		RGB(0, full, 0), RGB(0, half, 0),
		RGB(0, 0, full), RGB(0, 0, half),
		RGB(0, full, full), RGB(0, half, half),
		RGB(full, 0, full), RGB(half, 0, half),
		RGB(full, full, full), RGB(half, half, half), RGB(0,0,0)
	};
	width = 15;
	height = 30;
	for (unsigned int i = 0; i < size(colors); ++i)
	{
		CColorButton* button = new CColorButton(colors[i], colors[i]);
		const int flags = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON |
			BS_OWNERDRAW | BS_MULTILINE;
		button->Create(_T(""), flags, CRect(x, y, x + width, y + height), this, id);
		++id;
		GetColorButtons().push_back(button);
		x += width + 2;
	}

	return TRUE;
}

void CMainViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMainViewDlg, CDialogEx)

	ON_BN_CLICKED(IDC_BUTTON_IMPORT_IMAGE, &CMainViewDlg::OnBnClickedButtonImportImage)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &CMainViewDlg::OnCbnSelchangeComboType)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_ANIMATION, &CMainViewDlg::OnBnClickedButtonImportAnimation)
	ON_EN_CHANGE(IDC_OVERRIDE_TIME2, &CMainViewDlg::OnEnChangeOverrideTime2)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_OVERRIDE_TIME, &CMainViewDlg::OnBnClickedButtonImportOverrideTime)
	ON_CBN_SELCHANGE(IDC_COMBO_DEVICES, &CMainViewDlg::OnCbnSelchangeComboDevices)
	ON_BN_CLICKED(IDC_BUTTON_SET_DEVICE, &CMainViewDlg::OnBnClickedButtonSetDevice)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CMainViewDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_FILL, &CMainViewDlg::OnBnClickedButtonFill)
	ON_BN_CLICKED(IDC_BUTTON_RANDOM, &CMainViewDlg::OnBnClickedButtonRandom)
	ON_BN_CLICKED(IDC_BUTTON_COPY, &CMainViewDlg::OnBnClickedButtonCopy)
	ON_BN_CLICKED(IDC_BUTTON_PASTE, &CMainViewDlg::OnBnClickedButtonPaste)
	ON_BN_CLICKED(IDC_BUTTON_PREVIEW, &CMainViewDlg::OnBnClickedButtonPreview)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CMainViewDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CMainViewDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CMainViewDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_UNLOAD, &CMainViewDlg::OnBnClickedButtonUnload)
	ON_CBN_SELCHANGE(IDC_COMBO_KEYS, &CMainViewDlg::OnCbnSelchangeComboKeys)
	ON_BN_CLICKED(IDC_BUTTON_SET_KEY, &CMainViewDlg::OnBnClickedButtonSetKey)
	ON_CBN_SELCHANGE(IDC_COMBO_LEDS, &CMainViewDlg::OnCbnSelchangeComboLeds)
	ON_BN_CLICKED(IDC_BUTTON_SET_LED, &CMainViewDlg::OnBnClickedButtonSetLed)
	ON_EN_CHANGE(IDC_OVERRIDE_TIME, &CMainViewDlg::OnEnChangeOverrideTime)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, &CMainViewDlg::OnBnClickedButtonPrevious)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CMainViewDlg::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CMainViewDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CMainViewDlg::OnBnClickedButtonDelete)
	ON_COMMAND_RANGE(ID_DYNAMIC_BUTTON_MIN, ID_DYNAMIC_BUTTON_MAX, &CMainViewDlg::OnBnClickedButtonColor)
END_MESSAGE_MAP()

vector<CColorButton*>& CMainViewDlg::GetGridButtons()
{
	return _mGridButtons;
}

vector<CColorButton*>& CMainViewDlg::GetColorButtons()
{
	return _mColorButtons;
}

COLORREF CMainViewDlg::GetColor()
{
	return _mColor;
}

void CMainViewDlg::SetColor(COLORREF color)
{
	_mColor = color;
}

void CMainViewDlg::OnBnClickedButtonColor(UINT nID)
{
	if (nID >= ID_DYNAMIC_BUTTON_MIN)
	{
		if (nID < ID_DYNAMIC_COLOR_MIN)
		{
			int index = nID - ID_DYNAMIC_BUTTON_MIN;
			vector<CColorButton*> buttons = GetGridButtons();
			CColorButton* button = buttons[index];
			COLORREF color = GetColor();
			button->SetColor(color, color);
			button->Invalidate();
		}
		else
		{
			int index = nID - ID_DYNAMIC_COLOR_MIN;
			if (index == 0)
			{
				// Get the selected color from the CColorDialog. 
				CColorDialog dlg(GetColor());
				if (dlg.DoModal() == IDOK)
				{
					COLORREF color = dlg.GetColor();
					SetColor(color);
					GetColorButtons()[0]->SetColor(color, color);
					GetColorButtons()[0]->Invalidate();
				}
			}
			else
			{
				vector<CColorButton*> buttons = GetColorButtons();
				CColorButton* button = buttons[index];
				COLORREF color = button->GetBackgroundColor();
				SetColor(color);
				GetColorButtons()[0]->SetColor(color, color);
				GetColorButtons()[0]->Invalidate();
			}
		}
	}
}

void CMainViewDlg::OnBnClickedButtonImportImage()
{
	// TODO: Add your control notification handler code here
}


void CMainViewDlg::OnCbnSelchangeComboType()
{
	//1d or 2d
}


void CMainViewDlg::OnBnClickedButtonImportAnimation()
{
	// TODO: Add your control notification handler code here
}


void CMainViewDlg::OnEnChangeOverrideTime2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CMainViewDlg::OnBnClickedButtonImportOverrideTime()
{
	// TODO: Add your control notification handler code here
}


void CMainViewDlg::OnCbnSelchangeComboDevices()
{
	// TODO: Add your control notification handler code here
}


void CMainViewDlg::OnBnClickedButtonSetDevice()
{
	// TODO: Add your control notification handler code here
}


void CMainViewDlg::OnBnClickedButtonClear()
{
	// TODO: Add your control notification handler code here

	if (_mDeviceType == EChromaSDKDeviceTypeEnum::DE_2D)
	{
		FChromaSDKEffectResult result = _mPlugin.CreateEffectNone2D(_mDevice2D);
		if (result.Result == 0)
		{
			_mPlugin.SetEffect(result.EffectId);
			_mPlugin.DeleteEffect(result.EffectId);
		}
	}
}


void CMainViewDlg::OnBnClickedButtonFill()
{
	// TODO: Add your control notification handler code here
}


void CMainViewDlg::OnBnClickedButtonRandom()
{
	// TODO: Add your control notification handler code here
}


void CMainViewDlg::OnBnClickedButtonCopy()
{
	// TODO: Add your control notification handler code here
}


void CMainViewDlg::OnBnClickedButtonPaste()
{
	// TODO: Add your control notification handler code here
}


void CMainViewDlg::OnBnClickedButtonPreview()
{
	// TODO: Add your control notification handler code here
}


void CMainViewDlg::OnBnClickedButtonPlay()
{
	// TODO: Add your control notification handler code here
}


void CMainViewDlg::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
}


void CMainViewDlg::OnBnClickedButtonLoad()
{
	// TODO: Add your control notification handler code here
}


void CMainViewDlg::OnBnClickedButtonUnload()
{
	// TODO: Add your control notification handler code here
}


void CMainViewDlg::OnCbnSelchangeComboKeys()
{
	// TODO: Add your control notification handler code here
}


void CMainViewDlg::OnBnClickedButtonSetKey()
{
	// TODO: Add your control notification handler code here
}


void CMainViewDlg::OnCbnSelchangeComboLeds()
{
	// TODO: Add your control notification handler code here
}


void CMainViewDlg::OnBnClickedButtonSetLed()
{
	// TODO: Add your control notification handler code here
}


void CMainViewDlg::OnEnChangeOverrideTime()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CMainViewDlg::OnBnClickedButtonPrevious()
{
	// TODO: Add your control notification handler code here
}


void CMainViewDlg::OnBnClickedButtonNext()
{
	// TODO: Add your control notification handler code here
}


void CMainViewDlg::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
}


void CMainViewDlg::OnBnClickedButtonDelete()
{
	// TODO: Add your control notification handler code here
}
