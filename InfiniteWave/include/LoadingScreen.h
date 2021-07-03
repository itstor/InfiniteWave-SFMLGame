#pragma once
#ifndef LOADING_SCENE_H_
#define LOADING_SCENE_H_

#include <SFML/Graphics.hpp>

#include "Button.h"
#include "BaseScene.h"
#include "SpriteAnimation.h"

class SceneManager;


class LoadingScreen final : public BaseScene
{
public:
	LoadingScreen(SharedObject& shared_object, bool replace = true);
	~LoadingScreen() override;

	void Pause() override;
	void Draw() override;
	void Resume() override;
	void Update(float delta_time) override;

private:
	void InitBackground();
	void InitButton();


	//Define scene component here
	sf::Font mPixelFont;
	sf::Text mLoadingText;
	sf::Text mHowToText;
	sf::Text mMoveText;
	sf::Text mReloadText;
	sf::Text mAimText;

	std::vector<sf::RectangleShape> mLoadingBars;
	
	sf::RectangleShape mLoadingBarOutline;
	sf::RectangleShape mSingleLoadingBar;
	sf::RectangleShape mKeyWRect;
	sf::RectangleShape mKeyARect;
	sf::RectangleShape mKeySRect;
	sf::RectangleShape mKeyDRect;
	sf::RectangleShape mKeyRRect;
	sf::RectangleShape mMouseRect;

	sf::Texture mKeyWTex;
	sf::Texture mKeyATex;
	sf::Texture mKeySTex;
	sf::Texture mKeyDTex;
	sf::Texture mKeyRTex;
	sf::Texture mMouseTex;

	SpriteAnimation mKeyWAnim;
	SpriteAnimation mKeyAAnim;
	SpriteAnimation mKeySAnim;
	SpriteAnimation mKeyDAnim;
	SpriteAnimation mKeyRAnim;
	SpriteAnimation mMouseAnim;
};

#endif