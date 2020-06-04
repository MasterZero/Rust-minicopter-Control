#include "main.h"




App app;
HHOOK keyboardHook;




int onKeyPress(WORD vk, bool isModified, bool keydown)
{

	if (isModified) {
		return 0;
	}

	keyHelper.updateKeyState(vk, keydown);

	int ret = 0;

	if (ret = copter.onKeyPress(vk, isModified, keydown)) {
		return ret;
	}

	return 0;
}



LRESULT CALLBACK LowLevelKeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT* details = (KBDLLHOOKSTRUCT*)lParam;
	INPUT ip;

	if (code == HC_ACTION && (wParam == WM_KEYDOWN || wParam == WM_KEYUP))
	{
		bool isKeyModified = details->flags & 1;
		int ret = onKeyPress(details->vkCode, isKeyModified, wParam == WM_KEYDOWN);

		if (ret) {
			return ret;
		}
	}
	return CallNextHookEx(keyboardHook, code, wParam, lParam);
}

void mouse_move_proc()
{
	copter.mouseThread();
}



int
#if !defined(_MAC)
#if defined(_M_CEE_PURE)
__clrcall
#else
WINAPI
#endif
#else
CALLBACK
#endif
WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	app.hInstance = hInstance;

	keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hInstance, NULL);

	thread mouseThread(mouse_move_proc);

	DialogBox(app.hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), nullptr, &dialogCopterProc);
	app.exit = true;
	mouseThread.join();

	return 0;
}



App::App()
{
	window_name = "";
	copterHwnd = 0;
	hInstance = 0;
	exit = false;
}
