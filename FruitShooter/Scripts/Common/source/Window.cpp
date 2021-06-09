#include "Window.h"
#include "Config.h"

Window::Window(const std::string& winTitle, const sf::Vector2u& winSize, const sf::Image& winIcon)
{
	mWinSize = winSize;
	mWinTitle = winTitle;
	mWinIcon = winIcon;
	mIsFullScreen = conf::isFullscreen;
	mIsDone = false;

	Create();
}

Window::~Window()
{
	Destroy();
}

void Window::Create()
{
	const auto style = mIsFullScreen ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Close;

	mWindow.create({ mWinSize.x, mWinSize.y }, mWinTitle, style);
	mWindow.setIcon(mWinIcon.getSize().x, mWinIcon.getSize().y, mWinIcon.getPixelsPtr());
	//Set FPS Max to 60fps
	mWindow.setFramerateLimit(60);
}

void Window::Destroy()
{
	mIsDone = true;
	mWindow.close();
}

void Window::Update()
{
	sf::Event evnt{};

	while (mWindow.pollEvent(evnt))
	{
		switch (evnt.type)
		{
		case sf::Event::Closed: Destroy(); break;
		default: break;
		}
	}
}

void Window::ToggleFullScreen()
{
	mIsFullScreen = !mIsFullScreen;
	Destroy();
	Create();
}

sf::RenderWindow* Window::GetRenderWindow()
{
	return &mWindow;
}


void Window::Draw(sf::Drawable& Object)
{
	mWindow.draw(Object);
}

void Window::BeginDraw()
{
	mWindow.clear();
}

void Window::EndDraw()
{
	mWindow.display();
}

bool Window::isDone()
{
	return mIsDone;
}

bool Window::isFullScreen() const
{
	return mIsFullScreen;
}

sf::Vector2u Window::GetWindowSize() const
{
	return mWinSize;
}