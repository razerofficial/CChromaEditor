#pragma once

#include "Animation2D.h"
#include "EditorAnimationBase.h"

namespace ChromaSDK
{
	class EditorAnimation2D : public EditorAnimationBase
	{
	public:
		EditorAnimation2D();
		AnimationBase* GetAnimation();
		EChromaSDKDevice2DEnum GetDevice();
		bool SetDevice(EChromaSDKDevice2DEnum device);
		std::vector<FChromaSDKColorFrame2D>& GetFrames();
		void SetCopy(FChromaSDKColorFrame2D& copy);
		FChromaSDKColorFrame2D& GetCopy();
		void OverrideTime(float time);
	private:
		void Reset();
		Animation2D _mAnimation;
		FChromaSDKColorFrame2D _mFrameCopy;
	};
}
