#pragma once

#include "AnimationBase.h"
#include <mutex>
#include <set>
#include <string>
#include <thread>
#include <vector>

namespace ChromaSDK
{
	std::wstring GenerateGUID();

	struct ParamsGetAnimation
	{
		std::wstring _mPath;

		const std::wstring GenerateKey() {
			std::wstring key = L"GetAnimation_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsCloseAnimationName
	{
		std::wstring _mPath;

		const std::wstring GenerateKey() {
			std::wstring key = L"CloseAnimationName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsPlayChromaAnimationName
	{
		std::wstring _mPath;
		bool _mLoop;

		const std::wstring GenerateKey() {
			std::wstring key = L"PlayChromaAnimationName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsSetEventName
	{
		std::wstring _mName;

		const std::wstring GenerateKey() {
			std::wstring key = L"SetEventName_";
			key += _mName; // Collapse names, no real need for more than 30 FPS for event names
			return key;
		}
	};

	struct ParamsSetIdleAnimationName
	{
		std::wstring _mPath;

		const std::wstring GenerateKey() {
			std::wstring key = L"SetIdleAnimationName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsStopAnimationName
	{
		std::wstring _mPath;

		const std::wstring GenerateKey() {
			std::wstring key = L"StopChromaAnimationName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsStopAll
	{
		const std::wstring GenerateKey() {
			std::wstring key = L"StopAll_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsStopAnimationType
	{
		int _mDeviceType;
		int _mDevice;

		const std::wstring GenerateKey() {
			std::wstring key = L"StopAnimationType_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsUseForwardChromaEvents
	{
		bool _mFlag;

		static const std::wstring GenerateKey() {
			std::wstring key = L"UseForwardChromaEvents_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsUseIdleAnimations
	{
		bool _mFlag;

		static const std::wstring GenerateKey() {
			std::wstring key = L"UseIdleAnimations_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsMakeBlankFramesRGBName
	{
		std::wstring _mPath;
		int _mFrameCount = 0;
		float _mDuration = 0;
		int _mRed = 0;
		int _mGreen = 0;
		int _mBlue = 0;

		const std::wstring GenerateKey() {
			std::wstring key = L"MakeBlankFramesRGBName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsFillThresholdColorsMinMaxAllFramesRGBName
	{
		std::wstring _mPath;
		int _mMinThreshold;
		int _mMinRed;
		int _mMinGreen;
		int _mMinBlue;
		int _mMaxThreshold;
		int _mMaxRed;
		int _mMaxGreen;
		int _mMaxBlue;

		const std::wstring GenerateKey() {
			std::wstring key = L"FillThresholdColorsMinMaxAllFramesRGBName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsMultiplyIntensityAllFramesRGBName
	{
		std::wstring _mPath;
		int _mRed = 0;
		int _mGreen = 0;
		int _mBlue = 0;

		const std::wstring GenerateKey() {
			std::wstring key = L"MultiplyIntensityAllFramesRGBName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsFadeStartFramesName
	{
		std::wstring _mPath;
		int _mFade = 0;

		const std::wstring GenerateKey() {
			std::wstring key = L"FadeStartFramesName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsFadeEndFramesName
	{
		std::wstring _mPath;
		int _mFade = 0;

		const std::wstring GenerateKey() {
			std::wstring key = L"FadeEndFramesName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsMultiplyIntensityName
	{
		std::wstring _mPath;
		int _mFrameId = 0;
		float _mIntensity = 0;

		const std::wstring GenerateKey() {
			std::wstring key = L"FadeEndFramesName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsMultiplyIntensityAllFramesName
	{
		std::wstring _mPath;
		float _mIntensity = 0;

		const std::wstring GenerateKey() {
			std::wstring key = L"MultiplyIntensityAllFramesName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsMultiplyIntensityRGBName
	{
		std::wstring _mPath;
		int _mFrameId = 0;
		int _mRed = 0;
		int _mGreen = 0;
		int _mBlue = 0;

		const std::wstring GenerateKey() {
			std::wstring key = L"MultiplyIntensityRGBName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsMultiplyIntensityColorName
	{
		std::wstring _mPath;
		int _mFrameId = 0;
		int _mColor = 0;

		const std::wstring GenerateKey() {
			std::wstring key = L"MultiplyIntensityColorName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsFillThresholdColorsRGBName
	{
		std::wstring _mPath;
		int _mFrameId = 0;
		int _mThreshold;
		int _mRed;
		int _mGreen;
		int _mBlue;

		const std::wstring GenerateKey() {
			std::wstring key = L"FillThresholdColorsRGBName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsCopyNonZeroAllKeysAllFramesName
	{
		std::wstring _mSourceAnimation;
		std::wstring _mTargetAnimation;

		const std::wstring GenerateKey() {
			std::wstring key = L"CopyNonZeroAllKeysAllFramesName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsMakeBlankFramesName
	{
		std::wstring _mPath;
		int _mFrameCount = 0;
		float _mDuration = 0;
		int _mColor = 0;
		const std::wstring GenerateKey() {
			std::wstring key = L"MakeBlankFramesName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsFillThresholdColorsAllFramesName
	{
		std::wstring _mPath;
		int _mThreshold;
		int _mColor;
		const std::wstring GenerateKey() {
			std::wstring key = L"FillThresholdColorsAllFramesName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsAddNonZeroAllKeysAllFramesName
	{
		std::wstring _mSourceAnimation;
		std::wstring _mTargetAnimation;

		const std::wstring GenerateKey() {
			std::wstring key = L"AddNonZeroAllKeysAllFramesName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsSubtractNonZeroAllKeysAllFramesName
	{
		std::wstring _mSourceAnimation;
		std::wstring _mTargetAnimation;

		const std::wstring GenerateKey() {
			std::wstring key = L"SubtractNonZeroAllKeysAllFramesName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsCopyNonZeroTargetAllKeysAllFramesName
	{
		std::wstring _mSourceAnimation;
		std::wstring _mTargetAnimation;

		const std::wstring GenerateKey() {
			std::wstring key = L"CopyNonZeroTargetAllKeysAllFramesName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsFillZeroColorAllFramesRGBName
	{
		std::wstring _mPath;
		int _mRed = 0;
		int _mGreen = 0;
		int _mBlue = 0;
		const std::wstring GenerateKey() {
			std::wstring key = L"FillZeroColorAllFramesRGBName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsDuplicateFirstFrameName
	{
		std::wstring _mPath;
		int _mFrameCount = 0;
		const std::wstring GenerateKey() {
			std::wstring key = L"DuplicateFirstFrameName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsOverrideFrameDurationName
	{
		std::wstring _mPath;
		float _mDuration = 0;
		const std::wstring GenerateKey() {
			std::wstring key = L"OverrideFrameDurationName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsReverseAllFramesName
	{
		std::wstring _mPath;
		const std::wstring GenerateKey() {
			std::wstring key = L"ReverseAllFramesName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsInvertColorsAllFramesName
	{
		std::wstring _mPath;
		const std::wstring GenerateKey() {
			std::wstring key = L"InvertColorsAllFramesName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsDuplicateMirrorFramesName
	{
		std::wstring _mPath;
		const std::wstring GenerateKey() {
			std::wstring key = L"DuplicateMirrorFramesName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsInsertDelayName
	{
		std::wstring _mPath;
		int _mFrameId = 0;
		int _mDelay = 0;
		const std::wstring GenerateKey() {
			std::wstring key = L"InsertDelayName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsReduceFramesName
	{
		std::wstring _mPath;
		int _mN = 0;
		const std::wstring GenerateKey() {
			std::wstring key = L"ReduceFramesName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsDuplicateFramesName
	{
		std::wstring _mPath;
		const std::wstring GenerateKey() {
			std::wstring key = L"DuplicateFramesName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsTrimStartFramesName
	{
		std::wstring _mPath;
		int _mNumberOfFrames = 0;
		const std::wstring GenerateKey() {
			std::wstring key = L"TrimStartFramesName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsTrimEndFramesName
	{
		std::wstring _mPath;
		int _mLastFrameId = 0;
		const std::wstring GenerateKey() {
			std::wstring key = L"TrimEndFramesName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsFillRandomColorsBlackAndWhiteAllFramesName
	{
		std::wstring _mPath;
		const std::wstring GenerateKey() {
			std::wstring key = L"FillRandomColorsBlackAndWhiteAllFramesName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsUseIdleAnimation
	{
		int _mDevice;
		bool _mFlag;
		static const std::wstring GenerateKey() {
			std::wstring key = L"UseIdleAnimation";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsMultiplyColorLerpAllFramesName
	{
		std::wstring _mPath;
		int _mColor1 = 0;
		int _mColor2 = 0;
		float _mLerp = 0;
		const std::wstring GenerateKey() {
			std::wstring key = L"MultiplyColorLerpAllFramesName_";
			key += GenerateGUID();
			return key;
		}
	};

	enum class PendingCommandType
	{
		Command_Unknown,
		Command_CloseAnimationName,
		Command_GetAnimation,
		Command_PlayChromaAnimationName,
		Command_SetEventName,
		Command_SetIdleAnimationName,
		Command_StopAnimationName,
		Command_StopAll,
		Command_StopAnimationType,
		Command_UseForwardChromaEvents,
		Command_UseIdleAnimations,
		Command_MakeBlankFramesRGBName,
		Command_FillThresholdColorsMinMaxAllFramesRGBName,
		Command_MultiplyIntensityAllFramesRGBName,
		Command_FadeStartFramesName,
		Command_FadeEndFramesName,
		Command_MultiplyIntensityName,
		Command_MultiplyIntensityAllFramesName,
		Command_MultiplyIntensityRGBName,
		Command_MultiplyIntensityColorName,
		Command_FillThresholdColorsRGBName,
		Command_CopyNonZeroAllKeysAllFramesName,
		Command_MakeBlankFramesName,
		Command_FillThresholdColorsAllFramesName,
		Command_AddNonZeroAllKeysAllFramesName,
		Command_SubtractNonZeroAllKeysAllFramesName,
		Command_CopyNonZeroTargetAllKeysAllFramesName,
		Command_FillZeroColorAllFramesRGBName,
		Command_DuplicateFirstFrameName,
		Command_OverrideFrameDurationName,
		Command_ReverseAllFramesName,
		Command_InvertColorsAllFramesName,
		Command_DuplicateMirrorFramesName,
		Command_InsertDelayName,
		Command_ReduceFramesName,
		Command_DuplicateFramesName,
		Command_TrimStartFramesName,
		Command_TrimEndFramesName,
		Command_FillRandomColorsBlackAndWhiteAllFramesName,
		Command_UseIdleAnimation,
		Command_MultiplyColorLerpAllFramesName,
	};

	struct PendingCommand
	{
		PendingCommandType _mType = PendingCommandType::Command_Unknown;
		ParamsCloseAnimationName _mCloseAnimationName = { };
		ParamsGetAnimation _mGetAnimation = { };
		ParamsPlayChromaAnimationName _mPlayChromaAnimationName = { };
		ParamsSetEventName _mSetEventName = { };
		ParamsSetIdleAnimationName _mSetIdleAnimationName = { };
		ParamsStopAll _mStopAll = { };
		ParamsStopAnimationName _mStopAnimationName = { };
		ParamsStopAnimationType _mStopAnimationType = { };
		ParamsUseForwardChromaEvents _mUseForwardChromaEvents = { };
		ParamsUseIdleAnimations _mUseIdleAnimations = { };
		ParamsMakeBlankFramesRGBName _mMakeBlankFramesRGBName = { };
		ParamsFillThresholdColorsMinMaxAllFramesRGBName _mFillThresholdColorsMinMaxAllFramesRGBName = { };
		ParamsMultiplyIntensityAllFramesRGBName _mMultiplyIntensityAllFramesRGBName = { };
		ParamsFadeStartFramesName _mFadeStartFramesName = { };
		ParamsFadeEndFramesName _mFadeEndFramesName = { };
		ParamsMultiplyIntensityName _mMultiplyIntensityName = { };
		ParamsMultiplyIntensityAllFramesName _mMultiplyIntensityAllFramesName = { };
		ParamsMultiplyIntensityRGBName _mMultiplyIntensityRGBName = { };
		ParamsMultiplyIntensityColorName _mMultiplyIntensityColorName = { };
		ParamsFillThresholdColorsRGBName _mFillThresholdColorsRGBName = { };
		ParamsCopyNonZeroAllKeysAllFramesName _mCopyNonZeroAllKeysAllFramesName = { };
		ParamsMakeBlankFramesName _mMakeBlankFramesName = { };
		ParamsFillThresholdColorsAllFramesName _mFillThresholdColorsAllFramesName = { };
		ParamsAddNonZeroAllKeysAllFramesName _mAddNonZeroAllKeysAllFramesName = { };
		ParamsSubtractNonZeroAllKeysAllFramesName _mSubtractNonZeroAllKeysAllFramesName = { };
		ParamsCopyNonZeroTargetAllKeysAllFramesName _mCopyNonZeroTargetAllKeysAllFramesName = { };
		ParamsFillZeroColorAllFramesRGBName _mFillZeroColorAllFramesRGBName = { };
		ParamsDuplicateFirstFrameName _mDuplicateFirstFrameName = { };
		ParamsOverrideFrameDurationName _mOverrideFrameDurationName = { };
		ParamsReverseAllFramesName _mReverseAllFramesName = { };
		ParamsInvertColorsAllFramesName _mInvertColorsAllFramesName = { };
		ParamsDuplicateMirrorFramesName _mDuplicateMirrorFramesName = { };
		ParamsInsertDelayName _mInsertDelayName = { };
		ParamsReduceFramesName _mReduceFramesName = { };
		ParamsDuplicateFramesName _mDuplicateFramesName = { };
		ParamsTrimStartFramesName _mTrimStartFramesName = { };
		ParamsTrimEndFramesName _mTrimEndFramesName = { };
		ParamsFillRandomColorsBlackAndWhiteAllFramesName _mFillRandomColorsBlackAndWhiteAllFramesName = { };
		ParamsUseIdleAnimation _mUseIdleAnimation = { };
		ParamsMultiplyColorLerpAllFramesName _mMultiplyColorLerpAllFramesName = { };
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
		// async implementation
		int ImplGetAnimation(const wchar_t* name);
		void ImplCloseAnimationName(const wchar_t* path);
		void ImplSetIdleAnimationName(const wchar_t* name);
		void ImplStopAnimationType(int deviceType, int device);
		// color manipulation
		void ImplMakeBlankFramesRGBName(const wchar_t* path, int frameCount, float duration, int red, int green, int blue);
		void ImplFillThresholdColorsMinMaxAllFramesRGBName(const wchar_t* path, int minThreshold, int minRed, int minGreen, int minBlue, int maxThreshold, int maxRed, int maxGreen, int maxBlue);
		void ImplMultiplyIntensityAllFramesRGBName(const wchar_t* path, int red, int green, int blue);
		void ImplFadeStartFramesName(const wchar_t* path, int fade);
		void ImplFadeEndFramesName(const wchar_t* path, int fade);
		void ImplMultiplyIntensityName(const wchar_t* path, int frameId, float intensity);
		void ImplMultiplyIntensityAllFramesName(const wchar_t* path, float intensity);
		void ImplMultiplyIntensityRGBName(const wchar_t* path, int frameId, int red, int green, int blue);
		void ImplMultiplyIntensityColorName(const wchar_t* path, int frameId, int color);
		void ImplFillThresholdColorsRGBName(const wchar_t* path, int frameId, int threshold, int red, int green, int blue);
		void ImplCopyNonZeroAllKeysAllFramesName(const wchar_t* sourceAnimation, const wchar_t* targetAnimation);
		void ImplMakeBlankFramesName(const wchar_t* path, int frameCount, float duration, int color);
		void ImplFillThresholdColorsAllFramesName(const wchar_t* path, int threshold, int color);
		void ImplAddNonZeroAllKeysAllFramesName(const wchar_t* sourceAnimation, const wchar_t* targetAnimation);
		void ImplSubtractNonZeroAllKeysAllFramesName(const wchar_t* sourceAnimation, const wchar_t* targetAnimation);
		void ImplCopyNonZeroTargetAllKeysAllFramesName(const wchar_t* sourceAnimation, const wchar_t* targetAnimation);
		void ImplFillZeroColorAllFramesRGBName(const wchar_t* path, int red, int green, int blue);
		void ImplDuplicateFirstFrameName(const wchar_t* path, int frameCount);
		void ImplOverrideFrameDurationName(const wchar_t* path, float duration);
		void ImplReverseAllFramesName(const wchar_t* path);
		void ImplInvertColorsAllFramesName(const wchar_t* path);
		void ImplDuplicateMirrorFramesName(const wchar_t* path);
		void ImplInsertDelayName(const wchar_t* path, int frameId, int delay);
		void ImplReduceFramesName(const wchar_t* path, int n);
		void ImplDuplicateFramesName(const wchar_t* path);
		void ImplTrimStartFramesName(const wchar_t* path, int numberOfFrames);
		void ImplTrimEndFramesName(const wchar_t* path, int lastFrameId);
		void ImplFillRandomColorsBlackAndWhiteAllFramesName(const wchar_t* path);
		void ImplUseIdleAnimation(int device, bool flag);
		void ImplMultiplyColorLerpAllFramesName(const wchar_t* path, int color1, int color2);
		// async calls
		void AsyncGetAnimation(const wchar_t* path);
		void AsyncCloseAnimationName(const wchar_t* path);
		void AsyncPlayAnimationName(const wchar_t* path, bool loop);
		RZRESULT AsyncSetEventName(LPCTSTR Name);
		void AsyncSetIdleAnimationName(const wchar_t* path);
		void AsyncStopAll();
		void AsyncStopAnimationName(const wchar_t* path);
		void AsyncStopAnimationType(int deviceType, int device);
		void UseIdleAnimation(EChromaSDKDeviceEnum device, bool flag);
		void AsyncUseForwardChromaEvents(bool flag);
		void AsyncUseIdleAnimations(bool flag);
		void AsyncMultiplyIntensityAllFramesName(const wchar_t* path, float intensity);
		void AsyncMakeBlankFramesName(const wchar_t* path, int frameCount, float duration, int color);
		// color manipulation
		void AsyncMakeBlankFramesRGBName(const wchar_t* path, int frameCount, float duration, int red, int green, int blue);
		void AsyncFillThresholdColorsMinMaxAllFramesRGBName(const wchar_t* path, int minThreshold, int minRed, int minGreen, int minBlue, int maxThreshold, int maxRed, int maxGreen, int maxBlue);
		void AsyncMultiplyIntensityAllFramesRGBName(const wchar_t* path, int red, int green, int blue);
		void AsyncFadeStartFramesName(const wchar_t* path, int fade);
		void AsyncFadeEndFramesName(const wchar_t* path, int fade);
		void AsyncMultiplyIntensityName(const wchar_t* path, int frameId, float intensity);
		void AsyncMultiplyIntensityRGBName(const wchar_t* path, int frameId, int red, int green, int blue);
		void AsyncMultiplyIntensityColorName(const wchar_t* path, int frameId, int color);
		void AsyncFillThresholdColorsRGBName(const wchar_t* path, int frameId, int threshold, int red, int green, int blue);
		void AsyncCopyNonZeroAllKeysAllFramesName(const wchar_t* sourceAnimation, const wchar_t* targetAnimation);
		void AsyncFillThresholdColorsAllFramesName(const wchar_t* path, int threshold, int color);
		void AsyncAddNonZeroAllKeysAllFramesName(const wchar_t* sourceAnimation, const wchar_t* targetAnimation);
		void AsyncSubtractNonZeroAllKeysAllFramesName(const wchar_t* sourceAnimation, const wchar_t* targetAnimation);
		void AsyncCopyNonZeroTargetAllKeysAllFramesName(const wchar_t* sourceAnimation, const wchar_t* targetAnimation);
		void AsyncFillZeroColorAllFramesRGBName(const wchar_t* path, int red, int green, int blue);
		void AsyncDuplicateFirstFrameName(const wchar_t* path, int frameCount);
		void AsyncOverrideFrameDurationName(const wchar_t* path, float duration);
		void AsyncReverseAllFramesName(const wchar_t* path);
		void AsyncInvertColorsAllFramesName(const wchar_t* path);
		void AsyncDuplicateMirrorFramesName(const wchar_t* path);
		void AsyncInsertDelayName(const wchar_t* path, int frameId, int delay);
		void AsyncReduceFramesName(const wchar_t* path, int n);
		void AsyncDuplicateFramesName(const wchar_t* path);
		void AsyncTrimStartFramesName(const wchar_t* path, int numberOfFrames);
		void AsyncTrimEndFramesName(const wchar_t* path, int lastFrameId);
		void AsyncFillRandomColorsBlackAndWhiteAllFramesName(const wchar_t* path);
		void AsyncUseIdleAnimation(int device, bool flag);
		void AsyncMultiplyColorLerpAllFramesName(const wchar_t* path, int color1, int color2);
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
		static std::vector<std::wstring> _sIdleAnimation;
		static std::vector<std::wstring> _sOrderPendingCommands;
		static std::map<std::wstring, PendingCommand> _sPendingCommands;
		static RZRESULT _sLastResultSetEventName;
	};
}
