#include "stdafx.h"
#include "Animation1D.h"

using namespace ChromaSDK;

EChromaSDKDevice1DEnum Animation1D::GetDevice()
{
	return _mDevice;
}

void Animation1D::SetDevice(EChromaSDKDevice1DEnum device)
{
	_mDevice = device;
}
