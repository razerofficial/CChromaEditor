#pragma once

#include "AnimationBase.h"
#include <thread>
#include <vector>

namespace ChromaSDK
{
	class ChromaThread
	{
	public:
		ChromaThread();
		void Start();
		void AddAnimation(AnimationBase* animation);
		void RemoveAnimation(AnimationBase* animation);
	private:
		void ChromaWorker();
		std::vector<AnimationBase*> _mAnimations;
		std::vector<AnimationBase*> _mAnimationsToRemove;
		std::thread* _mThread;
	};
}
