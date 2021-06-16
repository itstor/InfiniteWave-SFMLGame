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
	initObstacles();
}

GamePlay::~GamePlay()
{
	std::cout << "GamePlay Deleted" << std::endl;
}

void GamePlay::initObstacles()
{
	wall[0].Create(sf::Vector2f(300, 300), sf::Vector2f(100, 100));
	obstacleContainer.push_back(wall[0]);
	wall[1].Create(sf::Vector2f(500, 500), sf::Vector2f(100, 500));
	obstacleContainer.push_back(wall[1]);
	wall[2].Create(sf::Vector2f(500, 500), sf::Vector2f(500, 100));
	obstacleContainer.push_back(wall[2]);
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
		//case sf::Event::MouseButtonPressed: 
		case sf::Event::KeyPressed:
		{
			switch (event.key.code)
			{
				/*Only for non-simultaneous key
				Use if statement for simultaneous key*/
			case sf::Keyboard::R: player.Reload(); break;
			default: break;
			}
			break;
		}
		case sf::Event::MouseButtonPressed:
			{
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
					{
						if (player.Shoot())
						{
							bullet.setStartPos(sf::Vector2f(player.getPosition().x + 20, player.getPosition().y + 20));
							bullet.setDir(player.getDirVect());

							bulletContainer.emplace_back(bullet);
						}
					}
				default: break;
				}
			}
		default: break;
		}
	}

	//Update player face dir
	const sf::Vector2i mousePos = sf::Mouse::getPosition(*mWindow.GetRenderWindow());
	const sf::Vector2f worldMousePos = mWindow.GetRenderWindow()->mapPixelToCoords(mousePos);
	player.lookAt(worldMousePos);

	//Update player anim
	player.Update(deltaTime);
	
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

	player.updateAllowShoot(deltaTime);

	//all object collision check here
	//On Collision with obstacle or wall
	for (auto &obs: obstacleContainer)
	{
		player.checkCollision(obs);
		for (size_t i = 0; i < bulletContainer.size(); i++)
		{
			//Check id bullet collided with obstacle delete
			if (bulletContainer[i].on_collision(obs))
			{
				bulletContainer.erase(bulletContainer.begin() + i);
			}

			//Check if bullet out of radius delete
			else if (pow(bulletContainer[i].startPosition.x - bulletContainer[i].getPosition().x, 2) 
				+ pow(bulletContainer[i].startPosition.y - bulletContainer[i].getPosition().y, 2) 
				> pow(1500, 2))
			{
				bulletContainer.erase(bulletContainer.begin() + i);
			}

			//TODO Check if collided with zombie
		}
	}

	//Move everything here
	player.PlayerMove(); // Move Player

	for (auto &bul:bulletContainer) //move bullet
	{
		bul.Move(deltaTime);
	}
	
	//Zombie PathFinding

	//Thunder Random

	//Rain Update
}

void GamePlay::Draw()
{
	mWindow.BeginDraw();

	/*Draw everything here*/
	mWindow.Draw(*player.getFeetDraw());
	mWindow.Draw(*player.getDraw());
	
	for (auto &bul:bulletContainer)
	{
		mWindow.Draw(*bul.getDraw());
	}
	for (auto &obs:obstacleContainer)
	{
		mWindow.Draw(*obs.getCollider());
	}
	
	mWindow.EndDraw();
}

