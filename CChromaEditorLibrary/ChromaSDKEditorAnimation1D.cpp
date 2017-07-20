#include "stdafx.h"
#include "ChromaSDKEditorAnimation1D.h"

EChromaSDKDevice1DEnum ChromaSDKEditorAnimation1D::GetDevice()
{
	return _mDevice;
}

void ChromaSDKEditorAnimation1D::SetDevice(EChromaSDKDevice1DEnum device)
{
	_mDevice = device;
}
