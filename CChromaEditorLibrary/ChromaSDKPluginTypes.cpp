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

FChromaSDKColorFrame2D::FChromaSDKColorFrame2D(const EChromaSDKDevice2DEnum device)
{
	Duration = 1.0f;

	switch (device)
	{
	case EChromaSDKDevice2DEnum::DE_Keyboard:
	case EChromaSDKDevice2DEnum::DE_KeyboardExtended:
		break;
	default:
		return;
	}

	Keys.clear();

	// Keyboard and KeyboardExtended use 6x22
	int maxRow = PluginGetMaxRow((int)EChromaSDKDevice2DEnum::DE_Keyboard);
	int maxColumn = PluginGetMaxColumn((int)EChromaSDKDevice2DEnum::DE_Keyboard);
	for (int i = 0; i < maxRow; ++i)
	{
		FChromaSDKColors row;
		for (int j = 0; j < maxColumn; ++j)
		{
			row.Colors.push_back(0);
		}
		Keys.push_back(row);
	}

}
FChromaSDKColorFrame2D::FChromaSDKColorFrame2D(const FChromaSDKColorFrame2D& copy)
{
	const std::vector<FChromaSDKColors>& colors = copy.Colors;
	int colorsSize = colors.size();
	for (int index = 0; index < colorsSize; ++index)
	{
		const FChromaSDKColors& color = colors[index];
		Colors.push_back(color);
	}
	
	const std::vector<FChromaSDKColors>& keys = copy.Keys;
	int maxRow = keys.size();
	Keys.clear();
	for (int i = 0; i < maxRow; ++i)
	{
		const FChromaSDKColors& sourceRow = keys[i];
		FChromaSDKColors row;
		const int maxColumn = sourceRow.Colors.size();
		for (int j = 0; j < maxColumn; ++j)
		{
			row.Colors.push_back(0);
		}
		Keys.push_back(row);
	}
	
	Duration = copy.Duration;
}
