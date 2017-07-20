#include "stdafx.h"
#include "Animation2D.h"

using namespace ChromaSDK;

EChromaSDKDevice2DEnum Animation2D::GetDevice()
{
	return _mDevice;
}

void Animation2D::SetDevice(EChromaSDKDevice2DEnum device)
{
	_mDevice = device;
}
