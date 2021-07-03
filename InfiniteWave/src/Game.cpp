#include "Game.h"
#include "Window.h"
#include "SplashScreen.h"
#include "SceneManager.h"
#include "SharedObject.h"
#include <SFML/Audio.hpp>

#include <ctime>

#include "AudioManager.h"

Game::Game(SharedObject& obj) : mObj(obj)
{
	RestartClock();
	srand(static_cast<unsigned int>(time(nullptr)));
	
	InitMusic();
	InitSFX();
}


void Game::RestartClock()
{
	mDeltaTime = mClock.restart().asSeconds();
}

void Game::Run()
{
	//Run game with SplashScreen as the first scene
	mObj.SceneManager->Run(SceneManager::Build<SplashScreen>(mObj, true));

	while (!mObj.Window->isDone())
	{
		//Window loop here
		mObj.SceneManager->NextScene(); //try to change the scene
		mObj.SceneManager->Update(mDeltaTime); //update current scene
		mObj.SceneManager->Draw(); //render current scene
		RestartClock(); //restart clock to get delta time
	}
}

void Game::InitSFX()
{
	mObj.AudioManager->AddSFX("button", "data/Audio/SFX/Button_9.wav");
	mObj.AudioManager->AddSFX("pistol_shoot", "data/Audio/SFX/pistol-shoot.wav");
	mObj.AudioManager->AddSFX("pistol_reload", "data/Audio/SFX/pistol-reload.wav");
	mObj.AudioManager->AddSFX("pistol_click", "data/Audio/SFX/pistol-click.wav");
	mObj.AudioManager->AddSFX("zombie_1", "data/Audio/SFX/zombie-alive1.wav");
	mObj.AudioManager->AddSFX("health_pickup", "data/Audio/SFX/health-pickup.wav");
}

void Game::InitMusic()
{
	mObj.AudioManager->AddMusic("Loading", "data/Audio/Backsound/backsound.wav", true);
	mObj.AudioManager->AddMusic("HeartBeat", "data/Audio/SFX/heartbeat.wav", true);
}

