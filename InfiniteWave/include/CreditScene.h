#pragma once

#include <SFML/Graphics.hpp>
#include "BaseScene.h"
#include "Button.h" //GUI Optional
#include "ToggleButton.h"

class SceneManager;

class CreditScene final : public BaseScene
{
public:
	CreditScene(SharedObject& obj, bool replace = true);
	~CreditScene() override;

	void Pause() override;
	void Draw() override;
	void Resume() override;
	void Update(float deltaTime) override;

private:
	//Define scene component here
	void initBg();
	void initButton();

	sf::Font headlineFont;
	sf::Font dccFont;
	sf::Text creditText;
	sf::Text createdbyText;
	sf::Text additionalText;
	sf::Text add_creditText;
	sf::Text libraryText;
	sf::Text library_credText;
	
	sf::Texture menuBgTex;
	sf::Sprite menuBgSpi;
	Button btnBack;
};

