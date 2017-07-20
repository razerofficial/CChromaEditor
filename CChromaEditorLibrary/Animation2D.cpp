#include "stdafx.h"
#include "Animation2D.h"
#include "ChromaSDKPlugin.h"

using namespace ChromaSDK;

Animation2D::Animation2D()
{
	Reset();
}

void Animation2D::Reset()
{
	_mFrames.clear();
	FChromaSDKColorFrame2D frame = FChromaSDKColorFrame2D();
	frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors2D(_mDevice);
	_mFrames.push_back(frame);
}

EChromaSDKDevice2DEnum Animation2D::GetDevice()
{
	return _mDevice;
}

bool Animation2D::SetDevice(EChromaSDKDevice2DEnum device)
{
	if (_mDevice != device)
	{
		_mDevice = device;
		Reset();
		return true;
	}
	else
	{
		return false;
	}
}
