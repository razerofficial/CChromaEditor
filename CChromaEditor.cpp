
// CChromaEditor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "CChromaEditor.h"
#include "MainFrm.h"
#include "ColorButton.h"
#include <vector>

#include "CChromaEditorDoc.h"
#include "CChromaEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCChromaEditorApp

BEGIN_MESSAGE_MAP(CCChromaEditorApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CCChromaEditorApp::OnAppMainView)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CCChromaEditorApp construction

CCChromaEditorApp::CCChromaEditorApp()
{
	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("CChromaEditor.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CCChromaEditorApp object

CCChromaEditorApp theApp;


// CCChromaEditorApp initialization

BOOL CCChromaEditorApp::InitInstance()
{
	// just show the main dialog
	CCChromaEditorApp::OnAppMainView();
	return false;
	// and exit

	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CCChromaEditorDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CCChromaEditorView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

// CCChromaEditorApp message handlers


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

	std::vector<CColorButton*> _mButtons;

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonImportImage();
	afx_msg void OnBnClickedButtonImportAnimation();
	afx_msg void OnEnChangeOverrideTime2();
	afx_msg void OnBnClickedButtonImportOverrideTime();
	afx_msg void OnCbnSelchangeCombo1();
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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonBrushColor();
};

CMainViewDlg::CMainViewDlg() : CDialogEx(IDD_MAIN_VIEW)
{
}

BOOL CMainViewDlg::OnInitDialog()
{
	const int width = 15;
	const int height = 30;
	int y = 238;
	int id = 1000;
	for (int j = 0; j < 6; ++j)
	{
		int x = 25;
		for (int i = 0; i < 22; ++i)
		{
			++id;
			CColorButton* button = new CColorButton(RGB(0, 0, 0), RGB(255, 0, 0));
			const int flags = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON |
				BS_OWNERDRAW | BS_MULTILINE;
			button->Create(_T(""), flags, CRect(x, y, x + width, y + height), this, id);
			_mButtons.push_back(button);
			x += width + 2;
		}

		y += height + 2;
	}

	return TRUE;
}

void CMainViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMainViewDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_IMAGE, &CMainViewDlg::OnBnClickedButtonImportImage)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_ANIMATION, &CMainViewDlg::OnBnClickedButtonImportAnimation)
	ON_EN_CHANGE(IDC_OVERRIDE_TIME2, &CMainViewDlg::OnEnChangeOverrideTime2)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_OVERRIDE_TIME, &CMainViewDlg::OnBnClickedButtonImportOverrideTime)
	ON_CBN_SELCHANGE(IDC_COMBO_DEVICES, &CMainViewDlg::OnCbnSelchangeCombo1)
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
	ON_BN_CLICKED(IDC_BUTTON_BRUSH_COLOR, &CMainViewDlg::OnBnClickedButtonBrushColor)
END_MESSAGE_MAP()

// App command to run the dialog
void CCChromaEditorApp::OnAppMainView()
{
	// dialog instance
	CMainViewDlg mainViewDlg;

	// keep dialog focused
	mainViewDlg.DoModal();
}

// CCChromaEditorApp message handlers





void CMainViewDlg::OnBnClickedButtonImportImage()
{
	// TODO: Add your control notification handler code here
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


void CMainViewDlg::OnCbnSelchangeCombo1()
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


void CMainViewDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
}


void CMainViewDlg::OnBnClickedButtonBrushColor()
{
	// TODO: Add your control notification handler code here
}
