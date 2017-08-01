#pragma once

#include "Animation1D.h"
#include "EditorAnimationBase.h"

namespace ChromaSDK
{
	class EditorAnimation1D : public EditorAnimationBase
	{
	public:
		EditorAnimation1D();
		AnimationBase* GetAnimation();
		void SetAnimation(Animation1D& animation);
		EChromaSDKDevice1DEnum GetDevice();
		bool SetDevice(EChromaSDKDevice1DEnum device);
		std::vector<FChromaSDKColorFrame1D>& GetFrames();
		void SetCopy(FChromaSDKColorFrame1D& copy);
		FChromaSDKColorFrame1D& GetCopy();
		void OverrideTime(float time);
		float GetDuration(int index);
		void Reset();
	private:
		Animation1D _mAnimation;
		FChromaSDKColorFrame1D _mFrameCopy;
	};
}
