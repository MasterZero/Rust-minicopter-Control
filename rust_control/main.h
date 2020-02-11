#pragma once
#include <Windows.h>
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>

using namespace std;

#include "resource.h"
#include "VK_controls.h"
#include "helpers.h"
#include "minicopter.h"




class App;
extern App app;


class App
{
public:
	HWND copterHwnd;
	string window_name;
	HINSTANCE hInstance;
	bool exit;
	App();
};

