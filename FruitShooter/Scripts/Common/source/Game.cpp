#include "Game.h"

Game::Game(const std::string& winTitle, const sf::Vector2u& winSize, const sf::Image& winIcon): mWindow(winTitle, winSize, winIcon)
{
	SharedObject shared;
	shared.mWindow = &mWindow;
	RestartClock();
	srand(time(nullptr));
}

Game::~Game() {}

sf::Time Game::GetElapsed()
{
	return mElapsed;
}

void Game::RestartClock()
{
	mElapsed = mClock.restart();
}

Window* Game::GetWindow()
{
	return &mWindow;
}

void Game::HandleInput()
{
	//TODO
}

void Game::Update()
{
	mWindow.Update();
}

void Game::Render()
{
	mWindow.BeginDraw();
	//window.Draw(NULL);
	mWindow.EndDraw();
}





