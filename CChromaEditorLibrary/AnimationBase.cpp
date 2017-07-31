#include "stdafx.h"
#include "AnimationBase.h"

using namespace ChromaSDK;

AnimationBase::AnimationBase()
{
	_mCurrentFrame = 0;
	_mPlaying = false;
}

int AnimationBase::GetCurrentFrame()
{
	return _mCurrentFrame;
}

void AnimationBase::SetCurrentFrame(int index)
{
	if (index < 0 ||
		index >= GetFrameCount())
	{
		index = 0;
	}
	_mCurrentFrame = index;
}

bool AnimationBase::IsPlaying()
{
	return _mPlaying;
}