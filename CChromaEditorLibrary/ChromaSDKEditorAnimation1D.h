#pragma once

#include "ChromaSDKPluginTypes.h"

class ChromaSDKEditorAnimation1D
{
public:
	EChromaSDKDevice1DEnum GetDevice();
private:
	EChromaSDKDevice1DEnum _mDevice;
};
