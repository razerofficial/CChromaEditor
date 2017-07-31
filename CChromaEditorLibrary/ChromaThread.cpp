#include "stdafx.h"
#include "ChromaThread.h"

using namespace ChromaSDK;
using namespace std;

ChromaThread ChromaThread::_sInstance = ChromaThread();

ChromaThread::ChromaThread()
{
	_mThread = nullptr;
}

ChromaThread* ChromaThread::Instance()
{
	return &_sInstance;
}

void ChromaThread::ChromaWorker()
{
	while (true)
	{
		while (_mAnimationsToRemove.size() > 0)
		{
			AnimationBase* animation = _mAnimationsToRemove[0];
			_mAnimationsToRemove.erase(_mAnimationsToRemove.begin());
			if (animation != nullptr)
			{
				auto it = std::find(_mAnimations.begin(), _mAnimations.end(), animation);
				if (it != _mAnimations.end())
				{
					_mAnimations.erase(it);
				}
			}
		}

		// update animations
		for (int i = 0; i < _mAnimations.size(); ++i)
		{
			AnimationBase* animation = _mAnimations[i];
			if (animation != nullptr)
			{
				animation->Update();
			}
		}

		//this_thread::yield();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		fprintf(stdout, "ChromaThread: Sleeping...\r\n");
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
	// Add animation if it's not found
	if (std::find(_mAnimations.begin(), _mAnimations.end(), animation) == _mAnimations.end())
	{
		_mAnimations.push_back(animation);
	}
	
}

void ChromaThread::RemoveAnimation(AnimationBase* animation)
{
	//queue for Chroma thread to remove
	_mAnimationsToRemove.push_back(animation);
}
