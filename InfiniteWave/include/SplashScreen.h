#pragma once
#ifndef SPLASH_SCREEN_H_
#define SPLASH_SCREEN_H_

#include <SFML/Graphics.hpp>

#include "BaseScene.h"
#include "Image.h"


class SplashScreen final: public BaseScene
{
public:
	SplashScreen(SharedObject& shared_object, bool replace = true);
	~SplashScreen() override;

	void Pause() override;
	void Draw() override;
	void Resume() override;
	void Update(float delta_time) override;

private:
	unsigned char mLogoFlag = 1;
	
	sf::RectangleShape mBackgroundRect; //black background
	sf::Color mAlphaMask; //Fader color
	sf::RectangleShape mMaskRect; //fader mask
	
	Image mITSLogo;
	Image mGameLogo;
};

#endif