#pragma once

#include "Animation1D.h"

namespace ChromaSDK
{
	class EditorAnimation1D
	{
	public:
		EChromaSDKDevice1DEnum GetDevice();
		bool SetDevice(EChromaSDKDevice1DEnum device);
	private:
		Animation1D _mAnimation;
	};
}
