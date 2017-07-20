#pragma once

#include "ChromaSDKPluginTypes.h"

class ChromaSDKEditorAnimation1D
{
public:
	EChromaSDKDevice1DEnum GetDevice();
	void SetDevice(EChromaSDKDevice1DEnum device);
private:
	EChromaSDKDevice1DEnum _mDevice;
};
