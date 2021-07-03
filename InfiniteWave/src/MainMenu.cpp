#include "SplashScreen.h"
#include "MainMenu.h"
#include "GamePlay.h"

#include <memory>

#include "Window.h"
#include "SceneManager.h"
#include "AudioManager.h"
#include "CreditScene.h"
#include "GameoverScene.h"
#include "LoadingScreen.h"
#include "SettingScene.h"


MainMenu::MainMenu(SharedObject& shared_object, bool replace) :BaseScene(shared_object, replace)
{
	InitBackground();
	InitButton();

	if(!mAudio.GetMuicStatus("Loading"))
	{
		mAudio.PlayMusic("Loading");
	}
}

MainMenu::~MainMenu() = default;

void MainMenu::InitButton()
{
	mButtonPlay.Setup("data/Texture/GUI/Buttons/Start_BTN.png",
	              "data/Texture/GUI/Buttons/Start_BTN_HOV.png",
	              "data/Texture/GUI/Buttons/Start_BTN_ACT.png",
	              1.0f, sf::Vector2f(204.47f,499.09f));
	btnContainer.push_back(&mButtonPlay);

	mButtonSetting.Setup("data/Texture/GUI/Buttons/Settings_BTN.png",
	                 "data/Texture/GUI/Buttons/Settings_BTN_HOV.png",
	                 "data/Texture/GUI/Buttons/Settings_BTN_ACT.png",
	                 1.0f, sf::Vector2f(204.47f, 579.9f));
	btnContainer.push_back(&mButtonSetting);

	mButtonCredit.Setup("data/Texture/GUI/Buttons/Credit_BTN.png",
	                 "data/Texture/GUI/Buttons/Credit_BTN_HOV.png",
	                 "data/Texture/GUI/Buttons/Credit_BTN_ACT.png",
	                 1.0f, sf::Vector2f(204.47f, 660.73f));
	btnContainer.push_back(&mButtonCredit);

	mButtonExit.Setup("data/Texture/GUI/Buttons/Close_BTN.png",
	              "data/Texture/GUI/Buttons/Close_BTN_HOV.png",
	              "data/Texture/GUI/Buttons/Close_BTN_ACT.png",
	              1.0f, sf::Vector2f(204.47f,746.77f));
	btnContainer.push_back(&mButtonExit);
}

void MainMenu::InitBackground()
{
	mMenuBgTex.loadFromFile("data/Texture/GUI/main-menu_background2.png");
	mMenuBgSpi.setTexture(mMenuBgTex);
	mMenuBgSpi.setScale(1.f, 1.f);
	mMenuBgSpi.setPosition(0, 0);
}

void MainMenu::Pause(){}

void MainMenu::Resume(){}

void MainMenu::Update(float delta_time)
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
				mNextScene = SceneManager::Build<LoadingScreen>(mSharedObject, true);
				break;
			case sf::Keyboard::Escape: mWindow.Destroy(); break;
			case sf::Keyboard::BackSpace: mScene.PrevScene(); break;
			case sf::Keyboard::M: mAudio.ToggleMute(); break;
			case sf::Keyboard::Add: mAudio.IncreaseVolume(); break;
			case sf::Keyboard::Hyphen: mAudio.DecreaseVolume(); break;
			case sf::Keyboard::F11: mWindow.ToggleFullScreen(); break;
			case sf::Keyboard::G: mNextScene = SceneManager::Build<GameoverScene>(mSharedObject, true);
				break; 
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
		if (btn->IsHover())
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				btn->Click();
				mAudio.PlaySFX("button");
			}
		}
	}

	//-=-=-=-=-=-=-=-=-=-CLICKED BUTTON HERE-=-=-=-=-=-=-=-=-=-=-=-
	if (mButtonExit.IsPressed())
	{
		mWindow.Destroy();
	}
	else if (mButtonPlay.IsPressed())
	{
		mNextScene = SceneManager::Build<LoadingScreen>(mSharedObject, true);
	}
	else if (mButtonSetting.IsPressed())
	{
		mNextScene = SceneManager::Build<SettingScene>(mSharedObject, false);
	}
	else if (mButtonCredit.IsPressed())
	{
		mNextScene = SceneManager::Build<CreditScene>(mSharedObject, false);
	}
}

void MainMenu::Draw()
{
	mWindow.BeginDraw();

	mWindow.Draw(mMenuBgSpi);

	//mWindow.Draw(rect);

	for (auto btn : btnContainer)
		mWindow.Draw(*btn->GetDraw());

	mWindow.EndDraw();
}

