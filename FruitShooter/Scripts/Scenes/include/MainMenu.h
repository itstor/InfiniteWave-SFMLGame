#pragma once

#include <SFML/Graphics.hpp>
#include "BaseScene.h"

class SceneManager;

class MainMenu final : public BaseScene
{
public:
	MainMenu(SceneManager& manager, Window& window, bool replace = true);

	void Pause() override;
	void Draw() override;
	void Resume() override;
	void Update() override;

private:
	sf::RectangleShape rect;
};

