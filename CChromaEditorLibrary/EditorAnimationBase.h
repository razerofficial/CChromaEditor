#pragma once

#include "AnimationBase.h"

class EditorAnimationBase
{
public:
	virtual ChromaSDK::AnimationBase* GetAnimation() = 0;
	int GetCurrentFrame();
	void SetCurrentFrame(unsigned int index);
	unsigned int GetFrameCount();
	virtual float GetDuration(unsigned int index) = 0;
};
