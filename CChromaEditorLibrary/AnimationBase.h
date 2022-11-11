#pragma once

#include "ChromaSDKPluginTypes.h"
#include <mutex>
#include <string>

namespace ChromaSDK
{
	class AnimationBase
	{
	public:
		AnimationBase();
		const std::string& GetName();
		void SetName(const std::string& name);
		virtual EChromaSDKDeviceTypeEnum GetDeviceType() = 0;
		int GetDeviceTypeId();
		virtual int GetDeviceId() = 0;
		int GetCurrentFrame();
		void SetCurrentFrame(int index);
		virtual int GetFrameCount() = 0;
		virtual float GetDuration(unsigned int index) = 0;
		virtual void Play(bool loop) = 0;
		virtual void Pause() = 0;
		virtual void Resume(bool loop) = 0;
		bool IsPlaying();
		bool IsPaused();
		bool HasLoop();
		virtual void Load() = 0;
		virtual void Unload() = 0;
		virtual void Stop() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void ResetFrames() = 0;
		virtual int Save(const char* path) = 0;
		void UsePreloading(bool flag);
		bool HasUsePreloading();

		// Support idle animation

		std::mutex& GetMutex();

		// Update the animation whether it's playing or not, used by the idle animation
		virtual void InternalUpdate(float deltaTime) = 0;
		virtual void InternalSetTime(float time);
		virtual void InternalSetCurrentFrame(int currentFrame);
		virtual void InternalSetIsPlaying(bool isPlaying);
		virtual void InternalSetLoop(bool loop);
		virtual void InternalSetIsPaused(bool isPaused);

		// Handle preload and immediate mode
		virtual void InternalShowFrame() = 0;

	protected:
		std::string _mName;
		int _mCurrentFrame;
		bool _mIsLoaded;
		bool _mIsPlaying;
		bool _mIsPaused;
		bool _mLoop;
		float _mTime;
		bool _mUsePreloading;
		std::vector<FChromaSDKEffectResult> _mEffects;
		std::mutex _mMutex;
	};
}
