#pragma once

#include <windows.h>

namespace MouseController
{

	BOOLEAN WINAPI Init();
	BOOLEAN WINAPI Uninit();

	BOOLEAN WINAPI NtUserSendInput(UINT cInputs, LPINPUT pInputs, int cbSize);
	UINT WINAPI NtUserGetAsyncKeyState(UINT Key);

	BOOLEAN WINAPI Move_Mouse(int X, int Y);
	UINT WINAPI GetAsyncKeyState(UINT Key);
}
