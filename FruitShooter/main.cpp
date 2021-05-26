#include "Window.h"
#include "Game.h"

int main()
{
	sf::Image icon;
	const std::string windowTitle = "Fruit Shooter";
	const sf::Vector2u windowSize(1920, 1080);
	const bool isFullscreen = false;
	
	icon.loadFromFile("Resource/Texture/Icon/icon.png");
	Window window(windowTitle, windowSize, icon, isFullscreen);
	window.Update();
	//Game game()
}