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
		return -1;
	}
	
	Game game(windowTitle, windowSize, icon);

	game.GetSceneManager()->run(SceneManager::build<SplashScreen>(*game.GetSceneManager(), *game.GetWindow(), true));

	while(!game.GetWindow()->isDone() && game.GetSceneManager()->running())
	{
		//Window loop here
		game.GetSceneManager()->nextScene();
		game.GetSceneManager()->Update();
		game.GetSceneManager()->Draw();
		game.RestartClock();
	}
	
	//Game game()
}
