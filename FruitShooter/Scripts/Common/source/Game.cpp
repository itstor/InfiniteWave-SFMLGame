#include "Game.h"

Game::Game(const std::string& winTitle, const sf::Vector2u& winSize, const sf::Image& winIcon): mWindow(winTitle, winSize, winIcon)
{
	SharedObject shared;
	shared.mWindow = &mWindow;
	RestartClock();
	srand(time(nullptr));
}

Game::~Game() {}

float Game::GetElapsed()
{
	return mDeltaTime;
}

void Game::RestartClock()
{
	mDeltaTime = mClock.restart().asMilliseconds();
}

Window* Game::GetWindow()
{
	return &mWindow;
}

void Game::Run()
{
	
}

void Game::Render()
{
	mWindow.BeginDraw();
	//window.Draw(NULL);
	mWindow.EndDraw();
}





