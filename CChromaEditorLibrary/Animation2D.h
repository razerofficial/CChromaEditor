#pragma once

#include "ChromaSDKPluginTypes.h"

namespace ChromaSDK
{
	class Animation2D
	{
	public:
		Animation2D();
		void Reset();
		EChromaSDKDevice2DEnum GetDevice();
		bool SetDevice(EChromaSDKDevice2DEnum device);
	private:
		EChromaSDKDevice2DEnum _mDevice;
		std::vector<FChromaSDKColorFrame2D> _mFrames;
	};
}
