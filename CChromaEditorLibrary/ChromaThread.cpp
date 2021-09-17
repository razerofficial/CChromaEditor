#include "stdafx.h"
#include "Animation1D.h"
#include "Animation2D.h"
#include "ChromaSDKPlugin.h"
#include "ChromaThread.h"
#include <chrono>
#include <sstream>

using namespace ChromaSDK;
using namespace std;
using namespace std::chrono;

ChromaThread* ChromaThread::_sInstance = nullptr;
mutex ChromaThread::_sMutex;
bool ChromaThread::_sWaitForExit = true;
thread* ChromaThread::_sThread = nullptr;
vector<AnimationBase*> ChromaThread::_sAnimations;
vector<bool> ChromaThread::_sUseIdleAnimation;
vector<std::string> ChromaThread::_sIdleAnimation;

ChromaThread::ChromaThread()
{
	_sThread = nullptr;
	_sWaitForExit = true;
	for (int i = 0; i < (int)EChromaSDKDeviceEnum::DE_MAX; ++i)
	{
		_sUseIdleAnimation.push_back(false);
		_sIdleAnimation.push_back("");
	}	
}

ChromaThread* ChromaThread::Instance()
{
	return _sInstance;
}

void ChromaThread::Init()
{
	if (_sInstance == nullptr)
	{
		_sInstance = new ChromaThread();
	}
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
		_sUseIdleAnimation[(int)device] = flag;
		break;
	}
}
void ChromaThread::SetIdleAnimationName(const char* name)
{
	lock_guard<mutex> guard(_sMutex);
	AnimationBase* animation = GetAnimationInstanceName(name);
	if (animation != nullptr)
	{
		if (animation->HasUsePreloading())
		{
			animation->Load();
		}
		Animation1D* animation1D = nullptr;
		Animation2D* animation2D = nullptr;
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
			animation1D = (Animation1D*)(animation);
			switch (animation1D->GetDevice())
			{
			case EChromaSDKDevice1DEnum::DE_ChromaLink:
				_sIdleAnimation[(int)EChromaSDKDeviceEnum::DE_ChromaLink] = name;
				break;
			case EChromaSDKDevice1DEnum::DE_Headset:
				_sIdleAnimation[(int)EChromaSDKDeviceEnum::DE_Headset] = name;
				break;
			case EChromaSDKDevice1DEnum::DE_Mousepad:
				_sIdleAnimation[(int)EChromaSDKDeviceEnum::DE_Mousepad] = name;
				break;
			}
			break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
			animation2D = (Animation2D*)(animation);
			switch (animation2D->GetDevice())
			{
			case EChromaSDKDevice2DEnum::DE_Keyboard:
				_sIdleAnimation[(int)EChromaSDKDeviceEnum::DE_Keyboard] = name;
				break;
			case EChromaSDKDevice2DEnum::DE_Keypad:
				_sIdleAnimation[(int)EChromaSDKDeviceEnum::DE_Keypad] = name;
				break;
			case EChromaSDKDevice2DEnum::DE_Mouse:
				_sIdleAnimation[(int)EChromaSDKDeviceEnum::DE_Mouse] = name;
				break;
			}
			break;
		}
	}
}

void ChromaThread::ProcessAnimations(float deltaTime)
{
	lock_guard<mutex> guard(_sMutex);

	// module shutdown while waiting for lock
	if (!_sWaitForExit)
	{
		return;
	}

	// detect if animations are playing
	vector<bool> detectIdle;
	for (int i = 0; i < (int)EChromaSDKDeviceEnum::DE_MAX && _sWaitForExit; ++i)
	{
		detectIdle.push_back(true);
	}

	// update animations
	vector<AnimationBase*> doneList = vector<AnimationBase*>();
	for (unsigned int i = 0; i < _sAnimations.size() && _sWaitForExit; ++i)
	{
		AnimationBase* animation = _sAnimations[i];
		if (animation != nullptr)
		{
			animation->Update(deltaTime);
			// no need to update animations that are no longer playing
			if (animation->IsPlaying())
			{
				// an animation is playing, idle condition is false
				Animation1D* animation1D = nullptr;
				Animation2D* animation2D = nullptr;
				switch (animation->GetDeviceType())
				{
				case EChromaSDKDeviceTypeEnum::DE_1D:
					animation1D = (Animation1D*)(animation);
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
					animation2D = (Animation2D*)(animation);
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
	for (int i = 0; i < (int)doneList.size() && _sWaitForExit; ++i)
	{
		AnimationBase* animation = doneList[i];
		if (animation != nullptr)
		{
			auto it = find(_sAnimations.begin(), _sAnimations.end(), animation);
			if (it != _sAnimations.end())
			{
				_sAnimations.erase(it);
			}
		}
	}

	// if no animations are playing, the idle animation can be played
	for (int i = 0; i < (int)EChromaSDKDeviceEnum::DE_MAX && _sWaitForExit; ++i)
	{
		if (_sUseIdleAnimation[i] &&
			detectIdle[i])
		{
			AnimationBase* idleAnimation = GetAnimationInstanceIfOpenName(_sIdleAnimation[i].c_str());
			if (idleAnimation != nullptr)
			{
				if (!idleAnimation->IsPlaying())
				{
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

	_sWaitForExit = true;

	while (_sWaitForExit)
	{
		// get current time
		timer = high_resolution_clock::now();

		// get time in seconds
		duration<double, milli> time_span = timer - timerLast;
		float deltaTime = (float)(time_span.count() / 1000.0f);
		timerLast = timer;

		ProcessAnimations(deltaTime);

		if (!_sWaitForExit)
		{
			break;
		}
			
		this_thread::sleep_for(chrono::milliseconds(1));
	}

	_sThread = nullptr;
}

void ChromaThread::Start()
{
	if (_sThread != nullptr)
	{
		return;
	}
	_sThread = new thread(&ChromaThread::ChromaWorker, this);

	// for debugging, log thread id
	/*
	stringstream ss;
	ss << _sThread->get_id();
	string strId = ss.str();
	ChromaLogger::printf("ChromaThread: %s\r\n", strId.c_str());
	*/

	_sThread->detach();
}

void ChromaThread::Stop()
{
	lock_guard<mutex> guard(_sMutex);

	_sWaitForExit = false;
	for (int i = 0; i < (int)EChromaSDKDeviceEnum::DE_MAX; ++i)
	{
		_sUseIdleAnimation[i] = false;
		_sIdleAnimation[i] = "";
	}
	_sAnimations.clear();

	if (_sInstance != nullptr)
	{
		delete _sInstance;
		_sInstance = nullptr;
	}
}

void ChromaThread::AddAnimation(AnimationBase* animation)
{
	lock_guard<mutex> guard(_sMutex);
	// Add animation if it's not found
	if (find(_sAnimations.begin(), _sAnimations.end(), animation) == _sAnimations.end())
	{
		_sAnimations.push_back(animation);
	}
}

void ChromaThread::RemoveAnimation(AnimationBase* animation)
{
	lock_guard<mutex> guard(_sMutex);
	if (animation != nullptr)
	{
		auto it = find(_sAnimations.begin(), _sAnimations.end(), animation);
		if (it != _sAnimations.end())
		{
			_sAnimations.erase(it);
		}
	}
}

void ChromaThread::DeleteAnimation(AnimationBase* animation)
{
	lock_guard<mutex> guard(_sMutex);
	if (animation != nullptr)
	{
		// remove animation if playing
		auto it = find(_sAnimations.begin(), _sAnimations.end(), animation);
		if (it != _sAnimations.end())
		{
			_sAnimations.erase(it);
		}
		// unload the animation if loaded
		animation->Unload();
		//delete animation safely
		delete animation;
	}
}

int ChromaThread::GetAnimationCount()
{
	lock_guard<mutex> guard(_sMutex);
	return _sAnimations.size();
}

int ChromaThread::GetAnimationId(int index)
{
	lock_guard<mutex> guard(_sMutex);
	if (index < 0)
	{
		return -1;
	}
	if (index < (int)_sAnimations.size())
	{
		AnimationBase* animation = _sAnimations[index];
		if (animation != nullptr)
		{
			return GetAnimationIdFromInstance(animation);
		}
	}
	return -1;
}
