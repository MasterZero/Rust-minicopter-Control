#pragma once


class Minicopter;

extern Minicopter copter;

INT_PTR CALLBACK dialogCopterProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM laparam);

class Minicopter
{
	bool active;
	int multiplier;
	int timeout;
	keycombo activationCombo;
public:



	struct {
		bool up;
		bool down;
		bool left;
		bool right;

	} move;

	Minicopter();
	bool isActive();
	void activate();
	void deactivate();
	int onKeyPress(WORD vk, bool isModified, bool keydown);
	void mouseThread();
	void updateControls();
};
