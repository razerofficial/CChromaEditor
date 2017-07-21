#include "stdafx.h"
#include "EditorAnimation1D.h"
#include "ChromaSDKPlugin.h"

using namespace ChromaSDK;
using namespace std;

EditorAnimation1D::EditorAnimation1D()
{
	Reset();
}

EChromaSDKDevice1DEnum EditorAnimation1D::GetDevice()
{
	return _mAnimation.GetDevice();
}

bool EditorAnimation1D::SetDevice(EChromaSDKDevice1DEnum device)
{
	if (_mAnimation.SetDevice(device))
	{
		Reset();
	}
	else
	{
		return false;
	}
}

int EditorAnimation1D::GetCurrentFrame()
{
	return _mCurrentFrame;
}

vector<FChromaSDKColorFrame1D>& EditorAnimation1D::GetFrames()
{
	return _mAnimation.GetFrames();
}

void EditorAnimation1D::Reset()
{
	EChromaSDKDevice1DEnum device = GetDevice();
	_mFrameCopy.Colors = ChromaSDKPlugin::GetInstance()->CreateColors1D(device);
}

void EditorAnimation1D::SetCopy(FChromaSDKColorFrame1D& copy)
{
	_mFrameCopy = copy;
}

FChromaSDKColorFrame1D& EditorAnimation1D::GetCopy()
{
	return _mFrameCopy;
}
