#include "Game.h"
#include "Window.h"
#include "AudioManager.h"
#include "SharedObject.h"
#include "SceneManager.h"

#include <iostream>


int main()
{
	sf::Image icon;
	
	const std::string windowTitle = "Space War";
	const unsigned int screenWidth = 1920;
	const unsigned int screenHeight = 1080;
	const sf::Vector2u windowSize(screenWidth, screenHeight);

	if (!icon.loadFromFile("Assets/Texture/Icon/icon.png"))
	{
#ifdef _DEBUG
		std::cout << "icon not found" << std::endl;
#endif
		return EXIT_FAILURE;
	}

	//init shared object
	SharedObject Obj;
	Obj.Window = new Window(windowTitle, windowSize, icon);
	Obj.AudioManager = new AudioManager;
	Obj.SceneManager = new SceneManager;

	Game game(Obj);

	game.run();
	
	return EXIT_SUCCESS;
}
