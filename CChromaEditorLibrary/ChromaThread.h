#pragma once

#include "AnimationBase.h"
#include <mutex>
#include <set>
#include <string>
#include <thread>
#include <vector>

namespace ChromaSDK
{
	struct ParamsPlayChromaAnimationName
	{
		std::string _mPath;
		bool _mLoop;

		const std::wstring GenerateKey() {
			std::wstring wPath(_mPath.begin(), _mPath.end());
			std::wstring key = L"PlayChromaAnimation_";
			key += wPath;
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
		std::string _mPath;

		const std::wstring GenerateKey() {
			std::wstring wPath(_mPath.begin(), _mPath.end());
			std::wstring key = L"SetIdleAnimationName_";
			key += wPath;
			return key;
		}
	};

	struct ParamsStopAnimationName
	{
		std::string _mPath;

		const std::wstring GenerateKey() {
			std::wstring wPath(_mPath.begin(), _mPath.end());
			std::wstring key = L"StopChromaAnimation_";
			key += wPath;
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

	struct ParamsUseForwardChromaEvents
	{
		bool _mFlag;

		static const std::wstring GenerateKey() {
			std::wstring key = L"UseForwardChromaEvents";
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
		Command_PlayChromaAnimationName,
		Command_SetEventName,
		Command_SetIdleAnimationName,
		Command_StopAnimationName,
		Command_StopAll,
		Command_StopAnimationType,
		Command_UseForwardChromaEvents,
		Command_UseIdleAnimations
	};

	struct PendingCommand
	{
		PendingCommandType _mType;
		ParamsPlayChromaAnimationName _mPlayChromaAnimationName;
		ParamsSetEventName _mSetEventName;
		ParamsSetIdleAnimationName _mSetIdleAnimationName;
		ParamsStopAll _mStopAll;
		ParamsStopAnimationName _mStopAnimationName;
		ParamsStopAnimationType _mStopAnimationType;
		ParamsUseForwardChromaEvents _mUseForwardChromaEvents;
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
		void ImplSetIdleAnimationName(const char* name);
		void ImplStopAnimationType(int deviceType, int device);
		// async calls
		void AsyncPlayAnimationName(const char* path, bool loop);
		RZRESULT AsyncSetEventName(LPCTSTR Name);
		void AsyncSetIdleAnimationName(const char* path);
		void AsyncStopAll();
		void AsyncStopAnimationName(const char* path);
		void AsyncStopAnimationType(int deviceType, int device);
		void UseIdleAnimation(EChromaSDKDeviceEnum device, bool flag);
		void AsyncUseForwardChromaEvents(bool flag);
		void AsyncUseIdleAnimations(bool flag);
	private:
		ChromaThread();
		void ProcessAnimations(float deltaTime);
		void ProcessPendingCommands();
		void ChromaWorker();
		void AddPendingCommandInOrder(const std::wstring& key, const PendingCommand& command);
		std::vector<PendingCommand> GetPendingCommands();
		static ChromaThread* _sInstance;
		static std::mutex _sMutex;
		static bool _sWaitForExit;
		static std::thread* _sThread;
		static std::vector<AnimationBase*> _sAnimations;
		static std::vector<bool> _sUseIdleAnimation;
		static std::vector<std::string> _sIdleAnimation;
		static std::vector<std::wstring> _sOrderPendingCommands;
		static std::map<std::wstring, PendingCommand> _sPendingCommands;
		static RZRESULT _sLastResultSetEventName;
	};
}
