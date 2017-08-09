#include "stdafx.h"
#include "EditorAnimationBase.h"
#include "direct.h"
#include <string>

using namespace std;

int EditorAnimationBase::GetCurrentFrame()
{
	return GetAnimation()->GetCurrentFrame();
}

void EditorAnimationBase::SetCurrentFrame(unsigned int index)
{
	GetAnimation()->SetCurrentFrame(index);
}

unsigned int EditorAnimationBase::GetFrameCount()
{
	return GetAnimation()->GetFrameCount();
}

void EditorAnimationBase::ImportTextureImage()
{
	char cCurrentPath[FILENAME_MAX];
	if (!_getcwd(cCurrentPath, sizeof(cCurrentPath)))
	{
		return;
	}

	const int MAX_CFileDialog_FILE_COUNT = 99;
	const int FILE_LIST_BUFFER_SIZE = ((MAX_CFileDialog_FILE_COUNT * (MAX_PATH + 1)) + 1);

	CString fileName;
	wchar_t* p = fileName.GetBuffer(FILE_LIST_BUFFER_SIZE);
	CFileDialog dlgFile(TRUE);
	OPENFILENAME& ofn = dlgFile.GetOFN();
	ofn.lpstrFilter = _TEXT("Image Files\0*.bmp;*.jpg;*.png\0");
	CString szDir;
	szDir += cCurrentPath;
	ofn.lpstrInitialDir = szDir;
	ofn.lpstrFile = p;
	ofn.nMaxFile = FILE_LIST_BUFFER_SIZE;

	if (dlgFile.DoModal() == IDOK)
	{
		string strFileName = string(CT2CA(fileName));
		LogDebug("ImportTextureImage: %s\r\n", strFileName.c_str());
	}
	fileName.ReleaseBuffer();
}

void EditorAnimationBase::ImportTextureAnimation()
{
	char cCurrentPath[FILENAME_MAX];
	if (!_getcwd(cCurrentPath, sizeof(cCurrentPath)))
	{
		return;
	}

	const int MAX_CFileDialog_FILE_COUNT = 99;
	const int FILE_LIST_BUFFER_SIZE = ((MAX_CFileDialog_FILE_COUNT * (MAX_PATH + 1)) + 1);

	CString fileName;
	wchar_t* p = fileName.GetBuffer(FILE_LIST_BUFFER_SIZE);
	CFileDialog dlgFile(TRUE);
	OPENFILENAME& ofn = dlgFile.GetOFN();
	ofn.lpstrFilter = _TEXT("Image Files\0*.gif\0");
	CString szDir;
	szDir += cCurrentPath;
	ofn.lpstrInitialDir = szDir;
	ofn.lpstrFile = p;
	ofn.nMaxFile = FILE_LIST_BUFFER_SIZE;

	if (dlgFile.DoModal() == IDOK)
	{
		string strFileName = string(CT2CA(fileName));
		LogDebug("ImportTextureAnimation: %s\r\n", strFileName.c_str());
	}
	fileName.ReleaseBuffer();
}
