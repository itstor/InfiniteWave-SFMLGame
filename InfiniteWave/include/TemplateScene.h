#pragma once

#include <SFML/Graphics.hpp>
#include "BaseScene.h"
#include "Button.h" //GUI Optional

class SceneManager;

class TemplateScene final : public BaseScene
{
public:
	TemplateScene(SharedObject& obj, bool replace = true);
	~TemplateScene() override;

	void Pause() override;
	void Draw() override;
	void Resume() override;
	void Update(float deltaTime) override;

	void initBg();
	void initButton();

private:
	//Define scene component here
};

