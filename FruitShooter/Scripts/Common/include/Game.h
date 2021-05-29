#pragma once
#ifndef GAME_H
#define GAME_H

#include "Window.h"

class Game
{
public:
	Game(const std::string& w_title, const sf::Vector2u& w_size, const sf::Image& w_icon);
	~Game();

	void HandleInput();
	void Update();
	void Render();

	Window* GetWindow();

	sf::Time GetElapsed();
	void RestartClock();

private:
	Window window;
	sf::Clock p_clock;
	sf::Time p_elapsed;
};

#endif