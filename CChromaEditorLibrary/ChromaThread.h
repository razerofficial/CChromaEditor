#pragma once

#include "AnimationBase.h"
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace ChromaSDK
{
	class ChromaThread
	{
	public:
		static ChromaThread* Instance();
		void Start();
		void Stop();
		void AddAnimation(AnimationBase* animation);
		void RemoveAnimation(AnimationBase* animation);
		void DeleteAnimation(AnimationBase* animation);
		int GetAnimationCount();
		int GetAnimationId(int index);
		void UseIdleAnimation(EChromaSDKDeviceEnum device, bool flag);
		void SetIdleAnimationName(const char* name);
	private:
		ChromaThread();
		void ProcessAnimations(float deltaTime);
		void ChromaWorker();
		static ChromaThread* _sInstance;
		std::vector<AnimationBase*> _mAnimations;
		std::thread* _mThread;
		std::mutex _mMutex;
		bool _mWaitForExit;
		std::vector<bool> _mUseIdleAnimation;
		std::vector<std::string> _mIdleAnimation;
	};
}
