#pragma once
#include <memory>
#include <stack>
#include "BaseScene.h"

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
	~SceneManager();

	void nextScene();
	void prevScene();
	void Update();
	void Draw();

	bool running() const;
	void quit();

	template <typename T>
	static std::unique_ptr<T> build(SceneManager& manager, sf::RenderWindow& window, bool replace = true);
};

template <typename T>
std::unique_ptr<T> SceneManager::build(SceneManager& manager, sf::RenderWindow& window, bool replace)
{
	return std::make_unique<T>(manager, window, replace);
}

