#pragma once

#include <SFML/Graphics.hpp>
#include "BaseScene.h"
#include "Button.h" //GUI Optional
#include "ToggleButton.h"

class SceneManager;

class SettingScene final : public BaseScene
{
public:
	SettingScene(SharedObject& obj, bool replace = true);
	~SettingScene() override;

	void Pause() override;
	void Draw() override;
	void Resume() override;
	void Update(float deltaTime) override;

	

private:
	//Define scene component here
	void initBg();
	void initButton();

	sf::Font headlineFont;
	sf::Text settingText;
	sf::Text fullscreenText;
	sf::Text muteText;
	
	sf::Texture menuBgTex;
	sf::Sprite menuBgSpi;

	ToggleButton btnMute;
	ToggleButton btnFullscreen;
	Button btnBack;
};

