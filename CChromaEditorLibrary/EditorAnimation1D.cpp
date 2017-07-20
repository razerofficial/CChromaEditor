#include "stdafx.h"
#include "EditorAnimation1D.h"

using namespace ChromaSDK;
using namespace std;

EChromaSDKDevice1DEnum EditorAnimation1D::GetDevice()
{
	return _mAnimation.GetDevice();
}

bool EditorAnimation1D::SetDevice(EChromaSDKDevice1DEnum device)
{
	return _mAnimation.SetDevice(device);
}

int EditorAnimation1D::GetCurrentFrame()
{
	return _mCurrentFrame;
}

vector<FChromaSDKColorFrame1D>& EditorAnimation1D::GetFrames()
{
	return _mAnimation.GetFrames();
}
