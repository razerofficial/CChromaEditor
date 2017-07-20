#pragma once

#include "ChromaSDKPluginTypes.h"

class ChromaSDKEditorAnimation2D
{
public:
	EChromaSDKDevice2DEnum GetDevice();
private:
	EChromaSDKDevice2DEnum _mDevice;
};
