#include "HandleInput.h"

#define WIN32_LEAN_AND_MEAN
#include "Windows.h"

HandleInput::HandleInput(int key)
{
	_mKey = key;
	_mWasPressed = false;
}
int HandleInput::GetKey()
{
	return _mKey;
}
bool HandleInput::WasReleased()
{
	if (GetConsoleWindow() != GetForegroundWindow())
	{
		return false;
	}
	if (GetAsyncKeyState(_mKey) != 0)
	{
		_mWasPressed = true;
	}
	else if (_mWasPressed)
	{
		_mWasPressed = false;
		return true;
	}
	return false;
}
