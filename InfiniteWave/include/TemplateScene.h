#pragma once

#include <SFML/Graphics.hpp>
#include "BaseScene.h"
#include "Button.h" //GUI Optional

class SceneManager;

class TemplateScene final : public BaseScene
{
public:
	TemplateScene(SharedObject& shared_object, bool replace = true);
	~TemplateScene() override;

	void Pause() override;
	void Draw() override;
	void Resume() override;
	void Update(float delta_time) override;

private:
	//Define scene component here
	void InitBackground();
	void InitButton();
};

