#include "Game.h"

Game::Game(const std::string& w_title, const sf::Vector2u& w_size, const sf::Image& w_icon): window(w_title, w_size, w_icon)
{
	RestartClock();
	srand(time(nullptr));
}

Game::~Game() {}

sf::Time Game::GetElapsed()
{
	return p_elapsed;
}

void Game::RestartClock()
{
	p_elapsed = p_clock.restart();
}

Window* Game::GetWindow()
{
	return &window;
}

void Game::HandleInput()
{
	//TODO
}

void Game::Update()
{
	window.Update();
}

void Game::Render()
{
	window.BeginDraw();
	//window.Draw(NULL);
	window.EndDraw();
}





