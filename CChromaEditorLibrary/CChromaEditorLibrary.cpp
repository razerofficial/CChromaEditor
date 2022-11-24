// CChromaEditorLibrary.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "CChromaEditorLibrary.h"
#include "ColorButton.h"
#include "ChromaLogger.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TEMP_FILE "temp.chroma"
#define ANIMATION_VERSION 1
#define ID_DYNAMIC_BUTTON_MIN	2000
#define ID_DYNAMIC_COLOR_MIN	2200
#define ID_DYNAMIC_BUTTON_MAX	2256
#define	IDT_TIMER_0				2257

#define DEFAULT_OVERRIDE_TIME 0.1f
#define DEFAULT_DURATION 1.0f
#define DEVICE_TYPE_1D "1D"
#define DEVICE_TYPE_2D "2D"
#define DEVICE_CHROMA_LINK "ChromaLink"
#define DEVICE_HEADSET "Headset"
#define DEVICE_KEYBOARD "Keyboard"
#define DEVICE_KEYBOARD_EXTENDED "KeyboardExtended"
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
	_mDialogInitialized = false; //must be first
	_mIndexLed = -1;
	_mIndexRow = -1;
	_mIndexColumn = -1;
	SetPath("");
	_mPlayOnOpen = false;
}

CMainViewDlg::~CMainViewDlg()
{
	_mEdit1D.GetAnimation()->Stop();
	_mEdit2D.GetAnimation()->Stop();
}

void CMainViewDlg::OpenOrCreateAnimation(const std::string& path)
{
	SetPath(path);
}

void CMainViewDlg::PlayAnimationOnOpen()
{
	_mPlayOnOpen = true;
}

void CMainViewDlg::LoadFile()
{
	if (_mPath.empty())
	{
		ChromaLogger::fprintf(stderr, "LoadFile: Path cannot be empty! Using `%s` instead.\r\n", TEMP_FILE);
		SetPath(TEMP_FILE);
	}
	
	UpdateWindowTitle();

	AnimationBase* animation = ChromaSDKPlugin::GetInstance()->OpenAnimation(_mPath);
	if (animation)
	{
		Animation1D* animation1D;
		Animation2D* animation2D;
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
			_mEdit1D.SetPath(_mPath);
			_mDeviceType = animation->GetDeviceType();
			animation1D = dynamic_cast<Animation1D*>(animation);
			_mEdit1D.SetAnimation(*animation1D);
			_mEdit1D.Reset();
			delete animation;
			break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
			_mEdit2D.SetPath(_mPath);
			_mDeviceType = animation->GetDeviceType();
			animation2D = dynamic_cast<Animation2D*>(animation);
			_mEdit2D.SetAnimation(*animation2D);
			delete animation;
			break;
		default:
			ChromaLogger::fprintf(stderr, "LoadFile: Unexpected animation type!");
			return;
		}
	}
}

void CMainViewDlg::SaveFile()
{
	FILE* stream;
	int result = fopen_s(&stream, _mPath.c_str(), "wb");
	if (result == 13)
	{
		ChromaLogger::fprintf(stderr, "SaveFile: Permission denied!\r\n");
		return;
	}
	else if (0 == result &&
		stream)
	{
		long write = 0;
		long expectedWrite = 1;
		long expectedSize = 0;

		int version = ANIMATION_VERSION;
		expectedSize = sizeof(int);
		write = fwrite(&version, expectedSize, 1, stream);
		if (expectedWrite != write)
		{
			ChromaLogger::fprintf(stderr, "SaveFile: Failed to write version!\r\n");
			std::fclose(stream);
			return;
		}

		//device
		BYTE device = 0;

		//device type
		BYTE deviceType = (BYTE)_mDeviceType;
		expectedSize = sizeof(BYTE);
		fwrite(&deviceType, expectedSize, 1, stream);

		//device
		switch (_mDeviceType)
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
			device = (int)_mEdit1D.GetDevice();
			fwrite(&device, expectedSize, 1, stream);
			break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
			device = (int)_mEdit2D.GetDevice();
			fwrite(&device, expectedSize, 1, stream);
			break;
		}

		//frame count
		unsigned int frameCount = 0;
		switch (_mDeviceType)
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
			frameCount = _mEdit1D.GetFrameCount();
			break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
			frameCount = _mEdit2D.GetFrameCount();
			break;
		}
		expectedSize = sizeof(unsigned int);
		fwrite(&frameCount, expectedSize, 1, stream);

		//frames
		float duration = 0.0f;
		COLORREF color = RGB(0, 0, 0);
		for (unsigned int index = 0; index < frameCount; ++index)
		{
			//duration
			switch (_mDeviceType)
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
				duration = _mEdit1D.GetDuration(index);
				break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
				duration = _mEdit2D.GetDuration(index);
				break;
			}
			expectedSize = sizeof(float);
			fwrite(&duration, expectedSize, 1, stream);

			//colors
			switch (_mDeviceType)
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
				{
					vector<FChromaSDKColorFrame1D>& frames = _mEdit1D.GetFrames();
					if (index < frames.size())
					{
						FChromaSDKColorFrame1D& frame = frames[index];
						for (unsigned int i = 0; i < frame.Colors.size(); ++i)
						{
							//color
							int color = (int)frame.Colors[i];
							expectedSize = sizeof(int);
							fwrite(&color, expectedSize, 1, stream);
						}
					}
				}
				break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
				{
					vector<FChromaSDKColorFrame2D>& frames = _mEdit2D.GetFrames();
					if (index < frames.size())
					{
						FChromaSDKColorFrame2D& frame = frames[index];
						for (unsigned int i = 0; i < frame.Colors.size(); ++i)
						{
							FChromaSDKColors& row = frame.Colors[i];
							for (unsigned int j = 0; j < row.Colors.size(); ++j)
							{
								//color
								int color = row.Colors[j];
								expectedSize = sizeof(int);
								fwrite(&color, expectedSize, 1, stream);
							}
						}
					}
				}
				break;
			}
		}

		fflush(stream);
		std::fclose(stream);
	}
}

CEdit* CMainViewDlg::GetControlOverrideTime()
{
	return (CEdit*)GetDlgItem(IDC_TEXT_OVERRIDE_TIME);
}

CStatic* CMainViewDlg::GetControlGridSize()
{
	return (CStatic*)GetDlgItem(IDC_STATIC_GRID_SIZE);
}

CStatic* CMainViewDlg::GetControlSetKeyLabel()
{
	return (CStatic*)GetDlgItem(IDC_STATIC_SELECT_KEY);
}

CComboBox* CMainViewDlg::GetControlSetKeyCombo()
{
	return (CComboBox*)GetDlgItem(IDC_COMBO_KEYS);
}

CButton* CMainViewDlg::GetControlSetKeyButton()
{
	return (CButton*)GetDlgItem(IDC_BUTTON_SET_KEY);
}

CStatic* CMainViewDlg::GetControlSetLEDLabel()
{
	return (CStatic*)GetDlgItem(IDC_STATIC_SELECT_LED);
}

CComboBox* CMainViewDlg::GetControlSetLEDCombo()
{
	return (CComboBox*)GetDlgItem(IDC_COMBO_LEDS);
}

CButton* CMainViewDlg::GetControlSetLEDButton()
{
	return (CButton*)GetDlgItem(IDC_BUTTON_SET_LED);
}

CStatic* CMainViewDlg::GetControlFrames()
{
	return (CStatic*)GetDlgItem(IDC_STATIC_FRAMES);
}

CEdit* CMainViewDlg::GetControlFrameIndex()
{
	return (CEdit*)GetDlgItem(IDC_EDIT_FRAME_INDEX);
}

CEdit* CMainViewDlg::GetControlDuration()
{
	return (CEdit*)GetDlgItem(IDC_EDIT_DURATION);
}

CSliderCtrl* CMainViewDlg::GetBrushSlider()
{
	return (CSliderCtrl*)GetDlgItem(IDC_SLIDER_BRUSH);
}

CEdit* CMainViewDlg::GetControlEditBrush()
{
	return (CEdit*)GetDlgItem(IDC_EDIT_BRUSH);
}

CEdit* CMainViewDlg::GetControlEditDelete()
{
	return (CEdit*)GetDlgItem(IDC_EDIT_DELETE);
}

void CMainViewDlg::UpdateOverrideTime(float time)
{
	char buffer[10] = { 0 };
	sprintf_s(buffer, "%f", time);
	GetControlOverrideTime()->SetWindowText(CString(buffer));
	GetControlOverrideTime()->Invalidate();
}

float CMainViewDlg::GetOverrideTime()
{
	CString text;
	GetControlOverrideTime()->GetWindowText(text);
	float time = (float)_ttof(text);
	if (time <= 0.0f)
	{
		UpdateOverrideTime(DEFAULT_OVERRIDE_TIME);
		return DEFAULT_OVERRIDE_TIME;
	}
	return time;
}

void CMainViewDlg::UpdateDuration(float time)
{
	char buffer[10] = { 0 };
	sprintf_s(buffer, "%f", time);
	GetControlDuration()->SetWindowText(CString(buffer));
	GetControlDuration()->Invalidate();
}

float CMainViewDlg::GetDuration()
{
	CString text;
	GetControlDuration()->GetWindowText(text);
	float time = (float)_ttof(text);
	if (time <= 0.0f)
	{
		UpdateDuration(DEFAULT_DURATION);
		return DEFAULT_DURATION;
	}
	return time;
}

void CMainViewDlg::RefreshDevice()
{
	_mIndexLed = -1;
	_mIndexRow = -1;
	_mIndexColumn = -1;

	int show = _mDeviceType == EChromaSDKDeviceTypeEnum::DE_2D && _mEdit2D.GetDevice() == EChromaSDKDevice2DEnum::DE_Keyboard;
	GetControlSetKeyLabel()->ShowWindow(show);
	GetControlSetKeyCombo()->ShowWindow(show);
	GetControlSetKeyButton()->ShowWindow(show);

	show = _mDeviceType == EChromaSDKDeviceTypeEnum::DE_2D && _mEdit2D.GetDevice() == EChromaSDKDevice2DEnum::DE_KeyboardExtended;
	GetControlSetKeyLabel()->ShowWindow(show);
	GetControlSetKeyCombo()->ShowWindow(show);
	GetControlSetKeyButton()->ShowWindow(show);

	show = _mDeviceType == EChromaSDKDeviceTypeEnum::DE_2D && _mEdit2D.GetDevice() == EChromaSDKDevice2DEnum::DE_Mouse;
	GetControlSetLEDLabel()->ShowWindow(show);
	GetControlSetLEDCombo()->ShowWindow(show);
	GetControlSetLEDButton()->ShowWindow(show);

	GetControlListTypes()->ResetContent();
	GetControlListTypes()->AddString(_T(DEVICE_CHROMA_LINK));
	GetControlListTypes()->AddString(_T(DEVICE_HEADSET));
	GetControlListTypes()->AddString(_T(DEVICE_KEYBOARD));
	GetControlListTypes()->AddString(_T(DEVICE_KEYBOARD_EXTENDED));
	GetControlListTypes()->AddString(_T(DEVICE_KEYPAD));
	GetControlListTypes()->AddString(_T(DEVICE_MOUSE));
	GetControlListTypes()->AddString(_T(DEVICE_MOUSEPAD));

	int index = 0;
	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		switch (_mEdit1D.GetDevice())
		{
		case EChromaSDKDevice1DEnum::DE_ChromaLink:
			index = 0;
			break;
		case EChromaSDKDevice1DEnum::DE_Headset:
			index = 1;
			break;
		case EChromaSDKDevice1DEnum::DE_Mousepad:
			index = 6;
			break;
		}
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		switch (_mEdit2D.GetDevice())
		{
		case EChromaSDKDevice2DEnum::DE_Keyboard:
			index = 2;
			break;
		case EChromaSDKDevice2DEnum::DE_KeyboardExtended:
			index = 3;
			break;
		case EChromaSDKDevice2DEnum::DE_Keypad:
			index = 4;
			break;
		case EChromaSDKDevice2DEnum::DE_Mouse:
			index = 5;
			break;
		}
		break;
	}
	GetControlListTypes()->SetCurSel(index);
}

void CMainViewDlg::RecreateGrid()
{
	// clear old grid
	vector<CColorButton*>& buttons = GetGridButtons();
	for (unsigned int i = 0; i < buttons.size(); ++i)
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
			int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(_mEdit1D.GetDevice());
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
			int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(_mEdit2D.GetDevice());
			int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(_mEdit2D.GetDevice());

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
			int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(_mEdit1D.GetDevice());
			if (_mIndexLed >= 0)
			{
				sprintf_s(buffer, "1 x %d (%d)", maxLeds, _mIndexLed);
			}
			else
			{
				sprintf_s(buffer, "1 x %d", maxLeds);
			}
		}
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(_mEdit2D.GetDevice());
			int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(_mEdit2D.GetDevice());
			if (_mIndexRow >= 0 && _mIndexColumn >= 0)
			{
				sprintf_s(buffer, "%d x %d (%d, %d)", maxRow, maxColumn, _mIndexRow, _mIndexColumn);
			}
			else
			{
				sprintf_s(buffer, "%d x %d", maxRow, maxColumn);
			}
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
			int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(_mEdit1D.GetDevice());
			EChromaSDKDevice1DEnum device = _mEdit1D.GetDevice();
			vector<FChromaSDKColorFrame1D>& frames = _mEdit1D.GetFrames();
			unsigned int currentFrame = _mEdit1D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
			if (currentFrame < frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[currentFrame];
				int id = 0;
				for (int i = 0; i < maxLeds && i < (int)frame.Colors.size(); ++i)
				{
					CColorButton* button = buttons[id];
					if (button)
					{
						button->SetIndex(i, -1, -1);
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
			int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(_mEdit2D.GetDevice());
			int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(_mEdit2D.GetDevice());
			EChromaSDKDevice2DEnum device = _mEdit2D.GetDevice();
			vector<FChromaSDKColorFrame2D>& frames = _mEdit2D.GetFrames();
			unsigned int currentFrame = _mEdit2D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
			if (currentFrame < frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[currentFrame];
				int id = 0;
				for (int i = 0; i < maxRow && i < (int)frame.Colors.size(); ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						CColorButton* button = buttons[id];
						if (button)
						{
							button->SetIndex(-1, i, j);
							COLORREF color = row.Colors[j];
							color = color & 0xFFFFFF;
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
	char bufferFrameInfo[48] = { 0 };
	int currentFrame = 0;
	int frameCount = 0;

	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		currentFrame = _mEdit1D.GetCurrentFrame();
		frameCount = _mEdit1D.GetFrames().size();
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		currentFrame = _mEdit2D.GetCurrentFrame();
		frameCount = _mEdit2D.GetFrames().size();
		break;
	}

	sprintf_s(bufferFrameInfo, "%d", currentFrame + 1);
	GetControlFrameIndex()->SetWindowText(CString(bufferFrameInfo));
	
	sprintf_s(bufferFrameInfo, "%d of %d", currentFrame + 1, frameCount);
	GetControlFrames()->SetWindowText(CString(bufferFrameInfo));

	//update the frame duration
	char bufferDuration[16] = { 0 };
	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			EChromaSDKDevice1DEnum device = _mEdit1D.GetDevice();
			vector<FChromaSDKColorFrame1D>& frames = _mEdit1D.GetFrames();
			unsigned int currentFrame = _mEdit1D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
			if (currentFrame < frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[currentFrame];
				sprintf_s(bufferDuration, "%f", frame.Duration);
			}
		}
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			EChromaSDKDevice2DEnum device = _mEdit2D.GetDevice();
			vector<FChromaSDKColorFrame2D>& frames = _mEdit2D.GetFrames();
			unsigned int currentFrame = _mEdit2D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
			if (currentFrame < frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[currentFrame];
				sprintf_s(bufferDuration, "%f", frame.Duration);
			}
		}
		break;
	}
	GetControlDuration()->SetWindowText(CString(bufferDuration));
}

CStatic* CMainViewDlg::GetControlVersion()
{
	return (CStatic*)GetDlgItem(IDC_LABEL_VERSION);
}

CListBox* CMainViewDlg::GetControlListTypes()
{
	return (CListBox*)GetDlgItem(IDC_LIST_TYPES);
}

void CMainViewDlg::UpdateWindowTitle()
{
	if (_mDialogInitialized)
	{
		CString title = _T("Chroma Animation Editor - ");
		if (_mPath.empty())
		{
			title += _T("Untitled");
		}
		else
		{
			title += _mPath.c_str();
		}
		SetWindowText(title);
	}
}

void CMainViewDlg::SetPath(const string& path)
{
	_mPath = path;
	UpdateWindowTitle();
}

BOOL CMainViewDlg::OnInitDialog()
{
	GetControlVersion()->SetWindowTextW(_T("Version: 1.13"));

	_mDialogInitialized = true;

	ModifyStyle(WS_SYSMENU, 0);

	_mBrushIntensitity = 1.0f;
	GetBrushSlider()->SetPos(100);
	GetControlEditBrush()->SetWindowText(_T("100"));

	GetControlEditDelete()->SetWindowText(_T("2"));

	// Setup default
	_mDeviceType = EChromaSDKDeviceTypeEnum::DE_2D;

	LoadFile();

	// setup dialog
	UpdateOverrideTime(DEFAULT_OVERRIDE_TIME);

	// setup keyboard chars
	for (int key = EChromaSDKKeyboardKey::KK_ESC; key < EChromaSDKKeyboardKey::KK_INVALID; ++key)
	{
		const char* strKey = ChromaSDKPlugin::GetInstance()->GetKeyboardChar((EChromaSDKKeyboardKey)key);
		GetControlSetKeyCombo()->AddString(CString(strKey));
	}
	GetControlSetKeyCombo()->SetCurSel(0);

	// setup mouse chars
	for (int led = (int)EChromaSDKMouseLED::ML_SCROLLWHEEL; led <= (int)EChromaSDKMouseLED::ML_RIGHT_SIDE7; ++led)
	{
		const char* strLed = ChromaSDKPlugin::GetInstance()->GetMouseChar((EChromaSDKMouseLED)led);
		GetControlSetLEDCombo()->AddString(CString(strLed));
	}
	GetControlSetLEDCombo()->SetCurSel(0);

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
	int y = 390;
	int x = 600;
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

	if (_mPlayOnOpen)
	{
		Sleep(500);
		OnBnClickedButtonPlay();
	}

	_mTimer = SetTimer(IDT_TIMER_0, 100, NULL);
	_mWasPlaying = false;

	return TRUE;
}

void CMainViewDlg::OnTextChangeFrameIndex()
{
	if (GetControlFrameIndex() != GetControlFrameIndex()->GetFocus())
	{
		return; //changed through code
	}

	//update frames label
	char bufferFrameInfo[48] = { 0 };
	int currentFrame = GetCurrentFrame();
	int frameCount = GetFrameCount();

	CString strIndex;
	GetControlFrameIndex()->GetWindowText(strIndex);
	int index;
	int result = swscanf_s(strIndex, _T("%d"), &index);
	if (result == 1 &&
		index > 0 &&
		index <= frameCount &&
		index != (currentFrame + 1))
	{
		SetCurrentFrame(index - 1);
		RefreshGrid();
		RefreshFrames();

		//show changes
		OnBnClickedButtonPreview();
	}
}

void CMainViewDlg::OnTextChangeBrush()
{
	CString strIntensity;
	GetControlEditBrush()->GetWindowText(strIntensity);
	int intensity;
	int result = swscanf_s(strIntensity, _T("%d"), &intensity);
	if (result == 1)
	{
		if (intensity < 0)
		{
			intensity = 0;
		}
		else if (intensity > 100)
		{
			intensity = 100;
		}
		if (GetBrushSlider()->GetPos() != intensity)
		{
			GetBrushSlider()->SetPos(intensity);
			OnSliderBrushIntensity();
		}
	}
}

void CMainViewDlg::OnBnClickedButtonNthDelete()
{
	OnBnClickedButtonUnload(); // delete frame state

	OnBnClickedButtonStop();
	OnBnClickedButtonUnload();
	OnBnClickedButtonFirst();

	CString strNth;
	GetControlEditDelete()->GetWindowText(strNth);

	int nth;
	int result = swscanf_s(strNth, _T("%d"), &nth);
	if (result == 1 &&
		nth > 1)
	{
		int index = 0;
		int currentFrame;
		do
		{
			currentFrame = GetCurrentFrame();
			++index;
			if (index == nth)
			{
				index = 0;
				OnBnClickedButtonDelete();
			}
			else
			{
				OnBnClickedButtonNext();
			}
		} while ((currentFrame + 1) < GetFrameCount());
	}
}

BOOL CMainViewDlg::PreTranslateMessage(MSG* pMsg)
{
	int refocusToControl = IDC_BUTTON_CLEAR;

	// check focus first
	bool textFieldHasFocus = false;
	CWnd* control = GetFocus();
	if (control)
	{
		switch (control->GetDlgCtrlID())
		{
		case IDC_COMBO_KEYS:
		case IDC_COMBO_LEDS:
		case IDC_EDIT_BRUSH:
		case IDC_EDIT_DELETE:
		case IDC_EDIT_DURATION:
		case IDC_EDIT_FRAME_INDEX:
		case IDC_LIST_TYPES:
		case IDC_SLIDER_BRUSH:
		case IDC_TEXT_OVERRIDE_TIME:
			textFieldHasFocus = true;
			break;
		}

		switch (control->GetDlgCtrlID())
		{
		case IDC_LIST_TYPES:
			GotoDlgCtrl(GetDlgItem(refocusToControl));
			break;
		}
	}

	if (!textFieldHasFocus)
	{
		if (pMsg->message == WM_KEYDOWN)
		{
			switch (pMsg->wParam)
			{
			case VK_CONTROL:
				_mControlModifier = true;
				break;
			case VK_SHIFT:
				_mShiftModifier = true;
				break;
			}
		}
		else if (pMsg->message == WM_KEYUP)
		{
			switch (pMsg->wParam)
			{
			case VK_OEM_MINUS:
				OnBnClickedButtonDelete();
				return true;
			case VK_OEM_PLUS:
				OnBnClickedButtonAdd();
				return true;
			case VK_LEFT:
				OnBnClickedButtonPrevious();
				return true;
			case VK_RIGHT:
				OnBnClickedButtonNext();
				return true;
			case VK_CONTROL:
				_mControlModifier = false;
				break;
			case VK_SHIFT:
				_mShiftModifier = false;
				break;
			case 'C':
				if (_mControlModifier)
				{
					OnBnClickedButtonCopy();
					return true;
				}
				break;
			case 'V':
				if (_mControlModifier)
				{
					OnBnClickedButtonPaste();
					return true;
				}
				break;
			case VK_OEM_4:
				_mBrushIntensitity -= 0.2f;
				if (_mBrushIntensitity < 0.0f)
				{
					_mBrushIntensitity = 0.0f;
				}
				GetBrushSlider()->SetPos((int)(_mBrushIntensitity * 100));
				OnSliderBrushIntensity();
				break;
			case VK_OEM_6:
				_mBrushIntensitity += 0.2f;
				if (_mBrushIntensitity > 100.0f)
				{
					_mBrushIntensitity = 100.0f;
				}
				GetBrushSlider()->SetPos((int)(_mBrushIntensitity * 100));
				OnSliderBrushIntensity();
				break;
			default:
				ChromaLogger::printf("Pressed: %d\r\n", pMsg->wParam);
				break;
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CMainViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMainViewDlg, CDialogEx)

	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CMainViewDlg::OnBnClickedMenuSave)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CMainViewDlg::OnBnClickedMenuExit)
	ON_LBN_SELCHANGE(IDC_LIST_TYPES, &CMainViewDlg::OnSelChangeListTypes)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_OVERRIDE_TIME, &CMainViewDlg::OnBnClickedButtonImportOverrideTime)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CMainViewDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_FILL, &CMainViewDlg::OnBnClickedButtonFill)
	ON_BN_CLICKED(IDC_BUTTON_FILL_BLANK, &CMainViewDlg::OnBnClickedButtonFillBlank)
	ON_BN_CLICKED(IDC_BUTTON_DARKEN, &CMainViewDlg::OnBnClickedButtonDarken)
	ON_BN_CLICKED(IDC_BUTTON_LIGHTEN, &CMainViewDlg::OnBnClickedButtonLighten)
	ON_BN_CLICKED(IDC_BUTTON_RANDOM, &CMainViewDlg::OnBnClickedButtonRandom)
	ON_BN_CLICKED(IDC_BUTTON_COPY, &CMainViewDlg::OnBnClickedButtonCopy)
	ON_BN_CLICKED(IDC_BUTTON_PASTE, &CMainViewDlg::OnBnClickedButtonPaste)
	ON_BN_CLICKED(IDC_BUTTON_PREVIEW, &CMainViewDlg::OnBnClickedButtonPreview)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CMainViewDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_LOOP, &CMainViewDlg::OnBnClickedButtonLoop)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CMainViewDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CMainViewDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_UNLOAD, &CMainViewDlg::OnBnClickedButtonUnload)
	ON_BN_CLICKED(IDC_BUTTON_SET_KEY, &CMainViewDlg::OnBnClickedButtonSetKey)
	ON_BN_CLICKED(IDC_BUTTON_SET_LED, &CMainViewDlg::OnBnClickedButtonSetLed)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, &CMainViewDlg::OnBnClickedButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_LAST, &CMainViewDlg::OnBnClickedButtonLast)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, &CMainViewDlg::OnBnClickedButtonPrevious)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CMainViewDlg::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CMainViewDlg::OnBnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CMainViewDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DUPLICATE, &CMainViewDlg::OnBnClickedButtonDuplicate)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CMainViewDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CMainViewDlg::OnBnClickedButtonReset)
	ON_COMMAND_RANGE(ID_DYNAMIC_BUTTON_MIN, ID_DYNAMIC_BUTTON_MAX, &CMainViewDlg::OnBnClickedButtonColor)
	ON_BN_CLICKED(IDC_BUTTON_SET_DURATION, &CMainViewDlg::OnBnClickedButtonSetDuration)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_FRAME_INDEX, &CMainViewDlg::OnTextChangeFrameIndex)
	ON_EN_CHANGE(IDC_EDIT_BRUSH, &CMainViewDlg::OnTextChangeBrush)
	ON_BN_CLICKED(IDC_BUTTON_NTH_DELETE, &CMainViewDlg::OnBnClickedButtonNthDelete)
	ON_BN_CLICKED(ID_MENU_NEW, &CMainViewDlg::OnBnClickedMenuNew)
	ON_BN_CLICKED(ID_MENU_OPEN, &CMainViewDlg::OnBnClickedMenuOpen)
	ON_BN_CLICKED(ID_MENU_SAVE, &CMainViewDlg::OnBnClickedMenuSave)
	ON_BN_CLICKED(ID_MENU_SAVE_AS, &CMainViewDlg::OnBnClickedMenuSaveAs)
	ON_BN_CLICKED(ID_MENU_EXIT, &CMainViewDlg::OnBnClickedMenuExit)
	ON_BN_CLICKED(ID_MENU_IMPORT_IMAGE, &CMainViewDlg::OnBnClickedMenuImportImage)
	ON_BN_CLICKED(ID_MENU_IMPORT_IMAGE_SEQUENCE, &CMainViewDlg::OnBnClickedMenuImportImageSequence)
	ON_BN_CLICKED(ID_MENU_IMPORT_ANIMATION, &CMainViewDlg::OnBnClickedMenuImportAnimation)
	ON_WM_TIMER()
END_MESSAGE_MAP()

void CMainViewDlg::OnBnClickedMenuNew()
{
	OnBnClickedButtonStop();
	OnBnClickedButtonUnload();

	SetPath("");
	OnBnClickedButtonReset();

	// Create the grid buttons
	RecreateGrid();

	// Display enums
	RefreshDevice();

	// Display grid
	RefreshGrid();

	// DIsplay frames
	RefreshFrames();

	//show changes
	OnBnClickedButtonPreview();
}

void CMainViewDlg::OnBnClickedMenuOpen()
{
	// stop animation
	OnBnClickedButtonStop();

	// get path from loaded filename
	CString szDir;
	size_t lastSlash = _mPath.find_last_of("/\\");
	if (lastSlash < 0)
	{
		return;
	}
	string path = _mPath.substr(0, lastSlash);
	//LogDebug("ImportTextureAnimation path=%s", path.c_str());
	szDir += path.c_str();

	const int MAX_CFileDialog_FILE_COUNT = 99;
	const int FILE_LIST_BUFFER_SIZE = ((MAX_CFileDialog_FILE_COUNT * (MAX_PATH + 1)) + 1);

	CString fileName;
	wchar_t* p = fileName.GetBuffer(FILE_LIST_BUFFER_SIZE);
	CFileDialog dlgFile(TRUE);
	OPENFILENAME& ofn = dlgFile.GetOFN();
	ofn.lpstrFilter = _TEXT("Animation\0*.chroma\0");
	ofn.lpstrInitialDir = szDir;
	ofn.lpstrFile = p;
	ofn.nMaxFile = FILE_LIST_BUFFER_SIZE;

	if (dlgFile.DoModal() == IDOK)
	{
		SetPath(string(CT2CA(fileName)));
		if (_mPath.size() <= 2 ||
			_mPath.substr(_mPath.find_last_of(".") + 1) != "chroma")
		{
			_mPath += ".chroma";
		}
		LoadFile();

		// Create the grid buttons
		RecreateGrid();

		// Display enums
		RefreshDevice();

		// Display grid
		RefreshGrid();

		//show changes
		OnBnClickedButtonPreview();
	}
	fileName.ReleaseBuffer();
}

void CMainViewDlg::OnBnClickedMenuSave()
{
	// stop animation
	OnBnClickedButtonStop();

	SaveFile();
}

void CMainViewDlg::OnBnClickedMenuSaveAs()
{
	// stop animation
	OnBnClickedButtonStop();

	// get path from loaded filename
	CString szDir;
	size_t lastSlash = _mPath.find_last_of("/\\");
	if (lastSlash < 0)
	{
		return;
	}
	string path = _mPath.substr(0, lastSlash);
	//LogDebug("ImportTextureAnimation path=%s", path.c_str());
	szDir += path.c_str();

	const int MAX_CFileDialog_FILE_COUNT = 99;
	const int FILE_LIST_BUFFER_SIZE = ((MAX_CFileDialog_FILE_COUNT * (MAX_PATH + 1)) + 1);

	CString fileName;
	wchar_t* p = fileName.GetBuffer(FILE_LIST_BUFFER_SIZE);
	CFileDialog dlgFile(TRUE);
	OPENFILENAME& ofn = dlgFile.GetOFN();
	ofn.lpstrFilter = _TEXT("Animation\0*.chroma\0");
	ofn.lpstrInitialDir = szDir;
	ofn.lpstrFile = p;
	ofn.nMaxFile = FILE_LIST_BUFFER_SIZE;

	if (dlgFile.DoModal() == IDOK)
	{
		SetPath(string(CT2CA(fileName)));
		if (_mPath.size() <= 2 ||
			_mPath.substr(_mPath.find_last_of(".") + 1) != "chroma")
		{
			_mPath += ".chroma";
		}
		SaveFile();
	}
	fileName.ReleaseBuffer();
}

void CMainViewDlg::OnBnClickedMenuExit()
{
	// stop animation
	OnBnClickedButtonStop();

	PluginClearAll();

	PluginUninit();

	PostQuitMessage(0);
}

void CMainViewDlg::OnBnClickedMenuImportImage()
{
	OnBnClickedButtonStop();

	OnBnClickedButtonUnload(); // delete frame state

	EditorAnimationBase* editor = GetEditor();
	if (editor == nullptr)
	{
		return;
	}
	editor->ImportTextureImage();
	RefreshGrid();
	RefreshFrames();

	//show changes
	OnBnClickedButtonPreview();
}

void CMainViewDlg::OnBnClickedMenuImportImageSequence()
{
	OnBnClickedButtonStop();

	OnBnClickedButtonUnload(); // delete frame state

	EditorAnimationBase* editor = GetEditor();
	if (editor == nullptr)
	{
		return;
	}
	editor->ImportTextureImageSequence();
	RefreshGrid();
	RefreshFrames();

	//show changes
	OnBnClickedButtonPreview();
}


void CMainViewDlg::OnBnClickedMenuImportAnimation()
{
	OnBnClickedButtonUnload(); // delete frame state

	EditorAnimationBase* editor = GetEditor();
	if (editor == nullptr)
	{
		return;
	}
	editor->ImportTextureAnimation();
	RefreshGrid();
	RefreshFrames();

	//show changes
	OnBnClickedButtonPreview();
}

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
	// temp copy
	COLORREF color = _mColor;
	int red = (color & 0xFF);
	int green = (color & 0xFF00) >> 8;
	int blue = (color & 0xFF0000) >> 16;

	red = (int)(red * _mBrushIntensitity);
	green = (int)(green * _mBrushIntensitity);
	blue = (int)(blue * _mBrushIntensitity);

	color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
	return color;
}

void CMainViewDlg::SetColor(COLORREF color)
{
	_mColor = color;
}

void CMainViewDlg::OnOK()
{
	// stop enter from closing the dialog
}

void CMainViewDlg::OnCancel()
{
	// stop escape from closing the dialog
}

void CMainViewDlg::OnTimer(UINT_PTR TimerVal)
{
	if (GetAnimation() == nullptr)
	{
		return;
	}
	if (GetAnimation()->IsPlaying())
	{
		// Display grid
		RefreshGrid();

		// Display frames
		RefreshFrames();

		_mWasPlaying = true;
	}
	else if (_mWasPlaying)
	{
		_mWasPlaying = false;

		// Display grid
		RefreshGrid();

		// Display frames
		RefreshFrames();
	}
}

void CMainViewDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	OnSliderBrushIntensity();
}

void CMainViewDlg::OnSliderBrushIntensity()
{
	UINT nPos = GetBrushSlider()->GetPos();
	char buffer[10] = { 0 };
	sprintf_s(buffer, "%d", nPos);
	GetControlEditBrush()->SetWindowText(CString(buffer));
	_mBrushIntensitity = nPos / 100.0f;

	// temp copy
	COLORREF color = _mColor;
	int red = (color & 0xFF);
	int green = (color & 0xFF00) >> 8;
	int blue = (color & 0xFF0000) >> 16;

	red = (int)(red * _mBrushIntensitity);
	green = (int)(green * _mBrushIntensitity);
	blue = (int)(blue * _mBrushIntensitity);

	color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);

	GetColorButtons()[0]->SetColor(color, color);
	GetColorButtons()[0]->Invalidate();
}

void CMainViewDlg::OnBnClickedButtonColor(UINT nID)
{
	OnBnClickedButtonUnload(); // delete frame state

	if (nID >= ID_DYNAMIC_BUTTON_MIN)
	{
		if (nID < ID_DYNAMIC_COLOR_MIN)
		{
			unsigned int index = nID - ID_DYNAMIC_BUTTON_MIN;
			vector<CColorButton*>& buttons = GetGridButtons();
			if (index < buttons.size())
			{
				COLORREF color = 0;
				CColorButton* button = buttons[index];

				button->GetIndex(_mIndexLed, _mIndexRow, _mIndexColumn);

				// capture color
				if (!_mShiftModifier && !_mControlModifier)
				{
					color = GetColor();
					button->SetColor(color, color);
					button->Invalidate();
				}

				switch (_mDeviceType)
				{
				case EChromaSDKDeviceTypeEnum::DE_1D:
					{
						EChromaSDKDevice1DEnum device = _mEdit1D.GetDevice();
						int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(device);
						vector<FChromaSDKColorFrame1D>& frames = _mEdit1D.GetFrames();
						unsigned int currentFrame = _mEdit1D.GetCurrentFrame();
						if (currentFrame < 0 ||
							currentFrame >= frames.size())
						{
							currentFrame = 0;
						}
						if (currentFrame < frames.size())
						{
							FChromaSDKColorFrame1D& frame = frames[currentFrame];
							int i = index;

							// invert color
							if (_mControlModifier)
							{
								color = frame.Colors[i];
								int red = color & 0xFF;
								int green = (color >> 8) & 0xFF;
								int blue = (color >> 16) & 0xFF;
								// invert
								red = 255 - red;
								green = 255 - green;
								blue = 255 - blue;
								color = red | (green << 8) | (blue << 16);
								frame.Colors[i] = color;
								button->SetColor(color, color);
								button->Invalidate();
							}

							// set color
							if (!_mShiftModifier && !_mControlModifier)
							{
								frame.Colors[i] = color;
								RefreshGrid();
							}

							// capture ccolor
							if (_mShiftModifier)
							{
								color = frame.Colors[i];
								SetColor(color);
								GetColorButtons()[0]->SetColor(color, color);
								GetColorButtons()[0]->Invalidate();
								OnSliderBrushIntensity();
							}
						}
					}
					break;
				case EChromaSDKDeviceTypeEnum::DE_2D:
					{
						EChromaSDKDevice2DEnum device = _mEdit2D.GetDevice();
						int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(device);
						int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(device);
						vector<FChromaSDKColorFrame2D>& frames = _mEdit2D.GetFrames();
						unsigned int currentFrame = _mEdit2D.GetCurrentFrame();
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

							// invert color
							if (_mControlModifier)
							{
								color = row.Colors[j];
								int red = color & 0xFF;
								int green = (color >> 8) & 0xFF;
								int blue = (color >> 16) & 0xFF;
								// invert
								red = 255 - red;
								green = 255 - green;
								blue = 255 - blue;
								color = red | (green << 8) | (blue << 16);
								row.Colors[j] = color;
								button->SetColor(color, color);
								button->Invalidate();
							}

							// set color
							if (!_mShiftModifier && !_mControlModifier)
							{
								row.Colors[j] = color;
								RefreshGrid();
							}

							// capture ccolor
							if (_mShiftModifier)
							{
								color = row.Colors[j];
								SetColor(color);
								GetColorButtons()[0]->SetColor(color, color);
								GetColorButtons()[0]->Invalidate();
								OnSliderBrushIntensity();
							}							
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
					OnSliderBrushIntensity();
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
				OnSliderBrushIntensity();
			}
		}
	}

	//show changes
	OnBnClickedButtonPreview();
}

void CMainViewDlg::OnSelChangeListTypes()
{
	// stop animation
	OnBnClickedButtonStop();

	bool changed = false;

	EChromaSDKDeviceTypeEnum deviceType = EChromaSDKDeviceTypeEnum::DE_1D;
	int index = GetControlListTypes()->GetCurSel();
	switch (index)
	{
	case 0: //ChromaLink
		deviceType = EChromaSDKDeviceTypeEnum::DE_1D;
		break;
	case 1: //Headset
		deviceType = EChromaSDKDeviceTypeEnum::DE_1D;
		break;
	case 2: //Keyboard
		deviceType = EChromaSDKDeviceTypeEnum::DE_2D;
		break;
	case 3: //KeyboardExtended
		deviceType = EChromaSDKDeviceTypeEnum::DE_2D;
		break;
	case 4: //Keypad
		deviceType = EChromaSDKDeviceTypeEnum::DE_2D;
		break;
	case 5: //Mouse
		deviceType = EChromaSDKDeviceTypeEnum::DE_2D;
		break;
	case 6: //Mousepad
		deviceType = EChromaSDKDeviceTypeEnum::DE_1D;
		break;
	}
	if (_mDeviceType != deviceType)
	{
		_mDeviceType = deviceType;
		changed = true;
	}
	if (changed)
	{
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
	}

	EChromaSDKDevice1DEnum device1D = EChromaSDKDevice1DEnum::DE_ChromaLink;
	EChromaSDKDevice2DEnum device2D = EChromaSDKDevice2DEnum::DE_Keyboard;
	switch (index)
	{
	//chromalink
	case 0:
		device1D = EChromaSDKDevice1DEnum::DE_ChromaLink;
		break;
	//headset
	case 1:
		device1D = EChromaSDKDevice1DEnum::DE_Headset;
		break;
	//keyboard
	case 2:
		device2D = EChromaSDKDevice2DEnum::DE_Keyboard;
		break;
	//keyboard extended
	case 3:
		device2D = EChromaSDKDevice2DEnum::DE_KeyboardExtended;
		break;
	// keypad
	case 4:
		device2D = EChromaSDKDevice2DEnum::DE_Keypad;
		break;
	// mouse
	case 5:
		device2D = EChromaSDKDevice2DEnum::DE_Mouse;
		break;
	// mousepad
	case 6:
		device1D = EChromaSDKDevice1DEnum::DE_Mousepad;
		break;
	}

	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		if (_mEdit1D.SetDevice(device1D))
		{
			changed = true;
		}
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		if (_mEdit2D.SetDevice(device2D))
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

	GetControlListTypes()->SetCurSel(index);

	//show changes
	OnBnClickedButtonPreview();
}

void CMainViewDlg::OnBnClickedButtonImportOverrideTime()
{
	float time = GetOverrideTime();
	_mOverrideTime = time;
	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		_mEdit1D.OverrideTime(time);
		RefreshFrames();
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		_mEdit2D.OverrideTime(time);
		RefreshFrames();
		break;
	}

	//show changes
	OnBnClickedButtonPreview();
}

int CMainViewDlg::GetCurrentFrame()
{
	return GetEditor()->GetCurrentFrame();
}

void CMainViewDlg::SetCurrentFrame(unsigned int index)
{
	GetEditor()->SetCurrentFrame(index);
}

int CMainViewDlg::GetFrameCount()
{
	return GetEditor()->GetFrameCount();
}

void CMainViewDlg::OnBnClickedButtonClear()
{
	OnBnClickedButtonUnload(); // delete frame state

	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			EChromaSDKDevice1DEnum device = _mEdit1D.GetDevice();
			vector<FChromaSDKColorFrame1D>& frames = _mEdit1D.GetFrames();
			unsigned int currentFrame = _mEdit1D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
			if (currentFrame < frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[currentFrame];
				frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors1D(device);
				RefreshGrid();
			}
		}
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			EChromaSDKDevice2DEnum device = _mEdit2D.GetDevice();
			vector<FChromaSDKColorFrame2D>& frames = _mEdit2D.GetFrames();
			unsigned int currentFrame = _mEdit2D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
			if (currentFrame < frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[currentFrame];
				frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors2D(device);
				RefreshGrid();
			}
		}
		break;
	}

	//show changes
	OnBnClickedButtonPreview();
}


void CMainViewDlg::OnBnClickedButtonFill()
{
	OnBnClickedButtonUnload(); // delete frame state

	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			EChromaSDKDevice1DEnum device = _mEdit1D.GetDevice();
			int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(device);
			vector<FChromaSDKColorFrame1D>& frames = _mEdit1D.GetFrames();
			unsigned int currentFrame = _mEdit1D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
			if (currentFrame < frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[currentFrame];
				for (int i = 0; i < maxLeds; ++i)
				{
					frame.Colors[i] = GetColor();
				}
				RefreshGrid();
			}
		}
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			EChromaSDKDevice2DEnum device = _mEdit2D.GetDevice();
			int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(device);
			int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(device);
			vector<FChromaSDKColorFrame2D>& frames = _mEdit2D.GetFrames();
			unsigned int currentFrame = _mEdit2D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
			if (currentFrame < frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[currentFrame];
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						row.Colors[j] = GetColor();
					}
				}
				RefreshGrid();
			}
		}
		break;
	}

	//show changes
	OnBnClickedButtonPreview();
}

void CMainViewDlg::OnBnClickedButtonFillBlank()
{
	OnBnClickedButtonUnload(); // delete frame state

	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
	{
		EChromaSDKDevice1DEnum device = _mEdit1D.GetDevice();
		int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(device);
		vector<FChromaSDKColorFrame1D>& frames = _mEdit1D.GetFrames();
		unsigned int currentFrame = _mEdit1D.GetCurrentFrame();
		if (currentFrame < 0 ||
			currentFrame >= frames.size())
		{
			currentFrame = 0;
		}
		if (currentFrame < frames.size())
		{
			FChromaSDKColorFrame1D& frame = frames[currentFrame];
			for (int i = 0; i < maxLeds; ++i)
			{
				if (frame.Colors[i] == 0)
				{
					frame.Colors[i] = GetColor();
				}
			}
			RefreshGrid();
		}
	}
	break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
	{
		EChromaSDKDevice2DEnum device = _mEdit2D.GetDevice();
		int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(device);
		int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(device);
		vector<FChromaSDKColorFrame2D>& frames = _mEdit2D.GetFrames();
		unsigned int currentFrame = _mEdit2D.GetCurrentFrame();
		if (currentFrame < 0 ||
			currentFrame >= frames.size())
		{
			currentFrame = 0;
		}
		if (currentFrame < frames.size())
		{
			FChromaSDKColorFrame2D& frame = frames[currentFrame];
			for (int i = 0; i < maxRow; ++i)
			{
				FChromaSDKColors& row = frame.Colors[i];
				for (int j = 0; j < maxColumn; ++j)
				{
					if (row.Colors[j] == 0)
					{
						row.Colors[j] = GetColor();
					}
				}
			}
			RefreshGrid();
		}
	}
	break;
	}

	//show changes
	OnBnClickedButtonPreview();
}

void CMainViewDlg::OnBnClickedButtonDarken()
{
	OnBnClickedButtonUnload(); // delete frame state

	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
	{
		EChromaSDKDevice1DEnum device = _mEdit1D.GetDevice();
		int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(device);
		vector<FChromaSDKColorFrame1D>& frames = _mEdit1D.GetFrames();
		unsigned int currentFrame = _mEdit1D.GetCurrentFrame();
		if (currentFrame < 0 ||
			currentFrame >= frames.size())
		{
			currentFrame = 0;
		}
		if (currentFrame < frames.size())
		{
			FChromaSDKColorFrame1D& frame = frames[currentFrame];
			for (int i = 0; i < maxLeds; ++i)
			{
				COLORREF color = frame.Colors[i];
				int red = (color & 0xFF);
				int green = (color & 0xFF00) >> 8;
				int blue = (color & 0xFF0000) >> 16;
				red = max(0, red - 16);
				green = max(0, green - 16);
				blue = max(0, blue - 16);
				frame.Colors[i] = RGB(red, green, blue);
			}
			RefreshGrid();
		}
	}
	break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
	{
		EChromaSDKDevice2DEnum device = _mEdit2D.GetDevice();
		int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(device);
		int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(device);
		vector<FChromaSDKColorFrame2D>& frames = _mEdit2D.GetFrames();
		unsigned int currentFrame = _mEdit2D.GetCurrentFrame();
		if (currentFrame < 0 ||
			currentFrame >= frames.size())
		{
			currentFrame = 0;
		}
		if (currentFrame < frames.size())
		{
			FChromaSDKColorFrame2D& frame = frames[currentFrame];
			for (int i = 0; i < maxRow; ++i)
			{
				FChromaSDKColors& row = frame.Colors[i];
				for (int j = 0; j < maxColumn; ++j)
				{
					COLORREF color = row.Colors[j];
					int red = (color & 0xFF);
					int green = (color & 0xFF00) >> 8;
					int blue = (color & 0xFF0000) >> 16;
					red = max(0, red - 16);
					green = max(0, green - 16);
					blue = max(0, blue - 16);
					row.Colors[j] = RGB(red, green, blue);
				}
			}
			RefreshGrid();
		}
	}
	break;
	}

	//show changes
	OnBnClickedButtonPreview();
}

void CMainViewDlg::OnBnClickedButtonLighten()
{
	OnBnClickedButtonUnload(); // delete frame state

	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
	{
		EChromaSDKDevice1DEnum device = _mEdit1D.GetDevice();
		int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(device);
		vector<FChromaSDKColorFrame1D>& frames = _mEdit1D.GetFrames();
		unsigned int currentFrame = _mEdit1D.GetCurrentFrame();
		if (currentFrame < 0 ||
			currentFrame >= frames.size())
		{
			currentFrame = 0;
		}
		if (currentFrame < frames.size())
		{
			FChromaSDKColorFrame1D& frame = frames[currentFrame];
			for (int i = 0; i < maxLeds; ++i)
			{
				COLORREF color = frame.Colors[i];
				int red = (color & 0xFF);
				int green = (color & 0xFF00) >> 8;
				int blue = (color & 0xFF0000) >> 16;
				red = min(255, red + 16);
				green = min(255, green + 16);
				blue = min(255, blue + 16);
				frame.Colors[i] = RGB(red, green, blue);
			}
			RefreshGrid();
		}
	}
	break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
	{
		EChromaSDKDevice2DEnum device = _mEdit2D.GetDevice();
		int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(device);
		int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(device);
		vector<FChromaSDKColorFrame2D>& frames = _mEdit2D.GetFrames();
		unsigned int currentFrame = _mEdit2D.GetCurrentFrame();
		if (currentFrame < 0 ||
			currentFrame >= frames.size())
		{
			currentFrame = 0;
		}
		if (currentFrame < frames.size())
		{
			FChromaSDKColorFrame2D& frame = frames[currentFrame];
			for (int i = 0; i < maxRow; ++i)
			{
				FChromaSDKColors& row = frame.Colors[i];
				for (int j = 0; j < maxColumn; ++j)
				{
					COLORREF color = row.Colors[j];
					int red = (color & 0xFF);
					int green = (color & 0xFF00) >> 8;
					int blue = (color & 0xFF0000) >> 16;
					red = min(255, red + 16);
					green = min(255, green + 16);
					blue = min(255, blue + 16);
					row.Colors[j] = RGB(red, green, blue);
				}
			}
			RefreshGrid();
		}
	}
	break;
	}

	//show changes
	OnBnClickedButtonPreview();
}

void CMainViewDlg::OnBnClickedButtonRandom()
{
	OnBnClickedButtonUnload(); // delete frame state

	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			EChromaSDKDevice1DEnum device = _mEdit1D.GetDevice();
			vector<FChromaSDKColorFrame1D>& frames = _mEdit1D.GetFrames();
			unsigned int currentFrame = _mEdit1D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
			if (currentFrame < frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[currentFrame];
				frame.Colors = ChromaSDKPlugin::GetInstance()->CreateRandomColors1D(device);
				RefreshGrid();
			}
		}
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			EChromaSDKDevice2DEnum device = _mEdit2D.GetDevice();
			vector<FChromaSDKColorFrame2D>& frames = _mEdit2D.GetFrames();
			unsigned int currentFrame = _mEdit2D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
			if (currentFrame < frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[currentFrame];
				frame.Colors = ChromaSDKPlugin::GetInstance()->CreateRandomColors2D(device);
				RefreshGrid();
			}
		}
		break;
	}

	//show changes
	OnBnClickedButtonPreview();
}


void CMainViewDlg::OnBnClickedButtonCopy()
{
	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			EChromaSDKDevice1DEnum device = _mEdit1D.GetDevice();
			vector<FChromaSDKColorFrame1D>& frames = _mEdit1D.GetFrames();
			unsigned int currentFrame = _mEdit1D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
			if (currentFrame < frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[currentFrame];
				_mEdit1D.SetCopy(frame);
			}
		}
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			EChromaSDKDevice2DEnum device = _mEdit2D.GetDevice();
			vector<FChromaSDKColorFrame2D>& frames = _mEdit2D.GetFrames();
			unsigned int currentFrame = _mEdit2D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
			if (currentFrame < frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[currentFrame];
				_mEdit2D.SetCopy(frame);
			}
		}
		break;
	}
}


void CMainViewDlg::OnBnClickedButtonPaste()
{
	OnBnClickedButtonUnload(); // delete frame state

	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			EChromaSDKDevice1DEnum device = _mEdit1D.GetDevice();
			vector<FChromaSDKColorFrame1D>& frames = _mEdit1D.GetFrames();
			unsigned int currentFrame = _mEdit1D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
			if (currentFrame < frames.size())
			{
				frames[currentFrame] = _mEdit1D.GetCopy();
				RefreshGrid();
				RefreshFrames();
			}
		}
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			EChromaSDKDevice2DEnum device = _mEdit2D.GetDevice();
			vector<FChromaSDKColorFrame2D>& frames = _mEdit2D.GetFrames();
			unsigned int currentFrame = _mEdit2D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
			if (currentFrame < frames.size())
			{
				frames[currentFrame] = _mEdit2D.GetCopy();
				RefreshGrid();
				RefreshFrames();
			}
		}
		break;
	}

	//show changes
	OnBnClickedButtonPreview();
}


void CMainViewDlg::OnBnClickedButtonPreview()
{
	OnBnClickedButtonUnload(); // delete frame state

	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			EChromaSDKDevice1DEnum device = _mEdit1D.GetDevice();
			vector<FChromaSDKColorFrame1D>& frames = _mEdit1D.GetFrames();
			unsigned int currentFrame = _mEdit1D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
			if (currentFrame < frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[currentFrame];
				FChromaSDKEffectResult result = ChromaSDKPlugin::GetInstance()->CreateEffectCustom1D(device, frame.Colors);
				if (result.Result == 0)
				{
					ChromaSDKPlugin::GetInstance()->SetEffect(result.EffectId);
					ChromaSDKPlugin::GetInstance()->DeleteEffect(result.EffectId);
				}
			}
		}
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			EChromaSDKDevice2DEnum device = _mEdit2D.GetDevice();
			vector<FChromaSDKColorFrame2D>& frames = _mEdit2D.GetFrames();
			unsigned int currentFrame = _mEdit2D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= frames.size())
			{
				currentFrame = 0;
			}
			if (currentFrame < frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[currentFrame];
				FChromaSDKEffectResult result = ChromaSDKPlugin::GetInstance()->CreateEffectCustom2D(device, frame.Colors, frame.Keys);
				if (result.Result == 0)
				{
					ChromaSDKPlugin::GetInstance()->SetEffect(result.EffectId);
					ChromaSDKPlugin::GetInstance()->DeleteEffect(result.EffectId);
				}
			}
		}
		break;
	}
}

EditorAnimationBase* CMainViewDlg::GetEditor()
{
	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		return &_mEdit1D;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		return &_mEdit2D;
	default:
		return nullptr;
	}
}

AnimationBase* CMainViewDlg::GetAnimation()
{
	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		return _mEdit1D.GetAnimation();
	case EChromaSDKDeviceTypeEnum::DE_2D:
		return _mEdit2D.GetAnimation();
	default:
		return nullptr;
	}
}

void CMainViewDlg::OnBnClickedButtonPlay()
{
	if (GetAnimation() != nullptr)
	{
		GetAnimation()->Load();
		GetAnimation()->Play(false);
	}
}

void CMainViewDlg::OnBnClickedButtonLoop()
{
	if (GetAnimation() != nullptr)
	{
		GetAnimation()->Load();
		GetAnimation()->Play(true);
	}
}

void CMainViewDlg::OnBnClickedButtonStop()
{
	if (GetAnimation() != nullptr)
	{
		GetAnimation()->Stop();
	}
}


void CMainViewDlg::OnBnClickedButtonLoad()
{
	if (GetAnimation() != nullptr)
	{
		GetAnimation()->Load();
	}
}


void CMainViewDlg::OnBnClickedButtonUnload()
{
	if (GetAnimation() != nullptr)
	{
		GetAnimation()->Unload();
	}
}


void CMainViewDlg::OnBnClickedButtonSetKey()
{
	OnBnClickedButtonUnload(); // delete frame state

	if (_mDeviceType == EChromaSDKDeviceTypeEnum::DE_2D &&
		_mEdit2D.GetDevice() == EChromaSDKDevice2DEnum::DE_Keyboard)
	{
		vector<FChromaSDKColorFrame2D>& frames = _mEdit2D.GetFrames();
		unsigned int currentFrame = _mEdit2D.GetCurrentFrame();
		if (currentFrame < 0 ||
			currentFrame >= frames.size())
		{
			currentFrame = 0;
		}
		if (currentFrame < frames.size())
		{
			int id = GetControlSetKeyCombo()->GetCurSel();
			EChromaSDKKeyboardKey key = (EChromaSDKKeyboardKey)id;
			FChromaSDKColorFrame2D& frame = frames[currentFrame];
			std::vector<FChromaSDKColors>& colors = frame.Colors;
			ChromaSDKPlugin::GetInstance()->SetKeyboardKeyColor(key, GetColor(), colors);
			RefreshGrid();
		}
	}

	//show changes
	OnBnClickedButtonPreview();
}

void CMainViewDlg::OnBnClickedButtonSetLed()
{
	OnBnClickedButtonUnload(); // delete frame state

	if (_mDeviceType == EChromaSDKDeviceTypeEnum::DE_2D &&
		_mEdit2D.GetDevice() == EChromaSDKDevice2DEnum::DE_Mouse)
	{
		vector<FChromaSDKColorFrame2D>& frames = _mEdit2D.GetFrames();
		unsigned int currentFrame = _mEdit2D.GetCurrentFrame();
		if (currentFrame < 0 ||
			currentFrame >= frames.size())
		{
			currentFrame = 0;
		}
		if (currentFrame < frames.size())
		{
			int id = GetControlSetLEDCombo()->GetCurSel();
			EChromaSDKMouseLED led = (EChromaSDKMouseLED)id;
			FChromaSDKColorFrame2D& frame = frames[currentFrame];
			std::vector<FChromaSDKColors>& colors = frame.Colors;
			ChromaSDKPlugin::GetInstance()->SetMouseLEDColor(led, GetColor(), colors);
			RefreshGrid();
		}
	}

	//show changes
	OnBnClickedButtonPreview();
}

void CMainViewDlg::OnBnClickedButtonFirst()
{
	SetCurrentFrame(0);
	RefreshGrid();
	RefreshFrames();

	//show changes
	OnBnClickedButtonPreview();
}

void CMainViewDlg::OnBnClickedButtonLast()
{
	int frameCount = GetFrameCount();
	if (frameCount > 0)
	{
		SetCurrentFrame(frameCount - 1);
		RefreshGrid();
		RefreshFrames();

		//show changes
		OnBnClickedButtonPreview();
	}
}

void CMainViewDlg::OnBnClickedButtonPrevious()
{
	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			unsigned int currentFrame = _mEdit1D.GetCurrentFrame();
			if (currentFrame < 1 ||
				currentFrame >= _mEdit1D.GetFrameCount())
			{
				currentFrame = 0;
			}
			else
			{
				--currentFrame;
			}
			_mEdit1D.SetCurrentFrame(currentFrame);
			RefreshGrid();
			RefreshFrames();
		}
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			unsigned int currentFrame = _mEdit2D.GetCurrentFrame();
			if (currentFrame < 1 ||
				currentFrame >= _mEdit2D.GetFrameCount())
			{
				currentFrame = 0;
			}
			else
			{
				--currentFrame;
			}
			_mEdit2D.SetCurrentFrame(currentFrame);			
			RefreshGrid();
			RefreshFrames();
		}
		break;
	}

	//show changes
	OnBnClickedButtonPreview();
}


void CMainViewDlg::OnBnClickedButtonNext()
{
	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			unsigned int currentFrame = _mEdit1D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= _mEdit1D.GetFrameCount())
			{
				currentFrame = 0;
			}
			if ((currentFrame + 1) < _mEdit1D.GetFrameCount())
			{
				++currentFrame;
			}
			_mEdit1D.SetCurrentFrame(currentFrame);
			RefreshGrid();
			RefreshFrames();
		}
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			unsigned int currentFrame = _mEdit2D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= _mEdit2D.GetFrameCount())
			{
				currentFrame = 0;
			}
			if ((currentFrame + 1) < _mEdit2D.GetFrameCount())
			{
				++currentFrame;
			}
			_mEdit2D.SetCurrentFrame(currentFrame);			
			RefreshGrid();
			RefreshFrames();
		}
		break;
	}

	//show changes
	OnBnClickedButtonPreview();
}

void CMainViewDlg::OnBnClickedButtonInsert()
{
	OnBnClickedButtonUnload(); // delete frame state

	OnBnClickedButtonCopy();
	OnBnClickedButtonAdd();
	OnBnClickedButtonNext();
	OnBnClickedButtonPaste();
	OnBnClickedButtonPrevious();
	OnBnClickedButtonClear();
}

void CMainViewDlg::OnBnClickedButtonAdd()
{
	OnBnClickedButtonUnload(); // delete frame state

	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		_mEdit1D.AddFrame();
		RefreshGrid();
		RefreshFrames();
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		_mEdit2D.AddFrame();
		RefreshGrid();
		RefreshFrames();
		break;
	}

	//show changes
	OnBnClickedButtonPreview();
}

void CMainViewDlg::OnBnClickedButtonDuplicate()
{
	OnBnClickedButtonUnload(); // delete frame state

	OnBnClickedButtonCopy();

	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		_mEdit1D.AddFrame();
		RefreshGrid();
		RefreshFrames();
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		_mEdit2D.AddFrame();
		RefreshGrid();
		RefreshFrames();
		break;
	}

	OnBnClickedButtonPaste();

	//show changes
	OnBnClickedButtonPreview();
}

void CMainViewDlg::OnBnClickedButtonDelete()
{
	OnBnClickedButtonUnload(); // delete frame state

	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			unsigned int currentFrame = _mEdit1D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= _mEdit1D.GetFrameCount())
			{
				currentFrame = 0;
			}			
			vector<FChromaSDKColorFrame1D>& frames = _mEdit1D.GetFrames();
			if (frames.size() == 1)
			{
				FChromaSDKColorFrame1D frame = FChromaSDKColorFrame1D();
				frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors1D(_mEdit1D.GetDevice());
				frames[0] = frame;
			}
			else if (frames.size() > 0)
			{
				auto it = frames.begin();
				frames.erase(it+currentFrame);
				if (currentFrame == frames.size())
				{
					currentFrame = frames.size() - 1;
					_mEdit1D.SetCurrentFrame(currentFrame);
				}
			}
			RefreshGrid();
			RefreshFrames();
		}
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			unsigned int currentFrame = _mEdit2D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= _mEdit2D.GetFrameCount())
			{
				currentFrame = 0;
			}			
			vector<FChromaSDKColorFrame2D>& frames = _mEdit2D.GetFrames();
			if (frames.size() == 1)
			{
				FChromaSDKColorFrame2D frame = FChromaSDKColorFrame2D(_mEdit2D.GetDevice());
				frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors2D(_mEdit2D.GetDevice());
				frames[0] = frame;
			}
			else if (frames.size() > 0)
			{
				auto it = frames.begin();
				frames.erase(it+currentFrame);
				if (currentFrame == frames.size())
				{
					currentFrame = frames.size() - 1;
					_mEdit2D.SetCurrentFrame(currentFrame);
				}
			}
			RefreshGrid();
			RefreshFrames();
		}
		break;
	}

	//show changes
	OnBnClickedButtonPreview();
}


void CMainViewDlg::OnBnClickedButtonReset()
{
	OnBnClickedButtonUnload(); // delete frame state

	OnBnClickedButtonStop();

	AnimationBase* animation = GetAnimation();
	if (animation != nullptr)
	{
		animation->ResetFrames();
		RefreshGrid();
		RefreshFrames();
	}

	//show changes
	OnBnClickedButtonPreview();
}


void CMainViewDlg::OnBnClickedButtonSetDuration()
{
	switch (_mDeviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			unsigned int currentFrame = _mEdit1D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= _mEdit1D.GetFrameCount())
			{
				currentFrame = 0;
			}			
			if (currentFrame < _mEdit1D.GetFrameCount())
			{
				vector<FChromaSDKColorFrame1D>& frames = _mEdit1D.GetFrames();
				FChromaSDKColorFrame1D& frame = frames[currentFrame];
				frame.Duration = GetDuration();
				RefreshFrames();
			}
		}
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			unsigned int currentFrame = _mEdit2D.GetCurrentFrame();
			if (currentFrame < 0 ||
				currentFrame >= _mEdit2D.GetFrameCount())
			{
				currentFrame = 0;
			}			
			if (currentFrame < _mEdit2D.GetFrameCount())
			{
				vector<FChromaSDKColorFrame2D>& frames = _mEdit2D.GetFrames();
				FChromaSDKColorFrame2D& frame = frames[currentFrame];
				frame.Duration = GetDuration();
				RefreshFrames();
			}
		}
		break;
	}

	//show changes
	OnBnClickedButtonPreview();
}
