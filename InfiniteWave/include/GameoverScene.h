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
	sf::RectangleShape fadeToBlack;
	sf::RectangleShape scoreMask;


	sf::Font pixelFont;
	sf::Text gameOverText;
	sf::Text scoreText;
	sf::Text newHighScoreText;
	sf::Text respawnText;
	sf::Text backToMainText;

	float elapsedTime = 0.0f;
};

