#include "Game.h"
#include "Window.h"
#include "SplashScreen.h"
#include "SceneManager.h"
#include "SharedObject.h"

#include <ctime>

Game::Game(SharedObject& obj)
{
	this->obj = obj;
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

void Game::run()
{
	//Run game with SplashScreen as the first scene
	obj.SceneManager->run(SceneManager::build<SplashScreen>(obj, true));

	while (!obj.Window->isDone())
	{
		//Window loop here
		obj.SceneManager->nextScene(); //try to change the scene
		obj.SceneManager->Update(); //update current scene
		obj.SceneManager->Draw(); //render current scene
		RestartClock(); //restart clock to randomize the random function
	}
}