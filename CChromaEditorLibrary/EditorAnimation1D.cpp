#include "stdafx.h"
#include "EditorAnimation1D.h"

using namespace ChromaSDK;

EChromaSDKDevice1DEnum EditorAnimation1D::GetDevice()
{
	return _mAnimation.GetDevice();
}

bool EditorAnimation1D::SetDevice(EChromaSDKDevice1DEnum device)
{
	return _mAnimation.SetDevice(device);
}
