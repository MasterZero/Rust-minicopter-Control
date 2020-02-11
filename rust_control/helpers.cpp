#include "main.h"


KeyHelper keyHelper;

KeyHelper::KeyHelper()
{
	ZeroMemory(vk_down, sizeof(vk_down));
}

bool KeyHelper::isDown(WORD vk)
{
	return vk_down[vk];
}

void KeyHelper::updateKeyState(WORD vk, bool isDown)
{
	vk_down[vk] = isDown;
}

bool KeyHelper::isKeykomboDown(keycombo combo)
{
	const int iSize = combo.size();

	for (int i = 0; i < iSize; ++i)
	{
		if (!isDown(combo[i])) {
			return false;
		}
	}

	return true;
}



string getControlContent(HWND hwnd, DWORD control_id)
{
	DWORD iLen = GetWindowTextLength(GetDlgItem(hwnd, control_id)) + 1; // Room for '\0'
	PCHAR pstrText = new CHAR[iLen];
	if (pstrText) {
		GetDlgItemText(hwnd, control_id, pstrText, iLen);
	}

	string ret(pstrText);
	delete pstrText;
	return ret;
}

bool isWindowFocusRust()
{
	HWND foreignHWND = GetForegroundWindow();
	DWORD iLen = GetWindowTextLength(foreignHWND) + 1;
	PCHAR pstrText = new CHAR[iLen];
	GetWindowText(foreignHWND, pstrText, iLen);
	string windowName(pstrText);
	delete pstrText;
	return windowName == app.window_name;
}