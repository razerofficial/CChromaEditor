#include "stdafx.h"
#include "EditorAnimation2D.h"
#include "ChromaSDKPlugin.h"

using namespace ChromaSDK;
using namespace std;

EditorAnimation2D::EditorAnimation2D()
{
	Reset();
}

EChromaSDKDevice2DEnum EditorAnimation2D::GetDevice()
{
	return _mAnimation.GetDevice();
}

bool EditorAnimation2D::SetDevice(EChromaSDKDevice2DEnum device)
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

int EditorAnimation2D::GetCurrentFrame()
{
	return _mCurrentFrame;
}

vector<FChromaSDKColorFrame2D>& EditorAnimation2D::GetFrames()
{
	return _mAnimation.GetFrames();
}

void EditorAnimation2D::Reset()
{
	EChromaSDKDevice2DEnum device = GetDevice();
	_mFrameCopy.Colors = ChromaSDKPlugin::GetInstance()->CreateColors2D(device);
}

void EditorAnimation2D::SetCopy(FChromaSDKColorFrame2D& copy)
{
	_mFrameCopy = copy;
}

FChromaSDKColorFrame2D& EditorAnimation2D::GetCopy()
{
	return _mFrameCopy;
}
