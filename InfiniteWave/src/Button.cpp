#include "Button.h"

#include <SFML/Window/Mouse.hpp>

#include "Config.h"


void Button::Setup(const std::string& idlePath, const std::string& hoverPath, const std::string& activePath, float sizeFact, sf::Vector2f pos)
{
	btnIdleTex.loadFromFile(idlePath);
	btnHoverTex.loadFromFile(hoverPath);
	btnActiveTex.loadFromFile(activePath);

	btn.setSize(sf::Vector2f(static_cast<float>(btnIdleTex.getSize().x), static_cast<float>(btnIdleTex.getSize().y)));
	btn.setScale(sizeFact, sizeFact);
	btn.setOrigin(btn.getSize().x/2, btn.getSize().y/2);
	btn.setPosition(pos);

	btnState = IDLE_BTN;
}

sf::RectangleShape* Button::getDraw()
{
	return &btn;
}

void Button::Update(sf::Vector2f mousePos)
{
	btnState = IDLE_BTN;
	if(btn.getGlobalBounds().contains(mousePos))
	{
		btnState = HOVER_BTN;
	}

	switch (btnState)
	{
	case IDLE_BTN:
		{
		btn.setTexture(&btnIdleTex);
	} break;
	case HOVER_BTN:
		{
		btn.setTexture(&btnHoverTex);
	} break;
	case ACTIVE_BTN:
		{
		btn.setTexture(&btnActiveTex);
	} break;
	default: break;
	}
}

bool Button::isPressed() const
{
	return btnState == ACTIVE_BTN ? true : false;
}

bool Button::isHover() const
{
	return btnState == HOVER_BTN ? true : false;
}

void Button::Click()
{
	btnState = ACTIVE_BTN;
}
