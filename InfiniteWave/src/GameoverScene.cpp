#include "GameoverScene.h"

//Related Scene
#include "SplashScreen.h"

//Required Library
#include <iostream>

#include "Config.h"
#include "GamePlay.h"
#include "MainMenu.h"
#include "Window.h"
#include "SceneManager.h"

GameoverScene::GameoverScene(SharedObject& shared_object, bool replace) :BaseScene(shared_object, replace)
{
#ifdef _DEBUG
	std::cout << "GameoverScene Created" << std::endl;
#endif
	mFadeToBlackOverlay.setSize({ 1920, 1080 });
	
	mPixelFont.loadFromFile("data/Font/Minecraft.ttf");
	mGameOverText.setFont(mPixelFont);
	mScoreText.setFont(mPixelFont);
	mNewHighScoreText.setFont(mPixelFont);
	mRespawnText.setFont(mPixelFont);
	mBackToMainText.setFont(mPixelFont);

	mGameOverText.setScale(3.45f,3.45f);
	mScoreText.setScale(1.67f,1.67f);
	mNewHighScoreText.setScale(0.81f,0.81f);
	mRespawnText.setScale(1.9f,1.9f);
	mBackToMainText.setScale(0.5f,0.5f);

	mFadeToBlackOverlay.setFillColor(sf::Color(0, 0, 0, 255));
	mGameOverText.setFillColor(sf::Color::White);
	mScoreText.setFillColor(sf::Color::White);

	mGameOverText.setString("Game Over");
	mScoreText.setString(std::string("Score: ").append(std::to_string(conf::gGameScore)));
	mNewHighScoreText.setString("New High Score!!");
	mRespawnText.setString("respawn in 5");
	mBackToMainText.setString("Press ESC to back to main menu");

	mGameOverText.setPosition(649.38f,485.85f); //set out of view
	mScoreText.setPosition(1920, 0); //set out of view
	mNewHighScoreText.setPosition(1920, 0); //set out of view
	mRespawnText.setPosition(1920, 0); //set out of view
	mBackToMainText.setPosition(1920, 0); //set out of view
	mFadeToBlackOverlay.setPosition(0.0f, 0.0f);
}

GameoverScene::~GameoverScene()
{
	std::cout << "GameoverScene Deleted" << std::endl;
}

void GameoverScene::InitButton()
{
	//Initialize button here
}

void GameoverScene::InitBackground()
{
	//Initialize background here
}

void GameoverScene::Pause()
{
	std::cout << "GameoverScene Paused" << std::endl;
}

void GameoverScene::Resume()
{
	std::cout << "GameoverScene Resume" << std::endl;
}

void GameoverScene::Update(float delta_time)
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
			case sf::Keyboard::Escape: mNextScene = SceneManager::Build<MainMenu>(mSharedObject, true);
			default: break;
			}
			break;
		}
		default: break;
		}
	}

	mElapsedTime += delta_time;

	//Keyframe here
	if (mElapsedTime <= 3.0f)
	{
		static float elapsedFadeTime = 0.0f;
		elapsedFadeTime += delta_time;
		const sf::Uint8 progress = 255 - (elapsedFadeTime / 3.0f * 255);
		mFadeToBlackOverlay.setFillColor(sf::Color(0, 0, 0, progress));
	}
	else if (mElapsedTime <= 4.0f) //
	{
		if (static bool played = false; !played) {
			mAnimManager.PlayAnimation(AnimType::MOVE, TransitionType::EASE_IN_OUT_BACK, { 649.38f,485.85f }, { 649.38f,87.0f }, 1.0f, mGameOverText, false);
			played = true;
		}
		
	}
	else if (mElapsedTime <= 10.0f)
	{
		const sf::FloatRect textBoxScore = mScoreText.getLocalBounds();
		const sf::FloatRect textBoxHigh = mNewHighScoreText.getLocalBounds();
		const sf::FloatRect textBoxRespawn = mRespawnText.getLocalBounds();
		const sf::FloatRect textBoxBack = mBackToMainText.getLocalBounds();

		mScoreText.setPosition(960 - textBoxScore.width, 221.27f);
		if (conf::gGameScore > conf::gHighScore)
		{
			conf::gHighScore = conf::gGameScore;
			mNewHighScoreText.setPosition(960 - textBoxHigh.width, 303.88f);
		}
		mRespawnText.setPosition(960 - textBoxRespawn.width, 851.84f);
		mBackToMainText.setOrigin(textBoxBack.width * 0.5f, textBoxBack.height * 0.5f);
		mBackToMainText.setPosition(960, 963.72f);

		static float respawnElaps = 0.0f;
		respawnElaps += delta_time;
		static int countdown = 5;
		if (respawnElaps >= 1.0f)
		{
			countdown--;
			mRespawnText.setString(std::string("respawn in ").append(std::to_string(countdown)));
			if (countdown == 0)
			{
				mNextScene = SceneManager::Build<GamePlay>(mSharedObject, true);
			}
			respawnElaps = 0;
		}
	}
	mAnimManager.Update(delta_time);
}

void GameoverScene::Draw()
{
	mWindow.BeginDraw();

	/*Draw everything here*/
	//mWindow.Draw(rectangle);
	mWindow.Draw(mGameOverText);
	mWindow.Draw(mScoreText);
	mWindow.Draw(mNewHighScoreText);
	mWindow.Draw(mRespawnText);
	mWindow.Draw(mBackToMainText);

	mWindow.Draw(mFadeToBlackOverlay);

	mWindow.EndDraw();
}

