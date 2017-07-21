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

#define DEVICE_TYPE_1D "1D"
#define DEVICE_TYPE_2D "2D"
#define DEVICE_CHROMA_LINK "ChromaLink"
#define DEVICE_HEADSET "Headset"
#define DEVICE_KEYBOARD "Keyboard"
#define DEVICE_KEYPAD "Keypad"
#define DEVICE_MOUSE "Mouse"
#define DEVICE_MOUSEPAD "Mousepad"

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

CComboBox* CMainViewDlg::GetControlDeviceType()
{
	return (CComboBox*)GetDlgItem(IDC_COMBO_TYPE);
}

CComboBox* CMainViewDlg::GetControlDevice()
{
	return (CComboBox*)GetDlgItem(IDC_COMBO_DEVICE);
}

CStatic* CMainViewDlg::GetControlGridSize()
{
	return (CStatic*)GetDlgItem(IDC_STATIC_GRID_SIZE);
}

CStatic* CMainViewDlg::GetControlFrames()
{
	return (CStatic*)GetDlgItem(IDC_STATIC_FRAMES);
}

void CMainViewDlg::RefreshDevice()
{
	GetControlDeviceType()->SetCurSel(_mDeviceType);

	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		GetControlDevice()->ResetContent();
		GetControlDevice()->AddString(_T(DEVICE_CHROMA_LINK));
		GetControlDevice()->AddString(_T(DEVICE_HEADSET));
		GetControlDevice()->AddString(_T(DEVICE_MOUSEPAD));
		GetControlDevice()->SetCurSel(_mEdit1D.GetDevice());
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		GetControlDevice()->ResetContent();
		GetControlDevice()->AddString(_T(DEVICE_KEYBOARD));
		GetControlDevice()->AddString(_T(DEVICE_KEYPAD));
		GetControlDevice()->AddString(_T(DEVICE_MOUSE));
		GetControlDevice()->SetCurSel(_mEdit2D.GetDevice());
		break;
	}
}

void CMainViewDlg::RecreateGrid()
{
	// clear old grid
	vector<CColorButton*>& buttons = GetGridButtons();
	for (int i = 0; i < buttons.size(); ++i)
	{
		CColorButton* button = buttons[i];
		if (button)
		{
			button->DestroyWindow();
			delete(button);
		}
	}
	buttons.clear();

	COLORREF black = RGB(0, 0, 0);

	// update grid label
	int width = 15;
	int height = 30;
	int y = 280;
	int id = ID_DYNAMIC_BUTTON_MIN;
	switch (_mDeviceType)
	{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			int maxLeds = _mPlugin.GetMaxLeds(_mEdit1D.GetDevice());
			int x = 25;
			for (int i = 0; i < maxLeds; ++i)
			{
				CColorButton* button = new CColorButton(black, black);
				const int flags = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON |
					BS_OWNERDRAW | BS_MULTILINE;
				button->Create(_T(""), flags, CRect(x, y, x + width, y + height), this, id);
				++id;
				buttons.push_back(button);
				x += width + 2;
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			int maxRow = _mPlugin.GetMaxRow(_mEdit2D.GetDevice());
			int maxColumn = _mPlugin.GetMaxColumn(_mEdit2D.GetDevice());

			// create grid buttons
			for (int j = 0; j < maxRow; ++j)
			{
				int x = 25;
				for (int i = 0; i < maxColumn; ++i)
				{
					CColorButton* button = new CColorButton(black, black);
					const int flags = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON |
						BS_OWNERDRAW | BS_MULTILINE;
					button->Create(_T(""), flags, CRect(x, y, x + width, y + height), this, id);
					++id;
					buttons.push_back(button);
					x += width + 2;
				}

				y += height + 2;
			}
		}
		break;
	}
}

void CMainViewDlg::RefreshGrid()
{
	// update grid label
	char buffer[20] = { 0 };
	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			int maxLeds = _mPlugin.GetMaxLeds(_mEdit1D.GetDevice());
			sprintf_s(buffer, "1 x %d", maxLeds);
		}
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			int maxRow = _mPlugin.GetMaxRow(_mEdit2D.GetDevice());
			int maxColumn = _mPlugin.GetMaxColumn(_mEdit2D.GetDevice());
			sprintf_s(buffer, "%d x %d", maxRow, maxColumn);
		}
		break;
	}
	GetControlGridSize()->SetWindowText(CString(buffer));


	// update buttons
	vector<CColorButton*>& buttons = GetGridButtons();

	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			int maxLeds = _mPlugin.GetMaxLeds(_mEdit1D.GetDevice());
			EChromaSDKDevice1DEnum device = _mEdit1D.GetDevice();
			vector<FChromaSDKColorFrame1D>& frames = _mEdit1D.GetFrames();
			int currentFrame = _mEdit1D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
			if (currentFrame < frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[currentFrame];
				int id = 0;
				for (int i = 0; i < maxLeds; ++i)
				{
					CColorButton* button = buttons[id];
					if (button)
					{
						COLORREF color = frame.Colors[i];
						button->SetColor(color, color);
						button->Invalidate();
					}
					++id;
				}
			}
		}
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			int maxRow = _mPlugin.GetMaxRow(_mEdit2D.GetDevice());
			int maxColumn = _mPlugin.GetMaxColumn(_mEdit2D.GetDevice());
			EChromaSDKDevice2DEnum device = _mEdit2D.GetDevice();
			vector<FChromaSDKColorFrame2D>& frames = _mEdit2D.GetFrames();
			int currentFrame = _mEdit2D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
			if (currentFrame < frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[currentFrame];
				int id = 0;
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						CColorButton* button = buttons[id];
						if (button)
						{
							COLORREF color = row.Colors[j];
							button->SetColor(color, color);
							button->Invalidate();
						}
						++id;
					}
				}
			}
		}
		break;
	}
}

void CMainViewDlg::RefreshFrames()
{
	//update frames label
	char buffer[48] = { 0 };
	int currentFrame = 0;
	int frameCount = 0;

	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		currentFrame = _mEdit1D.GetCurrentFrame() + 1;
		frameCount = _mEdit1D.GetFrames().size();
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		currentFrame = _mEdit2D.GetCurrentFrame() + 1;
		frameCount = _mEdit2D.GetFrames().size();
		break;
	}

	sprintf_s(buffer, "%d of %d", currentFrame, frameCount);
	GetControlFrames()->SetWindowText(CString(buffer));
}

BOOL CMainViewDlg::OnInitDialog()
{
	// setup dialog
	GetControlDeviceType()->AddString(_T(DEVICE_TYPE_1D));
	GetControlDeviceType()->AddString(_T(DEVICE_TYPE_2D));

	// Setup defaults
	_mDeviceType = EChromaSDKDeviceTypeEnum::DE_2D;
	_mEdit1D.SetDevice(EChromaSDKDevice1DEnum::DE_ChromaLink);
	_mEdit2D.SetDevice(EChromaSDKDevice2DEnum::DE_Keyboard);

	// Set default type
	GetControlDeviceType()->SetCurSel(_mDeviceType);

	// Create the grid buttons
	RecreateGrid();

	// Display enums
	RefreshDevice();

	// Display grid
	RefreshGrid();

	// DIsplay frames
	RefreshFrames();

	COLORREF black = RGB(0, 0, 0);
	COLORREF red = RGB(255, 0, 0);

	//create color picker
	int id = ID_DYNAMIC_COLOR_MIN;
	int y = 635;
	int x = 85;
	int width = 50;
	int height = 50;
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
	ON_BN_CLICKED(IDC_BUTTON_SET_DEVICE_TYPE, &CMainViewDlg::OnBnClickedButtonSetDeviceType)
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
			vector<CColorButton*>& buttons = GetGridButtons();
			if (index < buttons.size())
			{
				CColorButton* button = buttons[index];
				COLORREF color = GetColor();
				button->SetColor(color, color);
				button->Invalidate();

				switch (_mDeviceType)
				{
				case EChromaSDKDeviceTypeEnum::DE_1D:
					{
						EChromaSDKDevice1DEnum device = _mEdit1D.GetDevice();
						int maxLeds = _mPlugin.GetMaxLeds(device);
						vector<FChromaSDKColorFrame1D>& frames = _mEdit1D.GetFrames();
						int currentFrame = _mEdit1D.GetCurrentFrame();
						if (currentFrame < 0 ||
							currentFrame >= frames.size())
						{
							currentFrame = 0;
						}
						if (currentFrame < frames.size())
						{
							FChromaSDKColorFrame1D& frame = frames[currentFrame];
							int i = index;
							frame.Colors[i] = color;
							RefreshGrid();
						}
					}
					break;
				case EChromaSDKDeviceTypeEnum::DE_2D:
					{
						EChromaSDKDevice2DEnum device = _mEdit2D.GetDevice();
						int maxRow = _mPlugin.GetMaxRow(device);
						int maxColumn = _mPlugin.GetMaxColumn(device);
						vector<FChromaSDKColorFrame2D>& frames = _mEdit2D.GetFrames();
						int currentFrame = _mEdit2D.GetCurrentFrame();
						if (currentFrame < 0 ||
							currentFrame >= frames.size())
						{
							currentFrame = 0;
						}
						if (currentFrame < frames.size())
						{
							FChromaSDKColorFrame2D& frame = frames[currentFrame];
							int i = index / maxColumn;
							FChromaSDKColors& row = frame.Colors[i];
							int j = index - i * maxColumn;
							row.Colors[j] = color;
							RefreshGrid();
						}
					}
					break;
				}
			}
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

void CMainViewDlg::OnBnClickedButtonSetDeviceType()
{
	bool changed = false;
	if (_mDeviceType != (EChromaSDKDeviceTypeEnum)GetControlDeviceType()->GetCurSel())
	{
		_mDeviceType = (EChromaSDKDeviceTypeEnum)GetControlDeviceType()->GetCurSel();
		changed = true;
	}
	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		if (_mEdit1D.SetDevice(EChromaSDKDevice1DEnum::DE_ChromaLink))
		{
			changed = true;
		}
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		if (_mEdit2D.SetDevice(EChromaSDKDevice2DEnum::DE_Keyboard))
		{
			changed = true;
		}
		break;
	}

	if (changed)
	{
		// Create the grid buttons
		RecreateGrid();

		// Display enums
		RefreshDevice();

		// Display grid
		RefreshGrid();
	}
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
	bool changed = false;
	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		changed = _mEdit1D.SetDevice((EChromaSDKDevice1DEnum)GetControlDevice()->GetCurSel());
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		changed = _mEdit2D.SetDevice((EChromaSDKDevice2DEnum)GetControlDevice()->GetCurSel());
		break;
	}

	if (changed)
	{
		// Create the grid buttons
		RecreateGrid();

		// Display enums
		RefreshDevice();

		// Display grid
		RefreshGrid();
	}
}


void CMainViewDlg::OnBnClickedButtonClear()
{
	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			EChromaSDKDevice1DEnum device = _mEdit1D.GetDevice();
			vector<FChromaSDKColorFrame1D>& frames = _mEdit1D.GetFrames();
			int currentFrame = _mEdit1D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
			if (currentFrame < frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[currentFrame];
				frame.Colors = _mPlugin.CreateColors1D(device);
				RefreshGrid();
			}
		}
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			EChromaSDKDevice2DEnum device = _mEdit2D.GetDevice();
			vector<FChromaSDKColorFrame2D>& frames = _mEdit2D.GetFrames();
			int currentFrame = _mEdit2D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
			if (currentFrame < frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[currentFrame];
				frame.Colors = _mPlugin.CreateColors2D(device);
				RefreshGrid();
			}
		}
		break;
	}
}


void CMainViewDlg::OnBnClickedButtonFill()
{
	// TODO: Add your control notification handler code here
}


void CMainViewDlg::OnBnClickedButtonRandom()
{
	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			EChromaSDKDevice1DEnum device = _mEdit1D.GetDevice();
			vector<FChromaSDKColorFrame1D>& frames = _mEdit1D.GetFrames();
			int currentFrame = _mEdit1D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
			if (currentFrame < frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[currentFrame];
				frame.Colors = _mPlugin.CreateRandomColors1D(device);
				RefreshGrid();
			}
		}
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			EChromaSDKDevice2DEnum device = _mEdit2D.GetDevice();
			vector<FChromaSDKColorFrame2D>& frames = _mEdit2D.GetFrames();
			int currentFrame = _mEdit2D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
			if (currentFrame < frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[currentFrame];
				frame.Colors = _mPlugin.CreateRandomColors2D(device);
				RefreshGrid();
			}
		}
		break;
	}
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
	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			EChromaSDKDevice1DEnum device = _mEdit1D.GetDevice();
			vector<FChromaSDKColorFrame1D>& frames = _mEdit1D.GetFrames();
			int currentFrame = _mEdit1D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
			if (currentFrame < frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[currentFrame];
				FChromaSDKEffectResult result = _mPlugin.CreateEffectCustom1D(device, frame.Colors);
				if (result.Result == 0)
				{
					_mPlugin.SetEffect(result.EffectId);
					_mPlugin.DeleteEffect(result.EffectId);
				}
			}
		}
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			EChromaSDKDevice2DEnum device = _mEdit2D.GetDevice();
			vector<FChromaSDKColorFrame2D>& frames = _mEdit2D.GetFrames();
			int currentFrame = _mEdit2D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
			if (currentFrame < frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[currentFrame];
				FChromaSDKEffectResult result = _mPlugin.CreateEffectCustom2D(device, frame.Colors);
				if (result.Result == 0)
				{
					_mPlugin.SetEffect(result.EffectId);
					_mPlugin.DeleteEffect(result.EffectId);
				}
			}
		}
		break;
	}
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
