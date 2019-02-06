#include "stdafx.h"
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
}

ChromaThread* ChromaThread::Instance()
{
	return _sInstance;
}

void ChromaThread::UseIdleAnimation(bool flag)
{
	_mUseIdleAnimation = flag;
}
void ChromaThread::SetIdleAnimation(const char* name)
{
	lock_guard<mutex> guard(_mMutex);
	_mIdleAnimation = name;
}

void ChromaThread::ProcessAnimations(float deltaTime)
{
	lock_guard<mutex> guard(_mMutex);

	// detect if animations are playing
	bool detectIdle = true;

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
				detectIdle = false;
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
	if (_mUseIdleAnimation &&
		detectIdle)
	{
		AnimationBase* idleAnimation = GetAnimationInstanceName(_mIdleAnimation.c_str());
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
	_mUseIdleAnimation = false;
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
