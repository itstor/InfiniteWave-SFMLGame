#include "ToggleButton.h"

#include <iostream>

void ToggleButton::Setup(const std::string & first_state_path, const std::string & second_state_path, float scale_factor, sf::Vector2f position, ButtonState current_state)
{
	mFirstStateTex.loadFromFile(first_state_path);
	mSecondStateTex.loadFromFile(second_state_path);

	mButtonRect.setSize(sf::Vector2f(static_cast<float>(mFirstStateTex.getSize().x), static_cast<float>(mFirstStateTex.getSize().y)));
	mButtonRect.setScale(scale_factor, scale_factor);
	mButtonRect.setOrigin(mButtonRect.getSize().x / 2, mButtonRect.getSize().y / 2);
	mButtonRect.setPosition(position);

	mButtonState = current_state;
}

void ToggleButton::Update(sf::Vector2f mouse_pos)
{
	mIsHover = false;
	
	if(mButtonRect.getGlobalBounds().contains(mouse_pos))
	{
		mIsHover = true;
	}

	
	if (mButtonState == ButtonState::FIRST_STATE)
	{
		mButtonRect.setTexture(&mFirstStateTex);
	}
	else if (mButtonState == ButtonState::SECOND_STATE)
	{
		mButtonRect.setTexture(&mSecondStateTex);
	}
}

bool ToggleButton::IsHover() const
{
	return mIsHover;
}

ButtonState ToggleButton::ToggleState()
{
	mButtonState = mButtonState == ButtonState::FIRST_STATE ? ButtonState::SECOND_STATE : ButtonState::FIRST_STATE;

	return mButtonState;
}

