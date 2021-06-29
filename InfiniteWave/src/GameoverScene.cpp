#include "GameoverScene.h"

//Related Scene
#include "SplashScreen.h"

//Required Library
#include <iostream>

#include "Window.h"

GameoverScene::GameoverScene(SharedObject& obj, bool replace) :BaseScene(obj, replace)
{
#ifdef _DEBUG
	std::cout << "GameoverScene Created" << std::endl;
#endif
	rectangle.setSize({20.0f, 20.0f});
	rectangle.setPosition(50.0f, 50.0f);
	rectangle.setFillColor(sf::Color::Blue);
}

GameoverScene::~GameoverScene()
{
	std::cout << "GameoverScene Deleted" << std::endl;
}

void GameoverScene::initButton()
{
	//Initialize button here
}

void GameoverScene::initBg()
{
	//Initialize background here
}

void GameoverScene::Pause()
{
	std::cout << "GameoverScene Paused" << std::endl;
}

void GameoverScene::Resume()
{
	std::cout << "GameoverScene Resume" << std::endl;
}

void GameoverScene::Update(float deltaTime)
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
	if (once)
	{
		mAnimManager.playAnimation(AnimType::ZOOM, { 0.0f,0.0f }, { 20.0f,0.0f }, 2.0f, rectangle, true, 2.0f);
		once = false;
	}
	mAnimManager.Update(deltaTime);
	
}

void GameoverScene::Draw()
{
	mWindow.BeginDraw();

	/*Draw everything here*/
	mWindow.Draw(rectangle);

	mWindow.EndDraw();
}

