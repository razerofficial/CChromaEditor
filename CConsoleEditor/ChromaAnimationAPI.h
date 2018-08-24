#pragma once

#include "..\CChromaEditorLibrary\ChromaSDKPluginTypes.h"

#ifdef _WIN64
#define CHROMA_EDITOR_DLL	_T("CChromaEditorLibrary64.dll")
#else
#define CHROMA_EDITOR_DLL	_T("CChromaEditorLibrary.dll")
#endif

typedef bool(*PLUGIN_IS_DIALOG_OPEN)();
typedef bool(*PLUGIN_IS_INITIALIZED)();
typedef bool(*PLUGIN_IS_PLAYING_NAME)(const char* name);
typedef bool(*PLUGIN_IS_PLAYING_TYPE)(int deviceType, int device);
typedef bool(*PLUGIN_SET_CHROMA_CUSTOM_COLOR_ALL_FRAMES)(int animationId);
typedef bool(*PLUGIN_SET_CHROMA_CUSTOM_COLOR_ALL_FRAMES_NAME)(const char* path);
typedef bool(*PLUGIN_SET_CHROMA_CUSTOM_FLAG)(int animationId, bool flag);
typedef bool(*PLUGIN_SET_CHROMA_CUSTOM_FLAG_NAME)(const char* path, bool flag);
typedef const char*(*PLUGIN_GET_ANIMATION_NAME)(int animationId);
typedef int(*PLUGIN_ADD_FRAME)(int animationId, float duration, int* colors, int length);
typedef int(*PLUGIN_CLOSE_ANIMATION)(int animationId);
typedef int(*PLUGIN_CREATE_ANIMATION)(const char* path, int deviceType, int device);
typedef int(*PLUGIN_CREATE_ANIMATION_IN_MEMORY)(int deviceType, int device);
typedef int(*PLUGIN_GET_ANIMATION_COUNT)();
typedef int(*PLUGIN_GET_ANIMATION_ID)(int index);
typedef int(*PLUGIN_GET_FRAME)(int animationId, int frameIndex, float* duration, int* colors, int length);
typedef int(*PLUGIN_GET_FRAME_COUNT_NAME)(const char* path);
typedef int(*PLUGIN_GET_MAX_COLUMN)(int device);
typedef int(*PLUGIN_GET_MAX_ROW)(int device);
typedef int(*PLUGIN_GET_PLAYING_ANIMATION_COUNT)();
typedef int(*PLUGIN_GET_PLAYING_ANIMATION_ID)(int index);
typedef int(*PLUGIN_GET_RGB)(int red, int green, int blue);
typedef int(*PLUGIN_MAKE_BLANK_FRAMES)(int animationId, int frameCount, float duration, int color);
typedef int(*PLUGIN_MAKE_BLANK_FRAMES_RANDOM)(int animationId, int frameCount, float duration);
typedef int(*PLUGIN_MAKE_BLANK_FRAMES_RANDOM_BLACK_AND_WHITE)(int animationId, int frameCount, float duration);
typedef int(*PLUGIN_MAKE_BLANK_FRAMES_RGB)(int animationId, int frameCount, float duration, int red, int green, int blue);
typedef int(*PLUGIN_OPEN_ANIMATION)(const char* path);
typedef int(*PLUGIN_OPEN_EDITOR_DIALOG)(const char* path);
typedef int(*PLUGIN_OPEN_EDITOR_DIALOG_AND_PLAY)(const char* path);
typedef int(*PLUGIN_PLAY_ANIMATION)(int animationId);
typedef int(*PLUGIN_PREVIEW_FRAME)(int animationId, int frameIndex);
typedef long(*PLUGIN_CREATE_EFFECT)(RZDEVICEID deviceId, ChromaSDK::EFFECT_TYPE effect, int* colors, int size, ChromaSDK::FChromaSDKGuid* effectGUID);
typedef long(*PLUGIN_DELETE_EFFECT)(const ChromaSDK::FChromaSDKGuid& effectGUID);
typedef long(*PLUGIN_SET_EFFECT)(const ChromaSDK::FChromaSDKGuid& effectGUID);
typedef void(*PLUGIN_ADD_NONZERO_ALL_KEYS_ALL_FRAMES)(int sourceAnimationId, int targetAnimationId);
typedef void(*PLUGIN_ADD_NONZERO_ALL_KEYS_ALL_FRAMES_NAME)(const char* sourceAnimation, const char* targetAnimation);
typedef void(*PLUGIN_CLEAR_ALL)();
typedef void(*PLUGIN_CLEAR_ANIMATION_TYPE)(int deviceType, int device);
typedef void(*PLUGIN_CLOSE_ALL)();
typedef void(*PLUGIN_CLOSE_ANIMATION_NAME)(const char* path);
typedef void(*PLUGIN_CLOSE_COMPOSITE)(const char* name);
typedef void(*PLUGIN_COPY_KEY_COLOR_NAME)(const char* sourceAnimation, const char* targetAnimation, int frameId, int rzkey);
typedef void(*PLUGIN_COPY_NONZERO_ALL_KEYS)(int sourceAnimationId, int targetAnimationId, int frameId);
typedef void(*PLUGIN_COPY_NONZERO_ALL_KEYS_NAME)(const char* sourceAnimation, const char* targetAnimation, int frameId);
typedef void(*PLUGIN_COPY_NONZERO_ALL_KEYS_OFFSET)(int sourceAnimationId, int targetAnimationId, int frameId, int offset);
typedef void(*PLUGIN_COPY_NONZERO_ALL_KEYS_OFFSET_NAME)(const char* sourceAnimation, const char* targetAnimation, int frameId, int offset);
typedef void(*PLUGIN_COPY_NONZERO_ALL_KEYS_ALL_FRAMES_NAME)(const char* sourceAnimation, const char* targetAnimation);
typedef void(*PLUGIN_COPY_NONZERO_ALL_KEYS_ALL_FRAMES_OFFSET_NAME)(const char* sourceAnimation, const char* targetAnimation, int offset);
typedef void(*PLUGIN_COPY_NONZERO_TARGET_ALL_KEYS_ALL_FRAMES_NAME)(const char* sourceAnimation, const char* targetAnimation);
typedef void(*PLUGIN_COPY_ZERO_ALL_KEYS_ALL_FRAMES_NAME)(const char* sourceAnimation, const char* targetAnimation);
typedef void(*PLUGIN_COPY_ZERO_ALL_KEYS_ALL_FRAMES_OFFSET_NAME)(const char* sourceAnimation, const char* targetAnimation, int offset);
typedef void(*PLUGIN_COPY_ZERO_TARGET_ALL_KEYS_ALL_FRAMES_NAME)(const char* sourceAnimation, const char* targetAnimation);
typedef void(*PLUGIN_FILL_COLOR_ALL_FRAMES_RGB_NAME)(const char* path, int red, int green, int blue);
typedef void(*PLUGIN_FILL_COLOR_RGB_NAME)(const char* path, int frameId, int red, int green, int blue);
typedef void(*PLUGIN_FILL_NONZERO_COLOR_ALL_FRAMES_RGB_NAME)(const char* path, int red, int green, int blue);
typedef void(*PLUGIN_FILL_NONZERO_COLOR_NAME)(const char* path, int frameId, int color);
typedef void(*PLUGIN_FILL_NONZERO_COLOR_RGB_NAME)(const char* path, int frameId, int red, int green, int blue);
typedef void(*PLUGIN_FILL_RANDOM_COLORS)(int animationId, int frameId);
typedef void(*PLUGIN_FILL_RANDOM_COLORS_ALL_FRAMES)(int animationId);
typedef void(*PLUGIN_FILL_RANDOM_COLORS_ALL_FRAMES_NAME)(const char* path);
typedef void(*PLUGIN_FILL_RANDOM_COLORS_BLACK_AND_WHITE)(int animationId, int frameId);
typedef void(*PLUGIN_FILL_RANDOM_COLORS_BLACK_AND_WHITE_ALL_FRAMES)(int animationId);
typedef void(*PLUGIN_FILL_RANDOM_COLORS_BLACK_AND_WHITE_ALL_FRAMES_NAME)(const char* path);
typedef void(*PLUGIN_FILL_RANDOM_COLORS_BLACK_AND_WHITE_NAME)(const char* path, int frameId);
typedef void(*PLUGIN_FILL_RANDOM_COLORS_NAME)(const char* path, int frameId);
typedef void(*PLUGIN_FILL_ZERO_COLOR)(int animationId, int frameId, int color);
typedef void(*PLUGIN_FILL_ZERO_COLOR_ALL_FRAMES)(int animationId, int color);
typedef void(*PLUGIN_FILL_ZERO_COLOR_ALL_FRAMES_NAME)(const char* path, int color);
typedef void(*PLUGIN_FILL_ZERO_COLOR_ALL_FRAMES_RGB)(int animationId, int red, int green, int blue);
typedef void(*PLUGIN_FILL_ZERO_COLOR_ALL_FRAMES_RGB_NAME)(const char* path, int red, int green, int blue);
typedef void(*PLUGIN_FILL_ZERO_COLOR_NAME)(const char* path, int frameId, int color);
typedef void(*PLUGIN_FILL_ZERO_COLOR_RGB)(int animationId, int frameId, int red, int green, int blue);
typedef void(*PLUGIN_FILL_ZERO_COLOR_RGB_NAME)(const char* path, int frameId, int red, int green, int blue);
typedef void(*PLUGIN_INIT)();
typedef void(*PLUGIN_LOAD_ANIMATION_NAME)(const char* path);
typedef void(*PLUGIN_LOAD_COMPOSITE)(const char* name);
typedef void(*PLUGIN_MAKE_BLANK_FRAMES_NAME)(const char* path, int frameCount, float duration, int color);
typedef void(*PLUGIN_MAKE_BLANK_FRAMES_RANDOM_BLACK_AND_WHITE_NAME)(const char* path, int frameCount, float duration);
typedef void(*PLUGIN_MAKE_BLANK_FRAMES_RANDOM_NAME)(const char* path, int frameCount, float duration);
typedef void(*PLUGIN_MAKE_BLANK_FRAMES_RGB_NAME)(const char* path, int frameCount, float duration, int red, int green, int blue);
typedef void(*PLUGIN_MULTIPLY_INTENSITY_ALL_FRAMES)(int animationId, float intensity);
typedef void(*PLUGIN_MULTIPLY_INTENSITY_ALL_FRAMES_NAME)(const char* path, float intensity);
typedef void(*PLUGIN_MULTIPLY_INTENSITY_ALL_FRAMES_RGB_NAME)(const char* path, int red, int green, int blue);
typedef void(*PLUGIN_MULTIPLY_INTENSITY_COLOR)(int animationId, int frameId, int color);
typedef void(*PLUGIN_MULTIPLY_INTENSITY_COLOR_NAME)(const char* path, int frameId, int color);
typedef void(*PLUGIN_MULTIPLY_INTENSITY_NAME)(const char* path, int frameId, float intensity);
typedef void(*PLUGIN_MULTIPLY_INTENSITY_RGB_NAME)(const char* path, int frameId, int red, int green, int blue);
typedef void(*PLUGIN_OFFSET_COLORS_ALL_FRAMES_NAME)(const char* path, int red, int green, int blue);
typedef void(*PLUGIN_OFFSET_COLORS_NAME)(const char* path, int frameId, int red, int green, int blue);
typedef void(*PLUGIN_OFFSET_NONZERO_COLORS_ALL_FRAMES_NAME)(const char* path, int red, int green, int blue);
typedef void(*PLUGIN_OFFSET_NONZERO_COLORS_NAME)(const char* path, int frameId, int red, int green, int blue);
typedef void(*PLUGIN_OVERRIDE_FRAME_DURATION)(int animationId, float duration);
typedef void(*PLUGIN_OVERRIDE_FRAME_DURATION_NAME)(const char* path, float duration);
typedef void(*PLUGIN_PLAY_ANIMATION_LOOP)(int animationId, bool loop);
typedef void(*PLUGIN_PLAY_ANIMATION_NAME)(const char* path, bool loop);
typedef void(*PLUGIN_PLAY_COMPOSITE)(const char* name, bool loop);
typedef void(*PLUGIN_REVERSE_ALL_FRAMES_NAME)(const char* path);
typedef void(*PLUGIN_SET_KEY_COLOR)(int animationId, int frameId, int rzkey, int color);
typedef void(*PLUGIN_SET_KEY_COLOR_ALL_FRAMES)(int animationId, int rzkey, int color);
typedef void(*PLUGIN_SET_KEY_COLOR_ALL_FRAMES_NAME)(const char* path, int rzkey, int color);
typedef void(*PLUGIN_SET_KEY_COLOR_NAME)(const char* path, int frameId, int rzkey, int color);
typedef void(*PLUGIN_SET_KEY_NONZERO_COLOR_NAME)(const char* path, int frameId, int rzkey, int color);
typedef void(*PLUGIN_SET_KEY_ZERO_COLOR_NAME)(const char* path, int frameId, int rzkey, int color);
typedef void(*PLUGIN_SET_KEYS_COLOR_ALL_FRAMES)(int animationId, const int* rzkeys, int keyCount, int color);
typedef void(*PLUGIN_SET_KEYS_COLOR_ALL_FRAMES_NAME)(const char* path, const int* rzkeys, int keyCount, int color);
typedef void(*PLUGIN_SET_KEYS_COLOR_ALL_FRAMES_RGB)(int animationId, const int* rzkeys, int keyCount, int red, int green, int blue);
typedef void(*PLUGIN_SET_KEYS_COLOR_ALL_FRAMES_RGB_NAME)(const char* path, const int* rzkeys, int keyCount, int red, int green, int blue);
typedef void(*PLUGIN_SET_KEYS_COLOR_NAME)(const char* path, int frameId, const int* rzkeys, int keyCount, int color);
typedef void(*PLUGIN_SET_KEYS_NONZERO_COLOR_NAME)(const char* path, int frameId, const int* rzkeys, int keyCount, int color);
typedef void(*PLUGIN_SET_KEYS_ZERO_COLOR_NAME)(const char* path, int frameId, const int* rzkeys, int keyCount, int color);
typedef void(*PLUGIN_STOP_ALL)();
typedef void(*PLUGIN_STOP_ANIMATION_NAME)(const char* path);
typedef void(*PLUGIN_STOP_ANIMATION_TYPE)(int deviceType, int device);
typedef void(*PLUGIN_STOP_COMPOSITE)(const char* name);
typedef void(*PLUGIN_UNINIT)();
typedef void(*PLUGIN_UNLOAD_ANIMATION_NAME)(const char* path);
typedef void(*PLUGIN_UNLOAD_COMPOSITE)(const char* name);
typedef void(*PLUGIN_DUPLICATE_FRAMES)(int animationId);
typedef void(*PLUGIN_DUPLICATE_FRAMES_NAME)(const char* path);
typedef void(*PLUGIN_DUPLICATE_FIRST_FRAME)(int animationId, int frameCount);
typedef void(*PLUGIN_DUPLICATE_FIRST_FRAME_NAME)(const char* path, int frameCount);
typedef void(*PLUGIN_DUPLICATE_MIRROR_FRAMES)(int animationId);
typedef void(*PLUGIN_DUPLICATE_MIRROR_FRAMES_NAME)(const char* path);
typedef void(*PLUGIN_INSERT_FRAME)(int animationId, int sourceFrame, int targetFrame);
typedef void(*PLUGIN_INSERT_FRAME_NAME)(const char* path, int sourceFrame, int targetFrame);
typedef void(*PLUGIN_INSERT_DELAY)(int animationId, int frameId, int delay);
typedef void(*PLUGIN_INSERT_DELAY_NAME)(const char* path, int frameId, int delay);
typedef void(*PLUGIN_REDUCE_FRAMES)(int animationId, int n);
typedef void(*PLUGIN_REDUCE_FRAMES_NAME)(const char* path, int n);
typedef void(*PLUGIN_TRIM_FRAME)(int animationId, int frameId);
typedef void(*PLUGIN_TRIM_FRAME_NAME)(const char* path, int frameId);
typedef void(*PLUGIN_TRIM_START_FRAMES)(int animationId, int numberOfFrames);
typedef void(*PLUGIN_TRIM_START_FRAMES_NAME)(const char* path, int numberOfFrames);
typedef void(*PLUGIN_TRIM_END_FRAMES)(int animationId, int lastFrameId);
typedef void(*PLUGIN_TRIM_END_FRAMES_NAME)(const char* path, int lastFrameId);
typedef void(*PLUGIN_FADE_START_FRAMES)(int animationId, int fade);
typedef void(*PLUGIN_FADE_START_FRAMES_NAME)(const char* path, int fade);
typedef void(*PLUGIN_FADE_END_FRAMES)(int animationId, int fade);
typedef void(*PLUGIN_FADE_END_FRAMES_NAME)(const char* path, int fade);


#define CHROMASDK_DECLARE_METHOD(Signature, FieldName) static Signature FieldName;

namespace ChromaSDK
{
	class ChromaAnimationAPI
	{
	public:
		CHROMASDK_DECLARE_METHOD(PLUGIN_ADD_FRAME, AddFrame)
		CHROMASDK_DECLARE_METHOD(PLUGIN_ADD_NONZERO_ALL_KEYS_ALL_FRAMES, AddNonZeroAllKeysAllFrames)
		CHROMASDK_DECLARE_METHOD(PLUGIN_ADD_NONZERO_ALL_KEYS_ALL_FRAMES_NAME, AddNonZeroAllKeysAllFramesName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_CLEAR_ALL, ClearAll)
		CHROMASDK_DECLARE_METHOD(PLUGIN_CLEAR_ANIMATION_TYPE, ClearAnimationType)
		CHROMASDK_DECLARE_METHOD(PLUGIN_CLOSE_ALL, CloseAll)
		CHROMASDK_DECLARE_METHOD(PLUGIN_CLOSE_ANIMATION, CloseAnimation)
		CHROMASDK_DECLARE_METHOD(PLUGIN_CLOSE_ANIMATION_NAME, CloseAnimationName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_CLOSE_COMPOSITE, CloseComposite)
		CHROMASDK_DECLARE_METHOD(PLUGIN_COPY_KEY_COLOR_NAME, CopyKeyColorName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_COPY_NONZERO_ALL_KEYS, CopyNonZeroAllKeys)
		CHROMASDK_DECLARE_METHOD(PLUGIN_COPY_NONZERO_ALL_KEYS_NAME, CopyNonZeroAllKeysName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_COPY_NONZERO_ALL_KEYS_OFFSET, CopyNonZeroAllKeysOffset)
		CHROMASDK_DECLARE_METHOD(PLUGIN_COPY_NONZERO_ALL_KEYS_OFFSET_NAME, CopyNonZeroAllKeysOffsetName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_COPY_NONZERO_ALL_KEYS_ALL_FRAMES_NAME, CopyNonZeroAllKeysAllFramesName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_COPY_NONZERO_ALL_KEYS_ALL_FRAMES_OFFSET_NAME, CopyNonZeroAllKeysAllFramesOffsetName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_COPY_NONZERO_TARGET_ALL_KEYS_ALL_FRAMES_NAME, CopyNonZeroTargetAllKeysAllFramesName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_COPY_ZERO_ALL_KEYS_ALL_FRAMES_NAME, CopyZeroAllKeysAllFramesName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_COPY_ZERO_ALL_KEYS_ALL_FRAMES_OFFSET_NAME, CopyZeroAllKeysAllFramesOffsetName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_COPY_ZERO_TARGET_ALL_KEYS_ALL_FRAMES_NAME, CopyZeroTargetAllKeysAllFramesName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_CREATE_ANIMATION, CreateAnimation)
		CHROMASDK_DECLARE_METHOD(PLUGIN_CREATE_ANIMATION_IN_MEMORY, CreateAnimationInMemory)
		CHROMASDK_DECLARE_METHOD(PLUGIN_CREATE_EFFECT, CreateEffect)
		CHROMASDK_DECLARE_METHOD(PLUGIN_DELETE_EFFECT, DeleteEffect)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_COLOR_ALL_FRAMES_RGB_NAME, FillColorAllFramesRGBName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_COLOR_RGB_NAME, FillColorRGBName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_NONZERO_COLOR_ALL_FRAMES_RGB_NAME, FillNonZeroColorAllFramesRGBName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_NONZERO_COLOR_NAME, FillNonZeroColorName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_NONZERO_COLOR_RGB_NAME, FillNonZeroColorRGBName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_RANDOM_COLORS, FillRandomColors)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_RANDOM_COLORS_ALL_FRAMES, FillRandomColorsAllFrames)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_RANDOM_COLORS_ALL_FRAMES_NAME, FillRandomColorsAllFramesName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_RANDOM_COLORS_BLACK_AND_WHITE, FillRandomColorsBlackAndWhite)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_RANDOM_COLORS_BLACK_AND_WHITE_ALL_FRAMES, FillRandomColorsBlackAndWhiteAllFrames)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_RANDOM_COLORS_BLACK_AND_WHITE_ALL_FRAMES_NAME, FillRandomColorsBlackAndWhiteAllFramesName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_RANDOM_COLORS_BLACK_AND_WHITE_NAME, FillRandomColorsBlackAndWhiteName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_RANDOM_COLORS_NAME, FillRandomColorsName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_ZERO_COLOR, FillZeroColor)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_ZERO_COLOR_ALL_FRAMES, FillZeroColorAllFrames)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_ZERO_COLOR_ALL_FRAMES_NAME, FillZeroColorAllFramesName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_ZERO_COLOR_ALL_FRAMES_RGB, FillZeroColorAllFramesRGB)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_ZERO_COLOR_ALL_FRAMES_RGB_NAME, FillZeroColorAllFramesRGBName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_ZERO_COLOR_NAME, FillZeroColorName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_ZERO_COLOR_RGB, FillZeroColorRGB)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_ZERO_COLOR_RGB_NAME, FillZeroColorRGBName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_GET_ANIMATION_COUNT, GetAnimationCount)
		CHROMASDK_DECLARE_METHOD(PLUGIN_GET_ANIMATION_ID, GetAnimationId)
		CHROMASDK_DECLARE_METHOD(PLUGIN_GET_ANIMATION_NAME, GetAnimationName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_GET_FRAME, GetFrame)
		CHROMASDK_DECLARE_METHOD(PLUGIN_GET_FRAME_COUNT_NAME, GetFrameCountName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_GET_MAX_COLUMN, GetMaxColumn)
		CHROMASDK_DECLARE_METHOD(PLUGIN_GET_MAX_ROW, GetMaxRow)
		CHROMASDK_DECLARE_METHOD(PLUGIN_GET_PLAYING_ANIMATION_COUNT, GetPlayingAnimationCount)
		CHROMASDK_DECLARE_METHOD(PLUGIN_GET_PLAYING_ANIMATION_ID, GetPlayingAnimationId)
		CHROMASDK_DECLARE_METHOD(PLUGIN_GET_RGB, GetRGB)
		CHROMASDK_DECLARE_METHOD(PLUGIN_INIT, Init)
		CHROMASDK_DECLARE_METHOD(PLUGIN_IS_DIALOG_OPEN, IsDialogOpen)
		CHROMASDK_DECLARE_METHOD(PLUGIN_IS_INITIALIZED, IsInitialized)
		CHROMASDK_DECLARE_METHOD(PLUGIN_IS_INITIALIZED, IsInitialized2)
		CHROMASDK_DECLARE_METHOD(PLUGIN_IS_PLAYING_NAME, IsPlayingName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_IS_PLAYING_TYPE, IsPlayingType)
		CHROMASDK_DECLARE_METHOD(PLUGIN_LOAD_ANIMATION_NAME, LoadAnimationName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_LOAD_COMPOSITE, LoadComposite)
		CHROMASDK_DECLARE_METHOD(PLUGIN_MAKE_BLANK_FRAMES, MakeBlankFrames)
		CHROMASDK_DECLARE_METHOD(PLUGIN_MAKE_BLANK_FRAMES_NAME, MakeBlankFramesName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_MAKE_BLANK_FRAMES_RANDOM, MakeBlankFramesRandom)
		CHROMASDK_DECLARE_METHOD(PLUGIN_MAKE_BLANK_FRAMES_RANDOM_BLACK_AND_WHITE, MakeBlankFramesRandomBlackAndWhite)
		CHROMASDK_DECLARE_METHOD(PLUGIN_MAKE_BLANK_FRAMES_RANDOM_BLACK_AND_WHITE_NAME, MakeBlankFramesRandomBlackAndWhiteName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_MAKE_BLANK_FRAMES_RANDOM_NAME, MakeBlankFramesRandomName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_MAKE_BLANK_FRAMES_RGB, MakeBlankFramesRGB)
		CHROMASDK_DECLARE_METHOD(PLUGIN_MAKE_BLANK_FRAMES_RGB_NAME, MakeBlankFramesRGBName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_MULTIPLY_INTENSITY_ALL_FRAMES, MultiplyIntensityAllFrames)
		CHROMASDK_DECLARE_METHOD(PLUGIN_MULTIPLY_INTENSITY_ALL_FRAMES_NAME, MultiplyIntensityAllFramesName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_MULTIPLY_INTENSITY_ALL_FRAMES_RGB_NAME, MultiplyIntensityAllFramesRGBName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_MULTIPLY_INTENSITY_COLOR, MultiplyIntensityColor)
		CHROMASDK_DECLARE_METHOD(PLUGIN_MULTIPLY_INTENSITY_COLOR_NAME, MultiplyIntensityColorName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_MULTIPLY_INTENSITY_NAME, MultiplyIntensityName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_MULTIPLY_INTENSITY_RGB_NAME, MultiplyIntensityRGBName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_OFFSET_COLORS_ALL_FRAMES_NAME, OffsetColorsAllFramesName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_OFFSET_COLORS_NAME, OffsetColorsName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_OFFSET_NONZERO_COLORS_ALL_FRAMES_NAME, OffsetNonZeroColorsAllFramesName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_OFFSET_NONZERO_COLORS_NAME, OffsetNonZeroColorsName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_OPEN_ANIMATION, OpenAnimation)
		CHROMASDK_DECLARE_METHOD(PLUGIN_OPEN_EDITOR_DIALOG, OpenEditorDialog)
		CHROMASDK_DECLARE_METHOD(PLUGIN_OPEN_EDITOR_DIALOG_AND_PLAY, OpenEditorDialogAndPlay)
		CHROMASDK_DECLARE_METHOD(PLUGIN_OVERRIDE_FRAME_DURATION, OverrideFrameDuration)
		CHROMASDK_DECLARE_METHOD(PLUGIN_OVERRIDE_FRAME_DURATION_NAME, OverrideFrameDurationName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_PLAY_ANIMATION, PlayAnimation)
		CHROMASDK_DECLARE_METHOD(PLUGIN_PLAY_ANIMATION_LOOP, PlayAnimationLoop)
		CHROMASDK_DECLARE_METHOD(PLUGIN_PLAY_ANIMATION_NAME, PlayAnimationName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_PLAY_COMPOSITE, PlayComposite)
		CHROMASDK_DECLARE_METHOD(PLUGIN_PREVIEW_FRAME, PreviewFrame)
		CHROMASDK_DECLARE_METHOD(PLUGIN_REVERSE_ALL_FRAMES_NAME, ReverseAllFramesName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_SET_CHROMA_CUSTOM_COLOR_ALL_FRAMES, SetChromaCustomColorAllFrames)
		CHROMASDK_DECLARE_METHOD(PLUGIN_SET_CHROMA_CUSTOM_COLOR_ALL_FRAMES_NAME, SetChromaCustomColorAllFramesName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_SET_CHROMA_CUSTOM_FLAG, SetChromaCustomFlag);
		CHROMASDK_DECLARE_METHOD(PLUGIN_SET_CHROMA_CUSTOM_FLAG_NAME, SetChromaCustomFlagName);
		CHROMASDK_DECLARE_METHOD(PLUGIN_SET_EFFECT, SetEffect)
		CHROMASDK_DECLARE_METHOD(PLUGIN_SET_KEY_COLOR, SetKeyColor)
		CHROMASDK_DECLARE_METHOD(PLUGIN_SET_KEY_COLOR_ALL_FRAMES, SetKeyColorAllFrames)
		CHROMASDK_DECLARE_METHOD(PLUGIN_SET_KEY_COLOR_ALL_FRAMES_NAME, SetKeyColorAllFramesName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_SET_KEY_COLOR_NAME, SetKeyColorName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_SET_KEY_NONZERO_COLOR_NAME, SetKeyNonZeroColorName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_SET_KEY_ZERO_COLOR_NAME, SetKeyZeroColorName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_SET_KEYS_COLOR_ALL_FRAMES, SetKeysColorAllFrames)
		CHROMASDK_DECLARE_METHOD(PLUGIN_SET_KEYS_COLOR_ALL_FRAMES_NAME, SetKeysColorAllFramesName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_SET_KEYS_COLOR_ALL_FRAMES_RGB, SetKeysColorAllFramesRGB)
		CHROMASDK_DECLARE_METHOD(PLUGIN_SET_KEYS_COLOR_ALL_FRAMES_RGB_NAME, SetKeysColorAllFramesRGBName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_SET_KEYS_COLOR_NAME, SetKeysColorName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_SET_KEYS_NONZERO_COLOR_NAME, SetKeysNonZeroColorName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_SET_KEYS_ZERO_COLOR_NAME, SetKeysZeroColorName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_STOP_ALL, StopAll)
		CHROMASDK_DECLARE_METHOD(PLUGIN_STOP_ANIMATION_NAME, StopAnimationName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_STOP_ANIMATION_TYPE, StopAnimationType)
		CHROMASDK_DECLARE_METHOD(PLUGIN_STOP_COMPOSITE, StopComposite)
		CHROMASDK_DECLARE_METHOD(PLUGIN_UNINIT, Uninit)
		CHROMASDK_DECLARE_METHOD(PLUGIN_UNLOAD_ANIMATION_NAME, UnloadAnimationName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_UNLOAD_COMPOSITE, UnloadComposite)
		CHROMASDK_DECLARE_METHOD(PLUGIN_DUPLICATE_FRAMES, DuplicateFrames)
		CHROMASDK_DECLARE_METHOD(PLUGIN_DUPLICATE_FRAMES_NAME, DuplicateFramesName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_DUPLICATE_FIRST_FRAME, DuplicateFirstFrame)
		CHROMASDK_DECLARE_METHOD(PLUGIN_DUPLICATE_FIRST_FRAME_NAME, DuplicateFirstFrameName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_DUPLICATE_MIRROR_FRAMES, DuplicateMirrorFrames)
		CHROMASDK_DECLARE_METHOD(PLUGIN_DUPLICATE_MIRROR_FRAMES_NAME, DuplicateMirrorFramesName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_INSERT_FRAME, InsertFrame)
		CHROMASDK_DECLARE_METHOD(PLUGIN_INSERT_FRAME_NAME, InsertFrameName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_INSERT_DELAY, InsertDelay)
		CHROMASDK_DECLARE_METHOD(PLUGIN_INSERT_DELAY_NAME, InsertDelayName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_REDUCE_FRAMES, ReduceFrames)
		CHROMASDK_DECLARE_METHOD(PLUGIN_REDUCE_FRAMES_NAME, ReduceFramesName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_TRIM_FRAME, TrimFrame)
		CHROMASDK_DECLARE_METHOD(PLUGIN_TRIM_FRAME_NAME, TrimFrameName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_TRIM_START_FRAMES, TrimStartFrames)
		CHROMASDK_DECLARE_METHOD(PLUGIN_TRIM_START_FRAMES_NAME, TrimStartFramesName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_TRIM_END_FRAMES, TrimEndFrames)
		CHROMASDK_DECLARE_METHOD(PLUGIN_TRIM_END_FRAMES_NAME, TrimEndFramesName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FADE_START_FRAMES, FadeStartFrames)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FADE_START_FRAMES_NAME, FadeStartFramesName)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FADE_END_FRAMES, FadeEndFrames)
		CHROMASDK_DECLARE_METHOD(PLUGIN_FADE_END_FRAMES_NAME, FadeEndFramesName)


		static int InitAPI();

		float Lerp(float start, float end, float amt);
		int LerpColor(int from, int to, float t);
	};
}
