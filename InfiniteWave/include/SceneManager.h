#pragma once
#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

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
public:
	SceneManager();

	void Run(std::unique_ptr<BaseScene> scene);
	void NextScene();
	void PrevScene();
	void Update(float delta_time);
	void Draw();

	template <typename T>
	static std::unique_ptr<T> Build(SharedObject& obj, bool replace = true);

private:
	bool mIsResume;
	
	std::stack<std::unique_ptr<BaseScene>> mScene;
};

template <typename T>
std::unique_ptr<T> SceneManager::Build(SharedObject& obj, bool replace)
{
	return std::make_unique<T>(obj, replace);
}

#endif