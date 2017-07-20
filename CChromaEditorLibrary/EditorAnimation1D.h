#pragma once

#include "Animation1D.h"

namespace ChromaSDK
{
	class EditorAnimation1D
	{
	public:
		EChromaSDKDevice1DEnum GetDevice();
		void SetDevice(EChromaSDKDevice1DEnum device);
	private:
		Animation1D _mAnimation;
	};
}
