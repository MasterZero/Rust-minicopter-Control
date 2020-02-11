#include "main.h"



Minicopter copter;


const char * defaultTimeout = "1";
const char * defaultMultiplier = "5";
const char * defaultWindowName = "Rust";




INT_PTR CALLBACK dialogCopterProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM laparam)
{

	if (msg == WM_CLOSE || msg == WM_DESTROY)
	{
		EndDialog(hwnd, 0);
		return 0;
	}

	if (msg == WM_INITDIALOG)
	{
		app.copterHwnd = hwnd;
		copter.updateControls();

		SetDlgItemText(app.copterHwnd, IDC_MULTIPLIER, defaultMultiplier);
		SetDlgItemText(app.copterHwnd, IDC_TIMEOUT, defaultTimeout);
		SetDlgItemText(app.copterHwnd, IDC_WINDOW_NAME, defaultWindowName);
		return 0;
	}


	if (msg == WM_COMMAND)
	{
		if (HIWORD(wparam) == EN_CHANGE)
		{
			WORD control_id = LOWORD(wparam);
			if (control_id == IDC_MULTIPLIER || control_id == IDC_WINDOW_NAME) {
				copter.updateControls();
				return 0;
			}
		}
	}


	return 0;
}






void Minicopter::updateControls()
{
	string sMultiplier = getControlContent(app.copterHwnd, IDC_MULTIPLIER);
	string sTimeout = getControlContent(app.copterHwnd, IDC_TIMEOUT);
	app.window_name = getControlContent(app.copterHwnd, IDC_WINDOW_NAME);

	int iTimeout = atoi(sTimeout.c_str());
	int iMultiplier = atoi(sMultiplier.c_str());

	if (iTimeout < 1 || iTimeout > 1000) {
		iTimeout = 1;
	}

	if (iMultiplier < 1) {
		iMultiplier = 1;
	}


	timeout = iTimeout;
	multiplier = iMultiplier;


	const char * active_text = "status: active";
	const char * deactive_text = "status: deactive";
	const char * text = deactive_text;

	if (copter.isActive()) {
		text = active_text;
	}

	SetDlgItemText(app.copterHwnd, IDC_STATUS, text);
}





Minicopter::Minicopter()
{
	active = false;
	multiplier = 1;
	timeout = 1;
	activationCombo.push_back(KEY_U);
	activationCombo.push_back(KEY_LCONTROL);
	move = {};
}

bool Minicopter::isActive()
{
	return active;
}

void Minicopter::activate()
{
	active = true;
	updateControls();
}

void Minicopter::deactivate()
{
	active = false;
	move.down = move.up = move.left = move.right = false;
	updateControls();
}

void Minicopter::mouseThread()
{
	for (; !app.exit; Sleep(timeout)) {

		if (!isActive()) {
			continue;
		}

		if (move.left) {
			mouse_event(MOUSEEVENTF_MOVE, -1 * multiplier, 0, 0, 0);
		}

		if (move.right) {
			mouse_event(MOUSEEVENTF_MOVE, 1 * multiplier, 0, 0, 0);
		}

		if (move.up) {
			mouse_event(MOUSEEVENTF_MOVE, 0, -1 * multiplier, 0, 0);
		}

		if (move.down) {
			mouse_event(MOUSEEVENTF_MOVE, 0, 1 * multiplier, 0, 0);
		}

	}
}


int Minicopter::onKeyPress(WORD vk, bool isModified, bool keydown)
{
	if (!isActive()) {
		
		if (keyHelper.isKeykomboDown(activationCombo) &&
			isWindowFocusRust()) {
			activate();
		}
		return 0;
	}

	if (vk == VK_SPACE ||
		!isWindowFocusRust()) {
		deactivate();
		return 0;
	}
	

	if (vk == KEY_A) {
		move.left = keydown;
		return 1;
	}

	if (vk == KEY_D) {
		move.right = keydown;
		return 1;
	}

	if (vk == KEY_NUM8) {
		move.up = keydown;
		return 1;
	}

	if (vk == KEY_NUM5) {
		move.down = keydown;
		return 1;
	}

	if (vk == KEY_NUM4) {
		keybd_event(KEY_A, NULL, KEYEVENTF_EXTENDEDKEY | (keydown ? 0 : KEYEVENTF_KEYUP), NULL);
		return 1;
	}

	if (vk == KEY_NUM6) {
		keybd_event(KEY_D, NULL, KEYEVENTF_EXTENDEDKEY | (keydown ? 0 : KEYEVENTF_KEYUP), NULL);
		return 1;
	}

	return 0;
}