#pragma once

#include "AnimationBase.h"
#include "ChromaSDKPluginTypes.h"
#include <map>

namespace ChromaSDK
{
	class ChromaSDKPlugin
	{
	public:
		~ChromaSDKPlugin();

		static ChromaSDKPlugin* GetInstance();

		bool IsInitialized();

		// Library Methods
		int GetMaxLeds(const EChromaSDKDevice1DEnum& device);
		int GetMaxRow(const EChromaSDKDevice2DEnum& device);
		int GetMaxColumn(const EChromaSDKDevice2DEnum& device);
		std::vector<COLORREF> CreateColors1D(const EChromaSDKDevice1DEnum& device);
		std::vector<FChromaSDKColors> CreateColors2D(const EChromaSDKDevice2DEnum& device);
		std::vector<COLORREF> CreateRandomColors1D(const EChromaSDKDevice1DEnum& device);
		std::vector<FChromaSDKColors> CreateRandomColors2D(const EChromaSDKDevice2DEnum& device);
		std::vector<COLORREF> CreateRandomColorsBlackAndWhite1D(const EChromaSDKDevice1DEnum& device);
		std::vector<FChromaSDKColors> CreateRandomColorsBlackAndWhite2D(const EChromaSDKDevice2DEnum& device);
		const std::vector<FChromaSDKColors>& SetKeyboardKeyColor(const EChromaSDKKeyboardKey& key, COLORREF color, std::vector<FChromaSDKColors>& colors);
		const std::vector<FChromaSDKColors>& SetMouseLEDColor(const EChromaSDKMouseLED& led, COLORREF color, std::vector<FChromaSDKColors>& colors);
		FChromaSDKEffectResult CreateEffect(RZDEVICEID deviceId, EFFECT_TYPE effect, const std::vector<FChromaSDKColors>& colors);
		FChromaSDKEffectResult CreateEffectNone1D(const EChromaSDKDevice1DEnum& device);
		FChromaSDKEffectResult CreateEffectNone2D(const EChromaSDKDevice2DEnum& device);
		FChromaSDKEffectResult CreateEffectStatic1D(const EChromaSDKDevice1DEnum& device, COLORREF color);
		FChromaSDKEffectResult CreateEffectStatic2D(const EChromaSDKDevice2DEnum& device, COLORREF color);
		FChromaSDKEffectResult CreateEffectCustom1D(const EChromaSDKDevice1DEnum& device, const std::vector<COLORREF>& colors);
		FChromaSDKEffectResult CreateEffectCustom2D(const EChromaSDKDevice2DEnum& device, const std::vector<FChromaSDKColors>& colors, const std::vector<FChromaSDKColors>& keys);
		FChromaSDKEffectResult CreateEffectKeyboardCustom2D(const std::vector<FChromaSDKColors>& colors, const std::vector<FChromaSDKColors>& keys);
		FChromaSDKEffectResult CreateEffectKeyboardExtendedCustom2D(const std::vector<FChromaSDKColors>& colors, const std::vector<FChromaSDKColors>& keys);
		RZRESULT SetEffect(const FChromaSDKGuid& effectId);
		RZRESULT DeleteEffect(const FChromaSDKGuid& effectId);

		// editor methods
		const char* GetKeyboardChar(EChromaSDKKeyboardKey key);
		const char* GetMouseChar(EChromaSDKMouseLED led);

		AnimationBase* OpenAnimation(const std::string& path);
		AnimationBase* OpenAnimationFromMemory(const BYTE* data);

		void UseIdleAnimation(EChromaSDKDeviceEnum device, bool flag);
		void SetIdleAnimationName(const char* path);

	private:
		ChromaSDKPlugin();

		static ChromaSDKPlugin* _sInstance;

		//handle enum mapping
		std::map<EChromaSDKKeyboardKey, int> _mKeyboardEnumMap;
		std::map<EChromaSDKKeyboardKey, const char*> _mKeyboardCharMap;
		std::map<EChromaSDKMouseLED, Mouse::RZLED2> _mMouseEnumMap;
		std::map<EChromaSDKMouseLED, const char*> _mMouseCharMap;
	};
}
