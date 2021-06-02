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

	void HandleInput();
	void Update();
	void Render();

	Window* GetWindow();

	sf::Time GetElapsed();
	void RestartClock();

private:
	Window mWindow;
	sf::Clock mClock;
	sf::Time mElapsed;
};

#endif