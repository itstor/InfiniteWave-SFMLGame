#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <SFML/Graphics.hpp>

class Window
{
private:
	sf::Vector2u winSize;
	std::string winTitle;
	sf::Image winIcon;
	bool isFullscreen;

	void Create();
	void Render();
	void BeginRender();

public:
	sf::RenderWindow window;

	Window(const std::string& w_title, const sf::Vector2u& w_size, const sf::Image& w_icon, const bool& isFullscreen);
	void Update();
};

#endif

