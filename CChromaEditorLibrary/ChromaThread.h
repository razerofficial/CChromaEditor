#pragma once

#include "AnimationBase.h"
#include <mutex>
#include <set>
#include <string>
#include <thread>
#include <vector>

namespace ChromaSDK
{
	struct PendingPlayChromaAnimation
	{
		std::string _mPath;
		bool _mLoop;
	};

	class ChromaThread
	{
	public:
		static ChromaThread* Instance();
		static void Init();
		void Start();
		void Stop();
		void AddAnimation(AnimationBase* animation);
		void RemoveAnimation(AnimationBase* animation);
		void DeleteAnimation(AnimationBase* animation);
		int GetAnimationCount();
		int GetAnimationId(int index);
		void UseIdleAnimation(EChromaSDKDeviceEnum device, bool flag);
		void SetIdleAnimationName(const char* name);
		void PlayAnimationName(const char* path, bool loop);
		RZRESULT SetEventName(LPCTSTR Name);
	private:
		ChromaThread();
		void ProcessAnimations(float deltaTime);
		void ProcessPlayAnimationNames();
		void ProcessEventNames();
		void ChromaWorker();
		std::vector<PendingPlayChromaAnimation> GetPendingPlayAnimationNames();
		std::vector<std::wstring> GetPendingEventNames();
		static ChromaThread* _sInstance;
		static std::mutex _sMutex;
		static bool _sWaitForExit;
		static std::thread* _sThread;
		static std::vector<AnimationBase*> _sAnimations;
		static std::vector<bool> _sUseIdleAnimation;
		static std::vector<std::string> _sIdleAnimation;
		static std::map<std::string, bool> _sPendingPlayAnimationNames;
		static std::set<std::wstring> _sPendingEventNames;
		static RZRESULT _sLastResultSetEventName;
	};
}
