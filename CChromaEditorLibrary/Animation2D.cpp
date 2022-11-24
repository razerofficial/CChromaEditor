#include "stdafx.h"
#include "Animation2D.h"
#include "ChromaSDKPlugin.h"
#include "ChromaThread.h"
#include "ChromaLogger.h"

#define ANIMATION_VERSION 1

using namespace ChromaSDK;
using namespace std;

Animation2D::Animation2D()
{
	//default device
	_mDevice = EChromaSDKDevice2DEnum::DE_Keyboard;
	_mUseChromaCustom = false;
	Reset();
}

Animation2D& Animation2D::operator=(const Animation2D& rhs)
{
	_mDevice = rhs._mDevice;
	_mUseChromaCustom = rhs._mUseChromaCustom;
	_mFrames = rhs._mFrames;

	_mIsPlaying = rhs._mIsPlaying;
	_mIsLoaded = rhs._mIsLoaded;
	_mTime = rhs._mTime;
	_mCurrentFrame = rhs._mCurrentFrame;
	_mLoop = rhs._mLoop;
	return *this;
}

void Animation2D::Reset()
{
	_mFrames.clear();
	FChromaSDKColorFrame2D frame = FChromaSDKColorFrame2D(_mDevice);
	frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors2D(_mDevice);
	_mFrames.push_back(frame);

	_mIsPlaying = false;
	_mIsLoaded = false;
	_mTime = 0.0f;
	_mCurrentFrame = 0;
	_mLoop = false;
}

EChromaSDKDeviceTypeEnum Animation2D::GetDeviceType()
{
	return EChromaSDKDeviceTypeEnum::DE_2D;
}

EChromaSDKDevice2DEnum Animation2D::GetDevice()
{
	return _mDevice;
}

bool Animation2D::SetDevice(EChromaSDKDevice2DEnum device)
{
	if (_mDevice != device)
	{
		_mDevice = device;
		Reset();
		return true;
	}
	else
	{
		return false;
	}
}

int Animation2D::GetDeviceId()
{
	return (int)GetDevice();
}

vector<FChromaSDKColorFrame2D>& Animation2D::GetFrames()
{
	return _mFrames;
}

int Animation2D::GetFrameCount()
{
	return _mFrames.size();
}

float Animation2D::GetDuration(unsigned int index)
{
	if (index < _mFrames.size())
	{
		FChromaSDKColorFrame2D& frame = _mFrames[index];
		return frame.Duration;
	}
	return 0.0f;
}

void Animation2D::Load()
{
	if (_mIsLoaded)
	{
		return;
	}

	for (unsigned int i = 0; i < _mFrames.size(); ++i)
	{
		FChromaSDKColorFrame2D& frame = _mFrames[i];
		try
		{
			FChromaSDKEffectResult effect;
			switch (_mDevice)
			{
			case EChromaSDKDevice2DEnum::DE_Keyboard:
				if (_mUseChromaCustom)
				{
					effect = ChromaSDKPlugin::GetInstance()->CreateEffectKeyboardCustom2D(frame.Colors, frame.Keys);
				}
				else
				{
					effect = ChromaSDKPlugin::GetInstance()->CreateEffectCustom2D(_mDevice, frame.Colors, frame.Keys);
				}
				break;
			case EChromaSDKDevice2DEnum::DE_KeyboardExtended:
				if (_mUseChromaCustom)
				{
					effect = ChromaSDKPlugin::GetInstance()->CreateEffectKeyboardExtendedCustom2D(frame.Colors, frame.Keys);
				}
				else
				{
					effect = ChromaSDKPlugin::GetInstance()->CreateEffectCustom2D(_mDevice, frame.Colors, frame.Keys);
				}
				break;
			default:
				effect = ChromaSDKPlugin::GetInstance()->CreateEffectCustom2D(_mDevice, frame.Colors, frame.Keys);
				break;
			}			
			if (effect.Result != 0)
			{
				ChromaLogger::fprintf(stderr, "Load: Failed to create effect!\r\n");
			}
			_mEffects.push_back(effect);
		}
		catch (exception)
		{
			ChromaLogger::fprintf(stderr, "Load: Exception in create effect!\r\n");
			FChromaSDKEffectResult result = FChromaSDKEffectResult();
			result.Result = -1;
			_mEffects.push_back(result);
		}
	}

	_mIsLoaded = true;
}

void Animation2D::Unload()
{
	if (!_mIsLoaded)
	{
		return;
	}

	for (unsigned int i = 0; i < _mEffects.size(); ++i)
	{
		FChromaSDKEffectResult& effect = _mEffects[i];
		try
		{
			int result = ChromaSDKPlugin::GetInstance()->DeleteEffect(effect.EffectId);
			if (result != 0)
			{
				ChromaLogger::fprintf(stderr, "Unload: Failed to delete effect!\r\n");
			}
		}
		catch (exception)
		{
			ChromaLogger::fprintf(stderr, "Unload: Exception in delete effect!\r\n");
		}
	}
	_mEffects.clear();
	_mIsLoaded = false;
}

void Animation2D::Play(bool loop)
{
	_mTime = 0.0f;
	_mCurrentFrame = -1;
	_mIsPlaying = true;
	_mLoop = loop;
	_mIsPaused = false;

	if (ChromaThread::Instance())
	{
		ChromaThread::Instance()->AddAnimation(this);
	}
}

void Animation2D::Pause()
{
	_mIsPaused = true;
}

void Animation2D::Resume(bool loop)
{
	_mIsPaused = false;
	_mLoop = loop;
}

void Animation2D::Stop()
{
	_mIsPlaying = false;

	if (ChromaThread::Instance())
	{
		ChromaThread::Instance()->RemoveAnimation(this);
	}
}

void Animation2D::Update(float deltaTime)
{
	if (_mIsPaused)
	{
		return;
	}

	if (!_mIsPlaying)
	{
		return;
	}

	InternalUpdate(deltaTime);
}

void Animation2D::InternalShowFrame()
{
	if (_mUsePreloading)
	{
		// use cached effects
		if (_mCurrentFrame >= 0 && _mCurrentFrame < (int)_mEffects.size())
		{
			FChromaSDKEffectResult& effect = _mEffects[_mCurrentFrame];
			try
			{
				int result = ChromaSDKPlugin::GetInstance()->SetEffect(effect.EffectId);
				if (result != 0)
				{
					ChromaLogger::fprintf(stderr, "InternalShowFrame: Failed to set effect!\r\n");
				}
			}
			catch (exception)
			{
				ChromaLogger::fprintf(stderr, "InternalShowFrame: Exception in set effect!\r\n");
			}
		}
	}
	else
	{
		//immediate mode
		if (_mCurrentFrame >= 0 && _mCurrentFrame < (int)_mFrames.size())
		{
			FChromaSDKColorFrame2D& frame = _mFrames[_mCurrentFrame];
			try
			{
				FChromaSDKEffectResult effect;
				switch (_mDevice)
				{
				case EChromaSDKDevice2DEnum::DE_Keyboard:
					if (_mUseChromaCustom)
					{
						effect = ChromaSDKPlugin::GetInstance()->CreateEffectKeyboardCustom2D(frame.Colors, frame.Keys);
					}
					else
					{
						effect = ChromaSDKPlugin::GetInstance()->CreateEffectCustom2D(_mDevice, frame.Colors, frame.Keys);
					}
					break;
				case EChromaSDKDevice2DEnum::DE_KeyboardExtended:
					if (_mUseChromaCustom)
					{
						effect = ChromaSDKPlugin::GetInstance()->CreateEffectKeyboardExtendedCustom2D(frame.Colors, frame.Keys);
					}
					else
					{
						effect = ChromaSDKPlugin::GetInstance()->CreateEffectCustom2D(_mDevice, frame.Colors, frame.Keys);
					}
					break;
				default:
					effect = ChromaSDKPlugin::GetInstance()->CreateEffectCustom2D(_mDevice, frame.Colors, frame.Keys);
					break;
				}				
				if (effect.Result == RZRESULT_SUCCESS)
				{
					ChromaSDKPlugin::GetInstance()->SetEffect(effect.EffectId);
					ChromaSDKPlugin::GetInstance()->DeleteEffect(effect.EffectId);
				}
			}
			catch (exception)
			{
				ChromaLogger::fprintf(stderr, "InternalShowFrame: Exception in set effect!\r\n");
			}
		}
	}
}

void Animation2D::InternalUpdate(float deltaTime)
{
	if (_mCurrentFrame == -1)
	{
		_mCurrentFrame = 0;
		InternalShowFrame();
	}
	else
	{
		_mTime += deltaTime;
		float nextTime = GetDuration(_mCurrentFrame);
		if (nextTime < _mTime)
		{
			_mTime = 0.0f;
			if ((_mCurrentFrame + 1) < (int)_mFrames.size())
			{
				++_mCurrentFrame;
				InternalShowFrame();
			}
			else
			{
				if (_mLoop)
				{
					_mTime = 0.0f;
					_mCurrentFrame = -1;
				}
				else
				{
					//ChromaLogger::printf("Update: Animation Complete.\r\n");
					_mIsPlaying = false;
					_mTime = 0.0f;
					_mCurrentFrame = 0;
				}
			}
		}
	}
}

void Animation2D::ResetFrames()
{
	_mCurrentFrame = 0;
	while (_mFrames.size() > 0)
	{
		auto it = _mFrames.begin();
		_mFrames.erase(it);
	}
	FChromaSDKColorFrame2D frame = FChromaSDKColorFrame2D(_mDevice);
	frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors2D(_mDevice);
	frame.Duration = 1;
	_mFrames.push_back(frame);
}

int Animation2D::Save(const char* path)
{
	FILE* stream;
	int result = fopen_s(&stream, path, "wb");
	if (result == 13)
	{
		ChromaLogger::fprintf(stderr, "Save: Permission denied! %s\r\n", path);
		return - 1;
	}
	else if (0 == result &&
		stream)
	{
		long write = 0;
		long expectedWrite = 1;
		long expectedSize = 0;

		int version = ANIMATION_VERSION;
		expectedSize = sizeof(int);
		write = fwrite(&version, expectedSize, 1, stream);
		if (expectedWrite != write)
		{
			ChromaLogger::fprintf(stderr, "Save: Failed to write version!\r\n");
			std::fclose(stream);
			return -1;
		}

		//device type
		BYTE deviceType = (BYTE)EChromaSDKDeviceTypeEnum::DE_2D;
		expectedSize = sizeof(BYTE);
		fwrite(&deviceType, expectedSize, 1, stream);

		switch ((EChromaSDKDeviceTypeEnum)deviceType)
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
			LogDebug("Save: DeviceType: 1D\r\n");
			break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
			LogDebug("Save: DeviceType: 2D\r\n");
			break;
		}

		//device
		BYTE device = (BYTE)_mDevice;
		fwrite(&device, expectedSize, 1, stream);

		switch ((EChromaSDKDevice2DEnum)device)
		{
		case EChromaSDKDevice2DEnum::DE_Keyboard:
			LogDebug("Save: Device: DE_Keyboard\r\n");
			break;
		case EChromaSDKDevice2DEnum::DE_Keypad:
			LogDebug("Save: Device: DE_Keypad\r\n");
			break;
		case EChromaSDKDevice2DEnum::DE_Mouse:
			LogDebug("Save: Device: DE_Mouse\r\n");
			break;
		}

		//frame count
		unsigned int frameCount = _mFrames.size();
		expectedSize = sizeof(unsigned int);
		fwrite(&frameCount, expectedSize, 1, stream);

		LogDebug("Save: FrameCount: %d\r\n", frameCount);

		//frames
		COLORREF color = RGB(0, 0, 0);
		float duration = 0.0f;
		for (unsigned int index = 0; index < frameCount; ++index)
		{
			//duration
			duration = GetDuration(index);
			expectedSize = sizeof(float);
			fwrite(&duration, expectedSize, 1, stream);

			//colors
			if (index < _mFrames.size())
			{
				FChromaSDKColorFrame2D& frame = _mFrames[index];
				for (unsigned int i = 0; i < frame.Colors.size(); ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (unsigned int j = 0; j < row.Colors.size(); ++j)
					{
						//color
						color = row.Colors[j];
						expectedSize = sizeof(int);
						fwrite(&color, expectedSize, 1, stream);
					}
				}
			}
		}

		fflush(stream);
		std::fclose(stream);

		return 0;
	}

	return -1;
}

void Animation2D::SetChromaCustom(bool flag)
{
	_mUseChromaCustom = flag;
}

bool Animation2D::UseChromaCustom()
{
	return _mUseChromaCustom;
}
