#pragma once

class HandleInput
{
public:
	HandleInput(int key);
	int GetKey();
	bool WasPressed(const bool requireFocus);
	bool WasReleased(const bool requireFocus);
private:
	int _mKey;
	bool _mWasPressed;
};
