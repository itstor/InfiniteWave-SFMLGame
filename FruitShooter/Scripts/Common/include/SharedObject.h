#pragma once

#include "Window.h"

struct SharedObject
{
	SharedObject() :mWindow(nullptr){}
	Window* mWindow;
};