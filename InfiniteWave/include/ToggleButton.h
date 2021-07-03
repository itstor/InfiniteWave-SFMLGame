#pragma once
#ifndef TOGGLE_BUTTON_H_
#define TOGGLE_BUTTON_H_

#include <string>

#include "Button.h"


class ToggleButton: public Button
{
public:
	ToggleButton() = default;

	void Setup(const std::string& first_state_path, const std::string& second_state_path, float scale_factor, sf::Vector2f position, ButtonState current_state = ButtonState::FIRST_STATE);

	void Update(sf::Vector2f mouse_pos);
	ButtonState ToggleState();

	
	bool IsHover() const;

private:
	bool mIsHover;
	
	sf::Texture mFirstStateTex;
	sf::Texture mSecondStateTex;
};


#endif