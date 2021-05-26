#include "Window.h"

Window::Window(const std::string& w_title, const sf::Vector2u& w_size, const sf::Image& w_icon, const bool& isFullscreen)
{
	winSize = w_size;
	winTitle = w_title;
	winIcon = w_icon;
	this->isFullscreen = isFullscreen;

	Create();
}

void Window::Create()
{
	const auto style = isFullscreen ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Close;

	window.create({ winSize.x, winSize.y }, winTitle, style);
	//Set FPS Max to 60fps
	window.setFramerateLimit(60);
}

void Window::Update()
{
	sf::Event evnt{};
	while (window.pollEvent(evnt))
	{
		switch (evnt.type)
		{
		case sf::Event::Closed: window.close(); break;
		default: break;
		}
	}
}

void Window::Render()
{
	window.display();
}

