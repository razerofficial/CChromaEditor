#pragma once

#include "ChromaSDKPluginTypes.h"

namespace ChromaSDK
{
	class AnimationBase
	{
	public:
		AnimationBase();
		virtual EChromaSDKDeviceTypeEnum GetDeviceType() = 0;
		int GetCurrentFrame();
		void SetCurrentFrame(int index);
		virtual int GetFrameCount() = 0;
		virtual void Play() = 0;
		bool IsPlaying();
		virtual void Load() = 0;
		virtual void Unload() = 0;
		virtual void Stop() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void ResetFrames() = 0;
	protected:
		int _mCurrentFrame;
		bool _mIsLoaded;
		bool _mIsPlaying;
		float _mTime;
		std::vector<FChromaSDKEffectResult> _mEffects;
	};
}
