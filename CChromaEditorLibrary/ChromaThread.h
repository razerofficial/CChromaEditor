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
			key += _mPath; // Collapse names, no real need for more than 30 FPS for animation names
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
			key += _mPath; // Collapse names, no real need for more than 30 FPS for animation names
			return key;
		}
	};

	struct ParamsStopAnimationName
	{
		std::wstring _mPath;

		const std::wstring GenerateKey() {
			std::wstring key = L"StopChromaAnimationName_";
			key += _mPath; // Collapse names, no real need for more than 30 FPS for animation names
			return key;
		}
	};

	struct ParamsStopAll
	{
		const std::wstring GenerateKey() {
			std::wstring key = L"StopAll";
			// Rate limited use the last command
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
			// Rate limited, use the last command
			return key;
		}
	};

	struct ParamsUseIdleAnimations
	{
		bool _mFlag;

		static const std::wstring GenerateKey() {
			std::wstring key = L"UseIdleAnimations";
			// Rate limited, use the last command
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

	struct ParamsSetKeyColorName
	{
		std::wstring _mPath;
		int _mFrameId = 0;
		int _mRzKey = 0;
		int _mColor = 0;
		const std::wstring GenerateKey() {
			std::wstring key = L"SetKeyColorName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsSetChromaCustomFlagName
	{
		std::wstring _mPath;
		bool _mFlag;
		const std::wstring GenerateKey() {
			std::wstring key = L"SetChromaCustomFlagName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsMultiplyTargetColorLerpAllFramesName
	{
		std::wstring _mPath;
		int _mColor1 = 0;
		int _mColor2 = 0;
		const std::wstring GenerateKey() {
			std::wstring key = L"MultiplyTargetColorLerpAllFramesName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsSetKeysColorAllFramesName
	{
		std::wstring _mPath;
		std::vector<int> _mRzKeys;
		int _mColor = 0;
		const std::wstring GenerateKey() {
			std::wstring key = L"SetKeysColorAllFramesName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsCopyKeysColorAllFramesName
	{
		std::wstring _mSourceAnimation;
		std::wstring _mTargetAnimation;
		std::vector<int> _mKeys;
		const std::wstring GenerateKey() {
			std::wstring key = L"CopyKeysColorAllFramesName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsSetKeysColorAllFramesRGBName
	{
		std::wstring _mPath;
		std::vector<int> _mRzKeys;
		int _mRed = 0;
		int _mGreen = 0;
		int _mBlue = 0;
		const std::wstring GenerateKey() {
			std::wstring key = L"SetKeysColorAllFramesRGBName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsCoreStreamGetAuthShortcode
	{
		std::wstring _mPlatform;
		std::wstring _mTitle;

		const std::wstring GenerateKey() {
			std::wstring key = L"CoreStreamGetAuthShortcode";
			// definitely rate limit, no need to call more than 1 FPS
			return key;
		}
	};

	struct ResultCoreStreamGetAuthShortcode
	{
		std::string _mShortcode;
	};

	struct ParamsCoreStreamGetStatus
	{
		const std::wstring GenerateKey() {
			std::wstring key = L"CoreStreamGetStatus";
			// definitely rate limit, no need to call more than 1 FPS
			return key;
		}
	};

	struct ResultCoreStreamGetStatus
	{
		Stream::StreamStatusType _mStatus = Stream::StreamStatusType::SERVICE_OFFLINE;
	};

	struct ParamsCoreStreamSetFocus
	{
		std::string _mFocus;
		const std::wstring GenerateKey() {
			std::wstring key = L"CoreStreamSetFocus";
			// definitely rate limit, no need to call more than 1 FPS
			return key;
		}
	};

	struct ResultCoreStreamSetFocus
	{
		bool _mResult = false;
	};

	struct ParamsCoreStreamGetFocus
	{
		const std::wstring GenerateKey() {
			std::wstring key = L"CoreStreamGetFocus";
			// definitely rate limit, no need to call more than 1 FPS
			return key;
		}
	};

	struct ResultCoreStreamGetFocus
	{
		bool _mResult = false;
		std::string _mFocus;
	};

	struct ParamsCoreStreamGetId
	{
		std::string _mShortcode;

		const std::wstring GenerateKey() {
			std::wstring key = L"CoreStreamGetId";
			// definitely rate limit, no need to call more than 1 FPS
			return key;
		}
	};

	struct ResultCoreStreamGetId
	{
		std::string _mStreamId;
	};

	struct ParamsCoreStreamGetKey
	{
		std::string _mShortcode;
		const std::wstring GenerateKey() {
			std::wstring key = L"CoreStreamGetKey";
			// definitely rate limit, no need to call more than 1 FPS
			return key;
		}
	};

	struct ResultCoreStreamGetKey
	{
		std::string _mStreamKey;
	};

	struct ParamsCoreStreamBroadcast
	{
		std::string _mStreamId;
		std::string _mStreamKey;
		const std::wstring GenerateKey() {
			std::wstring key = L"CoreStreamBroadcast";
			// definitely rate limit, no need to call more than 1 FPS
			return key;
		}
	};

	struct ResultCoreStreamBroadcast
	{
		bool _mResult = false;
	};

	struct ParamsCoreStreamBroadcastEnd
	{
		const std::wstring GenerateKey() {
			std::wstring key = L"CoreStreamBroadcastEnd";
			// definitely rate limit, no need to call more than 1 FPS
			return key;
		}
	};

	struct ResultCoreStreamBroadcastEnd
	{
		bool _mResult = false;
	};

	struct ParamsCoreStreamWatch
	{
		std::string _mStreamId;
		unsigned long long _mTimestamp = 0;
		const std::wstring GenerateKey() {
			std::wstring key = L"CoreStreamWatch";
			// definitely rate limit, no need to call more than 1 FPS
			return key;
		}
	};

	struct ResultCoreStreamWatch
	{
		bool _mResult = false;
	};

	struct ParamsCoreStreamWatchEnd
	{
		const std::wstring GenerateKey() {
			std::wstring key = L"CoreStreamWatchEnd";
			// definitely rate limit, no need to call more than 1 FPS
			return key;
		}
	};

	struct ResultCoreStreamWatchEnd
	{
		bool _mResult = false;
	};

	struct ParamsCoreStreamReleaseShortcode
	{
		std::string _mShortcode;
		const std::wstring GenerateKey() {
			std::wstring key = L"CoreStreamReleaseShortcode";
			// definitely rate limit, no need to call more than 1 FPS
			return key;
		}
	};

	struct ResultCoreStreamReleaseShortcode
	{
		bool _mResult = false;
	};

	struct ParamsPreviewFrameName
	{
		std::wstring _mPath;
		int _mFrameIndex = 0;
		const std::wstring GenerateKey() {
			std::wstring key = L"PreviewFrameName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsCopyNonZeroAllKeysName
	{
		std::wstring _mSourceAnimation;
		std::wstring _mTargetAnimation;
		int _mFrameId = 0;
		const std::wstring GenerateKey() {
			std::wstring key = L"CopyNonZeroAllKeysName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsAddNonZeroAllKeysName
	{
		std::wstring _mSourceAnimation;
		std::wstring _mTargetAnimation;
		int _mFrameId = 0;
		const std::wstring GenerateKey() {
			std::wstring key = L"AddNonZeroAllKeysName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsSubtractNonZeroAllKeysName
	{
		std::wstring _mSourceAnimation;
		std::wstring _mTargetAnimation;
		int _mFrameId = 0;
		const std::wstring GenerateKey() {
			std::wstring key = L"SubtractNonZeroAllKeysName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsSetKeyColorAllFramesName
	{
		std::wstring _mPath;
		int _mRzKey = 0;
		int _mColor = 0;
		const std::wstring GenerateKey() {
			std::wstring key = L"SetKeyColorAllFramesName_";
			key += GenerateGUID();
			return key;
		}
	};

	struct ParamsCopyKeyColorName
	{
		std::wstring _mSourceAnimation;
		std::wstring _mTargetAnimation;
		int _mFrameId = 0;
		int _mRzKey = 0;
		const std::wstring GenerateKey() {
			std::wstring key = L"CopyKeyColorName_";
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
		Command_SetKeyColorName,
		Command_SetChromaCustomFlagName,
		Command_MultiplyTargetColorLerpAllFramesName,
		Command_SetKeysColorAllFramesName,
		Command_CopyKeysColorAllFramesName,
		Command_SetKeysColorAllFramesRGBName,
		Command_CoreStreamGetAuthShortcode,
		Command_CoreStreamGetStatus,
		Command_CoreStreamSetFocus,
		Command_CoreStreamGetFocus,
		Command_CoreStreamGetId,
		Command_CoreStreamGetKey,
		Command_CoreStreamBroadcast,
		Command_CoreStreamBroadcastEnd,
		Command_CoreStreamWatch,
		Command_CoreStreamWatchEnd,
		Command_CoreStreamReleaseShortcode,
		Command_PreviewFrameName,
		Command_CopyNonZeroAllKeysName,
		Command_AddNonZeroAllKeysName,
		Command_SubtractNonZeroAllKeysName,
		Command_SetKeyColorAllFramesName,
		Command_CopyKeyColorName,
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
		ParamsSetKeyColorName _mSetKeyColorName = { };
		ParamsSetChromaCustomFlagName _mSetChromaCustomFlagName = { };
		ParamsMultiplyTargetColorLerpAllFramesName _mMultiplyTargetColorLerpAllFramesName = { };
		ParamsSetKeysColorAllFramesName _mSetKeysColorAllFramesName = { };
		ParamsCopyKeysColorAllFramesName _mCopyKeysColorAllFramesName = { };
		ParamsSetKeysColorAllFramesRGBName _mSetKeysColorAllFramesRGBName = { };
		ParamsCoreStreamGetAuthShortcode _mCoreStreamGetAuthShortcode = { };
		ParamsCoreStreamGetStatus _mCoreStreamGetStatus = { };
		ParamsCoreStreamSetFocus _mCoreStreamSetFocus = { };
		ParamsCoreStreamGetFocus _mCoreStreamGetFocus = { };
		ParamsCoreStreamGetId _mCoreStreamGetId = { };
		ParamsCoreStreamGetKey _mCoreStreamGetKey = { };
		ParamsCoreStreamBroadcast _mCoreStreamBroadcast = { };
		ParamsCoreStreamBroadcastEnd _mCoreStreamBroadcastEnd = { };
		ParamsCoreStreamWatch _mCoreStreamWatch = { };
		ParamsCoreStreamWatchEnd _mCoreStreamWatchEnd = { };
		ParamsCoreStreamReleaseShortcode _mCoreStreamReleaseShortcode = { };
		ParamsPreviewFrameName _mPreviewFrameName = { };
		ParamsCopyNonZeroAllKeysName _mCopyNonZeroAllKeysName = { };
		ParamsAddNonZeroAllKeysName _mAddNonZeroAllKeysName = { };
		ParamsSubtractNonZeroAllKeysName _mSubtractNonZeroAllKeysName = { };
		ParamsSetKeyColorAllFramesName _mSetKeyColorAllFramesName = { };
		ParamsCopyKeyColorName _mCopyKeyColorName = { };
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
		void ImplSetKeyColorName(const wchar_t* path, int frameId, int rzkey, int color);
		void ImplSetChromaCustomFlagName(const wchar_t* path, bool flag);
		void ImplMultiplyTargetColorLerpAllFramesName(const wchar_t* path, int color1, int color2);
		void ImplSetKeysColorAllFramesName(const wchar_t* path, const int* rzkeys, int keyCount, int color);
		void ImplCopyKeysColorAllFramesName(const wchar_t* sourceAnimation, const wchar_t* targetAnimation, const int* keys, int size);
		void ImplSetKeysColorAllFramesRGBName(const wchar_t* path, const int* rzkeys, int keyCount, int red, int green, int blue);
		void ImplCoreStreamGetAuthShortcode(const wchar_t* platform, const wchar_t* title);
		void ImplCoreStreamGetStatus();
		void ImplCoreStreamSetFocus(const char* focus);
		void ImplCoreStreamGetFocus();
		void ImplCoreStreamGetId(const char* shortcode);
		void ImplCoreStreamGetKey(const char* shortcode);
		void ImplCoreStreamBroadcast(const char* streamId, const char* streamKey);
		void ImplCoreStreamBroadcastEnd();
		void ImplCoreStreamWatch(const char* streamId, unsigned long long timestamp);
		void ImplCoreStreamWatchEnd();
		void ImplCoreStreamReleaseShortcode(const char* shortcode);
		void ImplPreviewFrameName(const wchar_t* path, int frameIndex);
		void ImplCopyNonZeroAllKeysName(const wchar_t* sourceAnimation, const wchar_t* targetAnimation, int frameId);
		void ImplAddNonZeroAllKeysName(const wchar_t* sourceAnimation, const wchar_t* targetAnimation, int frameId);
		void ImplSubtractNonZeroAllKeysName(const wchar_t* sourceAnimation, const wchar_t* targetAnimation, int frameId);
		void ImplSetKeyColorAllFramesName(const wchar_t* path, int rzkey, int color);
		void ImplCopyKeyColorName(const wchar_t* sourceAnimation, const wchar_t* targetAnimation, int frameId, int rzkey);
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
		void AsyncSetKeyColorName(const wchar_t* path, int frameId, int rzkey, int color);
		void AsyncSetChromaCustomFlagName(const wchar_t* path, bool flag);
		void AsyncMultiplyTargetColorLerpAllFramesName(const wchar_t* path, int color1, int color2);
		void AsyncSetKeysColorAllFramesName(const wchar_t* path, const int* rzkeys, int keyCount, int color);
		void AsyncCopyKeysColorAllFramesName(const wchar_t* sourceAnimation, const wchar_t* targetAnimation, const int* keys, int size);
		void AsyncSetKeysColorAllFramesRGBName(const wchar_t* path, const int* rzkeys, int keyCount, int red, int green, int blue);
		void AsyncCoreStreamGetAuthShortcode(char* shortcode, unsigned char* length, const wchar_t* platform, const wchar_t* title);
		Stream::StreamStatusType AsyncCoreStreamGetStatus();
		bool AsyncCoreStreamSetFocus(const char* focus);
		bool AsyncCoreStreamGetFocus(char* focus, unsigned char* length);
		void AsyncCoreStreamGetId(const char* shortcode, char* streamId, unsigned char* length);
		void AsyncCoreStreamGetKey(const char* shortcode, char* streamKey, unsigned char* length);
		bool AsyncCoreStreamBroadcast(const char* streamId, const char* streamKey);
		bool AsyncCoreStreamBroadcastEnd();
		bool AsyncCoreStreamWatch(const char* streamId, unsigned long long timestamp);
		bool AsyncCoreStreamWatchEnd();
		bool AsyncCoreStreamReleaseShortcode(const char* shortcode);
		void AsyncPreviewFrameName(const wchar_t* path, int frameIndex);
		void AsyncCopyNonZeroAllKeysName(const wchar_t* sourceAnimation, const wchar_t* targetAnimation, int frameId);
		void AsyncAddNonZeroAllKeysName(const wchar_t* sourceAnimation, const wchar_t* targetAnimation, int frameId);
		void AsyncSubtractNonZeroAllKeysName(const wchar_t* sourceAnimation, const wchar_t* targetAnimation, int frameId);
		void AsyncSetKeyColorAllFramesName(const wchar_t* path, int rzkey, int color);
		void AsyncCopyKeyColorName(const wchar_t* sourceAnimation, const wchar_t* targetAnimation, int frameId, int rzkey);
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
		static ResultCoreStreamGetAuthShortcode _sLastResultCoreStreamGetAuthShortcode;
		static ResultCoreStreamGetStatus _sLastResultCoreStreamGetStatus;
		static ResultCoreStreamSetFocus	_sLastResultCoreStreamSetFocus;
		static ResultCoreStreamGetFocus _sLastResultCoreStreamGetFocus;
		static ResultCoreStreamGetId _sLastResultCoreStreamGetId;
		static ResultCoreStreamGetKey _sLastResultCoreStreamGetKey;
		static ResultCoreStreamBroadcast _sLastResultCoreStreamBroadcast;
		static ResultCoreStreamBroadcastEnd _sLastResultCoreStreamBroadcastEnd;
		static ResultCoreStreamWatch _sLastResultCoreStreamWatch;
		static ResultCoreStreamWatchEnd _sLastResultCoreStreamWatchEnd;
		static ResultCoreStreamReleaseShortcode _sLastResultCoreStreamReleaseShortcode;
	};
}
