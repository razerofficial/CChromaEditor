#pragma once

#include "ChromaSDKPluginTypes.h"
#include "AnimationBase.h"

namespace ChromaSDK
{
	class Animation2D : public AnimationBase
	{
	public:
		Animation2D();
		void Reset();
		EChromaSDKDevice2DEnum GetDevice();
		bool SetDevice(EChromaSDKDevice2DEnum device);
		std::vector<FChromaSDKColorFrame2D>& GetFrames();
		int GetFrameCount();
		void Play();
		void Stop();
		void Update();
	private:
		EChromaSDKDevice2DEnum _mDevice;
		std::vector<FChromaSDKColorFrame2D> _mFrames;
	};
}
