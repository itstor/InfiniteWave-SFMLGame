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

GameoverScene::GameoverScene(SharedObject& obj, bool replace) :BaseScene(obj, replace)
{
#ifdef _DEBUG
	std::cout << "GameoverScene Created" << std::endl;
#endif
	fadeToBlack.setSize({ 1920, 1080 });
	
	pixelFont.loadFromFile("data/Font/Minecraft.ttf");
	gameOverText.setFont(pixelFont);
	scoreText.setFont(pixelFont);
	newHighScoreText.setFont(pixelFont);
	respawnText.setFont(pixelFont);
	backToMainText.setFont(pixelFont);

	gameOverText.setScale(3.45f,3.45f);
	scoreText.setScale(1.67f,1.67f);
	newHighScoreText.setScale(0.81f,0.81f);
	respawnText.setScale(1.9f,1.9f);
	backToMainText.setScale(0.5f,0.5f);

	fadeToBlack.setFillColor(sf::Color(0, 0, 0, 255));
	gameOverText.setFillColor(sf::Color::White);
	scoreText.setFillColor(sf::Color::White);

	gameOverText.setString("Game Over");
	scoreText.setString(std::string("Score: ").append(std::to_string(conf::gameScore)));
	newHighScoreText.setString("New High Score!!");
	respawnText.setString("respawn in 5");
	backToMainText.setString("Press ESC to back to main menu");

	gameOverText.setPosition(649.38f,485.85f); //set out of view
	scoreText.setPosition(1920, 0); //set out of view
	newHighScoreText.setPosition(1920, 0); //set out of view
	respawnText.setPosition(1920, 0); //set out of view
	backToMainText.setPosition(1920, 0); //set out of view
	fadeToBlack.setPosition(0.0f, 0.0f);
}

GameoverScene::~GameoverScene()
{
	std::cout << "GameoverScene Deleted" << std::endl;
}

void GameoverScene::initButton()
{
	//Initialize button here
}

void GameoverScene::initBg()
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

void GameoverScene::Update(float deltaTime)
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
			case sf::Keyboard::Escape: mNext = SceneManager::build<MainMenu>(mObj, true);
			default: break;
			}
			break;
		}
		default: break;
		}
	}

	elapsedTime += deltaTime;

	//Keyframe here
	if (elapsedTime <= 3.0f)
	{
		static float elapsedFadeTime = 0.0f;
		elapsedFadeTime += deltaTime;
		const sf::Uint8 progress = 255 - (elapsedFadeTime / 3.0f * 255);
		fadeToBlack.setFillColor(sf::Color(0, 0, 0, progress));
	}
	else if (elapsedTime <= 4.0f) //
	{
		if (static bool played = false; !played) {
			mAnimManager.playAnimation(AnimType::MOVE, TransitionType::EASE_IN_OUT_BACK, { 649.38f,485.85f }, { 649.38f,87.0f }, 1.0f, gameOverText, false);
			played = true;
		}
		
	}
	else if (elapsedTime <= 10.0f)
	{
		const sf::FloatRect textBoxScore = scoreText.getLocalBounds();
		const sf::FloatRect textBoxHigh = newHighScoreText.getLocalBounds();
		const sf::FloatRect textBoxRespawn = respawnText.getLocalBounds();
		const sf::FloatRect textBoxBack = backToMainText.getLocalBounds();

		scoreText.setPosition(960 - textBoxScore.width, 221.27f);
		if (conf::gameScore > conf::highScore)
		{
			conf::highScore = conf::gameScore;
			newHighScoreText.setPosition(960 - textBoxHigh.width, 303.88f);
		}
		respawnText.setPosition(960 - textBoxRespawn.width, 851.84f);
		backToMainText.setOrigin(textBoxBack.width * 0.5f, textBoxBack.height * 0.5f);
		backToMainText.setPosition(960, 963.72f);

		static float respawnElaps = 0.0f;
		respawnElaps += deltaTime;
		static int countdown = 5;
		if (respawnElaps >= 1.0f)
		{
			countdown--;
			respawnText.setString(std::string("respawn in ").append(std::to_string(countdown)));
			if (countdown == 0)
			{
				mNext = SceneManager::build<GamePlay>(mObj, true);
			}
			respawnElaps = 0;
		}
	}
	mAnimManager.Update(deltaTime);
}

void GameoverScene::Draw()
{
	mWindow.BeginDraw();

	/*Draw everything here*/
	//mWindow.Draw(rectangle);
	mWindow.Draw(gameOverText);
	mWindow.Draw(scoreText);
	mWindow.Draw(newHighScoreText);
	mWindow.Draw(respawnText);
	mWindow.Draw(backToMainText);

	mWindow.Draw(fadeToBlack);

	mWindow.EndDraw();
}

