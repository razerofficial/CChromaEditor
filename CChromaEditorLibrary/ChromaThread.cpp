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
}

ChromaThread* ChromaThread::Instance()
{
	return _sInstance;
}

void ChromaThread::ChromaWorker()
{
	// get current time
	high_resolution_clock::time_point timer = high_resolution_clock::now();
	high_resolution_clock::time_point timerLast = high_resolution_clock::now();

	while (true)
	{
		// get current time
		timer = high_resolution_clock::now();

		// get time in seconds
		duration<double, std::milli> time_span = timer - timerLast;
		float deltaTime = time_span.count() / 1000.0f;
		timerLast = timer;

		std::lock_guard<std::mutex> guard(_mMutex);

		// update animations
		for (int i = 0; i < _mAnimations.size(); ++i)
		{
			AnimationBase* animation = _mAnimations[i];
			if (animation != nullptr)
			{
				animation->Update(deltaTime);
			}
		}

		//std::this_thread::sleep_for(std::chrono::seconds(1));
		//fprintf(stdout, "ChromaThread: Sleeping...\r\n");

		//std::this_thread::sleep_for(std::chrono::microseconds(1));

		this_thread::yield();
	}
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

void ChromaThread::AddAnimation(AnimationBase* animation)
{
	std::lock_guard<std::mutex> guard(_mMutex);
	// Add animation if it's not found
	if (std::find(_mAnimations.begin(), _mAnimations.end(), animation) == _mAnimations.end())
	{
		_mAnimations.push_back(animation);
	}
	
}

void ChromaThread::RemoveAnimation(AnimationBase* animation)
{
	std::lock_guard<std::mutex> guard(_mMutex);
	if (animation != nullptr)
	{
		auto it = std::find(_mAnimations.begin(), _mAnimations.end(), animation);
		if (it != _mAnimations.end())
		{
			_mAnimations.erase(it);
		}
	}
}
