#pragma once

typedef vector<byte> keycombo;


string getControlContent(HWND hwnd, DWORD control_id);
bool isWindowFocusRust();

class KeyHelper;
extern KeyHelper keyHelper;


class KeyHelper
{
	bool vk_down[65535];
public:
	KeyHelper();
	bool isDown(WORD vk);
	void updateKeyState(WORD vk, bool isDown);
	bool isKeykomboDown(keycombo combo);
};