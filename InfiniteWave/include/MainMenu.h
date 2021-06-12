#pragma once

#include <SFML/Graphics.hpp>
#include "BaseScene.h"
#include "Button.h"

class SceneManager;

class MainMenu final : public BaseScene
{
public:
	MainMenu(SharedObject& obj, bool replace = true);
	~MainMenu() override;

	void Pause() override;
	void Draw() override;
	void Resume() override;
	void Update(float deltaTime) override;

	void initBg();
	void initButton();

private:
	std::vector<Button*> btnContainer;
	
	sf::RectangleShape rect;
	sf::Texture title;
	sf::Texture menuBgTex;
	sf::Sprite menuBgSpi;
	
	Button btnPlay;
	Button btnSetting;
	Button btnExit;
	Button btnHow; //How to Play

	sf::Vector2i mousePos;
	sf::Vector2u winSize;
};

