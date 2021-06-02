#pragma once
#include <memory>
#include <stack>
#include "BaseScene.h"

class Window;

namespace sf
{
	class RenderWindow;
}

class SceneManager
{
private:
	std::stack<std::unique_ptr<BaseScene>> mScene;

	bool mIsResume;
	bool mIsRunning;

public:
	SceneManager();

	void run(std::unique_ptr<BaseScene> scene);
	void nextScene();
	void prevScene();
	void Update();
	void Draw();

	bool running() const;
	void quit();

	template <typename T>
	static std::unique_ptr<T> build(SceneManager& manager, Window& window, bool replace = true);
};

template <typename T>
std::unique_ptr<T> SceneManager::build(SceneManager& manager, Window& window, bool replace)
{
	return std::make_unique<T>(manager, window, replace);
}

