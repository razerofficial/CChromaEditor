#pragma once

#include "ChromaSDKPluginTypes.h"
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
		virtual void Play(bool loop) = 0;
		bool IsPlaying();
		virtual void Load() = 0;
		virtual void Unload() = 0;
		virtual void Stop() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void ResetFrames() = 0;
		virtual int Save(const char* path) = 0;
	protected:
		std::string _mName;
		int _mCurrentFrame;
		bool _mIsLoaded;
		bool _mIsPlaying;
		float _mTime;
		std::vector<FChromaSDKEffectResult> _mEffects;
	};
}
