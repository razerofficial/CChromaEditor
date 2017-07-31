#pragma once

#include "ChromaSDKPluginTypes.h"
#include "AnimationBase.h"

namespace ChromaSDK
{
	class Animation1D : public AnimationBase
	{
	public:
		Animation1D();
		void Reset();
		EChromaSDKDevice1DEnum GetDevice();
		bool SetDevice(EChromaSDKDevice1DEnum device);
		std::vector<FChromaSDKColorFrame1D>& GetFrames();
		int GetFrameCount();
		void Play();
		void Stop();
		void Update();
	private:
		EChromaSDKDevice1DEnum _mDevice;
		std::vector<FChromaSDKColorFrame1D> _mFrames;
	};
}
