#pragma once
#ifndef SETTING_SCENE_H_
#define SETTING_SCENE_H_

#include <SFML/Graphics.hpp>

#include "BaseScene.h"
#include "Button.h"
#include "ToggleButton.h"

class SceneManager;


class SettingScene final : public BaseScene
{
public:
	SettingScene(SharedObject& shared_object, bool replace = true);
	~SettingScene() override;

	void Pause() override;
	void Draw() override;
	void Resume() override;
	void Update(float delta_time) override;

private:
	//Define scene component here
	void InitBackground();
	void InitButton();

	sf::Font mHeadlineFont;
	sf::Text mSettingText;
	sf::Text mFullScreenText;
	sf::Text mMuteText;
	
	sf::Texture mMenuBgTex;
	sf::Sprite mMenuBgSpi;

	ToggleButton mButtonMute;
	ToggleButton mButtonFullScreen;
	Button mButtonBack;
};

#endif