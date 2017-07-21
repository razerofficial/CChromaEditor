#include "stdafx.h"
#include "EditorAnimationBase.h"

int EditorAnimationBase::GetCurrentFrame()
{
	return GetAnimation()->GetCurrentFrame();
}

void EditorAnimationBase::SetCurrentFrame(int index)
{
	GetAnimation()->SetCurrentFrame(index);
}

int EditorAnimationBase::GetFrameCount()
{
	return GetAnimation()->GetFrameCount();
}
