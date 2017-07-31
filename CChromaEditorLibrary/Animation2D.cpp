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

void Animation2D::Play()
{
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

void Animation2D::Update()
{
	fprintf(stdout, "Animation2D::Update()\r\n");
}
