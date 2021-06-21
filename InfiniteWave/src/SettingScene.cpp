#include "SettingScene.h"

//Related Scene
#include "MainMenu.h"

//Required Library
#include <iostream>
#include <memory>

#include "Window.h"
#include "SceneManager.h"
#include "AudioManager.h"
#include "Config.h"

SettingScene::SettingScene(SharedObject& obj, bool replace) :BaseScene(obj, replace)
{
#ifdef _DEBUG
	std::cout << "SettingScene Created" << std::endl;
#endif
	headlineFont.loadFromFile("Assets/Font/HeadlinerNo.45.ttf");


	settingText.setFont(headlineFont);
	fullscreenText.setFont(headlineFont);
	muteText.setFont(headlineFont);

	settingText.setString("SETTING");
	fullscreenText.setString("FULLSCREEN");
	muteText.setString("MUSIC SFX");

	settingText.setScale(1.56f, 1.56f);
	fullscreenText.setScale(1.1f, 1.1f);
	muteText.setScale(1.1f, 1.1f);

	settingText.setPosition(160.63f, 433.52f);
	fullscreenText.setPosition(100.12f, 548.89f);
	muteText.setPosition(100.12f, 612.86f);
	
	
	initBg();
	initButton();
}

SettingScene::~SettingScene()
{
	std::cout << "SettingScene Deleted" << std::endl;
}

void SettingScene::initButton()
{
	//Initialize button here
	btnBack.Setup("Assets/Texture/GUI/Buttons/Back_BTN.png",
				"Assets/Texture/GUI/Buttons/Back_BTN.png",
				"Assets/Texture/GUI/Buttons/Back_BTN.png",
				1.0f, sf::Vector2f(123.27f, 463.19f));

	btnFullscreen.Setup("Assets/Texture/GUI/Buttons/BTN_ONOFF_FIRST.png",
		"Assets/Texture/GUI/Buttons/BTN_ONOFF_SECOND.png",
		1.0f, sf::Vector2f(330.48f, 569.0f), conf::isFullscreen ? FIRST_STATE : SECOND_STATE);

	btnMute.Setup("Assets/Texture/GUI/Buttons/BTN_ONOFF_FIRST.png",
		"Assets/Texture/GUI/Buttons/BTN_ONOFF_SECOND.png",
		1.0f, sf::Vector2f(330.48f, 632.75f), conf::isMuted ? SECOND_STATE: FIRST_STATE);

}

void SettingScene::initBg()
{
	//Initialize background here
	menuBgTex.loadFromFile("Assets/Texture/GUI/main-menu_background2.png");
	menuBgSpi.setTexture(menuBgTex);
	menuBgSpi.setScale(1.f, 1.f);
	menuBgSpi.setPosition(0, 0);
}

void SettingScene::Pause()
{
	std::cout << "SettingScene Paused" << std::endl;
}

void SettingScene::Resume()
{
	std::cout << "SettingScene Resume" << std::endl;
}

void SettingScene::Update(float deltaTime)
{
	const sf::Vector2i mousePos = sf::Mouse::getPosition(*mWindow.GetRenderWindow());
	const sf::Vector2f worldMousePos = mWindow.GetRenderWindow()->mapPixelToCoords(mousePos);

	btnBack.Update(worldMousePos);
	btnFullscreen.Update(worldMousePos);
	btnMute.Update(worldMousePos);
	
	for (auto event = sf::Event{}; mWindow.GetRenderWindow()->pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::Closed: mWindow.Destroy(); break;
		case sf::Event::MouseButtonPressed:
		{
			switch (event.mouseButton.button)
			{
			case sf::Mouse::Left:
			{
				if (btnBack.isHover())
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						mAudio.playSFX("button");
						mNext = SceneManager::build<MainMenu>(mObj, true);
					}
				}
				else if (btnMute.isHover())
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						btnMute.toggleState();
						mAudio.toggleMute();
					}
				}
				else if (btnFullscreen.isHover())
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						btnFullscreen.toggleState();
						mWindow.ToggleFullScreen();
					}
				}
			} break;
			default: break;
			}
		} break;
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
}

void SettingScene::Draw()
{
	mWindow.BeginDraw();

	/*Draw everything here*/
	mWindow.Draw(menuBgSpi);
	mWindow.Draw(settingText);
	mWindow.Draw(fullscreenText);
	mWindow.Draw(muteText);
	mWindow.Draw(*btnBack.getDraw());
	mWindow.Draw(*btnMute.getDraw());
	mWindow.Draw(*btnFullscreen.getDraw());


	mWindow.EndDraw();
}