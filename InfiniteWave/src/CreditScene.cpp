#include "CreditScene.h"

//Related Scene
#include "MainMenu.h"

//Required Library
#include <iostream>

#include "Window.h"
#include "SceneManager.h"
#include "AudioManager.h"

CreditScene::CreditScene(SharedObject& shared_object, bool replace) :BaseScene(shared_object, replace)
{
#ifdef _DEBUG
	std::cout << "CreditScene Created" << std::endl;
#endif
	mHeadlineFont.loadFromFile("data/Font/HeadlinerNo.45.ttf");
	mDCCFont.loadFromFile("data/Font/DCC.otf");

	mCreditText.setFont(mHeadlineFont);
	mCreatedByText.setFont(mDCCFont);
	mAdditionalText.setFont(mDCCFont);
	mAddCreditText.setFont(mDCCFont);
	mLibraryText.setFont(mDCCFont);
	mLibraryCreditText.setFont(mDCCFont);

	mCreditText.setString("CREDIT");
	mCreatedByText.setString("Created by Akhmad Thoriq Afif (5024201028)\nas part of advanced programming final project");
	mAdditionalText.setString("Addtional Credit:");
	mAddCreditText.setString("+ freepik.com - some of UI graphics\n+ rileygombart - player and zombie sprites\n+ adamatomic - tile map");
	mLibraryText.setString("Library Used:");
	mLibraryCreditText.setString("+ SFML\n+ ltbl2");
	
	mCreditText.setScale(1.56f, 1.56f);
	mCreatedByText.setScale(1.2f,1.2f);
	mAdditionalText.setScale(0.95f,0.95f);
	mAddCreditText.setScale(0.86f,0.86f);
	mLibraryText.setScale(0.95f,0.95f);
	mLibraryCreditText.setScale(0.86f,0.86f);

	mCreditText.setPosition(160.63f, 433.52f);
	mCreatedByText.setPosition(99.51f, 544.52f);
	mAdditionalText.setPosition(99.51f,655.44f);
	mAddCreditText.setPosition(99.51f,691.7f);
	mLibraryText.setPosition(99.51f,824.33f);
	mLibraryCreditText.setPosition(99.51f,863.28f);
	
	
	InitBackground();
	InitButton();
}

CreditScene::~CreditScene()
{
	std::cout << "CreditScene Deleted" << std::endl;
}

void CreditScene::InitButton()
{
	//Initialize button here
	mButtonBack.Setup("data/Texture/GUI/Buttons/Back_BTN.png",
				"data/Texture/GUI/Buttons/Back_BTN.png",
				"data/Texture/GUI/Buttons/Back_BTN.png",
				1.0f, sf::Vector2f(123.27f, 463.19f));

}

void CreditScene::InitBackground()
{
	//Initialize background here
	mMenuBgTex.loadFromFile("data/Texture/GUI/main-menu_background2.png");
	mMenuBgSpi.setTexture(mMenuBgTex);
	mMenuBgSpi.setScale(1.f, 1.f);
	mMenuBgSpi.setPosition(0, 0);
}

void CreditScene::Pause()
{
	std::cout << "CreditScene Paused" << std::endl;
}

void CreditScene::Resume()
{
	std::cout << "CreditScene Resume" << std::endl;
}

void CreditScene::Update(float delta_time)
{
	const sf::Vector2i mousePos = sf::Mouse::getPosition(*mWindow.GetRenderWindow());
	const sf::Vector2f worldMousePos = mWindow.GetRenderWindow()->mapPixelToCoords(mousePos);

	mButtonBack.Update(worldMousePos);
	
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
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						mAudio.PlaySFX("button");
						mNextScene = SceneManager::Build<MainMenu>(mSharedObject, true);
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

void CreditScene::Draw()
{
	mWindow.BeginDraw();

	/*Draw everything here*/
	mWindow.Draw(mMenuBgSpi);
	mWindow.Draw(mCreditText);
	mWindow.Draw(mCreatedByText);
	mWindow.Draw(mAdditionalText);
	mWindow.Draw(mAddCreditText);
	mWindow.Draw(mLibraryText);
	mWindow.Draw(mLibraryCreditText);
	mWindow.Draw(*mButtonBack.GetDraw());

	mWindow.EndDraw();
}