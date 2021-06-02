#include "SplashScreen.h"

#include <iostream>
#include <memory>

#include "MainMenu.h"
#include "SceneManager.h"

MainMenu::MainMenu(SceneManager& manager, Window& window, bool replace):BaseScene(manager, window, replace)
{
#ifdef _DEBUG
	std::cout << "SplashScreen Created" << std::endl;
#endif
	rect.setSize(sf::Vector2f(50.0f, 50.0f));
	rect.setFillColor(sf::Color::Yellow);
}

void MainMenu::Pause()
{
	std::cout << "MainMenu Paused" << std::endl;
}

void MainMenu::Resume()
{
	std::cout << "MainMenu Resume" << std::endl;
}

void MainMenu::Update()
{
	for (auto event = sf::Event{}; mWindow.GetRenderWindow()->pollEvent(event);)
	{
		switch(event.type)
		{
		case sf::Event::Closed: mManager.quit(); break;
		case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Space:
					mNext = SceneManager::build<MainMenu>(mManager, mWindow, true);
					break;
				case sf::Keyboard::Escape: mManager.quit(); break;
				default: break;
				}
				break;
			}
		default: break;
		}
	}
}

void MainMenu::Draw()
{
	mWindow.BeginDraw();

	mWindow.Draw(rect);

	mWindow.EndDraw();
}

