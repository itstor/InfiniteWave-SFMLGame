#pragma once
#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "SceneManager.h"

class Game
{
public:
	Game(const std::string& winTitle, const sf::Vector2u& winSize, const sf::Image& winIcon);
	~Game();

	//void Render();

	Window* GetWindow();
	SceneManager* GetSceneManager();

	unsigned int DeltaTime() const;
	void RestartClock();

private:
	SceneManager mManager;
	Window mWindow;
	sf::Clock mClock;
	unsigned int mDeltaTime;
};

#endif