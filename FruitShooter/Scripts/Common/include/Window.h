#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


class Window
{
public:
	sf::RenderWindow window;

	Window(const std::string& w_title, const sf::Vector2u& w_size, const sf::Image& w_icon);
	~Window();

	void BeginDraw();
	void EndDraw();

	void Update();

	bool isDone();
	bool isFullScreen();
	sf::Vector2u GetWindowSize();

	void ToggleFullScreen();

	void Draw(sf::Drawable& Object);

private:
	sf::Vector2u p_winSize;
	std::string p_winTitle;
	sf::Image p_winIcon;
	bool p_isDone;
	bool p_isFullScreen;

	void Create();
	void Destroy();
};

#endif

