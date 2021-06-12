#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "BaseScene.h"

struct SharedObject;

class SplashScreen final: public BaseScene
{
public:
	SplashScreen(SharedObject& obj, bool replace = true);
#ifdef _DEBUG
	~SplashScreen() override { std::cout << "SplashScreen Deleted" << std::endl; }
#endif

	void Pause() override;
	void Draw() override;
	void Resume() override;
	void Update(float deltaTime) override;

private:
	unsigned char logoFlag = 1;
	sf::RectangleShape background; //White background
	sf::Color alphaMask; //Fader color
	sf::RectangleShape rectMask; //fader mask
	//----Logo ITS-----
	sf::Texture logoITS; //Texture logo
	sf::RectangleShape rectLogoITS; //Container logo
	//----End of Logo ITS----
	//----Game Logo-----
	sf::Texture logoGame; //Texture logo
	sf::RectangleShape rectLogoGame; //Container logo
	//----End of Game Logo----
};

