#include "stdafx.h"
#include "EditorAnimation2D.h"

using namespace ChromaSDK;
using namespace std;

EChromaSDKDevice2DEnum EditorAnimation2D::GetDevice()
{
	return _mAnimation.GetDevice();
}

bool EditorAnimation2D::SetDevice(EChromaSDKDevice2DEnum device)
{
	return _mAnimation.SetDevice(device);
}

int EditorAnimation2D::GetCurrentFrame()
{
	return _mCurrentFrame;
}

vector<FChromaSDKColorFrame2D>& EditorAnimation2D::GetFrames()
{
	return _mAnimation.GetFrames();
}
