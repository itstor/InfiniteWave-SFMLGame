#include <memory>

#include "SettingScene.h"

//Related Scene
#include "MainMenu.h"

#include "Window.h"
#include "SceneManager.h"
#include "AudioManager.h"
#include "Config.h"


SettingScene::SettingScene(SharedObject& shared_object, bool replace) :BaseScene(shared_object, replace)
{
	mHeadlineFont.loadFromFile("data/Font/HeadlinerNo.45.ttf");

	mSettingText.setFont(mHeadlineFont);
	mFullScreenText.setFont(mHeadlineFont);
	mMuteText.setFont(mHeadlineFont);

	mSettingText.setString("SETTING");
	mFullScreenText.setString("FULLSCREEN");
	mMuteText.setString("MUSIC SFX");

	mSettingText.setScale(1.56f, 1.56f);
	mFullScreenText.setScale(1.1f, 1.1f);
	mMuteText.setScale(1.1f, 1.1f);

	mSettingText.setPosition(160.63f, 433.52f);
	mFullScreenText.setPosition(100.12f, 548.89f);
	mMuteText.setPosition(100.12f, 612.86f);
	
	InitBackground();
	InitButton();
}

SettingScene::~SettingScene() = default;

void SettingScene::Pause(){}

void SettingScene::Resume(){}

void SettingScene::InitButton()
{
	//Initialize button here
	mButtonBack.Setup("data/Texture/GUI/Buttons/Back_BTN.png",
				"data/Texture/GUI/Buttons/Back_BTN.png",
				"data/Texture/GUI/Buttons/Back_BTN.png",
				1.0f, sf::Vector2f(123.27f, 463.19f));

	mButtonFullScreen.Setup("data/Texture/GUI/Buttons/BTN_ONOFF_FIRST.png",
		"data/Texture/GUI/Buttons/BTN_ONOFF_SECOND.png",
		1.0f, sf::Vector2f(330.48f, 569.0f), conf::gIsFullscreen ? ButtonState::FIRST_STATE : ButtonState::SECOND_STATE);

	mButtonMute.Setup("data/Texture/GUI/Buttons/BTN_ONOFF_FIRST.png",
		"data/Texture/GUI/Buttons/BTN_ONOFF_SECOND.png",
		1.0f, sf::Vector2f(330.48f, 632.75f), conf::gIsMuted ? ButtonState::SECOND_STATE: ButtonState::FIRST_STATE);

}

void SettingScene::InitBackground()
{
	//Initialize background here
	mMenuBgTex.loadFromFile("data/Texture/GUI/main-menu_background2.png");
	mMenuBgSpi.setTexture(mMenuBgTex);
	mMenuBgSpi.setScale(1.f, 1.f);
	mMenuBgSpi.setPosition(0, 0);
}

void SettingScene::Update(float delta_time)
{
	const sf::Vector2i mousePos = sf::Mouse::getPosition(*mWindow.GetRenderWindow());
	const sf::Vector2f worldMousePos = mWindow.GetRenderWindow()->mapPixelToCoords(mousePos);

	mButtonBack.Update(worldMousePos);
	mButtonFullScreen.Update(worldMousePos);
	mButtonMute.Update(worldMousePos);
	
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
				if (mButtonBack.IsHover())
				{
					mAudio.PlaySFX("button");
					mNextScene = SceneManager::Build<MainMenu>(mSharedObject, true);
				}
				else if (mButtonMute.IsHover())
				{
					mButtonMute.ToggleState();
					mAudio.ToggleMute();
				}
				else if (mButtonFullScreen.IsHover())
				{
					mButtonFullScreen.ToggleState();
					mWindow.ToggleFullScreen();
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
	mWindow.Draw(mMenuBgSpi);
	mWindow.Draw(mSettingText);
	mWindow.Draw(mFullScreenText);
	mWindow.Draw(mMuteText);
	mWindow.Draw(*mButtonBack.GetDraw());
	mWindow.Draw(*mButtonMute.GetDraw());
	mWindow.Draw(*mButtonFullScreen.GetDraw());


	mWindow.EndDraw();
}