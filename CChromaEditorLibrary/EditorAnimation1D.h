#pragma once

#include "Animation1D.h"

namespace ChromaSDK
{
	class EditorAnimation1D
	{
	public:
		EChromaSDKDevice1DEnum GetDevice();
		bool SetDevice(EChromaSDKDevice1DEnum device);
		int GetCurrentFrame();
		std::vector<FChromaSDKColorFrame1D>& GetFrames();
	private:
		Animation1D _mAnimation;
		int _mCurrentFrame;
	};
}
