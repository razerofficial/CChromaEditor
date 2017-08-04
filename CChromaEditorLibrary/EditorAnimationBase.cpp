#include "stdafx.h"
#include "EditorAnimationBase.h"

int EditorAnimationBase::GetCurrentFrame()
{
	return GetAnimation()->GetCurrentFrame();
}

void EditorAnimationBase::SetCurrentFrame(unsigned int index)
{
	GetAnimation()->SetCurrentFrame(index);
}

unsigned int EditorAnimationBase::GetFrameCount()
{
	return GetAnimation()->GetFrameCount();
}
