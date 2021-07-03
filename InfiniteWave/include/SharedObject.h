#pragma once

class Window;
class SceneManager;
class AudioManager;

struct SharedObject
{
	SharedObject() :Window(nullptr), SceneManager(nullptr), AudioManager(nullptr){}
	Window* Window;
	SceneManager* SceneManager;
	AudioManager* AudioManager;
};