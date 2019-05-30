#pragma once

#include "AnimationBase.h"

class EditorAnimationBase
{
public:
	virtual ChromaSDK::AnimationBase* GetAnimation() = 0;
	int GetCurrentFrame();
	void SetCurrentFrame(unsigned int index);
	unsigned int GetFrameCount();
	virtual float GetDuration(unsigned int index) = 0;
	void ImportTextureImage();
	void ImportTextureImageSequence();
	void ImportTextureAnimation();
	void ReadImage(const std::string& texturePath, bool isAnimation);
	virtual void CopyPixels(COLORREF* pColor, UINT width, UINT height) = 0;
	virtual void AddFrame() = 0;
	void SetPath(const std::string& path);
private:
	std::string _mPath;
};
