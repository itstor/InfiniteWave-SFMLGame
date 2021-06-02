#pragma once
#include <SFML/Graphics.hpp>
#include "SceneManager.h"

class BaseScene
{
	friend class SceneManager;
public:
	BaseScene(SceneManager* manager) :mManager(manager){}
	~BaseScene() = default;

	void ToggleScene();
	void Update(const sf::Time& deltaTime);
	void Draw();

	SceneManager* GetSceneManager();

private:
	SceneManager* mManager;
	bool mIsActive = false;
};

