#include "stdafx.h"
#include "Animation1D.h"
#include "Animation2D.h"
#include "ChromaThread.h"
#include <chrono>

using namespace ChromaSDK;
using namespace std;
using namespace std::chrono;

ChromaThread* ChromaThread::_sInstance = new ChromaThread();

ChromaThread::ChromaThread()
{
	_mThread = nullptr;
	_mWaitForExit = true;
	for (int i = 0; i < (int)EChromaSDKDeviceEnum::DE_MAX; ++i)
	{
		_mUseIdleAnimation.push_back(false);
		_mIdleAnimation.push_back("");
	}	
}

ChromaThread* ChromaThread::Instance()
{
	return _sInstance;
}

void ChromaThread::UseIdleAnimation(EChromaSDKDeviceEnum device, bool flag)
{
	switch (device)
	{
	case EChromaSDKDeviceEnum::DE_ChromaLink:
	case EChromaSDKDeviceEnum::DE_Headset:
	case EChromaSDKDeviceEnum::DE_Keyboard:
	case EChromaSDKDeviceEnum::DE_Keypad:
	case EChromaSDKDeviceEnum::DE_Mouse:
	case EChromaSDKDeviceEnum::DE_Mousepad:
		_mUseIdleAnimation[(int)device] = flag;
		break;
	}
}
void ChromaThread::SetIdleAnimation(const char* name)
{
	lock_guard<mutex> guard(_mMutex);
	AnimationBase* animation = GetAnimationInstanceName(name);
	if (animation)
	{
		EChromaSDKDeviceEnum device;
		Animation1D* animation1D;
		Animation2D* animation2D;
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
			animation1D = dynamic_cast<Animation1D*>(animation);
			switch (animation1D->GetDevice())
			{
			case EChromaSDKDevice1DEnum::DE_ChromaLink:
				_mIdleAnimation[(int)EChromaSDKDeviceEnum::DE_ChromaLink] = name;
				break;
			case EChromaSDKDevice1DEnum::DE_Headset:
				_mIdleAnimation[(int)EChromaSDKDeviceEnum::DE_Headset] = name;
				break;
			case EChromaSDKDevice1DEnum::DE_Mousepad:
				_mIdleAnimation[(int)EChromaSDKDeviceEnum::DE_Mousepad] = name;
				break;
			}
			break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
			animation2D = dynamic_cast<Animation2D*>(animation);
			switch (animation2D->GetDevice())
			{
			case EChromaSDKDevice2DEnum::DE_Keyboard:
				_mIdleAnimation[(int)EChromaSDKDeviceEnum::DE_Keyboard] = name;
				break;
			case EChromaSDKDevice2DEnum::DE_Keypad:
				_mIdleAnimation[(int)EChromaSDKDeviceEnum::DE_Keypad] = name;
				break;
			case EChromaSDKDevice2DEnum::DE_Mouse:
				_mIdleAnimation[(int)EChromaSDKDeviceEnum::DE_Mouse] = name;
				break;
			}
			break;
		}
	}
}

void ChromaThread::ProcessAnimations(float deltaTime)
{
	lock_guard<mutex> guard(_mMutex);

	// detect if animations are playing
	vector<bool> detectIdle;
	for (int i = 0; i < (int)EChromaSDKDeviceEnum::DE_MAX; ++i)
	{
		detectIdle.push_back(true);
	}

	// update animations
	vector<AnimationBase*> doneList = vector<AnimationBase*>();
	for (int i = 0; i < int(_mAnimations.size()) && _mWaitForExit; ++i)
	{
		AnimationBase* animation = _mAnimations[i];
		if (animation != nullptr)
		{
			animation->Update(deltaTime);
			// no need to update animations that are no longer playing
			if (animation->IsPlaying())
			{
				// an animation is playing, idle condition is false
				Animation1D* animation1D;
				Animation2D* animation2D;
				switch (animation->GetDeviceType())
				{
				case EChromaSDKDeviceTypeEnum::DE_1D:
					animation1D = dynamic_cast<Animation1D*>(animation);
					switch (animation1D->GetDevice())
					{
					case EChromaSDKDevice1DEnum::DE_ChromaLink:
						detectIdle[(int)EChromaSDKDeviceEnum::DE_ChromaLink] = false;
						break;
					case EChromaSDKDevice1DEnum::DE_Headset:
						detectIdle[(int)EChromaSDKDeviceEnum::DE_Headset] = false;
						break;
					case EChromaSDKDevice1DEnum::DE_Mousepad:
						detectIdle[(int)EChromaSDKDeviceEnum::DE_Mousepad] = false;
						break;
					}
					break;
				case EChromaSDKDeviceTypeEnum::DE_2D:
					animation2D = dynamic_cast<Animation2D*>(animation);
					switch (animation2D->GetDevice())
					{
					case EChromaSDKDevice2DEnum::DE_Keyboard:
						detectIdle[(int)EChromaSDKDeviceEnum::DE_Keyboard] = false;
						break;
					case EChromaSDKDevice2DEnum::DE_Keypad:
						detectIdle[(int)EChromaSDKDeviceEnum::DE_Keypad] = false;
						break;
					case EChromaSDKDevice2DEnum::DE_Mouse:
						detectIdle[(int)EChromaSDKDeviceEnum::DE_Mouse] = false;
						break;
					}
					break;
				}
			}
			else
			{
				doneList.push_back(animation);
			}
		}
	}

	// remove animations that are done from the playing animation list
	for (int i = 0; i < int(doneList.size()) && _mWaitForExit; ++i)
	{
		AnimationBase* animation = doneList[i];
		if (animation != nullptr)
		{
			auto it = find(_mAnimations.begin(), _mAnimations.end(), animation);
			if (it != _mAnimations.end())
			{
				_mAnimations.erase(it);
			}
		}
	}

	// if no animations are playing, the idle animation can be played
	for (int i = 0; i < (int)EChromaSDKDeviceEnum::DE_MAX; ++i)
	{
		if (_mUseIdleAnimation[i] &&
			detectIdle[i])
		{
			AnimationBase* idleAnimation = GetAnimationInstanceName(_mIdleAnimation[i].c_str());
			if (idleAnimation)
			{
				if (!idleAnimation->IsPlaying())
				{
					idleAnimation->Load();

					idleAnimation->InternalSetTime(0.0f);
					idleAnimation->InternalSetCurrentFrame(-1);
					idleAnimation->InternalSetIsPlaying(true);
					idleAnimation->InternalSetLoop(false);
					idleAnimation->InternalSetIsPaused(false);
				}
				idleAnimation->InternalUpdate(deltaTime);
			}
		}
	}
}

void ChromaThread::ChromaWorker()
{
	// get current time
	high_resolution_clock::time_point timer = high_resolution_clock::now();
	high_resolution_clock::time_point timerLast = high_resolution_clock::now();

	_mWaitForExit = true;

	while (_mWaitForExit)
	{
		// get current time
		timer = high_resolution_clock::now();

		// get time in seconds
		duration<double, milli> time_span = timer - timerLast;
		float deltaTime = (float)(time_span.count() / 1000.0f);
		timerLast = timer;

		ProcessAnimations(deltaTime);

		if (!_mWaitForExit)
		{
			break;
		}
			
		this_thread::sleep_for(chrono::milliseconds(1));
	}

	_mThread = nullptr;
}

void ChromaThread::Start()
{
	if (_mThread != nullptr)
	{
		return;
	}
	_mThread = new thread(&ChromaThread::ChromaWorker, this);
	_mThread->detach();
}

void ChromaThread::Stop()
{
	_mWaitForExit = false;

	lock_guard<mutex> guard(_mMutex);
	for (int i = 0; i < (int)EChromaSDKDeviceEnum::DE_MAX; ++i)
	{
		_mUseIdleAnimation[i] = false;
	}
	_mAnimations.clear();
}

void ChromaThread::AddAnimation(AnimationBase* animation)
{
	lock_guard<mutex> guard(_mMutex);
	// Add animation if it's not found
	if (find(_mAnimations.begin(), _mAnimations.end(), animation) == _mAnimations.end())
	{
		_mAnimations.push_back(animation);
	}
}

void ChromaThread::RemoveAnimation(AnimationBase* animation)
{
	lock_guard<mutex> guard(_mMutex);
	if (animation != nullptr)
	{
		auto it = find(_mAnimations.begin(), _mAnimations.end(), animation);
		if (it != _mAnimations.end())
		{
			_mAnimations.erase(it);
		}
	}
}

void ChromaThread::DeleteAnimation(AnimationBase* animation)
{
	lock_guard<mutex> guard(_mMutex);
	//delete animation safely
	delete animation;
}

int ChromaThread::GetAnimationCount()
{
	lock_guard<mutex> guard(_mMutex);
	return _mAnimations.size();
}

int ChromaThread::GetAnimationId(int index)
{
	lock_guard<mutex> guard(_mMutex);
	if (index < 0)
	{
		return -1;
	}
	if (index < int(_mAnimations.size()))
	{
		AnimationBase* animation = _mAnimations[index];
		if (animation != nullptr)
		{
			return PluginGetAnimationIdFromInstance(animation);
		}
	}
	return -1;
}
