#pragma once

#include "ChromaSDKPluginTypes.h"
#include "AnimationBase.h"

namespace ChromaSDK
{
	class Animation2D : public AnimationBase
	{
	public:
		Animation2D();
		Animation2D& operator=(const Animation2D& rhs);
		void Reset();
		EChromaSDKDeviceTypeEnum GetDeviceType();
		EChromaSDKDevice2DEnum GetDevice();
		bool SetDevice(EChromaSDKDevice2DEnum device);
		int GetDeviceId();
		std::vector<FChromaSDKColorFrame2D>& GetFrames();
		int GetFrameCount();
		float GetDuration(unsigned int index);
		void Load();
		void Unload();
		void Play(bool loop);
		void Pause();
		void Resume(bool loop);
		void Stop();
		void Update(float deltaTime);
		void ResetFrames();
		int Save(const wchar_t* path);
		void SetChromaCustom(bool flag);
		bool UseChromaCustom();

		// Support idle animation
		void InternalUpdate(float deltaTime);

		// Handle preload and immediate mode
		void InternalShowFrame();
	private:
		EChromaSDKDevice2DEnum _mDevice;
		std::vector<FChromaSDKColorFrame2D> _mFrames;
		bool _mUseChromaCustom;
	};
}
