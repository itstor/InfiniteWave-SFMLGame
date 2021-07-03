#include <memory>

//Related Scene
#include "SplashScreen.h"
#include "MainMenu.h"

#include "Window.h"
#include "Config.h"
#include "SceneManager.h"
#include "AudioManager.h"


SplashScreen::SplashScreen(SharedObject& shared_object, bool replace) :BaseScene(shared_object, replace), mAlphaMask(0, 0, 0, 255)
{	
	//Background
	mBackgroundRect.setSize(sf::Vector2f(static_cast<float>(mWindow.GetWindowSize().x), static_cast<float>(mWindow.GetWindowSize().y)));
	mBackgroundRect.setFillColor(sf::Color::Black);
	
	//Mask fader
	mMaskRect.setFillColor(mAlphaMask);
	mMaskRect.setSize(sf::Vector2f(static_cast<float>(mWindow.GetWindowSize().x), static_cast<float>(mWindow.GetWindowSize().y)));

	mITSLogo.Setup("data/Texture/GUI/splash_whiteits.png",
		sf::Vector2f(static_cast<float>(conf::gWindowWidth) / 2, static_cast<float>(conf::gWindowHeight) / 2),
		sf::Vector2f(500, 500));
	
	mGameLogo.Setup("data/Texture/GUI/splash_logogame.png",
		sf::Vector2f(static_cast<float>(conf::gWindowWidth) / 2, static_cast<float>(conf::gWindowHeight) / 2),
		sf::Vector2f(500, 548));
	
	mAudio.PlayMusic("Loading");
}

SplashScreen::~SplashScreen() = default;


void SplashScreen::Pause(){}

void SplashScreen::Resume(){}

void SplashScreen::Update(float delta_time)
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
			case sf::Keyboard::Space:
				mNextScene = SceneManager::Build<MainMenu>(mSharedObject, true);
				break;
#ifdef _DEBUG
			case sf::Keyboard::Escape: mWindow.Destroy(); break;
			case sf::Keyboard::M: mAudio.ToggleMute(); break;
#endif
			default: break;
			}
			break;
		}
		default: break;
		}
	}

	
	if (mAlphaMask.a != 0 && (mLogoFlag == 1 || mLogoFlag == 3))
		mAlphaMask.a -= 1;
	else
		mAlphaMask.a += 1;

	if (mLogoFlag == 3 && mAlphaMask.a == 0)
		mNextScene = SceneManager::Build<MainMenu>(mSharedObject, true);

	if (mAlphaMask.a == 0 || (mAlphaMask.a == 255 && mLogoFlag == 2))
		mLogoFlag++;


	mMaskRect.setFillColor(mAlphaMask);
}

void SplashScreen::Draw()
{
	mWindow.BeginDraw();

	mWindow.Draw(mBackgroundRect);

	if (mLogoFlag == 1 || mLogoFlag == 2)
		mWindow.Draw(*mITSLogo.GetDraw());
	else
		mWindow.Draw(*mGameLogo.GetDraw());

	if (mAlphaMask.a != 0)
	{
		mWindow.Draw(mMaskRect);
	}

	mWindow.EndDraw();
}



