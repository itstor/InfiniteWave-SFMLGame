#include "SplashScreen.h"
#include "MainMenu.h"
#include "GamePlay.h"

#include <iostream>
#include <memory>

#include "Window.h"
#include "SceneManager.h"
#include "AudioManager.h"


MainMenu::MainMenu(SharedObject& obj, bool replace) :BaseScene(obj, replace)
{
#ifdef _DEBUG
	std::cout << "MainMenu Created" << std::endl;
#endif
	winSize = mWindow.GetWindowSize();
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
	              "Assets/Texture/GUI/Buttons/Start_BTN_ACT.png",
	              "Assets/Texture/GUI/Buttons/Start_BTN_HOV.png",
	              1.0f, sf::Vector2f(winSize.x / 2, winSize.y - 250));
	btnContainer.push_back(&btnPlay);

	btnExit.Setup("Assets/Texture/GUI/Buttons/Close_BTN.png",
	              "Assets/Texture/GUI/Buttons/Close_BTN_HOV.png",
	              "Assets/Texture/GUI/Buttons/Close_BTN_ACT.png",
	              0.3f, sf::Vector2f(winSize.x - 100, 100));
	btnContainer.push_back(&btnExit);

	btnSetting.Setup("Assets/Texture/GUI/Buttons/Settings_BTN.png",
	                 "Assets/Texture/GUI/Buttons/Settings_BTN_HOV.png",
	                 "Assets/Texture/GUI/Buttons/Settings_BTN_ACT.png",
	                 0.3f, sf::Vector2f(100, 100));
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
				mNext = SceneManager::build<SplashScreen>(mObj, true);
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
		btn->Update(worldMousePos);

	//-=-=-=-=-=-=-=-=-=-CLICKED BUTTON HERE-=-=-=-=-=-=-=-=-=-=-=-
	if (btnExit.isPressed())
	{
		mWindow.Destroy();
	}
	if (btnPlay.isPressed())
	{
		mNext = SceneManager::build<GamePlay>(mObj, true);
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

