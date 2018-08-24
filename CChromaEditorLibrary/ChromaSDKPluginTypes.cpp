#include "stdafx.h"
#include "ChromaSDKPluginTypes.h"

using namespace ChromaSDK;

FChromaSDKColors::FChromaSDKColors()
{
}
FChromaSDKColors::FChromaSDKColors(const FChromaSDKColors& copy)
{
	const std::vector<COLORREF>& colors = copy.Colors;
	int size = colors.size();
	for (int index = 0; index < size; ++index)
	{
		const COLORREF& color = colors[index];
		Colors.push_back(color);
	}
}

FChromaSDKColorFrame1D::FChromaSDKColorFrame1D()
{
	Duration = 1.0f;
}
FChromaSDKColorFrame1D::FChromaSDKColorFrame1D(const FChromaSDKColorFrame1D& copy)
{
	const std::vector<COLORREF>& colors = copy.Colors;
	int size = colors.size();
	for (int index = 0; index < size; ++index)
	{
		const COLORREF& color = colors[index];
		Colors.push_back(color);
	}
	Duration = copy.Duration;
}

FChromaSDKColorFrame2D::FChromaSDKColorFrame2D()
{
	Duration = 1.0f;
}
FChromaSDKColorFrame2D::FChromaSDKColorFrame2D(const FChromaSDKColorFrame2D& copy)
{
	const std::vector<FChromaSDKColors>& colors = copy.Colors;
	int size = colors.size();
	for (int index = 0; index < size; ++index)
	{
		const FChromaSDKColors& color = colors[index];
		Colors.push_back(color);
	}
	Duration = copy.Duration;
}
