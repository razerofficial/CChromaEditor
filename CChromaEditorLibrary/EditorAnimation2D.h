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
		void SetAnimation(Animation2D& animation);
		EChromaSDKDevice2DEnum GetDevice();
		bool SetDevice(EChromaSDKDevice2DEnum device);
		std::vector<FChromaSDKColorFrame2D>& GetFrames();
		void SetCopy(FChromaSDKColorFrame2D& copy);
		FChromaSDKColorFrame2D& GetCopy();
		void OverrideTime(float time);
		float GetDuration(unsigned int index);
		void Reset();
	private:
		Animation2D _mAnimation;
		FChromaSDKColorFrame2D _mFrameCopy;
	};
}
