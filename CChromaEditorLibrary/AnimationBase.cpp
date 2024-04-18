#include "stdafx.h"
#include "AnimationBase.h"

using namespace ChromaSDK;
using namespace std;

AnimationBase::AnimationBase()
{
	_mName = "";
	_mCurrentFrame = 0;
	_mIsLoaded = false;
	_mIsPlaying = false;
	_mIsPaused = true;
	_mTime = 0.0f;
	_mUsePreloading = true;
	_mLoop = false;
}

const string& AnimationBase::GetName()
{
	return _mName;
}

void AnimationBase::SetName(const std::string& name)
{
	_mName = name;
}

int AnimationBase::GetDeviceTypeId()
{
	return (int)GetDeviceType();
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
	return _mIsPlaying;
}

bool AnimationBase::IsPaused()
{
	return _mIsPaused;
}

bool AnimationBase::HasLoop()
{
	return _mLoop;
}

void AnimationBase::InternalSetTime(float time)
{
	_mTime = time;
}
void AnimationBase::InternalSetCurrentFrame(int currentFrame)
{
	_mCurrentFrame = currentFrame;
}
void AnimationBase::InternalSetIsPlaying(bool isPlaying)
{
	_mIsPlaying = isPlaying;
}
void AnimationBase::InternalSetLoop(bool loop)
{
	_mLoop = loop;
}
void AnimationBase::InternalSetIsPaused(bool isPaused)
{
	_mIsPaused = isPaused;
}

mutex& AnimationBase::GetMutex()
{
	return _mMutex;
}

void AnimationBase::UsePreloading(bool flag)
{
	_mUsePreloading = flag;
}

bool AnimationBase::HasUsePreloading()
{
	return _mUsePreloading;
}
