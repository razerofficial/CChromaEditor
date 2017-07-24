#include "stdafx.h"
#include "Animation1D.h"
#include "ChromaSDKPlugin.h"

using namespace ChromaSDK;
using namespace std;

Animation1D::Animation1D()
{
	// default devie
	_mDevice = EChromaSDKDevice1DEnum::DE_ChromaLink;
	Reset();
}

void Animation1D::Reset()
{
	_mFrames.clear();
	FChromaSDKColorFrame1D frame = FChromaSDKColorFrame1D();
	frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors1D(_mDevice);
	_mFrames.push_back(frame);
}

EChromaSDKDevice1DEnum Animation1D::GetDevice()
{
	return _mDevice;
}

bool Animation1D::SetDevice(EChromaSDKDevice1DEnum device)
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

vector<FChromaSDKColorFrame1D>& Animation1D::GetFrames()
{
	return _mFrames;
}

int Animation1D::GetFrameCount()
{
	return _mFrames.size();
}

void Animation1D::Update()
{

}
