#include "Window.h"

Window::Window(const std::string& w_title, const sf::Vector2u& w_size, const sf::Image& w_icon)
{
	p_winSize = w_size;
	p_winTitle = w_title;
	p_winIcon = w_icon;
	p_isFullScreen = true;
	p_isDone = false;

	Create();
}

Window::~Window()
{
	Destroy();
}

void Window::Create()
{
	const auto style = p_isFullScreen ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Close;

	window.create({ p_winSize.x, p_winSize.y }, p_winTitle, style);
	window.setIcon(p_winIcon.getSize().x, p_winIcon.getSize().y, p_winIcon.getPixelsPtr());
	//Set FPS Max to 60fps
	window.setFramerateLimit(60);
}

void Window::Destroy()
{
	window.close();
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

void Window::ToggleFullScreen()
{
	p_isFullScreen = !p_isFullScreen;
	Destroy();
	Create();
}

void Window::Draw(sf::Drawable& Object)
{
	window.draw(Object);
}

void Window::BeginDraw()
{
	window.clear();
}

void Window::EndDraw()
{
	window.display();
}

bool Window::isDone()
{
	return p_isDone;
}

bool Window::isFullScreen()
{
	return p_isFullScreen;
}

sf::Vector2u Window::GetWindowSize()
{
	return p_winSize;
}




