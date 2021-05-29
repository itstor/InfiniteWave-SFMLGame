#include "Window.h"
#include "Game.h"
#include <iostream>

int main()
{
	sf::Image icon;
	const std::string windowTitle = "Fruit Shooter";
	sf::Vector2u windowSize(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	
	if (!icon.loadFromFile("Assets/Texture/Icon/icon.png"))
	{
		std::cout << "Icon Not Found" << std::endl;
		return -1;
	}
	
	Game game(windowTitle, windowSize, icon);

	while(!game.GetWindow()->isDone())
	{
		game.HandleInput();
		game.Update();
		game.Render();
		game.RestartClock();
	}
	
	//Game game()
}