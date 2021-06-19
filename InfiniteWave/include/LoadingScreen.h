#pragma once

#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "BaseScene.h"
#include "Button.h" //GUI Optional

class SceneManager;

class LoadingScreen final : public BaseScene
{
public:
	LoadingScreen(SharedObject& obj, bool replace = true);
	~LoadingScreen() override;

	void Pause() override;
	void Draw() override;
	void Resume() override;
	void Update(float deltaTime) override;
private:
	void initBg();
	void initButton();


	//Define scene component here
	sf::Font pixelFont;
	sf::Text loadingText;
	sf::Text howToText;
	sf::Text moveText;
	sf::Text reloadText;
	sf::Text aimText;

	std::vector<sf::RectangleShape> loadingBars;
	
	sf::RectangleShape loadingFrame;
	sf::RectangleShape loadingBar;
	sf::RectangleShape keyWRect;
	sf::RectangleShape keyARect;
	sf::RectangleShape keySRect;
	sf::RectangleShape keyDRect;
	sf::RectangleShape keyRRect;
	sf::RectangleShape mouseRect;

	sf::Texture keyWTex;
	sf::Texture keyATex;
	sf::Texture keySTex;
	sf::Texture keyDTex;
	sf::Texture keyRTex;
	sf::Texture mouseTex;

	Animation keyWAnim;
	Animation keyAAnim;
	Animation keySAnim;
	Animation keyDAnim;
	Animation keyRAnim;
	Animation mouseAnim;
};

