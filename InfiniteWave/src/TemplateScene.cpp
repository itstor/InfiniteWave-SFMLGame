#include "TemplateScene.h"

//Related Scene
#include "SplashScreen.h"

//Required Library
#include <iostream>
#include <memory>

#include "Window.h"
#include "SceneManager.h"
#include "AudioManager.h"

TemplateScene::TemplateScene(SharedObject& shared_object, bool replace) :BaseScene(shared_object, replace)
{
#ifdef _DEBUG
	std::cout << "TemplateScene Created" << std::endl;
#endif
}

TemplateScene::~TemplateScene()
{
	std::cout << "TemplateScene Deleted" << std::endl;
}

void TemplateScene::InitButton()
{
	//Initialize button here
}

void TemplateScene::InitBackground()
{
	//Initialize background here
}

void TemplateScene::Pause()
{
	std::cout << "TemplateScene Paused" << std::endl;
}

void TemplateScene::Resume()
{
	std::cout << "TemplateScene Resume" << std::endl;
}

void TemplateScene::Update(float delta_time)
{
	for (auto event = sf::Event{}; mWindow.GetRenderWindow()->pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::Closed: mWindow.Destroy(); break;
		case sf::Event::KeyPressed:
		{
			switch (event.key.code)
			{
				/*Only for non-simultaneous key
				Use if statement for simultaneous key*/
			default: break;
			}
			break;
		}
		default: break;
		}
	}
}

void TemplateScene::Draw()
{
	mWindow.BeginDraw();

	/*Draw everything here*/
	//mWindow.Draw(rect);

	mWindow.EndDraw();
}

