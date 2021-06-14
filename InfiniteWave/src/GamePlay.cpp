#include "GamePlay.h"

//Related Scene
#include "SplashScreen.h"

//Required Library
#include <iostream>
#include <memory>

#include "Window.h"
#include "SceneManager.h"
#include "AudioManager.h"

GamePlay::GamePlay(SharedObject& obj, bool replace) :BaseScene(obj, replace)
{
#ifdef _DEBUG
	std::cout << "GamePlay Created" << std::endl;
#endif
	//TEST
	wall.Create(sf::Vector2f(300, 300), sf::Vector2f(100, 100));
	obstacle.push_back(wall);
	wall2.Create(sf::Vector2f(500, 500), sf::Vector2f(100, 500));
	obstacle.push_back(wall2);
	player.getDraw()->setSize(sf::Vector2f(50, 50));
	player.getDraw()->setOrigin(25, 25);
	player.getDraw()->setFillColor(sf::Color::Red);
}

GamePlay::~GamePlay()
{
	std::cout << "GamePlay Deleted" << std::endl;
}

void GamePlay::initButton()
{
	//Initialize button here
}

void GamePlay::initBg()
{
	//Initialize background here
}

void GamePlay::Pause()
{
	std::cout << "GamePlay Paused" << std::endl;
}

void GamePlay::Resume()
{
	std::cout << "GamePlay Resume" << std::endl;
}

void GamePlay::Update(float deltaTime)
{
	for (auto event = sf::Event{}; mWindow.GetRenderWindow()->pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::Closed: mWindow.Destroy(); break;
		case sf::Event::KeyPressed:
		{
			switch (event.key.code)
			{
				/*Only for non-simultaneous key
				Use if statement for simultaneous key*/
			default: break;
			}
			break;
		}
		default: break;
		}
	}

	//Player face direction update
	mousePos = sf::Mouse::getPosition(*mWindow.GetRenderWindow());
	worldMousePos = mWindow.GetRenderWindow()->mapPixelToCoords(mousePos);
	player.lookAt(worldMousePos);

	//Player keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		player.Move(sf::Vector2i(0, -1), deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player.Move(sf::Vector2i(-1, 0), deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		player.Move(sf::Vector2i(0, 1), deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player.Move(sf::Vector2i(1, 0), deltaTime);
	}

	//On Collision with obstacle or wall
	for (auto &obs: obstacle)
	{
		player.checkCollision(obs, deltaTime);

	}

	player.PlayerMove();
	
	//Zombie PathFinding

	//Thunder Random

	//Rain Update
}

void GamePlay::Draw()
{
	mWindow.BeginDraw();

	/*Draw everything here*/
	mWindow.Draw(*player.getDraw());
	mWindow.Draw(*wall.getCollider());
	mWindow.Draw(*wall2.getCollider());

	mWindow.EndDraw();
}

