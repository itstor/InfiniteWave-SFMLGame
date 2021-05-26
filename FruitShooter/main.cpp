#include "Window.h"

int main()
{
	sf::Image icon;
	std::string windowTitle = "Fruit Shooter";
	sf::Vector2u windowSize(1080, 1920);
	bool isFullscreen = true;
	
	icon.loadFromFile("/Texture/Icon/icon.png");
	Window window(windowTitle, windowSize, icon, isFullscreen);
	
}