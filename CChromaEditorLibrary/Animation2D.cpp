#include "stdafx.h"
#include "Animation2D.h"

using namespace ChromaSDK;

EChromaSDKDevice2DEnum Animation2D::GetDevice()
{
	return _mDevice;
}

bool Animation2D::SetDevice(EChromaSDKDevice2DEnum device)
{
	if (_mDevice != device)
	{
		_mDevice = device;
		return true;
	}
	else
	{
		return false;
	}
}
