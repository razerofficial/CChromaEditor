#pragma once

namespace ChromaSDK
{
	class AnimationBase
	{
	public:
		AnimationBase();
		int GetCurrentFrame();
		void SetCurrentFrame(int index);
		virtual int GetFrameCount() = 0;
		virtual void Update() = 0;
	protected:
		int _mCurrentFrame;
	};
}
