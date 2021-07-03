#pragma once
#ifndef MAIN_MENU_H_
#define MAIN_MENU_H_

#include <SFML/Graphics.hpp>

#include "BaseScene.h"
#include "Button.h"

class SceneManager;


class MainMenu final : public BaseScene
{
public:
	MainMenu(SharedObject& shared_object, bool replace = true);
	~MainMenu() override;

	void Pause() override;
	void Draw() override;
	void Resume() override;
	void Update(float delta_time) override;

private:
	void InitBackground();
	void InitButton();
	
	sf::Texture mMenuBgTex;
	sf::Sprite mMenuBgSpi;
	
	Button mButtonPlay;
	Button mButtonSetting;
	Button mButtonExit;
	Button mButtonCredit;

	std::vector<Button*> btnContainer;
};

#endif