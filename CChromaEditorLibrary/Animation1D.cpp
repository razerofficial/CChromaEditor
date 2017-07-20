#include "stdafx.h"
#include "Animation1D.h"
#include "ChromaSDKPlugin.h"

using namespace ChromaSDK;

Animation1D::Animation1D()
{
	Reset();
}

void Animation1D::Reset()
{
	_mFrames.clear();
	FChromaSDKColorFrame1D frame = FChromaSDKColorFrame1D();
	frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors1D(_mDevice);
	_mFrames.push_back(frame);
}

EChromaSDKDevice1DEnum Animation1D::GetDevice()
{
	return _mDevice;
}

bool Animation1D::SetDevice(EChromaSDKDevice1DEnum device)
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
