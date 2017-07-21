#pragma once

#include "Animation1D.h"

namespace ChromaSDK
{
	class EditorAnimation1D
	{
	public:
		EditorAnimation1D();
		EChromaSDKDevice1DEnum GetDevice();
		bool SetDevice(EChromaSDKDevice1DEnum device);
		int GetCurrentFrame();
		std::vector<FChromaSDKColorFrame1D>& GetFrames();
		void SetCopy(FChromaSDKColorFrame1D& copy);
		FChromaSDKColorFrame1D& GetCopy();
		void OverrideTime(float time);
	private:
		void Reset();
		Animation1D _mAnimation;
		int _mCurrentFrame;
		FChromaSDKColorFrame1D _mFrameCopy;
	};
}
