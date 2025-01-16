#pragma once

#include "AnimationBase.h"
#include <mutex>
#include <set>
#include <string>
#include <thread>
#include <vector>

namespace ChromaSDK
{
	struct ParamsPlayChromaAnimation
	{
		std::wstring _mPath;
		bool _mLoop;

		const std::wstring GenerateKey() {
			std::wstring key = L"PlayChromaAnimation_";
			key += _mPath;
			return key;
		}
	};

	struct ParamsSetEventName
	{
		std::wstring _mName;

		const std::wstring GenerateKey() {
			std::wstring key = L"SetEventName_";
			key += _mName;
			return key;
		}
	};

	struct ParamsSetIdleAnimationName
	{
		std::wstring _mPath;

		const std::wstring GenerateKey() {
			std::wstring key = L"SetIdleAnimationName_";
			key += _mPath;
			return key;
		}
	};

	struct ParamsStopChromaAnimation
	{
		std::wstring _mPath;

		const std::wstring GenerateKey() {
			std::wstring key = L"StopChromaAnimation_";
			key += _mPath;
			return key;
		}
	};

	struct ParamsStopAll
	{
		const std::wstring GenerateKey() {
			std::wstring key = L"StopAll";
			return key;
		}
	};

	struct ParamsStopAnimationType
	{
		int _mDeviceType;
		int _mDevice;

		const std::wstring GenerateKey() {
			std::wstring key = L"StopAnimationType_";
			key += std::to_wstring(_mDeviceType);
			key += L"_";
			key += std::to_wstring(_mDevice);
			return key;
		}
	};

	struct ParamsUseIdleAnimations
	{
		bool _mFlag;

		static const std::wstring GenerateKey() {
			std::wstring key = L"UseIdleAnimations";
			return key;
		}
	};

	enum class PendingCommandType
	{
		Command_Unknown,
		Command_PlayChromaAnimation,
		Command_SetEventName,
		Command_SetIdleAnimationName,
		Command_StopChromaAnimation,
		Command_StopAll,
		Command_StopAnimationType,
		Command_UseIdleAnimations
	};

	struct PendingCommand
	{
		PendingCommandType _mType;
		ParamsPlayChromaAnimation _mPlayChromaAnimation;
		ParamsSetEventName _mSetEventName;
		ParamsSetIdleAnimationName _mSetIdleAnimation;
		ParamsStopAll _mStopAll;
		ParamsStopAnimationType _mStopAnimationType;
		ParamsStopChromaAnimation _mStopChromaAnimation;
		ParamsUseIdleAnimations _mUseIdleAnimations;
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
		void SetIdleAnimationName(const wchar_t* name);
		void PlayAnimationName(const wchar_t* path, bool loop);
		RZRESULT SetEventName(LPCTSTR Name);
	private:
		ChromaThread();
		void ProcessAnimations(float deltaTime);
		void ProcessPendingCommands();
		void ChromaWorker();
		std::vector<PendingCommand> GetPendingCommands();
		static ChromaThread* _sInstance;
		static std::mutex _sMutex;
		static bool _sWaitForExit;
		static std::thread* _sThread;
		static std::vector<AnimationBase*> _sAnimations;
		static std::vector<bool> _sUseIdleAnimation;
		static std::vector<std::wstring> _sIdleAnimation;
		static std::map<std::wstring, PendingCommand> _sPendingCommands;
		static RZRESULT _sLastResultSetEventName;
	};
}
