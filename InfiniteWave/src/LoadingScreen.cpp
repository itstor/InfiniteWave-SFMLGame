#include "LoadingScreen.h"

//Related Scene
#include "SplashScreen.h"

//Required Library
#include <iostream>
#include <memory>

#include "Window.h"
#include "SceneManager.h"
#include "AudioManager.h"
#include "GamePlay.h"

LoadingScreen::LoadingScreen(SharedObject& obj, bool replace) :BaseScene(obj, replace)
{
#ifdef _DEBUG
	std::cout << "LoadingScreen Created" << std::endl;
#endif

	//setup loading bar and fram
	loadingFrame.setOutlineColor(sf::Color::White);
	loadingFrame.setFillColor(sf::Color::Transparent);
	loadingFrame.setOutlineThickness(5);
	loadingFrame.setSize(sf::Vector2f(551, 44));
	loadingFrame.setPosition(684.5f, 1080.0f - 611.0f);

	loadingBar.setFillColor(sf::Color::White);
	loadingBar.setSize(sf::Vector2f(22, 30));
	
	//load font
	pixelFont.loadFromFile("Assets/Font/Minecraft.ttf");

	//setup text
	moveText.setFont(pixelFont);
	moveText.setString("move");
	moveText.setCharacterSize(38);
	moveText.setFillColor(sf::Color::White);

	reloadText.setFont(pixelFont);
	reloadText.setString("reload");
	reloadText.setCharacterSize(38);
	reloadText.setFillColor(sf::Color::White);

	aimText.setFont(pixelFont);
	aimText.setString("aim");
	aimText.setCharacterSize(38);
	aimText.setFillColor(sf::Color::White);

	howToText.setFont(pixelFont);
	howToText.setString("How to Play:");
	howToText.setCharacterSize(38);
	howToText.setFillColor(sf::Color::White);

	loadingText.setFont(pixelFont);
	loadingText.setString("loading");
	loadingText.setCharacterSize(38);
	loadingText.setFillColor(sf::Color::White);

	moveText.setPosition(749.1f, 1060.0f - 178.13f);
	reloadText.setPosition(943.52f, 1060.0f - 178.13f);
	aimText.setPosition(1153.0f, 1060.0f - 178.13f);
	howToText.setPosition(863.96f, 1050.0f - 402.72f);
	loadingText.setPosition(887.22f, 1050.0f - 664.63f);

	//setup texture
	keyWTex.loadFromFile("Assets/Texture/Sprites/Loading/W-Key.png");
	keyATex.loadFromFile("Assets/Texture/Sprites/Loading/A-Key.png");
	keySTex.loadFromFile("Assets/Texture/Sprites/Loading/S-Key.png");
	keyDTex.loadFromFile("Assets/Texture/Sprites/Loading/D-Key.png");
	keyRTex.loadFromFile("Assets/Texture/Sprites/Loading/R-Key.png");
	mouseTex.loadFromFile("Assets/Texture/Sprites/Loading/mouse-sprite.png");

	//setup anim
	keyWAnim.Setup(&keyWTex, 1, 2);
	keyAAnim.Setup(&keyATex, 1, 2);
	keySAnim.Setup(&keySTex, 1, 2);
	keyDAnim.Setup(&keyDTex, 1, 2);
	keyRAnim.Setup(&keyRTex, 1, 2);
	mouseAnim.Setup(&mouseTex, 1, 2);

	//setup rectangle
	keyWRect.setSize(sf::Vector2f(keyWTex.getSize().x/2, keyWTex.getSize().y));
	keyARect.setSize(sf::Vector2f(keyATex.getSize().x/2, keyATex.getSize().y));
	keySRect.setSize(sf::Vector2f(keySTex.getSize().x/2, keySTex.getSize().y));
	keyDRect.setSize(sf::Vector2f(keyDTex.getSize().x/2, keyDTex.getSize().y));
	keyRRect.setSize(sf::Vector2f(keyRTex.getSize().x/2, keyRTex.getSize().y));
	mouseRect.setSize(sf::Vector2f(113, 132));

	keyWRect.setScale(1.57f, 1.57f);
	keyARect.setScale(1.57f, 1.57f);
	keySRect.setScale(1.57f, 1.57f);
	keyDRect.setScale(1.57f, 1.57f);
	keyRRect.setScale(1.57f, 1.57f);
	
	keyWRect.setTexture(&keyWTex);
	keyARect.setTexture(&keyATex);
	keySRect.setTexture(&keySTex);
	keyDRect.setTexture(&keyDTex);
	keyRRect.setTexture(&keyRTex);
	mouseRect.setTexture(&mouseTex);

	keyWRect.setPosition(770.83f, 1080.0f - 308.45f);
	keyARect.setPosition(706.17f, 1080.0f - 255.43f);
	keySRect.setPosition(770.83f, 1080.0f - 255.43f);
	keyDRect.setPosition(835.49f, 1080.0f - 255.43f);
	keyRRect.setPosition(969.98f, 1080.0f - 255.43f);
	mouseRect.setPosition(1127.0f, 1080.0f - 321.43f);
}

LoadingScreen::~LoadingScreen()
{
	std::cout << "LoadingScreen Deleted" << std::endl;
}

void LoadingScreen::initButton()
{
	//Initialize button here
}

void LoadingScreen::initBg()
{
	//Initialize background here
}

void LoadingScreen::Pause()
{
	std::cout << "LoadingScreen Paused" << std::endl;
}

void LoadingScreen::Resume()
{
	std::cout << "LoadingScreen Resume" << std::endl;
}

void LoadingScreen::Update(float deltaTime)
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
			case sf::Keyboard::Space: mNext = SceneManager::build<GamePlay>(mObj, true);
			default: break;
			}
			break;
		}
		default: break;
		}
	}

	keyWAnim.Update(deltaTime, 0, 1.f, 0, 2);
	keyAAnim.Update(deltaTime, 0, 1.f, 0, 2);
	keySAnim.Update(deltaTime, 0, 1.f, 0, 2);
	keyDAnim.Update(deltaTime, 0, 1.f, 0, 2);
	keyRAnim.Update(deltaTime, 0, 1.f, 0, 2);
	mouseAnim.Update(deltaTime, 0, 1.f, 0, 2);

	keyWRect.setTextureRect(*keyWAnim.getTexture());
	keyARect.setTextureRect(*keyAAnim.getTexture());
	keySRect.setTextureRect(*keySAnim.getTexture());
	keyDRect.setTextureRect(*keyDAnim.getTexture());
	keyRRect.setTextureRect(*keyRAnim.getTexture());
	mouseRect.setTextureRect(*mouseAnim.getTexture());

	//loading text animation update
	static float totalTimeLoading;
	totalTimeLoading += deltaTime;

	if (totalTimeLoading >= 0.5f)
	{
		static unsigned int currentLoading = 0;
		
		totalTimeLoading = 0;
		if (currentLoading == 0) loadingText.setString("loading");
		if (currentLoading == 1) loadingText.setString("loading.");
		if (currentLoading == 2) loadingText.setString("loading..");
		if (currentLoading == 3) loadingText.setString("loading...");

		currentLoading++;
		if (currentLoading > 3) currentLoading = 0;
	}

	//loading bar animation update
	static float totalTimeBar;
	totalTimeBar += deltaTime;

	if (totalTimeBar >= 0.5f)
	{
		static unsigned int currentBar = 0;

		loadingBar.setPosition(693.0f + (26.75f * static_cast<float>(currentBar)), 1080.0f - 604);
		loadingBars.emplace_back(loadingBar);

		totalTimeBar = 0;
		currentBar++;
		if (currentBar >= 21) mNext = SceneManager::build<GamePlay>(mObj, true);
	}

}

void LoadingScreen::Draw()
{
	mWindow.BeginDraw();

	/*Draw everything here*/
	mWindow.Draw(keyWRect);
	mWindow.Draw(keyARect);
	mWindow.Draw(keySRect);
	mWindow.Draw(keyDRect);
	mWindow.Draw(keyRRect);
	mWindow.Draw(mouseRect);
	mWindow.Draw(moveText);
	mWindow.Draw(reloadText);
	mWindow.Draw(aimText);
	mWindow.Draw(howToText);
	mWindow.Draw(loadingText);
	mWindow.Draw(loadingFrame);

	for (auto &bar:loadingBars)
	{
		mWindow.Draw(bar);
	}


	mWindow.EndDraw();
}

