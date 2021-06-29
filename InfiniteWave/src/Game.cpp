#include "Game.h"
#include "Window.h"
#include "SplashScreen.h"
#include "SceneManager.h"
#include "SharedObject.h"
#include <SFML/Audio.hpp>

#include <ctime>

#include "AudioManager.h"

Game::Game(SharedObject& obj) : obj(obj)
{
	RestartClock();
	srand(static_cast<unsigned int>(time(nullptr)));
	
	initMusic();
	initSFX();
}

Game::~Game() = default;

void Game::RestartClock()
{
	mDeltaTime = mClock.restart().asSeconds();
}

void Game::run()
{
	//Run game with SplashScreen as the first scene
	obj.SceneManager->run(SceneManager::build<SplashScreen>(obj, true));

	while (!obj.Window->isDone())
	{
		//Window loop here
		obj.SceneManager->nextScene(); //try to change the scene
		obj.SceneManager->Update(mDeltaTime); //update current scene
		obj.SceneManager->Draw(); //render current scene
		RestartClock(); //restart clock to get delta time
	}
}

void Game::initSFX()
{
	obj.AudioManager->addSFX("button", "data/Audio/SFX/Button_9.wav");
	obj.AudioManager->addSFX("pistol_shoot", "data/Audio/SFX/pistol-shoot.wav");
	obj.AudioManager->addSFX("pistol_reload", "data/Audio/SFX/pistol-reload.wav");
	obj.AudioManager->addSFX("pistol_click", "data/Audio/SFX/pistol-click.wav");
	obj.AudioManager->addSFX("zombie_1", "data/Audio/SFX/zombie-alive1.wav");
}

void Game::initMusic()
{
	obj.AudioManager->addMusic("Loading", "data/Audio/Backsound/backsound.wav", true);
}

