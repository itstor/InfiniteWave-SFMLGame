#include "Game.h"
//#include "Music.h"

Game::Game(const std::string& winTitle, const sf::Vector2u& winSize, const sf::Image& winIcon): mWindow(winTitle, winSize, winIcon)
{
	music.openFromFile("Assets/Audio/Backsound/loading.wav");
	music.setLoop(true);
	music.play();
	RestartClock();
	srand(time(nullptr));
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


//void Game::Render()
//{
//	mWindow.BeginDraw();
//	//window.Draw(NULL);
//	mWindow.EndDraw();
//}





