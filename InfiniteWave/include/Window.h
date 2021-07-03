#pragma once
#ifndef WINDOW_H_
#define WINDOW_H_

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


class Window
{
public:
	Window(const std::string& winTitle, const sf::Vector2u& winSize, const sf::Image& winIcon);
	~Window();

	void BeginDraw();
	void EndDraw();

	void Update();
	void Destroy();

	bool isDone() const;
	sf::Vector2u GetWindowSize() const;
	sf::RenderWindow* GetRenderWindow();

	void ToggleFullScreen();

	void Draw(sf::Drawable& Object);

private:
	sf::RenderWindow mWindow;
	sf::Vector2u mWinSize;
	std::string mWinTitle;
	sf::Image mWinIcon;
	bool mIsDone;

	void Create();
};

#endif

