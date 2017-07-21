#pragma once

#include "Animation2D.h"

namespace ChromaSDK
{
	class EditorAnimation2D
	{
	public:
		EditorAnimation2D();
		EChromaSDKDevice2DEnum GetDevice();
		bool SetDevice(EChromaSDKDevice2DEnum device);
		int GetCurrentFrame();
		std::vector<FChromaSDKColorFrame2D>& GetFrames();
		void SetCopy(FChromaSDKColorFrame2D& copy);
		FChromaSDKColorFrame2D& GetCopy();
	private:
		void Reset();
		Animation2D _mAnimation;
		int _mCurrentFrame;
		FChromaSDKColorFrame2D _mFrameCopy;
	};
}
