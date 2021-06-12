#pragma once
#include <memory>
#include <stack>
#include "BaseScene.h"

struct SharedObject;

namespace sf
{
	class RenderWindow;
}

class SceneManager
{
private:
	std::stack<std::unique_ptr<BaseScene>> mScene;

	bool mIsResume;

public:
	SceneManager();

	void run(std::unique_ptr<BaseScene> scene);
	void nextScene();
	void prevScene();
	void Update(float deltaTime);
	void Draw();

	template <typename T>
	static std::unique_ptr<T> build(SharedObject& obj, bool replace = true);
};

template <typename T>
std::unique_ptr<T> SceneManager::build(SharedObject& obj, bool replace)
{
	return std::make_unique<T>(obj, replace);
}