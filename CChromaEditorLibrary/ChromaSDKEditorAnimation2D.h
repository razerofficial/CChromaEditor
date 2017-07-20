#pragma once

#include "ChromaSDKPluginTypes.h"

class ChromaSDKEditorAnimation2D
{
public:
	EChromaSDKDevice2DEnum GetDevice();
	void SetDevice(EChromaSDKDevice2DEnum device);
private:
	EChromaSDKDevice2DEnum _mDevice;
};
