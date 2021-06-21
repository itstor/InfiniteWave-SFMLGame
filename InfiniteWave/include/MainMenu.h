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

private:
	void initBg();
	void initButton();

	
	std::vector<Button*> btnContainer;
	
	sf::Texture menuBgTex;
	sf::Sprite menuBgSpi;
	
	Button btnPlay;
	Button btnSetting;
	Button btnExit;
	Button btnCredit;
};

