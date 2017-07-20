#include "stdafx.h"
#include "EditorAnimation2D.h"

using namespace ChromaSDK;

EChromaSDKDevice2DEnum EditorAnimation2D::GetDevice()
{
	return _mAnimation.GetDevice();
}

bool EditorAnimation2D::SetDevice(EChromaSDKDevice2DEnum device)
{
	return _mAnimation.SetDevice(device);
}
