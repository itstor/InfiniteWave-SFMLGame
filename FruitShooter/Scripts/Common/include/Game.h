#pragma once
#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "SharedObject.h"

class Game
{
public:
	Game(const std::string& winTitle, const sf::Vector2u& winSize, const sf::Image& winIcon);
	~Game();

	void Run();
	void Render();

	Window* GetWindow();

	float GetDeltaTime();
	void RestartClock();

private:
	Window mWindow;
	sf::Clock mClock;
	float mDeltaTime;
};

#endif