#include "SplashScreen.h"
#include "MainMenu.h"
#include "GamePlay.h"

#include <iostream>
#include <memory>

#include "Window.h"
#include "SceneManager.h"
#include "AudioManager.h"
#include "LoadingScreen.h"
#include "SettingScene.h"


MainMenu::MainMenu(SharedObject& obj, bool replace) :BaseScene(obj, replace)
{
#ifdef _DEBUG
	std::cout << "MainMenu Created" << std::endl;
#endif
	initBg();
	initButton();
}

MainMenu::~MainMenu()
{
	std::cout << "MainMenu Deleted" << std::endl;
}

void MainMenu::initButton()
{
	btnPlay.Setup("Assets/Texture/GUI/Buttons/Start_BTN.png",
	              "Assets/Texture/GUI/Buttons/Start_BTN_HOV.png",
	              "Assets/Texture/GUI/Buttons/Start_BTN_ACT.png",
	              1.0f, sf::Vector2f(204.47f,499.09f));
	btnContainer.push_back(&btnPlay);

	btnSetting.Setup("Assets/Texture/GUI/Buttons/Settings_BTN.png",
	                 "Assets/Texture/GUI/Buttons/Settings_BTN_HOV.png",
	                 "Assets/Texture/GUI/Buttons/Settings_BTN_ACT.png",
	                 1.0f, sf::Vector2f(204.47f, 579.9f));
	btnContainer.push_back(&btnSetting);

	btnCredit.Setup("Assets/Texture/GUI/Buttons/Credit_BTN.png",
	                 "Assets/Texture/GUI/Buttons/Credit_BTN_HOV.png",
	                 "Assets/Texture/GUI/Buttons/Credit_BTN_ACT.png",
	                 1.0f, sf::Vector2f(204.47f, 660.73f));
	btnContainer.push_back(&btnCredit);

	btnExit.Setup("Assets/Texture/GUI/Buttons/Close_BTN.png",
	              "Assets/Texture/GUI/Buttons/Close_BTN_HOV.png",
	              "Assets/Texture/GUI/Buttons/Close_BTN_ACT.png",
	              1.0f, sf::Vector2f(204.47f,746.77f));
	btnContainer.push_back(&btnExit);
}

void MainMenu::initBg()
{
	menuBgTex.loadFromFile("Assets/Texture/GUI/main-menu_background2.png");
	menuBgSpi.setTexture(menuBgTex);
	menuBgSpi.setScale(1.f, 1.f);
	menuBgSpi.setPosition(0, 0);
}

void MainMenu::Pause()
{
	std::cout << "MainMenu Paused" << std::endl;
}

void MainMenu::Resume()
{
	std::cout << "MainMenu Resume" << std::endl;
}

void MainMenu::Update(float deltaTime)
{
	for (auto event = sf::Event{}; mWindow.GetRenderWindow()->pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::Closed: mWindow.Destroy(); break;
#ifdef _DEBUG
		case sf::Event::KeyPressed:
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Space:
				mNext = SceneManager::build<LoadingScreen>(mObj, true);
				break;
			case sf::Keyboard::Escape: mWindow.Destroy(); break;
			case sf::Keyboard::BackSpace: mManager.prevScene(); break;
			case sf::Keyboard::M: mAudio.toggleMute(); break;
			case sf::Keyboard::Add: mAudio.increase_volume(); break;
			case sf::Keyboard::Hyphen: mAudio.decrease_volume(); break;
			case sf::Keyboard::F11: mWindow.ToggleFullScreen(); break;
			default: break;
			}
			break;
		}
#endif
		default: break;
		}
	}

	const sf::Vector2i mousePos = sf::Mouse::getPosition(*mWindow.GetRenderWindow());
	const sf::Vector2f worldMousePos = mWindow.GetRenderWindow()->mapPixelToCoords(mousePos);
	
	for (auto btn : btnContainer)
	{
		btn->Update(worldMousePos);
		if (btn->isHover())
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				btn->Click();
				mAudio.playSFX("button");
			}
		}
	}

	//-=-=-=-=-=-=-=-=-=-CLICKED BUTTON HERE-=-=-=-=-=-=-=-=-=-=-=-
	if (btnExit.isPressed())
	{
		mWindow.Destroy();
	}
	else if (btnPlay.isPressed())
	{
		mNext = SceneManager::build<LoadingScreen>(mObj, true);
	}
	else if (btnSetting.isPressed())
	{
		mNext = SceneManager::build<SettingScene>(mObj, false);
	}
}

void MainMenu::Draw()
{
	mWindow.BeginDraw();

	mWindow.Draw(menuBgSpi);

	//mWindow.Draw(rect);

	for (auto btn : btnContainer)
		mWindow.Draw(*btn->getDraw());

	mWindow.EndDraw();
}

