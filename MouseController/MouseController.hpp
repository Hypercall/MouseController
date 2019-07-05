#pragma once

#include <windows.h>

namespace MouseController
{

	BOOLEAN WINAPI Init();
	BOOLEAN WINAPI Uninit();

	BOOLEAN WINAPI Sendinput(UINT cInputs, LPINPUT pInputs, int cbSize);

	BOOLEAN WINAPI Move_Mouse(int X, int Y);
}