#pragma once
#include <Windows.h>
#include <vector>

class GameEngine;
class Input 
{
private:
	static bool currentStates[256];
	static bool prevStates[256];

	static void BeginUpdate();

	friend GameEngine;

public:
	static bool IsKeyDownOnce(int keyCode);
	static bool IsKeyDown(int keyCode);
	static bool IsKeyUpOnce(int keyCode);
};