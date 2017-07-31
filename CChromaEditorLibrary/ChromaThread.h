#pragma once

#include "AnimationBase.h"
#include <thread>
#include <vector>

namespace ChromaSDK
{
	class ChromaThread
	{
	public:
		static ChromaThread* Instance();
		void Start();
		void AddAnimation(AnimationBase* animation);
		void RemoveAnimation(AnimationBase* animation);
	private:
		ChromaThread();
		void ChromaWorker();
		static ChromaThread _sInstance;
		std::vector<AnimationBase*> _mAnimations;
		std::vector<AnimationBase*> _mAnimationsToRemove;
		std::thread* _mThread;
	};
}
