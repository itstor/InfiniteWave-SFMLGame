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

LoadingScreen::LoadingScreen(SharedObject& shared_object, bool replace) :BaseScene(shared_object, replace)
{
#ifdef _DEBUG
	std::cout << "LoadingScreen Created" << std::endl;
#endif

	//setup loading bar and fram
	mLoadingBarOutline.setOutlineColor(sf::Color::White);
	mLoadingBarOutline.setFillColor(sf::Color::Transparent);
	mLoadingBarOutline.setOutlineThickness(5);
	mLoadingBarOutline.setSize(sf::Vector2f(551, 44));
	mLoadingBarOutline.setPosition(684.5f, 1080.0f - 611.0f);

	mSingleLoadingBar.setFillColor(sf::Color::White);
	mSingleLoadingBar.setSize(sf::Vector2f(22, 30));
	
	//load font
	mPixelFont.loadFromFile("data/Font/Minecraft.ttf");

	//setup text
	mMoveText.setFont(mPixelFont);
	mMoveText.setString("move");
	mMoveText.setCharacterSize(38);
	mMoveText.setFillColor(sf::Color::White);

	mReloadText.setFont(mPixelFont);
	mReloadText.setString("reload");
	mReloadText.setCharacterSize(38);
	mReloadText.setFillColor(sf::Color::White);

	mAimText.setFont(mPixelFont);
	mAimText.setString("aim");
	mAimText.setCharacterSize(38);
	mAimText.setFillColor(sf::Color::White);

	mHowToText.setFont(mPixelFont);
	mHowToText.setString("How to Play:");
	mHowToText.setCharacterSize(38);
	mHowToText.setFillColor(sf::Color::White);

	mLoadingText.setFont(mPixelFont);
	mLoadingText.setString("loading");
	mLoadingText.setCharacterSize(38);
	mLoadingText.setFillColor(sf::Color::White);

	mMoveText.setPosition(749.1f, 1060.0f - 178.13f);
	mReloadText.setPosition(943.52f, 1060.0f - 178.13f);
	mAimText.setPosition(1153.0f, 1060.0f - 178.13f);
	mHowToText.setPosition(863.96f, 1050.0f - 402.72f);
	mLoadingText.setPosition(887.22f, 1050.0f - 664.63f);

	//setup texture
	mKeyWTex.loadFromFile("data/Texture/Sprites/Loading/W-Key.png");
	mKeyATex.loadFromFile("data/Texture/Sprites/Loading/A-Key.png");
	mKeySTex.loadFromFile("data/Texture/Sprites/Loading/S-Key.png");
	mKeyDTex.loadFromFile("data/Texture/Sprites/Loading/D-Key.png");
	mKeyRTex.loadFromFile("data/Texture/Sprites/Loading/R-Key.png");
	mMouseTex.loadFromFile("data/Texture/Sprites/Loading/mouse-sprite.png");

	//setup anim
	mKeyWAnim.Setup(&mKeyWTex, 1, 2);
	mKeyAAnim.Setup(&mKeyATex, 1, 2);
	mKeySAnim.Setup(&mKeySTex, 1, 2);
	mKeyDAnim.Setup(&mKeyDTex, 1, 2);
	mKeyRAnim.Setup(&mKeyRTex, 1, 2);
	mMouseAnim.Setup(&mMouseTex, 1, 2);

	//setup rectangle
	mKeyWRect.setSize(sf::Vector2f(static_cast<float>(mKeyWTex.getSize().x)/2, static_cast<float>(mKeyWTex.getSize().y)));
	mKeyARect.setSize(sf::Vector2f(static_cast<float>(mKeyATex.getSize().x)/2, static_cast<float>(mKeyATex.getSize().y)));
	mKeySRect.setSize(sf::Vector2f(static_cast<float>(mKeySTex.getSize().x)/2, static_cast<float>(mKeySTex.getSize().y)));
	mKeyDRect.setSize(sf::Vector2f(static_cast<float>(mKeyDTex.getSize().x)/2, static_cast<float>(mKeyDTex.getSize().y)));
	mKeyRRect.setSize(sf::Vector2f(static_cast<float>(mKeyRTex.getSize().x)/2, static_cast<float>(mKeyRTex.getSize().y)));
	mMouseRect.setSize(sf::Vector2f(113, 132));

	mKeyWRect.setScale(1.57f, 1.57f);
	mKeyARect.setScale(1.57f, 1.57f);
	mKeySRect.setScale(1.57f, 1.57f);
	mKeyDRect.setScale(1.57f, 1.57f);
	mKeyRRect.setScale(1.57f, 1.57f);
	
	mKeyWRect.setTexture(&mKeyWTex);
	mKeyARect.setTexture(&mKeyATex);
	mKeySRect.setTexture(&mKeySTex);
	mKeyDRect.setTexture(&mKeyDTex);
	mKeyRRect.setTexture(&mKeyRTex);
	mMouseRect.setTexture(&mMouseTex);

	mKeyWRect.setPosition(770.83f, 1080.0f - 308.45f);
	mKeyARect.setPosition(706.17f, 1080.0f - 255.43f);
	mKeySRect.setPosition(770.83f, 1080.0f - 255.43f);
	mKeyDRect.setPosition(835.49f, 1080.0f - 255.43f);
	mKeyRRect.setPosition(969.98f, 1080.0f - 255.43f);
	mMouseRect.setPosition(1127.0f, 1080.0f - 321.43f);
}

LoadingScreen::~LoadingScreen()
{
	std::cout << "LoadingScreen Deleted" << std::endl;
}

void LoadingScreen::InitButton()
{
	//Initialize button here
}

void LoadingScreen::InitBackground()
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

void LoadingScreen::Update(float delta_time)
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
			case sf::Keyboard::Space: mNextScene = SceneManager::Build<GamePlay>(mSharedObject, true);
			default: break;
			}
			break;
		}
		default: break;
		}
	}

	mKeyWAnim.Update(delta_time, 0, 1.f, 0, 2);
	mKeyAAnim.Update(delta_time, 0, 1.f, 0, 2);
	mKeySAnim.Update(delta_time, 0, 1.f, 0, 2);
	mKeyDAnim.Update(delta_time, 0, 1.f, 0, 2);
	mKeyRAnim.Update(delta_time, 0, 1.f, 0, 2);
	mMouseAnim.Update(delta_time, 0, 1.f, 0, 2);

	mKeyWRect.setTextureRect(*mKeyWAnim.GetTextureRect());
	mKeyARect.setTextureRect(*mKeyAAnim.GetTextureRect());
	mKeySRect.setTextureRect(*mKeySAnim.GetTextureRect());
	mKeyDRect.setTextureRect(*mKeyDAnim.GetTextureRect());
	mKeyRRect.setTextureRect(*mKeyRAnim.GetTextureRect());
	mMouseRect.setTextureRect(*mMouseAnim.GetTextureRect());

	//loading text animation update
	static float totalTimeLoading;
	totalTimeLoading += delta_time;

	if (totalTimeLoading >= 0.5f)
	{
		static unsigned int currentLoading = 0;
		
		totalTimeLoading = 0;
		if (currentLoading == 0) mLoadingText.setString("loading");
		if (currentLoading == 1) mLoadingText.setString("loading.");
		if (currentLoading == 2) mLoadingText.setString("loading..");
		if (currentLoading == 3) mLoadingText.setString("loading...");

		currentLoading++;
		if (currentLoading > 3) currentLoading = 0;
	}

	//loading bar animation update
	static float totalTimeBar;
	totalTimeBar += delta_time;

	if (totalTimeBar >= 0.5f)
	{
		static unsigned int currentBar = 0;

		mSingleLoadingBar.setPosition(693.0f + (26.75f * static_cast<float>(currentBar)), 1080.0f - 604);
		mLoadingBars.emplace_back(mSingleLoadingBar);

		totalTimeBar = 0;
		currentBar++;
		if (currentBar >= 21) mNextScene = SceneManager::Build<GamePlay>(mSharedObject, true);
	}

}

void LoadingScreen::Draw()
{
	mWindow.BeginDraw();

	/*Draw everything here*/
	mWindow.Draw(mKeyWRect);
	mWindow.Draw(mKeyARect);
	mWindow.Draw(mKeySRect);
	mWindow.Draw(mKeyDRect);
	mWindow.Draw(mKeyRRect);
	mWindow.Draw(mMouseRect);
	mWindow.Draw(mMoveText);
	mWindow.Draw(mReloadText);
	mWindow.Draw(mAimText);
	mWindow.Draw(mHowToText);
	mWindow.Draw(mLoadingText);
	mWindow.Draw(mLoadingBarOutline);

	for (auto &bar:mLoadingBars)
	{
		mWindow.Draw(bar);
	}


	mWindow.EndDraw();
}

