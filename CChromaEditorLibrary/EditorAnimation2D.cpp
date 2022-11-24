#include "stdafx.h"
#include "EditorAnimation2D.h"
#include "ChromaSDKPlugin.h"

using namespace ChromaSDK;
using namespace std;

EditorAnimation2D::EditorAnimation2D() :
	_mFrameCopy(EChromaSDKDevice2DEnum::DE_Keyboard)
{
	Reset();
}

AnimationBase* EditorAnimation2D::GetAnimation()
{
	return &_mAnimation;
}

void EditorAnimation2D::SetAnimation(Animation2D& animation)
{
	_mAnimation = animation;
}

EChromaSDKDevice2DEnum EditorAnimation2D::GetDevice()
{
	return _mAnimation.GetDevice();
}

bool EditorAnimation2D::SetDevice(EChromaSDKDevice2DEnum device)
{
	if (_mAnimation.SetDevice(device))
	{
		Reset();
		return true;
	}
	else
	{
		return false;
	}
}

vector<FChromaSDKColorFrame2D>& EditorAnimation2D::GetFrames()
{
	return _mAnimation.GetFrames();
}

void EditorAnimation2D::Reset()
{
	EChromaSDKDevice2DEnum device = GetDevice();
	_mFrameCopy.Colors = ChromaSDKPlugin::GetInstance()->CreateColors2D(device);
}

void EditorAnimation2D::SetCopy(FChromaSDKColorFrame2D& copy)
{
	_mFrameCopy = copy;
}

FChromaSDKColorFrame2D& EditorAnimation2D::GetCopy()
{
	return _mFrameCopy;
}

void EditorAnimation2D::OverrideTime(float time)
{
	vector<FChromaSDKColorFrame2D>& frames = GetFrames();
	for (unsigned int i = 0; i < frames.size(); ++i)
	{
		FChromaSDKColorFrame2D& frame = frames[i];
		frame.Duration = time;
	}
}

float EditorAnimation2D::GetDuration(unsigned int index)
{
	vector<FChromaSDKColorFrame2D>& frames = GetFrames();
	if (index < frames.size())
	{
		FChromaSDKColorFrame2D& frame = frames[index];
		return frame.Duration;
	}
	return 0.0f;
}

void EditorAnimation2D::CopyPixels(COLORREF* pColor, const UINT width, const UINT height)
{
	//copy pixels into an array
	vector<vector<int>> rows = vector<vector<int>>();
	for (UINT i = 0; i < height; ++i)
	{
		vector<int> row = vector<int>();
		for (UINT j = 0; j < width; ++j)
		{
			int red = GetBValue(*pColor);
			int green = GetGValue(*pColor) << 8;
			int blue = GetRValue(*pColor) << 16;
			int color = red | green | blue;
			row.push_back(color);
			++pColor;
		}
		rows.push_back(row);
	}

	//clear copy
	EChromaSDKDevice2DEnum device = GetDevice();
	_mFrameCopy.Colors = ChromaSDKPlugin::GetInstance()->CreateColors2D(device);

	//scale pixels
	std::vector<FChromaSDKColors>& colors = _mFrameCopy.Colors;
	for (unsigned int i = 0; i < _mFrameCopy.Colors.size(); ++i)
	{
		int a = (int)(i / (float)_mFrameCopy.Colors.size()) * height;
		FChromaSDKColors& row = _mFrameCopy.Colors[i];
		for (unsigned int j = 0; j < row.Colors.size(); ++j)
		{
			int b = (int)(j / (float)row.Colors.size()) * width;
			row.Colors[j] = rows[a][b];
		}
	}

	vector<FChromaSDKColorFrame2D>& frames = GetFrames();
	unsigned int currentFrame = GetCurrentFrame();
	if (currentFrame < 0 ||
		currentFrame >= frames.size())
	{
		currentFrame = 0;
	}
	if (currentFrame < frames.size())
	{
		frames[currentFrame] = GetCopy();
	}
}

void EditorAnimation2D::AddFrame()
{
	unsigned int currentFrame = GetCurrentFrame();
	if (currentFrame < 0 ||
		currentFrame >= GetFrameCount())
	{
		currentFrame = 0;
	}

	vector<FChromaSDKColorFrame2D>& frames = GetFrames();
	FChromaSDKColorFrame2D frame = FChromaSDKColorFrame2D(GetDevice());
	frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors2D(GetDevice());

	if (currentFrame == GetFrameCount())
	{
		frames.push_back(frame);
		currentFrame = GetFrameCount() - 1;
	}
	else
	{
		auto it = frames.begin();
		++currentFrame;
		frames.insert(it + currentFrame, frame);
	}
	SetCurrentFrame(currentFrame);
}
