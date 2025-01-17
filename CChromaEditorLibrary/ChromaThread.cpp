#include "stdafx.h"
#include "Animation1D.h"
#include "Animation2D.h"
#include "ChromaSDKPlugin.h"
#include "ChromaThread.h"
#include "RzChromaSDK.h"
#include <chrono>
#include <sstream>

using namespace ChromaSDK;
using namespace std;
using namespace std::chrono;

ChromaThread* ChromaThread::_sInstance = nullptr;
mutex ChromaThread::_sMutex;
bool ChromaThread::_sWaitForExit = true;
thread* ChromaThread::_sThread = nullptr;
vector<AnimationBase*> ChromaThread::_sAnimations;
vector<bool> ChromaThread::_sUseIdleAnimation;
vector<std::string> ChromaThread::_sIdleAnimation;
std::vector<std::wstring> ChromaThread::_sOrderPendingCommands;
std::map<std::wstring, PendingCommand> ChromaThread::_sPendingCommands;
RZRESULT ChromaThread::_sLastResultSetEventName = RZRESULT_SUCCESS;

extern map<EChromaSDKDevice1DEnum, int> _gPlayMap1D;
extern map<EChromaSDKDevice2DEnum, int> _gPlayMap2D;
extern bool _gForwardChromaEvents;

ChromaThread::ChromaThread()
{
	_sThread = nullptr;
	_sWaitForExit = true;
	for (int i = 0; i < (int)EChromaSDKDeviceEnum::DE_MAX; ++i)
	{
		_sUseIdleAnimation.push_back(false);
		_sIdleAnimation.push_back("");
	}	
}

ChromaThread* ChromaThread::Instance()
{
	return _sInstance;
}

void ChromaThread::Init()
{
	if (_sInstance == nullptr)
	{
		_sInstance = new ChromaThread();
	}
}

void ChromaThread::UseIdleAnimation(EChromaSDKDeviceEnum device, bool flag)
{
	switch (device)
	{
	case EChromaSDKDeviceEnum::DE_KeyboardExtended:
		_sUseIdleAnimation[(int)EChromaSDKDeviceEnum::DE_Keyboard] = flag;
		break;
	case EChromaSDKDeviceEnum::DE_ChromaLink:
	case EChromaSDKDeviceEnum::DE_Headset:
	case EChromaSDKDeviceEnum::DE_Keyboard:
	case EChromaSDKDeviceEnum::DE_Keypad:
	case EChromaSDKDeviceEnum::DE_Mouse:
	case EChromaSDKDeviceEnum::DE_Mousepad:
		_sUseIdleAnimation[(int)device] = flag;
		break;
	}
}
void ChromaThread::ImplSetIdleAnimationName(const char* name)
{
	lock_guard<mutex> guard(_sMutex);
	AnimationBase* animation = GetAnimationInstanceName(name);
	if (animation != nullptr)
	{
		if (animation->HasUsePreloading())
		{
			animation->Load();
		}
		Animation1D* animation1D = nullptr;
		Animation2D* animation2D = nullptr;
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
			animation1D = (Animation1D*)(animation);
			switch (animation1D->GetDevice())
			{
			case EChromaSDKDevice1DEnum::DE_ChromaLink:
				_sIdleAnimation[(int)EChromaSDKDeviceEnum::DE_ChromaLink] = name;
				break;
			case EChromaSDKDevice1DEnum::DE_Headset:
				_sIdleAnimation[(int)EChromaSDKDeviceEnum::DE_Headset] = name;
				break;
			case EChromaSDKDevice1DEnum::DE_Mousepad:
				_sIdleAnimation[(int)EChromaSDKDeviceEnum::DE_Mousepad] = name;
				break;
			}
			break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
			animation2D = (Animation2D*)(animation);
			switch (animation2D->GetDevice())
			{
			case EChromaSDKDevice2DEnum::DE_Keyboard:
			case EChromaSDKDevice2DEnum::DE_KeyboardExtended:
				_sIdleAnimation[(int)EChromaSDKDeviceEnum::DE_Keyboard] = name;
				break;
			case EChromaSDKDevice2DEnum::DE_Keypad:
				_sIdleAnimation[(int)EChromaSDKDeviceEnum::DE_Keypad] = name;
				break;
			case EChromaSDKDevice2DEnum::DE_Mouse:
				_sIdleAnimation[(int)EChromaSDKDeviceEnum::DE_Mouse] = name;
				break;
			}
			break;
		}
	}
}

void ChromaThread::ImplStopAnimationType(int deviceType, int device)
{
	int deviceId = device;
	if (deviceType == (int)EChromaSDKDeviceTypeEnum::DE_2D &&
		device == (int)EChromaSDKDevice2DEnum::DE_KeyboardExtended)
	{
		deviceId = (int)EChromaSDKDevice2DEnum::DE_Keyboard;
	}

	switch ((EChromaSDKDeviceTypeEnum)deviceType)
	{
	case EChromaSDKDeviceTypeEnum::DE_1D:
	{
		if (_gPlayMap1D.find((EChromaSDKDevice1DEnum)deviceId) != _gPlayMap1D.end())
		{
			int prevAnimation = _gPlayMap1D[(EChromaSDKDevice1DEnum)deviceId];
			if (prevAnimation != -1)
			{
				PluginStopAnimation(prevAnimation);
			}
		}
	}
	break;
	case EChromaSDKDeviceTypeEnum::DE_2D:
	{
		if (_gPlayMap2D.find((EChromaSDKDevice2DEnum)deviceId) != _gPlayMap2D.end())
		{
			int prevAnimation = _gPlayMap2D[(EChromaSDKDevice2DEnum)deviceId];
			if (prevAnimation != -1)
			{
				PluginStopAnimation(prevAnimation);
			}
		}
	}
	break;
	}
}

void ChromaThread::ProcessAnimations(float deltaTime)
{
	lock_guard<mutex> guard(_sMutex);

	// module shutdown while waiting for lock
	if (!_sWaitForExit)
	{
		return;
	}

	// detect if animations are playing
	vector<bool> detectIdle;
	for (int i = 0; i < (int)EChromaSDKDeviceEnum::DE_MAX && _sWaitForExit; ++i)
	{
		detectIdle.push_back(true);
	}

	// update animations
	vector<AnimationBase*> doneList = vector<AnimationBase*>();
	for (unsigned int i = 0; i < _sAnimations.size() && _sWaitForExit; ++i)
	{
		AnimationBase* animation = _sAnimations[i];
		if (animation != nullptr)
		{
			animation->Update(deltaTime);
			// no need to update animations that are no longer playing
			if (animation->IsPlaying())
			{
				// an animation is playing, idle condition is false
				Animation1D* animation1D = nullptr;
				Animation2D* animation2D = nullptr;
				switch (animation->GetDeviceType())
				{
				case EChromaSDKDeviceTypeEnum::DE_1D:
					animation1D = (Animation1D*)(animation);
					switch (animation1D->GetDevice())
					{
					case EChromaSDKDevice1DEnum::DE_ChromaLink:
						detectIdle[(int)EChromaSDKDeviceEnum::DE_ChromaLink] = false;
						break;
					case EChromaSDKDevice1DEnum::DE_Headset:
						detectIdle[(int)EChromaSDKDeviceEnum::DE_Headset] = false;
						break;
					case EChromaSDKDevice1DEnum::DE_Mousepad:
						detectIdle[(int)EChromaSDKDeviceEnum::DE_Mousepad] = false;
						break;
					}
					break;
				case EChromaSDKDeviceTypeEnum::DE_2D:
					animation2D = (Animation2D*)(animation);
					switch (animation2D->GetDevice())
					{
					case EChromaSDKDevice2DEnum::DE_Keyboard:
					case EChromaSDKDevice2DEnum::DE_KeyboardExtended:
						detectIdle[(int)EChromaSDKDeviceEnum::DE_Keyboard] = false;
						break;
					case EChromaSDKDevice2DEnum::DE_Keypad:
						detectIdle[(int)EChromaSDKDeviceEnum::DE_Keypad] = false;
						break;
					case EChromaSDKDevice2DEnum::DE_Mouse:
						detectIdle[(int)EChromaSDKDeviceEnum::DE_Mouse] = false;
						break;
					}
					break;
				}
			}
			else
			{
				if (!animation->HasLoop())
				{
					doneList.push_back(animation);
				}
			}
		}
	}

	// remove animations that are done from the playing animation list
	for (int i = 0; i < (int)doneList.size() && _sWaitForExit; ++i)
	{
		AnimationBase* animation = doneList[i];
		if (animation != nullptr)
		{
			auto it = find(_sAnimations.begin(), _sAnimations.end(), animation);
			if (it != _sAnimations.end())
			{
				_sAnimations.erase(it);
			}
		}
	}

	// if no animations are playing, the idle animation can be played
	for (int i = 0; i < (int)EChromaSDKDeviceEnum::DE_MAX && _sWaitForExit; ++i)
	{
		if (_sUseIdleAnimation[i] &&
			detectIdle[i])
		{
			AnimationBase* idleAnimation = GetAnimationInstanceIfOpenName(_sIdleAnimation[i].c_str());
			if (idleAnimation != nullptr)
			{
				if (!idleAnimation->IsPlaying())
				{
					idleAnimation->InternalSetTime(0.0f);
					idleAnimation->InternalSetCurrentFrame(-1);
					idleAnimation->InternalSetIsPlaying(true);
					idleAnimation->InternalSetLoop(false);
					idleAnimation->InternalSetIsPaused(false);
				}
				idleAnimation->InternalUpdate(deltaTime);
			}
		}
	}
}

void ChromaThread::AddPendingCommandInOrder(const wstring& key, const PendingCommand& command)
{
	_sPendingCommands[key] = command;
	// maintain the order of pending commands
	auto it = std::find(_sOrderPendingCommands.begin(), _sOrderPendingCommands.end(), key);
	if (it != _sOrderPendingCommands.end())
	{
		_sOrderPendingCommands.erase(it);
	}
	_sOrderPendingCommands.push_back(key);
}

void ChromaThread::AsyncPlayAnimationName(const char* path, bool loop)
{
	lock_guard<mutex> guard(_sMutex);

	// module shutdown early abort
	if (!_sWaitForExit)
	{
		return;
	}

	// use the path as key and save the loop state
	ParamsPlayChromaAnimationName params;
	params._mPath = path;
	params._mLoop = loop;
	wstring key = params.GenerateKey();

	PendingCommand command;
	command._mType = PendingCommandType::Command_PlayChromaAnimationName;
	command._mPlayChromaAnimationName = params;
	AddPendingCommandInOrder(key, command);
}

void ChromaThread::AsyncStopAnimationName(const char* path)
{
	lock_guard<mutex> guard(_sMutex);

	// module shutdown early abort
	if (!_sWaitForExit)
	{
		return;
	}

	// use the path as key and save the loop state
	ParamsStopAnimationName params;
	params._mPath = path;
	wstring key = params.GenerateKey();

	PendingCommand command;
	command._mType = PendingCommandType::Command_StopAnimationName;
	command._mStopAnimationName = params;
	AddPendingCommandInOrder(key, command);
}

void ChromaThread::AsyncStopAnimationType(int deviceType, int device)
{
	lock_guard<mutex> guard(_sMutex);

	// module shutdown early abort
	if (!_sWaitForExit)
	{
		return;
	}

	// use the path as key and save the loop state
	ParamsStopAnimationType params;
	params._mDeviceType = deviceType;
	params._mDevice = device;
	wstring key = params.GenerateKey();

	PendingCommand command;
	command._mType = PendingCommandType::Command_StopAnimationType;
	command._mStopAnimationType = params;
	AddPendingCommandInOrder(key, command);
}

void ChromaThread::AsyncSetIdleAnimationName(const char* path)
{
	lock_guard<mutex> guard(_sMutex);

	// module shutdown early abort
	if (!_sWaitForExit)
	{
		return;
	}

	// use the path as key and save the loop state
	ParamsSetIdleAnimationName params;
	params._mPath = path;
	wstring key = params.GenerateKey();

	PendingCommand command;
	command._mType = PendingCommandType::Command_SetIdleAnimationName;
	command._mSetIdleAnimationName = params;
	AddPendingCommandInOrder(key, command);
}

void ChromaThread::AsyncStopAll()
{
	lock_guard<mutex> guard(_sMutex);

	// module shutdown early abort
	if (!_sWaitForExit)
	{
		return;
	}

	// use the path as key and save the loop state
	ParamsStopAll params;
	wstring key = params.GenerateKey();

	PendingCommand command;
	command._mType = PendingCommandType::Command_StopAll;
	command._mStopAll = params;
	AddPendingCommandInOrder(key, command);
}

RZRESULT ChromaThread::AsyncSetEventName(LPCTSTR Name)
{
	lock_guard<mutex> guard(_sMutex);

	// module shutdown early abort
	if (!_sWaitForExit)
	{
		return RZRESULT_FAILED;
	}

	// Add only a new item
	ParamsSetEventName params;
	params._mName = Name;
	wstring key = params.GenerateKey();

	PendingCommand command;
	command._mType = PendingCommandType::Command_SetEventName;
	command._mSetEventName = params;
	AddPendingCommandInOrder(key, command);

	// return last result since method is asynchronous
	return _sLastResultSetEventName;
}

void ChromaThread::AsyncUseForwardChromaEvents(bool flag)
{
	lock_guard<mutex> guard(_sMutex);

	// module shutdown early abort
	if (!_sWaitForExit)
	{
		return;
	}

	// Add only a new item
	ParamsUseForwardChromaEvents params;
	params._mFlag = flag;
	wstring key = params.GenerateKey();

	PendingCommand command;
	command._mType = PendingCommandType::Command_UseForwardChromaEvents;
	command._mUseForwardChromaEvents = params;
	AddPendingCommandInOrder(key, command);
}

void ChromaThread::AsyncUseIdleAnimations(bool flag)
{
	lock_guard<mutex> guard(_sMutex);

	// module shutdown early abort
	if (!_sWaitForExit)
	{
		return;
	}

	// Add only a new item
	ParamsUseIdleAnimations params;
	params._mFlag = flag;
	wstring key = params.GenerateKey();

	PendingCommand command;
	command._mType = PendingCommandType::Command_UseIdleAnimations;
	command._mUseIdleAnimations = params;
	AddPendingCommandInOrder(key, command);
}

std::vector<PendingCommand> ChromaThread::GetPendingCommands()
{
	lock_guard<mutex> guard(_sMutex);

	std::vector<PendingCommand> results;

	// module shutdown early abort
	if (!_sWaitForExit)
	{
		return results;
	}

	// build a list of pending commands in the original order
	for (auto it = _sOrderPendingCommands.begin(); it != _sOrderPendingCommands.end(); ++it)
	{
		const wstring& key = *it;
		//printf("GetPendingCommands: %S\r\n", key.c_str());
		const PendingCommand& command = _sPendingCommands[key];
		results.push_back(command);
	}

	_sOrderPendingCommands.clear();
	_sPendingCommands.clear();

	return results;
}

void ChromaThread::ProcessPendingCommands()
{
	// module shutdown early abort
	if (!_sWaitForExit)
	{
		return;
	}

	// Get the pending commands and clear the list
	std::vector<PendingCommand> pendingCommands = GetPendingCommands();

	// execute the commands from the worker thread
	for (std::vector<PendingCommand>::iterator it = pendingCommands.begin(); it != pendingCommands.end(); ++it)
	{
		// module shutdown early abort
		if (!_sWaitForExit)
		{
			return;
		}

		const PendingCommand& pendingCommand = *it;

		switch (pendingCommand._mType)
		{
			case PendingCommandType::Command_PlayChromaAnimationName:
			{
				const ParamsPlayChromaAnimationName& params = pendingCommand._mPlayChromaAnimationName;
				const char* path = params._mPath.c_str();

				if (_gForwardChromaEvents)
				{
					// default is ON, forward animation names to SetEventName
					string strPath = path;
					wstring eventName(strPath.begin(), strPath.end());
					_sLastResultSetEventName = RzChromaSDK::SetEventName(eventName.c_str());
				}

				int animationId = PluginGetAnimation(path);
				if (animationId < 0)
				{
					//LogError("ProcessPendingCommands: Animation not found! %s\r\n", path);
					break;
				}
				PluginPlayAnimationLoop(animationId, params._mLoop);
			}
			break;
			case PendingCommandType::Command_SetIdleAnimationName:
			{
				const ParamsSetIdleAnimationName& params = pendingCommand._mSetIdleAnimationName;
				const std::string& path = params._mPath;
				ImplSetIdleAnimationName(path.c_str());
			}
			break;
			case PendingCommandType::Command_SetEventName:
			{
				const ParamsSetEventName& params = pendingCommand._mSetEventName;
				const std::wstring& eventName = params._mName;
				_sLastResultSetEventName = RzChromaSDK::SetEventName(eventName.c_str());
			}
			break;
			case PendingCommandType::Command_StopAll:
			{
				const ParamsStopAll& params = pendingCommand._mStopAll;				
				ImplStopAnimationType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_ChromaLink);
				ImplStopAnimationType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_Headset);
				ImplStopAnimationType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keyboard);
				ImplStopAnimationType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keypad);
				ImplStopAnimationType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Mouse);
				ImplStopAnimationType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_Mousepad);
			}
			break;
			case PendingCommandType::Command_StopAnimationName:
			{
				const ParamsStopAnimationName& params = pendingCommand._mStopAnimationName;
				const char* path = params._mPath.c_str();

				int animationId = PluginGetAnimation(path);
				if (animationId < 0)
				{
					//LogError("ProcessPendingCommands: Animation not found! %s\r\n", path);
					break;
				}
				PluginStopAnimation(animationId);
			}
			break;
			case PendingCommandType::Command_StopAnimationType:
			{
				const ParamsStopAnimationType& params = pendingCommand._mStopAnimationType;
				int device = params._mDevice;
				int deviceType = params._mDeviceType;
				ImplStopAnimationType(deviceType, device);
			}
			break;
			case PendingCommandType::Command_UseForwardChromaEvents:
			{
				const ParamsUseForwardChromaEvents& params = pendingCommand._mUseForwardChromaEvents;
				_gForwardChromaEvents = params._mFlag;
			}
			break;
			case PendingCommandType::Command_UseIdleAnimations:
			{
				const ParamsUseIdleAnimations& params = pendingCommand._mUseIdleAnimations;
				bool flag = params._mFlag;
				ChromaSDKPlugin::GetInstance()->UseIdleAnimation(EChromaSDKDeviceEnum::DE_ChromaLink, flag);
				ChromaSDKPlugin::GetInstance()->UseIdleAnimation(EChromaSDKDeviceEnum::DE_Headset, flag);
				ChromaSDKPlugin::GetInstance()->UseIdleAnimation(EChromaSDKDeviceEnum::DE_Keyboard, flag);
				ChromaSDKPlugin::GetInstance()->UseIdleAnimation(EChromaSDKDeviceEnum::DE_Keypad, flag);
				ChromaSDKPlugin::GetInstance()->UseIdleAnimation(EChromaSDKDeviceEnum::DE_Mouse, flag);
				ChromaSDKPlugin::GetInstance()->UseIdleAnimation(EChromaSDKDeviceEnum::DE_Mousepad, flag);
			}
			break;
		}
	}
}

void ChromaThread::ChromaWorker()
{
	// get current time
	high_resolution_clock::time_point timer = high_resolution_clock::now();
	high_resolution_clock::time_point timerLast = high_resolution_clock::now();

	_sWaitForExit = true;

	while (_sWaitForExit)
	{
		// get current time
		timer = high_resolution_clock::now();

		// get time in seconds
		duration<double, milli> time_span = timer - timerLast;
		float deltaTime = (float)(time_span.count() / 1000.0f);
		timerLast = timer;

		ProcessAnimations(deltaTime);

		// process items from the worker
		ProcessPendingCommands();

		if (!_sWaitForExit)
		{
			break;
		}
			
		this_thread::sleep_for(chrono::milliseconds(1));
	}

	_sThread = nullptr;
}

void ChromaThread::Start()
{
	if (_sThread != nullptr)
	{
		return;
	}
	_sThread = new thread(&ChromaThread::ChromaWorker, this);

	// for debugging, log thread id
	/*
	stringstream ss;
	ss << _sThread->get_id();
	string strId = ss.str();
	ChromaLogger::printf("ChromaThread: %s\r\n", strId.c_str());
	*/

	_sThread->detach();
}

void ChromaThread::Stop()
{
	lock_guard<mutex> guard(_sMutex);

	_sWaitForExit = false;
	for (int i = 0; i < (int)EChromaSDKDeviceEnum::DE_MAX; ++i)
	{
		_sUseIdleAnimation[i] = false;
		_sIdleAnimation[i] = "";
	}
	_sAnimations.clear();

	if (_sInstance != nullptr)
	{
		delete _sInstance;
		_sInstance = nullptr;
	}
}

void ChromaThread::AddAnimation(AnimationBase* animation)
{
	lock_guard<mutex> guard(_sMutex);
	// Add animation if it's not found
	if (find(_sAnimations.begin(), _sAnimations.end(), animation) == _sAnimations.end())
	{
		_sAnimations.push_back(animation);
	}
}

void ChromaThread::RemoveAnimation(AnimationBase* animation)
{
	lock_guard<mutex> guard(_sMutex);
	if (animation != nullptr)
	{
		auto it = find(_sAnimations.begin(), _sAnimations.end(), animation);
		if (it != _sAnimations.end())
		{
			_sAnimations.erase(it);
		}
	}
}

void ChromaThread::DeleteAnimation(AnimationBase* animation)
{
	lock_guard<mutex> guard(_sMutex);
	if (animation != nullptr)
	{
		// remove animation if playing
		auto it = find(_sAnimations.begin(), _sAnimations.end(), animation);
		if (it != _sAnimations.end())
		{
			_sAnimations.erase(it);
		}
		// unload the animation if loaded
		animation->Unload();
		// clear memory
		animation->SetName("");
		animation->ClearFrames();
		//delete animation safely
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)animation;
			delete animation1D;
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)animation;
			delete animation2D;
		}
		break;
		}
	}
}

int ChromaThread::GetAnimationCount()
{
	lock_guard<mutex> guard(_sMutex);
	return (int)_sAnimations.size();
}

int ChromaThread::GetAnimationId(int index)
{
	lock_guard<mutex> guard(_sMutex);
	if (index < 0)
	{
		return -1;
	}
	if (index < (int)_sAnimations.size())
	{
		AnimationBase* animation = _sAnimations[index];
		if (animation != nullptr)
		{
			return GetAnimationIdFromInstance(animation);
		}
	}
	return -1;
}
