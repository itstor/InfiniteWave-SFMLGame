#pragma once

#include <SFML/Graphics.hpp>
#include "BaseScene.h"

class SceneManager;

class SplashScreen final: public BaseScene
{
public:
	SplashScreen(SceneManager& manager, Window& window, bool replace = true);

	void Pause() override;
	void Draw() override;
	void Resume() override;
	void Update() override;

private:
	sf::RectangleShape rect;
};

