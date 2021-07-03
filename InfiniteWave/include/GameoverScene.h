#pragma once
#ifndef GAMEOVER_SCENE_H_
#define GAMEOVER_SCENE_H_

#include <SFML/Graphics.hpp>

#include "AnimationManager.h"
#include "BaseScene.h"

class SceneManager;


class GameoverScene final : public BaseScene
{
public:
	GameoverScene(SharedObject& shared_object, bool replace = true);
	~GameoverScene() override;

	void Pause() override;
	void Draw() override;
	void Resume() override;
	void Update(float delta_time) override;

private:
	void InitBackground();
	void InitButton();

	float mElapsedTime = 0.0f;
	
	//Define scene component here
	AnimationManager mAnimManager;

	sf::RectangleShape mFadeToBlackOverlay;
	sf::Font mPixelFont;
	sf::Text mGameOverText;
	sf::Text mScoreText;
	sf::Text mNewHighScoreText;
	sf::Text mRespawnText;
	sf::Text mBackToMainText;
};

#endif