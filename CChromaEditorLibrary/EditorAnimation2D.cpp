#include "stdafx.h"
#include "EditorAnimation2D.h"
#include "ChromaSDKPlugin.h"

using namespace ChromaSDK;
using namespace std;

EditorAnimation2D::EditorAnimation2D()
{
	Reset();
}

AnimationBase* EditorAnimation2D::GetAnimation()
{
	return &_mAnimation;
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

vector<FChromaSDKColorFrame2D>& EditorAnimation2D::GetFrames()
{
	return _mAnimation.GetFrames();
}

void EditorAnimation2D::Reset()
{
	EChromaSDKDevice2DEnum device = GetDevice();
	_mFrameCopy.Colors = ChromaSDKPlugin::GetInstance()->CreateColors2D(device);
	_mAnimation.Reset();
}

void EditorAnimation2D::SetCopy(FChromaSDKColorFrame2D& copy)
{
	_mFrameCopy = copy;
}

FChromaSDKColorFrame2D& EditorAnimation2D::GetCopy()
{
	return _mFrameCopy;
}

void EditorAnimation2D::OverrideTime(float time)
{
	vector<FChromaSDKColorFrame2D>& frames = GetFrames();
	for (int i = 0; i < frames.size(); ++i)
	{
		FChromaSDKColorFrame2D& frame = frames[i];
		frame.Duration = time;
	}
}

float EditorAnimation2D::GetDuration(int index)
{
	vector<FChromaSDKColorFrame2D>& frames = GetFrames();
	if (index < frames.size())
	{
		FChromaSDKColorFrame2D& frame = frames[index];
		return frame.Duration;
	}
	return 0.0f;
}
