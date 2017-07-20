#pragma once

#include "ChromaSDKPluginTypes.h"

namespace ChromaSDK
{
	class Animation1D
	{
	public:
		Animation1D();
		void Reset();
		EChromaSDKDevice1DEnum GetDevice();
		bool SetDevice(EChromaSDKDevice1DEnum device);
	private:
		EChromaSDKDevice1DEnum _mDevice;
		std::vector<FChromaSDKColorFrame1D> _mFrames;
	};
}
