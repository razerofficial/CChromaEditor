#include "stdafx.h"
#include "ChromaSDKEditorAnimation2D.h"

EChromaSDKDevice2DEnum ChromaSDKEditorAnimation2D::GetDevice()
{
	return _mDevice;
}

void ChromaSDKEditorAnimation2D::SetDevice(EChromaSDKDevice2DEnum device)
{
	_mDevice = device;
}
