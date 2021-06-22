#include "CreditScene.h"

//Related Scene
#include "MainMenu.h"

//Required Library
#include <iostream>

#include "Window.h"
#include "SceneManager.h"
#include "AudioManager.h"

CreditScene::CreditScene(SharedObject& obj, bool replace) :BaseScene(obj, replace)
{
#ifdef _DEBUG
	std::cout << "CreditScene Created" << std::endl;
#endif
	headlineFont.loadFromFile("Assets/Font/HeadlinerNo.45.ttf");
	dccFont.loadFromFile("Assets/Font/DCC.otf");

	creditText.setFont(headlineFont);
	createdbyText.setFont(dccFont);
	additionalText.setFont(dccFont);
	add_creditText.setFont(dccFont);
	libraryText.setFont(dccFont);
	library_credText.setFont(dccFont);

	creditText.setString("CREDIT");
	createdbyText.setString("Created by Akhmad Thoriq Afif (5024201028)\nas part of advanced programming final project");
	additionalText.setString("Addtional Credit:");
	add_creditText.setString("+ freepik.com - some of UI graphics\n+ rileygombart - player and zombie sprites\n+ adamatomic - tile map");
	libraryText.setString("Library Used:");
	library_credText.setString("+ SFML\n+ ltbl2");
	
	creditText.setScale(1.56f, 1.56f);
	createdbyText.setScale(1.2f,1.2f);
	additionalText.setScale(0.95f,0.95f);
	add_creditText.setScale(0.86f,0.86f);
	libraryText.setScale(0.95f,0.95f);
	library_credText.setScale(0.86f,0.86f);

	creditText.setPosition(160.63f, 433.52f);
	createdbyText.setPosition(99.51f, 544.52f);
	additionalText.setPosition(99.51f,655.44f);
	add_creditText.setPosition(99.51f,691.7f);
	libraryText.setPosition(99.51f,824.33f);
	library_credText.setPosition(99.51f,863.28f);
	
	
	initBg();
	initButton();
}

CreditScene::~CreditScene()
{
	std::cout << "CreditScene Deleted" << std::endl;
}

void CreditScene::initButton()
{
	//Initialize button here
	btnBack.Setup("Assets/Texture/GUI/Buttons/Back_BTN.png",
				"Assets/Texture/GUI/Buttons/Back_BTN.png",
				"Assets/Texture/GUI/Buttons/Back_BTN.png",
				1.0f, sf::Vector2f(123.27f, 463.19f));

}

void CreditScene::initBg()
{
	//Initialize background here
	menuBgTex.loadFromFile("Assets/Texture/GUI/main-menu_background2.png");
	menuBgSpi.setTexture(menuBgTex);
	menuBgSpi.setScale(1.f, 1.f);
	menuBgSpi.setPosition(0, 0);
}

void CreditScene::Pause()
{
	std::cout << "CreditScene Paused" << std::endl;
}

void CreditScene::Resume()
{
	std::cout << "CreditScene Resume" << std::endl;
}

void CreditScene::Update(float deltaTime)
{
	const sf::Vector2i mousePos = sf::Mouse::getPosition(*mWindow.GetRenderWindow());
	const sf::Vector2f worldMousePos = mWindow.GetRenderWindow()->mapPixelToCoords(mousePos);

	btnBack.Update(worldMousePos);
	
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
	mWindow.Draw(menuBgSpi);
	mWindow.Draw(creditText);
	mWindow.Draw(createdbyText);
	mWindow.Draw(additionalText);
	mWindow.Draw(add_creditText);
	mWindow.Draw(libraryText);
	mWindow.Draw(library_credText);
	mWindow.Draw(*btnBack.getDraw());

	mWindow.EndDraw();
}