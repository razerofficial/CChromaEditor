#pragma once

class HandleInput
{
public:
	HandleInput(int key);
	int GetKey();
	bool WasReleased();
private:
	int _mKey;
	bool _mWasPressed;
};
