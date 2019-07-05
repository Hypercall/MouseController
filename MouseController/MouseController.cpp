#include "MouseController.hpp"

namespace MouseController
{
	BYTE NtUserSendInput_Bytes[30];

	// Call this once
	BOOLEAN WINAPI Init()
	{
		// windows 8.1 / windows 10
		LPVOID NtUserSendInput_Addr = GetProcAddress(GetModuleHandle("win32u"), "NtUserSendInput");
		if (!NtUserSendInput_Addr)
		{
			NtUserSendInput_Addr = GetProcAddress(GetModuleHandle("user32"), "NtUserSendInput");
			if (!NtUserSendInput_Addr)
			{
				// Windows 7 or lower detected
				NtUserSendInput_Addr = GetProcAddress(GetModuleHandle("user32"), "SendInput");
				if (!NtUserSendInput_Addr)
					return FALSE;
			}
		}
		memcpy(NtUserSendInput_Bytes, NtUserSendInput_Addr, 30);
		return TRUE;
	}

	// Call this when you leave application or don't need it anymore
	BOOLEAN WINAPI Uninit()
	{
		ZeroMemory(NtUserSendInput_Bytes, 30);
		return TRUE;
	}

	/* This function spoofs the function. It prevents BattlEye from scanning it! */
	BOOLEAN WINAPI Sendinput(UINT cInputs, LPINPUT pInputs, int cbSize)
	{
		LPVOID NtUserSendInput_Spoof = VirtualAlloc(0, 0x1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE); // allocate space for syscall
		if (!NtUserSendInput_Spoof)
			return FALSE;
		memcpy(NtUserSendInput_Spoof, NtUserSendInput_Bytes, 30); // copy syscall
		NTSTATUS Result = reinterpret_cast<NTSTATUS(NTAPI*)(UINT, LPINPUT, int)>(NtUserSendInput_Spoof)(cInputs, pInputs, cbSize); // calling spoofed function
		ZeroMemory(NtUserSendInput_Spoof, 0x1000); // clean address
		VirtualFree(NtUserSendInput_Spoof, 0, MEM_RELEASE); // free it
		return (Result > 0); // return the status
	}

	/* This function moves the mouse using the syscall*/
	BOOLEAN WINAPI Move_Mouse(int X, int Y)
	{
		INPUT input;
		input.type = INPUT_MOUSE;
		input.mi.mouseData = 0;
		input.mi.time = 0;
		input.mi.dx = X * (65536 / GetSystemMetrics(SM_CXSCREEN));
		input.mi.dy = Y * (65536 / GetSystemMetrics(SM_CYSCREEN));
		input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_ABSOLUTE;
		return Sendinput(1, &input, sizeof(input));
	}
}