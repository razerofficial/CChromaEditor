#pragma once

class HandleInput
{
public:
	HandleInput(int key);
	int GetKey();
	bool WasPressed();
	bool WasReleased();
private:
	int _mKey;
	bool _mWasPressed;
};
