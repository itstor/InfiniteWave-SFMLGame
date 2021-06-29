#pragma once

#include <SFML/Graphics.hpp>

#include "AnimationManager.h"
#include "BaseScene.h"
#include "Button.h" //GUI Optional

class SceneManager;

class GameoverScene final : public BaseScene
{
public:
	GameoverScene(SharedObject& obj, bool replace = true);
	~GameoverScene() override;

	void Pause() override;
	void Draw() override;
	void Resume() override;
	void Update(float deltaTime) override;

	void initBg();
	void initButton();

private:
	//Define scene component here
	AnimationManager mAnimManager;
	bool once = true;
	sf::RectangleShape rectangle;
};

