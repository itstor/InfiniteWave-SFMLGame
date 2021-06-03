#include "Window.h"
#include "Game.h"
#include <iostream>

#include "SplashScreen.h"

int main()
{
	sf::Image icon;
	const std::string windowTitle = "Space War";
	const unsigned int screenWidth = sf::VideoMode::getDesktopMode().width;
	const unsigned int screenHeight = sf::VideoMode::getDesktopMode().height;
	const sf::Vector2u windowSize(screenWidth, screenHeight);

	if (!icon.loadFromFile("Assets/Texture/Icon/icon.png"))
	{
#ifdef _DEBUG
		std::cout << "Icon Not Found" << std::endl;
#endif
		return EXIT_FAILURE;
	}

	Game game(windowTitle, windowSize, icon);

	//Run game with SplashScreen as the first scene
	game.GetSceneManager()->run(SceneManager::build<SplashScreen>(*game.GetSceneManager(), *game.GetWindow(), true));

	while (!game.GetWindow()->isDone())
	{
		//Window loop here
		game.GetSceneManager()->nextScene(); //try to change the scene
		game.GetSceneManager()->Update(); //update current scene
		game.GetSceneManager()->Draw(); //render current scene
		game.RestartClock(); //restart clock to randomize the random function
	}
}
