#include "Input.h"

bool Input::currentStates[256];
bool Input::prevStates[256];

void Input::BeginUpdate()
{
	for (int i = 0; i < 256; i++) {
		prevStates[i] = currentStates[i];
		currentStates[i] = GetAsyncKeyState(i) & 0x8000;
	}
}

bool Input::IsKeyDownOnce(int keyCode)
{
	return currentStates[keyCode] && !prevStates[keyCode];
}

bool Input::IsKeyDown(int keyCode)
{
	return currentStates[keyCode];
}

bool Input::IsKeyUpOnce(int keyCode)
{
	return !currentStates[keyCode] && prevStates[keyCode];
}


