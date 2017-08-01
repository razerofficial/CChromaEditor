#include "stdafx.h"
#include "Animation2D.h"
#include "ChromaSDKPlugin.h"
#include "ChromaThread.h"

using namespace ChromaSDK;
using namespace std;

Animation2D::Animation2D()
{
	//default device
	_mDevice = EChromaSDKDevice2DEnum::DE_Keyboard;
	Reset();
}

void Animation2D::Reset()
{
	_mFrames.clear();
	FChromaSDKColorFrame2D frame = FChromaSDKColorFrame2D();
	frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors2D(_mDevice);
	_mFrames.push_back(frame);

	_mIsPlaying = false;
	_mIsLoaded = false;
	_mTime = 0.0f;
	_mCurrentFrame = 0;
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

vector<FChromaSDKColorFrame2D>& Animation2D::GetFrames()
{
	return _mFrames;
}

int Animation2D::GetFrameCount()
{
	return _mFrames.size();
}

float Animation2D::GetDuration(int index)
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

	for (int i = 0; i < _mFrames.size(); ++i)
	{
		FChromaSDKColorFrame2D& frame = _mFrames[i];
		try
		{
			FChromaSDKEffectResult effect = ChromaSDKPlugin::GetInstance()->CreateEffectCustom2D(_mDevice, frame.Colors);
			if (effect.Result != 0)
			{
				fprintf(stderr, "Load: Failed to create effect!\r\n");
			}
			_mEffects.push_back(effect);
		}
		catch (std::exception)
		{
			fprintf(stderr, "Load: Exception in create effect!\r\n");
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

	for (int i = 0; i < _mEffects.size(); ++i)
	{
		FChromaSDKEffectResult& effect = _mEffects[i];
		try
		{
			int result = ChromaSDKPlugin::GetInstance()->DeleteEffect(effect.EffectId);
			if (result != 0)
			{
				fprintf(stderr, "Unload: Failed to delete effect!\r\n");
			}
		}
		catch (std::exception)
		{
			fprintf(stderr, "Unload: Exception in delete effect!\r\n");
		}
	}
	_mEffects.clear();
	_mIsLoaded = false;
}

void Animation2D::Play()
{
	if (!_mIsLoaded)
	{
		Load();
	}

	_mTime = 0.0f;
	_mIsPlaying = true;
	_mCurrentFrame = 0;

	if (_mCurrentFrame < _mEffects.size())
	{
		FChromaSDKEffectResult& effect = _mEffects[_mCurrentFrame];
		try
		{
			int result = ChromaSDKPlugin::GetInstance()->SetEffect(effect.EffectId);
			if (result != 0)
			{
				fprintf(stderr, "Play: Failed to set effect!\r\n");
			}
		}
		catch (std::exception)
		{
			fprintf(stderr, "Play: Exception in set effect!\r\n");
		}
	}

	if (ChromaThread::Instance())
	{
		ChromaThread::Instance()->AddAnimation(this);
	}
}

void Animation2D::Stop()
{
	if (ChromaThread::Instance())
	{
		ChromaThread::Instance()->RemoveAnimation(this);
	}
}

void Animation2D::Update(float deltaTime)
{
	if (!_mIsPlaying)
	{
		return;
	}

	_mTime += deltaTime;
	float nextTime = GetDuration(_mCurrentFrame);
	if (nextTime < _mTime)
	{
		_mTime = 0.0f;
		++_mCurrentFrame;
		if (_mCurrentFrame < _mEffects.size())
		{
			FChromaSDKEffectResult& effect = _mEffects[_mCurrentFrame];
			try
			{
				int result = ChromaSDKPlugin::GetInstance()->SetEffect(effect.EffectId);
				if (result != 0)
				{
					fprintf(stderr, "Update: Failed to set effect!\r\n");
				}
			}
			catch (std::exception)
			{
				fprintf(stderr, "Update: Exception in set effect!\r\n");
			}
		}
		else
		{
			//fprintf(stdout, "Update: Animation Complete.\r\n");
			_mIsPlaying = false;
			_mTime = 0.0f;
			_mCurrentFrame = 0;
		}
	}
}
