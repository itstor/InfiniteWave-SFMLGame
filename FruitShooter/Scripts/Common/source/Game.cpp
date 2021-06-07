#include "Game.h"
#include "SharedObject.h"

Game::Game(const std::string& winTitle, const sf::Vector2u& winSize, const sf::Image& winIcon): mWindow(winTitle, winSize, winIcon)
{
	//Pack common object
	SharedObject obj; 

	obj.SceneManager = &mManager;
	obj.AudioManager = &mAudio;
	obj.Window = &mWindow;
	
	RestartClock();
	srand(static_cast<unsigned int>(time(nullptr)));
}

Game::~Game() = default;

unsigned int Game::DeltaTime() const
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

SceneManager* Game::GetSceneManager()
{
	return &mManager;
}