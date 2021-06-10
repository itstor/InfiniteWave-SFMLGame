#pragma once

#include <iostream>

class Window;
class SceneManager;
class AudioManager;

struct SharedObject
{
	SharedObject() :Window(nullptr), SceneManager(nullptr), AudioManager(nullptr)
	{
#ifdef _DEBUG
		std::cout << "Created Shared Object\n";
#endif
	}
	Window* Window;
	SceneManager* SceneManager;
	AudioManager* AudioManager;
};