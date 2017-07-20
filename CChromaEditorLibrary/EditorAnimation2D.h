#pragma once

#include "Animation2D.h"

namespace ChromaSDK
{
	class EditorAnimation2D
	{
	public:
		EChromaSDKDevice2DEnum GetDevice();
		bool SetDevice(EChromaSDKDevice2DEnum device);
		int GetCurrentFrame();
		std::vector<FChromaSDKColorFrame2D>& GetFrames();
	private:
		Animation2D _mAnimation;
		int _mCurrentFrame;
	};
}
