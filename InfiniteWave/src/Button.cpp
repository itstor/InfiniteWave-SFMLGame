#include "Button.h"

#include <SFML/Window/Mouse.hpp>

#include "Config.h"


void Button::Setup(const std::string& idle_path, const std::string& hover_path, const std::string& active_path, float scale_factor, sf::Vector2f position)
{
	mButtonIdleTex.loadFromFile(idle_path);
	mButtonHoverTex.loadFromFile(hover_path);
	mButtonActiveTex.loadFromFile(active_path);

	mButtonRect.setSize(sf::Vector2f(static_cast<float>(mButtonIdleTex.getSize().x), static_cast<float>(mButtonIdleTex.getSize().y)));
	mButtonRect.setScale(scale_factor, scale_factor);
	mButtonRect.setOrigin(mButtonRect.getSize().x/2, mButtonRect.getSize().y/2);
	mButtonRect.setPosition(position);

	mButtonState = ButtonState::IDLE_BTN;
}

sf::RectangleShape* Button::GetDraw()
{
	return &mButtonRect;
}

void Button::Update(sf::Vector2f mouse_pos)
{
	mButtonState = ButtonState::IDLE_BTN;
	if(mButtonRect.getGlobalBounds().contains(mouse_pos))
	{
		mButtonState = ButtonState::HOVER_BTN;
	}

	switch (mButtonState)
	{
	case ButtonState::IDLE_BTN:
		{
		mButtonRect.setTexture(&mButtonIdleTex);
	} break;
	case ButtonState::HOVER_BTN:
		{
		mButtonRect.setTexture(&mButtonHoverTex);
	} break;
	case ButtonState::ACTIVE_BTN:
		{
		mButtonRect.setTexture(&mButtonActiveTex);
	} break;
	default: break;
	}
}

bool Button::IsPressed() const
{
	return mButtonState == ButtonState::ACTIVE_BTN ? true : false;
}

bool Button::IsHover() const
{
	return mButtonState == ButtonState::HOVER_BTN ? true : false;
}

void Button::Click()
{
	mButtonState = ButtonState::ACTIVE_BTN;
}
