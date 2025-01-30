﻿#include "stdafx.h"
#include "Animation1D.h"
#include "Animation2D.h"
#include "ChromaSDKPlugin.h"
#include "ChromaThread.h"
#include "RzChromaSDK.h"

#define ANIMATION_VERSION 1

using namespace ChromaSDK;
using namespace std;

int g_seed = 0;
inline int fastrand() {
	g_seed = (214013 * g_seed + 2531011);
	return (g_seed >> 16) & 0x7FFF;
}

ChromaSDKPlugin* ChromaSDKPlugin::_sInstance = nullptr;

ChromaSDKPlugin::ChromaSDKPlugin()
{
	if (RzChromaSDK::GetLibraryLoadedState() != RZRESULT_SUCCESS)
	{
		LogError(L"ChromaSDKPlugin failed to load!\r\n");
		return;
	}
	//LogDebug(L"ChromaSDKPlugin loaded.\r\n");	

	// keyboard mapping
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_ESC] = Keyboard::RZKEY::RZKEY_ESC;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F1] = Keyboard::RZKEY::RZKEY_F1;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F2] = Keyboard::RZKEY::RZKEY_F2;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F3] = Keyboard::RZKEY::RZKEY_F3;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F4] = Keyboard::RZKEY::RZKEY_F4;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F5] = Keyboard::RZKEY::RZKEY_F5;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F6] = Keyboard::RZKEY::RZKEY_F6;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F7] = Keyboard::RZKEY::RZKEY_F7;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F8] = Keyboard::RZKEY::RZKEY_F8;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F9] = Keyboard::RZKEY::RZKEY_F9;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F10] = Keyboard::RZKEY::RZKEY_F10;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F11] = Keyboard::RZKEY::RZKEY_F11;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F12] = Keyboard::RZKEY::RZKEY_F12;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_1] = Keyboard::RZKEY::RZKEY_1;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_2] = Keyboard::RZKEY::RZKEY_2;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_3] = Keyboard::RZKEY::RZKEY_3;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_4] = Keyboard::RZKEY::RZKEY_4;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_5] = Keyboard::RZKEY::RZKEY_5;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_6] = Keyboard::RZKEY::RZKEY_6;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_7] = Keyboard::RZKEY::RZKEY_7;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_8] = Keyboard::RZKEY::RZKEY_8;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_9] = Keyboard::RZKEY::RZKEY_9;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_0] = Keyboard::RZKEY::RZKEY_0;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_A] = Keyboard::RZKEY::RZKEY_A;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_B] = Keyboard::RZKEY::RZKEY_B;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_C] = Keyboard::RZKEY::RZKEY_C;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_D] = Keyboard::RZKEY::RZKEY_D;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_E] = Keyboard::RZKEY::RZKEY_E;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F] = Keyboard::RZKEY::RZKEY_F;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_G] = Keyboard::RZKEY::RZKEY_G;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_H] = Keyboard::RZKEY::RZKEY_H;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_I] = Keyboard::RZKEY::RZKEY_I;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_J] = Keyboard::RZKEY::RZKEY_J;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_K] = Keyboard::RZKEY::RZKEY_K;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_L] = Keyboard::RZKEY::RZKEY_L;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_M] = Keyboard::RZKEY::RZKEY_M;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_N] = Keyboard::RZKEY::RZKEY_N;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_O] = Keyboard::RZKEY::RZKEY_O;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_P] = Keyboard::RZKEY::RZKEY_P;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_Q] = Keyboard::RZKEY::RZKEY_Q;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_R] = Keyboard::RZKEY::RZKEY_R;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_S] = Keyboard::RZKEY::RZKEY_S;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_T] = Keyboard::RZKEY::RZKEY_T;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_U] = Keyboard::RZKEY::RZKEY_U;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_V] = Keyboard::RZKEY::RZKEY_V;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_W] = Keyboard::RZKEY::RZKEY_W;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_X] = Keyboard::RZKEY::RZKEY_X;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_Y] = Keyboard::RZKEY::RZKEY_Y;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_Z] = Keyboard::RZKEY::RZKEY_Z;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMLOCK] = Keyboard::RZKEY::RZKEY_NUMLOCK;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD0] = Keyboard::RZKEY::RZKEY_NUMPAD0;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD1] = Keyboard::RZKEY::RZKEY_NUMPAD1;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD2] = Keyboard::RZKEY::RZKEY_NUMPAD2;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD3] = Keyboard::RZKEY::RZKEY_NUMPAD3;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD4] = Keyboard::RZKEY::RZKEY_NUMPAD4;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD5] = Keyboard::RZKEY::RZKEY_NUMPAD5;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD6] = Keyboard::RZKEY::RZKEY_NUMPAD6;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD7] = Keyboard::RZKEY::RZKEY_NUMPAD7;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD8] = Keyboard::RZKEY::RZKEY_NUMPAD8;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD9] = Keyboard::RZKEY::RZKEY_NUMPAD9;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD_DIVIDE] = Keyboard::RZKEY::RZKEY_NUMPAD_DIVIDE;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD_MULTIPLY] = Keyboard::RZKEY::RZKEY_NUMPAD_MULTIPLY;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD_SUBTRACT] = Keyboard::RZKEY::RZKEY_NUMPAD_SUBTRACT;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD_ADD] = Keyboard::RZKEY::RZKEY_NUMPAD_ADD;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD_ENTER] = Keyboard::RZKEY::RZKEY_NUMPAD_ENTER;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD_DECIMAL] = Keyboard::RZKEY::RZKEY_NUMPAD_DECIMAL;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_PRINTSCREEN] = Keyboard::RZKEY::RZKEY_PRINTSCREEN;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_SCROLL] = Keyboard::RZKEY::RZKEY_SCROLL;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_PAUSE] = Keyboard::RZKEY::RZKEY_PAUSE;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_INSERT] = Keyboard::RZKEY::RZKEY_INSERT;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_HOME] = Keyboard::RZKEY::RZKEY_HOME;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_PAGEUP] = Keyboard::RZKEY::RZKEY_PAGEUP;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_DELETE] = Keyboard::RZKEY::RZKEY_DELETE;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_END] = Keyboard::RZKEY::RZKEY_END;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_PAGEDOWN] = Keyboard::RZKEY::RZKEY_PAGEDOWN;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_UP] = Keyboard::RZKEY::RZKEY_UP;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_LEFT] = Keyboard::RZKEY::RZKEY_LEFT;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_DOWN] = Keyboard::RZKEY::RZKEY_DOWN;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_RIGHT] = Keyboard::RZKEY::RZKEY_RIGHT;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_TAB] = Keyboard::RZKEY::RZKEY_TAB;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_CAPSLOCK] = Keyboard::RZKEY::RZKEY_CAPSLOCK;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_BACKSPACE] = Keyboard::RZKEY::RZKEY_BACKSPACE;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_ENTER] = Keyboard::RZKEY::RZKEY_ENTER;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_LCTRL] = Keyboard::RZKEY::RZKEY_LCTRL;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_LWIN] = Keyboard::RZKEY::RZKEY_LWIN;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_LALT] = Keyboard::RZKEY::RZKEY_LALT;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_SPACE] = Keyboard::RZKEY::RZKEY_SPACE;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_RALT] = Keyboard::RZKEY::RZKEY_RALT;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_FN] = Keyboard::RZKEY::RZKEY_FN;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_RMENU] = Keyboard::RZKEY::RZKEY_RMENU;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_RCTRL] = Keyboard::RZKEY::RZKEY_RCTRL;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_LSHIFT] = Keyboard::RZKEY::RZKEY_LSHIFT;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_RSHIFT] = Keyboard::RZKEY::RZKEY_RSHIFT;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_MACRO1] = Keyboard::RZKEY::RZKEY_MACRO1;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_MACRO2] = Keyboard::RZKEY::RZKEY_MACRO2;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_MACRO3] = Keyboard::RZKEY::RZKEY_MACRO3;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_MACRO4] = Keyboard::RZKEY::RZKEY_MACRO4;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_MACRO5] = Keyboard::RZKEY::RZKEY_MACRO5;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_1] = Keyboard::RZKEY::RZKEY_OEM_1;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_2] = Keyboard::RZKEY::RZKEY_OEM_2;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_3] = Keyboard::RZKEY::RZKEY_OEM_3;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_4] = Keyboard::RZKEY::RZKEY_OEM_4;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_5] = Keyboard::RZKEY::RZKEY_OEM_5;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_6] = Keyboard::RZKEY::RZKEY_OEM_6;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_7] = Keyboard::RZKEY::RZKEY_OEM_7;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_8] = Keyboard::RZKEY::RZKEY_OEM_8;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_9] = Keyboard::RZKEY::RZKEY_OEM_9;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_10] = Keyboard::RZKEY::RZKEY_OEM_10;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_11] = Keyboard::RZKEY::RZKEY_OEM_11;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_EUR_1] = Keyboard::RZKEY::RZKEY_EUR_1;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_EUR_2] = Keyboard::RZKEY::RZKEY_EUR_2;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_JPN_1] = Keyboard::RZKEY::RZKEY_JPN_1;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_JPN_2] = Keyboard::RZKEY::RZKEY_JPN_2;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_JPN_3] = Keyboard::RZKEY::RZKEY_JPN_3;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_JPN_4] = Keyboard::RZKEY::RZKEY_JPN_4;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_JPN_5] = Keyboard::RZKEY::RZKEY_JPN_5;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_KOR_1] = Keyboard::RZKEY::RZKEY_KOR_1;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_KOR_2] = Keyboard::RZKEY::RZKEY_KOR_2;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_KOR_3] = Keyboard::RZKEY::RZKEY_KOR_3;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_KOR_4] = Keyboard::RZKEY::RZKEY_KOR_4;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_KOR_5] = Keyboard::RZKEY::RZKEY_KOR_5;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_KOR_6] = Keyboard::RZKEY::RZKEY_KOR_6;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_KOR_7] = Keyboard::RZKEY::RZKEY_KOR_7;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_LOGO] = Keyboard::RZLED::RZLED_LOGO;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_INVALID] = Keyboard::RZKEY::RZKEY_INVALID;

	// keyboard char mapping
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_ESC] = L"Esc (VK_ESCAPE)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_F1] = L"F1 (VK_F1)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_F2] = L"F2 (VK_F2)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_F3] = L"F3 (VK_F3)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_F4] = L"F4 (VK_F4)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_F5] = L"F5 (VK_F5)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_F6] = L"F6 (VK_F6)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_F7] = L"F7 (VK_F7)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_F8] = L"F8 (VK_F8)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_F9] = L"F9 (VK_F9)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_F10] = L"F10 (VK_F10)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_F11] = L"F11 (VK_F11)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_F12] = L"F12 (VK_F12)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_1] = L"1 (VK_1)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_2] = L"2 (VK_2)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_3] = L"3 (VK_3)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_4] = L"4 (VK_4)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_5] = L"5 (VK_5)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_6] = L"6 (VK_6)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_7] = L"7 (VK_7)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_8] = L"8 (VK_8)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_9] = L"9 (VK_9)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_0] = L"0 (VK_0)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_A] = L"A (VK_A)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_B] = L"B (VK_B)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_C] = L"C (VK_C)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_D] = L"D (VK_D)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_E] = L"E (VK_E)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_F] = L"F (VK_F)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_G] = L"G (VK_G)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_H] = L"H (VK_H)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_I] = L"I (VK_I)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_J] = L"J (VK_J)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_K] = L"K (VK_K)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_L] = L"L (VK_L)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_M] = L"M (VK_M)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_N] = L"N (VK_N)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_O] = L"O (VK_O)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_P] = L"P (VK_P)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_Q] = L"Q (VK_Q)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_R] = L"R (VK_R)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_S] = L"S (VK_S)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_T] = L"T (VK_T)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_U] = L"U (VK_U)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_V] = L"V (VK_V)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_W] = L"W (VK_W)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_X] = L"X (VK_X)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_Y] = L"Y (VK_Y)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_Z] = L"Z (VK_Z)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_NUMLOCK] = L"Numlock (VK_NUMLOCK)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_NUMPAD0] = L"Numpad 0 (VK_NUMPAD0)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_NUMPAD1] = L"Numpad 1 (VK_NUMPAD1)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_NUMPAD2] = L"Numpad 2 (VK_NUMPAD2)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_NUMPAD3] = L"Numpad 3 (VK_NUMPAD3)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_NUMPAD4] = L"Numpad 4 (VK_NUMPAD4)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_NUMPAD5] = L"Numpad 5 (VK_NUMPAD5)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_NUMPAD6] = L"Numpad 6 (VK_NUMPAD6)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_NUMPAD7] = L"Numpad 7 (VK_NUMPAD7)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_NUMPAD8] = L"Numpad 8 (VK_NUMPAD8)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_NUMPAD9] = L"Numpad 9 (VK_ NUMPAD9)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_NUMPAD_DIVIDE] = L"Divide (VK_DIVIDE)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_NUMPAD_MULTIPLY] = L"Multiply (VK_MULTIPLY)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_NUMPAD_SUBTRACT] = L"Subtract (VK_SUBTRACT)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_NUMPAD_ADD] = L"Add (VK_ADD)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_NUMPAD_ENTER] = L"Enter (VK_RETURN - Extended)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_NUMPAD_DECIMAL] = L"Decimal (VK_DECIMAL)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_PRINTSCREEN] = L"Print Screen (VK_PRINT)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_SCROLL] = L"Scroll Lock (VK_SCROLL)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_PAUSE] = L"Pause (VK_PAUSE)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_INSERT] = L"Insert (VK_INSERT)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_HOME] = L"Home (VK_HOME)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_PAGEUP] = L"Page Up (VK_PRIOR)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_DELETE] = L"Delete (VK_DELETE)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_END] = L"End (VK_END)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_PAGEDOWN] = L"Page Down (VK_NEXT)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_UP] = L"Up (VK_UP)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_LEFT] = L"Left (VK_LEFT)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_DOWN] = L"Down (VK_DOWN)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_RIGHT] = L"Right (VK_RIGHT)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_TAB] = L"Tab (VK_TAB)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_CAPSLOCK] = L"Caps Lock(VK_CAPITAL)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_BACKSPACE] = L"Backspace (VK_BACK)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_ENTER] = L"Enter (VK_RETURN)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_LCTRL] = L"Left Control(VK_LCONTROL)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_LWIN] = L"Left Window (VK_LWIN)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_LALT] = L"Left Alt (VK_LMENU)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_SPACE] = L"Spacebar (VK_SPACE)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_RALT] = L"Right Alt (VK_RMENU)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_FN] = L"Function key";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_RMENU] = L"Right Menu (VK_APPS)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_RCTRL] = L"Right Control (VK_RCONTROL)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_LSHIFT] = L"Left Shift (VK_LSHIFT)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_RSHIFT] = L"Right Shift (VK_RSHIFT)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_MACRO1] = L"Macro Key 1";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_MACRO2] = L"Macro Key 2";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_MACRO3] = L"Macro Key 3";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_MACRO4] = L"Macro Key 4";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_MACRO5] = L"Macro Key 5";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_OEM_1] = L"~ (tilde)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_OEM_2] = L"-- (minus) (VK_OEM_MINUS)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_OEM_3] = L"= (equal) (VK_OEM_PLUS)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_OEM_4] = L"[ (left sqaure bracket) (VK_OEM_4)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_OEM_5] = L"] (right square bracket) (VK_OEM_6)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_OEM_6] = L"\\ (backslash) (VK_OEM_5)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_OEM_7] = L"; (semi-colon) (VK_OEM_1)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_OEM_8] = L"' (apostrophe) (VK_OEM_7)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_OEM_9] = L", (comma) (VK_OEM_COMMA)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_OEM_10] = L". (period) (VK_OEM_PERIOD)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_OEM_11] = L"/ (forward slash) (VK_OEM_2)";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_EUR_1] = L"KK_EUR_1";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_EUR_2] = L"KK_EUR_2";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_JPN_1] = L"KK_JPN_1";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_JPN_2] = L"KK_JPN_2";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_JPN_3] = L"KK_JPN_3";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_JPN_4] = L"KK_JPN_4";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_JPN_5] = L"KK_JPN_5";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_KOR_1] = L"KK_KOR_1";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_KOR_2] = L"KK_KOR_2";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_KOR_3] = L"KK_KOR_3";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_KOR_4] = L"KK_KOR_4";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_KOR_5] = L"KK_KOR_5";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_KOR_6] = L"KK_KOR_6";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_KOR_7] = L"KK_KOR_7";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_LOGO] = L"Razer logo";
	_mKeyboardCharMap[EChromaSDKKeyboardKey::KK_INVALID] = L"Invalid keys.";

	// mouse mapping
	_mMouseEnumMap[EChromaSDKMouseLED::ML_SCROLLWHEEL] = Mouse::RZLED2::RZLED2_SCROLLWHEEL;
	_mMouseEnumMap[EChromaSDKMouseLED::ML_LOGO] = Mouse::RZLED2::RZLED2_LOGO;
	_mMouseEnumMap[EChromaSDKMouseLED::ML_BACKLIGHT] = Mouse::RZLED2::RZLED2_BACKLIGHT;
	_mMouseEnumMap[EChromaSDKMouseLED::ML_LEFT_SIDE1] = Mouse::RZLED2::RZLED2_LEFT_SIDE1;
	_mMouseEnumMap[EChromaSDKMouseLED::ML_LEFT_SIDE2] = Mouse::RZLED2::RZLED2_LEFT_SIDE2;
	_mMouseEnumMap[EChromaSDKMouseLED::ML_LEFT_SIDE3] = Mouse::RZLED2::RZLED2_LEFT_SIDE3;
	_mMouseEnumMap[EChromaSDKMouseLED::ML_LEFT_SIDE4] = Mouse::RZLED2::RZLED2_LEFT_SIDE4;
	_mMouseEnumMap[EChromaSDKMouseLED::ML_LEFT_SIDE5] = Mouse::RZLED2::RZLED2_LEFT_SIDE5;
	_mMouseEnumMap[EChromaSDKMouseLED::ML_LEFT_SIDE6] = Mouse::RZLED2::RZLED2_LEFT_SIDE6;
	_mMouseEnumMap[EChromaSDKMouseLED::ML_LEFT_SIDE7] = Mouse::RZLED2::RZLED2_LEFT_SIDE7;
	_mMouseEnumMap[EChromaSDKMouseLED::ML_BOTTOM1] = Mouse::RZLED2::RZLED2_BOTTOM1;
	_mMouseEnumMap[EChromaSDKMouseLED::ML_BOTTOM2] = Mouse::RZLED2::RZLED2_BOTTOM2;
	_mMouseEnumMap[EChromaSDKMouseLED::ML_BOTTOM3] = Mouse::RZLED2::RZLED2_BOTTOM3;
	_mMouseEnumMap[EChromaSDKMouseLED::ML_BOTTOM4] = Mouse::RZLED2::RZLED2_BOTTOM4;
	_mMouseEnumMap[EChromaSDKMouseLED::ML_BOTTOM5] = Mouse::RZLED2::RZLED2_BOTTOM5;
	_mMouseEnumMap[EChromaSDKMouseLED::ML_RIGHT_SIDE1] = Mouse::RZLED2::RZLED2_RIGHT_SIDE1;
	_mMouseEnumMap[EChromaSDKMouseLED::ML_RIGHT_SIDE2] = Mouse::RZLED2::RZLED2_RIGHT_SIDE2;
	_mMouseEnumMap[EChromaSDKMouseLED::ML_RIGHT_SIDE3] = Mouse::RZLED2::RZLED2_RIGHT_SIDE3;
	_mMouseEnumMap[EChromaSDKMouseLED::ML_RIGHT_SIDE4] = Mouse::RZLED2::RZLED2_RIGHT_SIDE4;
	_mMouseEnumMap[EChromaSDKMouseLED::ML_RIGHT_SIDE5] = Mouse::RZLED2::RZLED2_RIGHT_SIDE5;
	_mMouseEnumMap[EChromaSDKMouseLED::ML_RIGHT_SIDE6] = Mouse::RZLED2::RZLED2_RIGHT_SIDE6;
	_mMouseEnumMap[EChromaSDKMouseLED::ML_RIGHT_SIDE7] = Mouse::RZLED2::RZLED2_RIGHT_SIDE7;

	// mouse char mapping
	_mMouseCharMap[EChromaSDKMouseLED::ML_SCROLLWHEEL] = L"Scroll Wheel LED";
	_mMouseCharMap[EChromaSDKMouseLED::ML_LOGO] = L"Logo LED";
	_mMouseCharMap[EChromaSDKMouseLED::ML_BACKLIGHT] = L"Backlight LED";
	_mMouseCharMap[EChromaSDKMouseLED::ML_LEFT_SIDE1] = L"Left LED 1";
	_mMouseCharMap[EChromaSDKMouseLED::ML_LEFT_SIDE2] = L"Left LED 2";
	_mMouseCharMap[EChromaSDKMouseLED::ML_LEFT_SIDE3] = L"Left LED 3";
	_mMouseCharMap[EChromaSDKMouseLED::ML_LEFT_SIDE4] = L"Left LED 4";
	_mMouseCharMap[EChromaSDKMouseLED::ML_LEFT_SIDE5] = L"Left LED 5";
	_mMouseCharMap[EChromaSDKMouseLED::ML_LEFT_SIDE6] = L"Left LED 6";
	_mMouseCharMap[EChromaSDKMouseLED::ML_LEFT_SIDE7] = L"Left LED 7";
	_mMouseCharMap[EChromaSDKMouseLED::ML_BOTTOM1] = L"Bottom LED 1";
	_mMouseCharMap[EChromaSDKMouseLED::ML_BOTTOM2] = L"Bottom LED 2";
	_mMouseCharMap[EChromaSDKMouseLED::ML_BOTTOM3] = L"Bottom LED 3";
	_mMouseCharMap[EChromaSDKMouseLED::ML_BOTTOM4] = L"Bottom LED 4";
	_mMouseCharMap[EChromaSDKMouseLED::ML_BOTTOM5] = L"Bottom LED 5";
	_mMouseCharMap[EChromaSDKMouseLED::ML_RIGHT_SIDE1] = L"Right LED 1";
	_mMouseCharMap[EChromaSDKMouseLED::ML_RIGHT_SIDE2] = L"Right LED 2";
	_mMouseCharMap[EChromaSDKMouseLED::ML_RIGHT_SIDE3] = L"Right LED 3";
	_mMouseCharMap[EChromaSDKMouseLED::ML_RIGHT_SIDE4] = L"Right LED 4";
	_mMouseCharMap[EChromaSDKMouseLED::ML_RIGHT_SIDE5] = L"Right LED 5";
	_mMouseCharMap[EChromaSDKMouseLED::ML_RIGHT_SIDE6] = L"Right LED 6";
	_mMouseCharMap[EChromaSDKMouseLED::ML_RIGHT_SIDE7] = L"Right LED 7";
}

ChromaSDKPlugin::~ChromaSDKPlugin()
{
	RzChromaSDK::UnInit();
}

ChromaSDKPlugin* ChromaSDKPlugin::GetInstance()
{
	if (_sInstance == nullptr)
	{
		_sInstance = new ChromaSDKPlugin();
	}
	return _sInstance;
}

bool ChromaSDKPlugin::IsInitialized()
{
	return RzChromaSDK::GetLibraryLoadedState() == RZRESULT_SUCCESS;
}

int ChromaSDKPlugin::GetMaxLeds(const EChromaSDKDevice1DEnum& device)
{
	switch (device)
	{
	case EChromaSDKDevice1DEnum::DE_ChromaLink:
		return ChromaLink::MAX_LEDS;
	case EChromaSDKDevice1DEnum::DE_Headset:
		return Headset::MAX_LEDS;
	case EChromaSDKDevice1DEnum::DE_Mousepad:
		return Mousepad::MAX_LEDS;
	}
	return 0;
}

int ChromaSDKPlugin::GetMaxRow(const EChromaSDKDevice2DEnum& device)
{
	switch (device)
	{
	case EChromaSDKDevice2DEnum::DE_Keyboard:
		return Keyboard::MAX_ROW;
	case EChromaSDKDevice2DEnum::DE_KeyboardExtended:
		return Keyboard::v2::MAX_ROW;
	case EChromaSDKDevice2DEnum::DE_Keypad:
		return Keypad::MAX_ROW;
	case EChromaSDKDevice2DEnum::DE_Mouse:
		return Mouse::MAX_ROW;
	}
	return 0;
}

int ChromaSDKPlugin::GetMaxColumn(const EChromaSDKDevice2DEnum& device)
{
	switch (device)
	{
	case EChromaSDKDevice2DEnum::DE_Keyboard:
		return Keyboard::MAX_COLUMN;
	case EChromaSDKDevice2DEnum::DE_KeyboardExtended:
		return Keyboard::v2::MAX_COLUMN;
	case EChromaSDKDevice2DEnum::DE_Keypad:
		return Keypad::MAX_COLUMN;
	case EChromaSDKDevice2DEnum::DE_Mouse:
		return Mouse::MAX_COLUMN;
	}
	return 0;
}

vector<COLORREF> ChromaSDKPlugin::CreateColors1D(const EChromaSDKDevice1DEnum& device)
{
	vector<COLORREF> colors = vector<COLORREF>();
	int elements = GetMaxLeds(device);
	COLORREF black = RGB(0, 0, 0);
	for (int i = 0; i < elements; ++i)
	{
		colors.push_back(black);
	}
	return colors;
}

vector<FChromaSDKColors> ChromaSDKPlugin::CreateColors2D(const EChromaSDKDevice2DEnum& device)
{
	vector<FChromaSDKColors> result = vector<FChromaSDKColors>();
	int maxRow = GetMaxRow(device);
	int maxColumn = GetMaxColumn(device);
	COLORREF black = RGB(0, 0, 0);
	for (int i = 0; i < maxRow; ++i)
	{
		FChromaSDKColors row = FChromaSDKColors();
		for (int j = 0; j < maxColumn; ++j)
		{
			row.Colors.push_back(black);
		}
		result.push_back(row);
	}
	return result;
}

vector<COLORREF> ChromaSDKPlugin::CreateRandomColors1D(const EChromaSDKDevice1DEnum& device)
{
	vector<COLORREF> colors = vector<COLORREF>();
	int elements = GetMaxLeds(device);
	for (int i = 0; i < elements; ++i)
	{
		int red = fastrand() % 256;
		int green = fastrand() % 256;
		int blue = fastrand() % 256;
		COLORREF color = RGB(red, green, blue);
		colors.push_back(color);
	}
	return colors;
}

vector<FChromaSDKColors> ChromaSDKPlugin::CreateRandomColors2D(const EChromaSDKDevice2DEnum& device)
{
	vector<FChromaSDKColors> result = vector<FChromaSDKColors>();
	int maxRows = GetMaxRow(device);
	int maxColumns = GetMaxColumn(device);
	for (int i = 0; i < maxRows; ++i)
	{
		FChromaSDKColors row = FChromaSDKColors();
		for (int j = 0; j < maxColumns; ++j)
		{
			int red = fastrand() % 256;
			int green = fastrand() % 256;
			int blue = fastrand() % 256;
			COLORREF color = RGB(red, green, blue);
			row.Colors.push_back(color);
		}
		result.push_back(row);
	}
	return result;
}

vector<COLORREF> ChromaSDKPlugin::CreateRandomColorsBlackAndWhite1D(const EChromaSDKDevice1DEnum& device)
{
	vector<COLORREF> colors = vector<COLORREF>();
	int elements = GetMaxLeds(device);
	for (int i = 0; i < elements; ++i)
	{
		int gray = fastrand() % 256;
		COLORREF color = RGB(gray, gray, gray);
		colors.push_back(color);
	}
	return colors;
}

vector<FChromaSDKColors> ChromaSDKPlugin::CreateRandomColorsBlackAndWhite2D(const EChromaSDKDevice2DEnum& device)
{
	vector<FChromaSDKColors> result = vector<FChromaSDKColors>();
	int maxRows = GetMaxRow(device);
	int maxColumns = GetMaxColumn(device);
	for (int i = 0; i < maxRows; ++i)
	{
		FChromaSDKColors row = FChromaSDKColors();
		for (int j = 0; j < maxColumns; ++j)
		{
			int gray = fastrand() % 256;
			COLORREF color = RGB(gray, gray, gray);
			row.Colors.push_back(color);
		}
		result.push_back(row);
	}
	return result;
}

const vector<FChromaSDKColors>& ChromaSDKPlugin::SetKeyboardKeyColor(const EChromaSDKKeyboardKey& key, COLORREF color, vector<FChromaSDKColors>& colors)
{
	int maxRow = Keyboard::MAX_ROW;
	int maxColumn = Keyboard::MAX_COLUMN;
	if (maxRow != colors.size() ||
		colors.size() == 0 ||
		maxColumn != colors[0].Colors.size())
	{
		LogError(L"ChromaSDKPlugin::SetKeyboardKeyColor Array size mismatch row: %d==%d column: %d==%d!\r\n",
			maxRow,
			colors.size(),
			maxColumn,
			colors.size() > 0 ? colors[0].Colors.size() : 0);
		return colors;
	}

	int rzkey = _mKeyboardEnumMap[key];
	if (rzkey != Keyboard::RZKEY::RZKEY_INVALID)
	{
		colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] = color;
	}
	return colors;
}

const vector<FChromaSDKColors>& ChromaSDKPlugin::SetMouseLEDColor(const EChromaSDKMouseLED& led, COLORREF color, vector<FChromaSDKColors>& colors)
{
	int maxRow = Mouse::MAX_ROW;
	int maxColumn = Mouse::MAX_COLUMN;
	if (maxRow != colors.size() ||
		colors.size() == 0 ||
		maxColumn != colors[0].Colors.size())
	{
		LogError(L"ChromaSDKPlugin::SetMouseLedColor Array size mismatch row: %d==%d column: %d==%d!\r\n",
			maxRow,
			colors.size(),
			maxColumn,
			colors.size() > 0 ? colors[0].Colors.size() : 0);
		return colors;
	}

	Mouse::RZLED2 rzled = _mMouseEnumMap[led];
	colors[HIBYTE(rzled)].Colors[LOBYTE(rzled)] = color;
	return colors;
}

FChromaSDKEffectResult ChromaSDKPlugin::CreateEffect(RZDEVICEID deviceId, EFFECT_TYPE effect, const vector<FChromaSDKColors>& colors)
{
	//LogDebug(L"ChromaSDKPlugin::CreateEffect Invoke.\r\n");

	FChromaSDKEffectResult data = FChromaSDKEffectResult();

	CUSTOM_EFFECT_TYPE pParam = {};
	for (int i = 0; i < MAX_ROW; i++)
	{
		const FChromaSDKColors& row = colors[i];
		for (int j = 0; j < MAX_COLUMN; ++j)
		{
			pParam.Color[i][j] = row.Colors[j];
		}
	}

	RZRESULT result = 0;
	RZEFFECTID effectId = RZEFFECTID();
	result = RzChromaSDK::CreateEffect(deviceId, EFFECT_TYPE::CHROMA_CUSTOM, &pParam, &effectId);
	data.EffectId.Data = effectId;
	data.Result = result;

	if (data.Result != 0)
	{
		LogDebug(L"ChromaSDKPlugin::CreateEffect Result=%d.\r\n", data.Result);
	}

	return data;
}

FChromaSDKEffectResult ChromaSDKPlugin::CreateEffectNone1D(const EChromaSDKDevice1DEnum& device)
{
	//LogDebug(L"ChromaSDKPlugin::CreateEffectNone1D Invoke.\r\n");

	FChromaSDKEffectResult data = FChromaSDKEffectResult();

	RZRESULT result = 0;
	RZEFFECTID effectId = RZEFFECTID();
	switch (device)
	{
	case EChromaSDKDevice1DEnum::DE_ChromaLink:
		result = RzChromaSDK::CreateChromaLinkEffect(ChromaLink::CHROMA_NONE, NULL, &effectId);
		break;
	case EChromaSDKDevice1DEnum::DE_Headset:
		result = RzChromaSDK::CreateHeadsetEffect(Headset::CHROMA_NONE, NULL, &effectId);
		break;
	case EChromaSDKDevice1DEnum::DE_Mousepad:
		result = RzChromaSDK::CreateMousepadEffect(Mousepad::CHROMA_NONE, NULL, &effectId);
		break;
	default:
		LogError(L"ChromaSDKPlugin::CreateEffectNone1D Unsupported device used!\r\n");
		break;
	}
	data.EffectId.Data = effectId;
	data.Result = result;

	if (data.Result != 0)
	{
		LogDebug(L"ChromaSDKPlugin::CreateEffectNone1D Result=%d.\r\n", data.Result);
	}

	return data;
}

FChromaSDKEffectResult ChromaSDKPlugin::CreateEffectNone2D(const EChromaSDKDevice2DEnum& device)
{
	//LogDebug(L"ChromaSDKPlugin::CreateEffectNone2D Invoke.\r\n");

	FChromaSDKEffectResult data = FChromaSDKEffectResult();

	int result = 0;
	RZEFFECTID effectId = RZEFFECTID();
	switch (device)
	{
	case EChromaSDKDevice2DEnum::DE_Keyboard:
	case EChromaSDKDevice2DEnum::DE_KeyboardExtended:
		result = RzChromaSDK::CreateKeyboardEffect(Keyboard::CHROMA_NONE, NULL, &effectId);
		break;
	case EChromaSDKDevice2DEnum::DE_Keypad:
		result = RzChromaSDK::CreateKeypadEffect(Keypad::CHROMA_NONE, NULL, &effectId);
		break;
	case EChromaSDKDevice2DEnum::DE_Mouse:
		result = RzChromaSDK::CreateMouseEffect(Mouse::CHROMA_NONE, NULL, &effectId);
		break;
	default:
		LogError(L"ChromaSDKPlugin::CreateEffectNone2D Unsupported device used!\r\n");
		break;
	}
	data.EffectId.Data = effectId;
	data.Result = result;

	if (data.Result != 0)
	{
		LogDebug(L"ChromaSDKPlugin::CreateEffectNone2D Result=%d.\r\n", data.Result);
	}

	return data;
}

FChromaSDKEffectResult ChromaSDKPlugin::CreateEffectStatic1D(const EChromaSDKDevice1DEnum& device, COLORREF color)
{
	FChromaSDKEffectResult data = FChromaSDKEffectResult();

	RZRESULT result = 0;
	RZEFFECTID effectId = RZEFFECTID();
	switch (device)
	{
	case EChromaSDKDevice1DEnum::DE_ChromaLink:
	{
		ChromaLink::STATIC_EFFECT_TYPE pParam = {};
		pParam.Color = color;
		result = RzChromaSDK::CreateChromaLinkEffect(ChromaLink::CHROMA_STATIC, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice1DEnum::DE_Headset:
	{
		Headset::STATIC_EFFECT_TYPE pParam = {};
		pParam.Color = color;
		result = RzChromaSDK::CreateHeadsetEffect(Headset::CHROMA_STATIC, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice1DEnum::DE_Mousepad:
	{
		Mousepad::STATIC_EFFECT_TYPE pParam = {};
		pParam.Color = color;
		result = RzChromaSDK::CreateMousepadEffect(Mousepad::CHROMA_STATIC, &pParam, &effectId);
	}
	break;
	default:
		LogError(L"ChromaSDKPlugin::CreateEffectStatic1D Unsupported device used!\r\n");
		break;
	}
	data.EffectId.Data = effectId;
	data.Result = result;

	return data;
}

FChromaSDKEffectResult ChromaSDKPlugin::CreateEffectStatic2D(const EChromaSDKDevice2DEnum& device, COLORREF color)
{
	FChromaSDKEffectResult data = FChromaSDKEffectResult();

	RZRESULT result = 0;
	RZEFFECTID effectId = RZEFFECTID();
	switch (device)
	{
	case EChromaSDKDevice2DEnum::DE_Keyboard:
	case EChromaSDKDevice2DEnum::DE_KeyboardExtended:
	{
		Keyboard::STATIC_EFFECT_TYPE pParam = {};
		pParam.Color = color;
		result = RzChromaSDK::CreateKeyboardEffect(Keyboard::CHROMA_STATIC, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice2DEnum::DE_Keypad:
	{
		Keypad::STATIC_EFFECT_TYPE pParam = {};
		pParam.Color = color;
		result = RzChromaSDK::CreateKeypadEffect(Keypad::CHROMA_STATIC, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice2DEnum::DE_Mouse:
	{
		Mouse::STATIC_EFFECT_TYPE pParam = {};
		pParam.Color = color;
		pParam.LEDId = Mouse::RZLED_ALL;
		result = RzChromaSDK::CreateMouseEffect(Mouse::CHROMA_STATIC, &pParam, &effectId);
	}
	break;
	default:
		LogError(L"ChromaSDKPlugin::CreateEffectStatic2D Unsupported device used!\r\n");
		break;
	}
	data.EffectId.Data = effectId;
	data.Result = result;

	return data;
}

FChromaSDKEffectResult ChromaSDKPlugin::CreateEffectCustom1D(const EChromaSDKDevice1DEnum& device, const vector<COLORREF>& colors)
{
	FChromaSDKEffectResult data = FChromaSDKEffectResult();

	RZRESULT result = 0;
	RZEFFECTID effectId = RZEFFECTID();
	int maxLeds = 0;
	switch (device)
	{
	case EChromaSDKDevice1DEnum::DE_ChromaLink:
	{
		maxLeds = ChromaLink::MAX_LEDS;
		if (maxLeds != colors.size())
		{
			LogError(L"ChromaSDKPlugin::CreateEffectCustom1D Array size mismatch elements: %d==%d!\r\n",
				maxLeds,
				colors.size());
			break;
		}
		ChromaLink::CUSTOM_EFFECT_TYPE pParam = {};
		for (int i = 0; i < maxLeds; i++)
		{
			pParam.Color[i] = colors[i];
		}
		result = RzChromaSDK::CreateChromaLinkEffect(ChromaLink::CHROMA_CUSTOM, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice1DEnum::DE_Headset:
	{
		maxLeds = Headset::MAX_LEDS;
		if (maxLeds != colors.size())
		{
			LogError(L"ChromaSDKPlugin::CreateEffectCustom1D Array size mismatch elements: %d==%d!\r\n",
				maxLeds,
				colors.size());
			break;
		}
		Headset::CUSTOM_EFFECT_TYPE pParam = {};
		for (int i = 0; i < maxLeds; i++)
		{
			pParam.Color[i] = colors[i];
		}
		result = RzChromaSDK::CreateHeadsetEffect(Headset::CHROMA_CUSTOM, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice1DEnum::DE_Mousepad:
	{
		maxLeds = Mousepad::MAX_LEDS;
		if (maxLeds != colors.size())
		{
			LogError(L"ChromaSDKPlugin::CreateEffectCustom1D Array size mismatch elements: %d==%d!\r\n",
				maxLeds,
				colors.size());
			break;
		}
		Mousepad::CUSTOM_EFFECT_TYPE pParam = {};
		for (int i = 0; i < maxLeds; i++)
		{
			pParam.Color[i] = colors[i];
		}
		result = RzChromaSDK::CreateMousepadEffect(Mousepad::CHROMA_CUSTOM, &pParam, &effectId);
	}
	break;
	default:
		LogError(L"ChromaSDKPlugin::CreateEffectCustom1D Unsupported device used!\r\n");
		break;
	}
	data.EffectId.Data = effectId;
	data.Result = result;

	return data;
}

FChromaSDKEffectResult ChromaSDKPlugin::CreateEffectCustom2D(const EChromaSDKDevice2DEnum& device, const vector<FChromaSDKColors>& colors, const vector<FChromaSDKColors>& keys)
{
	FChromaSDKEffectResult data = FChromaSDKEffectResult();

	RZRESULT result = 0;
	RZEFFECTID effectId = RZEFFECTID();
	int maxRow = 0;
	int maxColumn = 0;
	switch (device)
	{
	case EChromaSDKDevice2DEnum::DE_Keyboard:
	{
		maxRow = GetMaxRow(device);
		maxColumn = GetMaxColumn(device);
		if (maxRow != colors.size() ||
			(colors.size() > 0 &&
				maxColumn != colors[0].Colors.size()))
		{
			LogError(L"ChromaSDKPlugin::CreateEffectCustom2D Colors Array size mismatch row: %d==%d column: %d==%d!\r\n",
				maxRow,
				colors.size(),
				maxColumn,
				colors.size() > 0 ? colors[0].Colors.size() : 0);
			break;
		}
		Keyboard::CUSTOM_EFFECT_TYPE pParam = {};
		for (int i = 0; i < maxRow; i++)
		{
			const FChromaSDKColors& row = colors[i];
			for (int j = 0; j < maxColumn; j++)
			{
				pParam.Color[i][j] = row.Colors[j];
			}
		}
		result = RzChromaSDK::CreateKeyboardEffect(Keyboard::CHROMA_CUSTOM, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice2DEnum::DE_KeyboardExtended:
	{
		maxRow = GetMaxRow(device);
		maxColumn = GetMaxColumn(device);
		if (maxRow != colors.size() ||
			(colors.size() > 0 &&
				maxColumn != colors[0].Colors.size()))
		{
			LogError(L"ChromaSDKPlugin::CreateEffectCustom2D Colors Array size mismatch row: %d==%d column: %d==%d!\r\n",
				maxRow,
				colors.size(),
				maxColumn,
				colors.size() > 0 ? colors[0].Colors.size() : 0);
			break;
		}
		Keyboard::v2::CUSTOM_EFFECT_TYPE pParam = {};
		for (int i = 0; i < maxRow; i++)
		{
			const FChromaSDKColors& row = colors[i];
			for (int j = 0; j < maxColumn; j++)
			{
				pParam.Color[i][j] = row.Colors[j];
			}
		}
		// Keyboard and KeyboardExtended use 6x22
		maxRow = GetMaxRow(EChromaSDKDevice2DEnum::DE_Keyboard);
		maxColumn = GetMaxColumn(EChromaSDKDevice2DEnum::DE_Keyboard);
		if (maxRow != keys.size() ||
			(keys.size() > 0 &&
				maxColumn != keys[0].Colors.size()))
		{
			LogError(L"ChromaSDKPlugin::CreateEffectCustom2D Keys Array size mismatch row: %d==%d column: %d==%d!\r\n",
				maxRow,
				keys.size(),
				maxColumn,
				keys.size() > 0 ? colors[0].Colors.size() : 0);
			break;
		}
		for (int i = 0; i < maxRow; i++)
		{
			const FChromaSDKColors& row = keys[i];
			for (int j = 0; j < maxColumn; j++)
			{
				pParam.Key[i][j] = row.Colors[j];
			}
		}
		result = RzChromaSDK::CreateKeyboardEffect(Keyboard::CHROMA_CUSTOM2, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice2DEnum::DE_Keypad:
	{
		maxRow = Keypad::MAX_ROW;
		maxColumn = Keypad::MAX_COLUMN;
		if (maxRow != colors.size() ||
			(colors.size() > 0 &&
				maxColumn != colors[0].Colors.size()))
		{
			LogError(L"ChromaSDKPlugin::CreateEffectCustom2D Array size mismatch row: %d==%d column: %d==%d!\r\n",
				maxRow,
				colors.size(),
				maxColumn,
				colors.size() > 0 ? colors[0].Colors.size() : 0);
			break;
		}
		Keypad::CUSTOM_EFFECT_TYPE pParam = {};
		for (int i = 0; i < maxRow; i++)
		{
			const FChromaSDKColors& row = colors[i];
			for (int j = 0; j < maxColumn; j++)
			{
				pParam.Color[i][j] = row.Colors[j];
			}
		}
		result = RzChromaSDK::CreateKeypadEffect(Keypad::CHROMA_CUSTOM, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice2DEnum::DE_Mouse:
	{
		maxRow = Mouse::MAX_ROW;
		maxColumn = Mouse::MAX_COLUMN;
		if (maxRow != colors.size() ||
			(colors.size() > 0 &&
				maxColumn != colors[0].Colors.size()))
		{
			LogError(L"ChromaSDKPlugin::CreateEffectCustom2D Array size mismatch row: %d==%d column: %d==%d!\r\n",
				maxRow,
				colors.size(),
				maxColumn,
				colors.size() > 0 ? colors[0].Colors.size() : 0);
			break;
		}
		Mouse::CUSTOM_EFFECT_TYPE2 pParam = {};
		for (int i = 0; i < maxRow; i++)
		{
			const FChromaSDKColors& row = colors[i];
			for (int j = 0; j < maxColumn; j++)
			{
				pParam.Color[i][j] = row.Colors[j];
			}
		}
		result = RzChromaSDK::CreateMouseEffect(Mouse::CHROMA_CUSTOM2, &pParam, &effectId);
	}
	break;
	default:
		LogError(L"ChromaSDKPlugin::CreateEffectCustom2D Unsupported device used!\r\n");
		break;
	}
	data.EffectId.Data = effectId;
	data.Result = result;

	return data;
}

FChromaSDKEffectResult ChromaSDKPlugin::CreateEffectKeyboardCustom2D(const vector<FChromaSDKColors>& colors, const vector<FChromaSDKColors>& keys)
{
	FChromaSDKEffectResult data = FChromaSDKEffectResult();

	RZRESULT result = 0;
	RZEFFECTID effectId = RZEFFECTID();
	int maxRow = GetMaxRow(EChromaSDKDevice2DEnum::DE_Keyboard);
	int maxColumn = GetMaxColumn(EChromaSDKDevice2DEnum::DE_Keyboard);

	if (maxRow != colors.size() ||
		(colors.size() > 0 &&
			maxColumn != colors[0].Colors.size()))
	{
		LogError(L"ChromaSDKPlugin::CreateEffectKeyboardCustom2D Colors Array size mismatch row: %d==%d column: %d==%d!\r\n",
			maxRow,
			colors.size(),
			maxColumn,
			colors.size() > 0 ? colors[0].Colors.size() : 0);
	}
	else
	{
		Keyboard::CUSTOM_KEY_EFFECT_TYPE pParam = {};

		for (int i = 0; i < maxRow; i++)
		{
			const FChromaSDKColors& row = colors[i];
			for (int j = 0; j < maxColumn; j++)
			{
				pParam.Color[i][j] = row.Colors[j];
			}
		}


		if (maxRow != keys.size() ||
			(keys.size() > 0 &&
				maxColumn != colors[0].Colors.size()))
		{
			LogError(L"ChromaSDKPlugin::CreateEffectKeyboardCustom2D Keys Array size mismatch row: %d==%d column: %d==%d!\r\n",
				maxRow,
				keys.size(),
				maxColumn,
				keys.size() > 0 ? keys[0].Colors.size() : 0);
		}
		else
		{
			for (int i = 0; i < maxRow; i++)
			{
				const FChromaSDKColors& row = keys[i];
				for (int j = 0; j < maxColumn; j++)
				{
					pParam.Key[i][j] = row.Colors[j];
				}
			}
		}

		result = RzChromaSDK::CreateKeyboardEffect(Keyboard::CHROMA_CUSTOM_KEY, &pParam, &effectId);
	}

	data.EffectId.Data = effectId;
	data.Result = result;

	return data;
}

FChromaSDKEffectResult ChromaSDKPlugin::CreateEffectKeyboardExtendedCustom2D(const vector<FChromaSDKColors>& colors, const vector<FChromaSDKColors>& keys)
{
	FChromaSDKEffectResult data = FChromaSDKEffectResult();

	RZRESULT result = 0;
	RZEFFECTID effectId = RZEFFECTID();
	int maxRow = GetMaxRow(EChromaSDKDevice2DEnum::DE_KeyboardExtended);
	int maxColumn = GetMaxColumn(EChromaSDKDevice2DEnum::DE_KeyboardExtended);

	if (maxRow != colors.size() ||
		(colors.size() > 0 &&
			maxColumn != colors[0].Colors.size()))
	{
		LogError(L"ChromaSDKPlugin::CreateEffectKeyboardExtendedCustom2D Colors Array size mismatch row: %d==%d column: %d==%d!\r\n",
			maxRow,
			colors.size(),
			maxColumn,
			colors.size() > 0 ? colors[0].Colors.size() : 0);
	}
	else
	{
		Keyboard::v2::CUSTOM_EFFECT_TYPE pParam = {};

		for (int i = 0; i < maxRow; i++)
		{
			const FChromaSDKColors& row = colors[i];
			for (int j = 0; j < maxColumn; j++)
			{
				pParam.Color[i][j] = row.Colors[j];
			}
		}

		// Keyboard and KeyboardExtended use 6x22

		maxRow = GetMaxRow(EChromaSDKDevice2DEnum::DE_Keyboard);
		maxColumn = GetMaxColumn(EChromaSDKDevice2DEnum::DE_Keyboard);

		if (maxRow != keys.size() ||
			(keys.size() > 0 &&
				maxColumn != keys[0].Colors.size()))
		{
			LogError(L"ChromaSDKPlugin::CreateEffectKeyboardExtendedCustom2D Keys Array size mismatch row: %d==%d column: %d==%d!\r\n",
				maxRow,
				keys.size(),
				maxColumn,
				keys.size() > 0 ? keys[0].Colors.size() : 0);
		}
		else
		{
			for (int i = 0; i < maxRow; i++)
			{
				const FChromaSDKColors& row = keys[i];
				for (int j = 0; j < maxColumn; j++)
				{
					pParam.Key[i][j] = row.Colors[j];
				}
			}
		}

		result = RzChromaSDK::CreateKeyboardEffect(Keyboard::CHROMA_CUSTOM2, &pParam, &effectId);
	}

	data.EffectId.Data = effectId;
	data.Result = result;

	return data;
}

RZRESULT ChromaSDKPlugin::SetEffect(const FChromaSDKGuid& effectId)
{
	//LogDebug(L"ChromaSDKPlugin::SetEffect Invoke.\r\n");
	RZRESULT result = RzChromaSDK::SetEffect(effectId.Data);
	if (result != 0)
	{
		LogError(L"ChromaSDKPlugin::SetEffect Result=%d.\r\n", result);
	}
	return result;
}

RZRESULT ChromaSDKPlugin::DeleteEffect(const FChromaSDKGuid& effectId)
{
	//LogDebug(L"ChromaSDKPlugin::DeleteEffect Invoke.\r\n");
	RZRESULT result = RzChromaSDK::DeleteEffect(effectId.Data);
	if (result != 0)
	{
		LogError(L"ChromaSDKPlugin::DeleteEffect Result=%d.\r\n", result);
	}
	return result;
}

const wchar_t* ChromaSDKPlugin::GetKeyboardChar(EChromaSDKKeyboardKey key)
{
	return _mKeyboardCharMap[key];
}

const wchar_t* ChromaSDKPlugin::GetMouseChar(EChromaSDKMouseLED led)
{
	return _mMouseCharMap[led];
}

AnimationBase* ChromaSDKPlugin::OpenAnimation(const wstring& path)
{
	AnimationBase* animation = nullptr;

	//LogDebug(L"OpenAnimation: %s\r\n", path.c_str());
	FILE* stream = nullptr;
	if (0 != _wfopen_s(&stream, path.c_str(), L"rb") ||
		stream == nullptr)
	{
		LogError(L"OpenAnimation: Failed to open animation! %s\r\n", path.c_str());
	}
	else
	{
		fseek(stream, 0, SEEK_END);
		const int size = ftell(stream);
		if (size <= 0)
		{
			LogError(L"OpenAnimation: Failed to open empty animation! %s\r\n", path.c_str());
		}
		else
		{
			BYTE* data = new BYTE[size];
			fseek(stream, 0, SEEK_SET);
			fread(data, size, 1, stream);
			animation = OpenAnimationFromMemory(data);
			delete[] data;
			std::fclose(stream);
		}

		//LogDebug(L"OpenAnimation: Loaded %s\r\n", path.c_str());
	}

	return animation;
}

AnimationBase* ChromaSDKPlugin::OpenAnimationFromMemory(const BYTE* data)
{
	const BYTE* pointer = data;
	AnimationBase* animation = nullptr;

	if (0 == data)
	{
		LogError(L"OpenAnimationFromMemory: Failed to open animation!\r\n");
		return nullptr;
	}

	long read = 0;
	long expectedRead = 1;
	long expectedSize = sizeof(BYTE);

	//version
	int version = 0;
	expectedSize = sizeof(int);
	memcpy(&version, pointer, expectedSize);
	pointer += expectedSize;
	if (version != ANIMATION_VERSION)
	{
		LogError(L"OpenAnimationFromMemory: Unexpected Version!\r\n");
		return nullptr;
	}

	//LogDebug(L"OpenAnimationFromMemory: Version: %d\r\n", version);

	//device
	BYTE device = 0;

	// device type
	BYTE deviceType = 0;
	expectedSize = sizeof(BYTE);
	memcpy(&deviceType, pointer, expectedSize);
	pointer += expectedSize;

	//device
	switch ((EChromaSDKDeviceTypeEnum)deviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
		//LogDebug(L"OpenAnimation: DeviceType: 1D\r\n");
		break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
		//LogDebug(L"OpenAnimation: DeviceType: 2D\r\n");
		break;
	default:
		LogError(L"OpenAnimationFromMemory: Unexpected DeviceType!\r\n");
		return nullptr;
	}

	switch (deviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
	{
		expectedSize = sizeof(BYTE);
		memcpy(&device, pointer, expectedSize);
		pointer += expectedSize;

		switch ((EChromaSDKDevice1DEnum)device)
		{
		case EChromaSDKDevice1DEnum::DE_ChromaLink:
			//LogDebug(L"OpenAnimation: Device: DE_ChromaLink\r\n");
			break;
		case EChromaSDKDevice1DEnum::DE_Headset:
			//LogDebug(L"OpenAnimation: Device: DE_Headset\r\n");
			break;
		case EChromaSDKDevice1DEnum::DE_Mousepad:
			//LogDebug(L"OpenAnimation: Device: DE_Mousepad\r\n");
			break;
		}

		Animation1D* animation1D = new Animation1D();
		animation = animation1D;

		// device
		animation1D->SetDevice((EChromaSDKDevice1DEnum)device);

		//frame count
		int frameCount;

		expectedSize = sizeof(int);
		memcpy(&frameCount, pointer, expectedSize);
		pointer += expectedSize;

		vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
		for (int index = 0; index < frameCount; ++index)
		{
			FChromaSDKColorFrame1D frame = FChromaSDKColorFrame1D();
			int maxLeds = GetMaxLeds((EChromaSDKDevice1DEnum)device);

			//duration
			float duration = 0.0f;
			expectedSize = sizeof(float);
			memcpy(&duration, pointer, expectedSize);
			pointer += expectedSize;

			if (duration >= 0.033f)
			{
				frame.Duration = duration;
			}
			else
			{
				frame.Duration = 0.033f;
			}

			// colors
			expectedSize = sizeof(int);
			for (int i = 0; i < maxLeds; ++i)
			{
				int color = 0;
				memcpy(&color, pointer, expectedSize);
				pointer += expectedSize;

				frame.Colors.push_back((COLORREF)color);
			}
			if (index == 0)
			{
				frames[0] = frame;
			}
			else
			{
				frames.push_back(frame);
			}
		}
	}
	break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
	{
		expectedSize = sizeof(BYTE);
		memcpy(&device, pointer, expectedSize);
		pointer += expectedSize;

		switch ((EChromaSDKDevice2DEnum)device)
		{
		case EChromaSDKDevice2DEnum::DE_Keyboard:
			//LogDebug(L"OpenAnimation: Device: DE_Keyboard\r\n");
			break;
		case EChromaSDKDevice2DEnum::DE_KeyboardExtended:
			//LogDebug(L"OpenAnimation: Device: DE_KeyboardExtended\r\n");
			break;
		case EChromaSDKDevice2DEnum::DE_Keypad:
			//LogDebug(L"OpenAnimation: Device: DE_Keypad\r\n");
			break;
		case EChromaSDKDevice2DEnum::DE_Mouse:
			//LogDebug(L"OpenAnimation: Device: DE_Mouse\r\n");
			break;
		}

		Animation2D* animation2D = new Animation2D();
		animation = animation2D;

		//device
		animation2D->SetDevice((EChromaSDKDevice2DEnum)device);

		//frame count
		int frameCount;

		expectedSize = sizeof(int);
		memcpy(&frameCount, pointer, expectedSize);
		pointer += expectedSize;

		vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
		for (int index = 0; index < frameCount; ++index)
		{
			FChromaSDKColorFrame2D frame = FChromaSDKColorFrame2D((EChromaSDKDevice2DEnum)device);
			int maxRow = GetMaxRow((EChromaSDKDevice2DEnum)device);
			int maxColumn = GetMaxColumn((EChromaSDKDevice2DEnum)device);

			//duration
			float duration = 0.0f;
			expectedSize = sizeof(float);
			memcpy(&duration, pointer, expectedSize);
			pointer += expectedSize;

			if (duration >= 0.033f)
			{
				frame.Duration = duration;
			}
			else
			{
				frame.Duration = 0.033f;
			}

			// colors
			expectedSize = sizeof(int);
			for (int i = 0; i < maxRow; ++i)
			{
				FChromaSDKColors row = FChromaSDKColors();
				for (int j = 0; j < maxColumn; ++j)
				{
					int color = 0;
					memcpy(&color, pointer, expectedSize);
					pointer += expectedSize;

					row.Colors.push_back((COLORREF)color);
				}
				frame.Colors.push_back(row);
			}
			if (index == 0)
			{
				frames[0] = frame;
			}
			else
			{
				frames.push_back(frame);
			}
		}
	}
	break;
	}

	//LogDebug(L"OpenAnimationFromMemory: Loaded %s\r\n", path.c_str());

	return animation;
}
