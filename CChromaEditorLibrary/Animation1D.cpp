#include "stdafx.h"
#include "Animation1D.h"

using namespace ChromaSDK;

EChromaSDKDevice1DEnum Animation1D::GetDevice()
{
	return _mDevice;
}

bool Animation1D::SetDevice(EChromaSDKDevice1DEnum device)
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
