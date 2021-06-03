#include "SplashScreen.h"

#include <iostream>
#include <memory>

#include "MainMenu.h"
#include "SceneManager.h"

MainMenu::MainMenu(SceneManager& manager, Window& window, bool replace):BaseScene(manager, window, replace)
{
#ifdef _DEBUG
	std::cout << "MainMenu Created" << std::endl;
#endif
	winSize = mWindow.GetWindowSize();
	initBg();
	initButton();
}

void MainMenu::initButton()
{
	btnPlay.Setup("Assets/Texture/GUI/Buttons/Start_BTN.png", 
		"Assets/Texture/GUI/Buttons/Start_BTN_ACT.png", 
		"Assets/Texture/GUI/Buttons/Start_BTN_HOV.png", 
		1.5f, sf::Vector2f(winSize.x/2, winSize.y-250));
	btnContainer.push_back(&btnPlay);

	btnExit.Setup("Assets/Texture/GUI/Buttons/Close_BTN.png",
		"Assets/Texture/GUI/Buttons/Close_BTN_HOV.png",
		"Assets/Texture/GUI/Buttons/Close_BTN_ACT.png",
		0.4f, sf::Vector2f(winSize.x - 100, 100));
	btnContainer.push_back(&btnExit);

	btnSetting.Setup("Assets/Texture/GUI/Buttons/Settings_BTN.png",
		"Assets/Texture/GUI/Buttons/Settings_BTN_HOV.png",
		"Assets/Texture/GUI/Buttons/Settings_BTN_ACT.png",
		0.4f, sf::Vector2f(100, 100));
	btnContainer.push_back(&btnSetting);
}


void MainMenu::initBg()
{
	rect.setSize(sf::Vector2f(961, 107));
	rect.setScale(1.5, 1.5);
	title.loadFromFile("Assets/Texture/GUI/title.png");
	title.setSmooth(true);
	rect.setTexture(&title);
	rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
	rect.setPosition(static_cast<float>(mWindow.GetWindowSize().x) / 2, static_cast<float>(mWindow.GetWindowSize().y) / 5);

	menuBgTex.loadFromFile("Assets/Texture/GUI/backgroundn.png");
	menuBgSpi.setTexture(menuBgTex);
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
					mNext = SceneManager::build<SplashScreen>(mManager, mWindow, true);
					break;
				case sf::Keyboard::Escape: mManager.quit(); break;
				case sf::Keyboard::BackSpace: mManager.prevScene(); break;
				default: break;
				}
				break;
			}
		default: break;
		}
	}
	mousePos = sf::Mouse::getPosition(*mWindow.GetRenderWindow());
	for (auto btn : btnContainer)
		btn->Update(sf::Vector2f(mousePos.x, mousePos.y));

	if (btnExit.isPressed())
	{
		mManager.quit();
	}
}

void MainMenu::Draw()
{
	mWindow.BeginDraw();

	mWindow.Draw(menuBgSpi);

	mWindow.Draw(rect);

	for (auto btn : btnContainer)
		mWindow.Draw(*btn->getDraw());

	mWindow.EndDraw();
}

