#pragma once
#ifndef BUTTON_H_
#define BUTTON_H_

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

enum class ButtonState { IDLE_BTN, HOVER_BTN, ACTIVE_BTN, FIRST_STATE, SECOND_STATE};


class Button
{
public:
	Button() = default;
	
	void Setup(const std::string& idle_path, const std::string& hover_path, const std::string& active_path, float scale_factor, sf::Vector2f position);
	void Update(sf::Vector2f mouse_pos);
	void Click();

	bool IsPressed() const;
	bool IsHover() const;
	sf::RectangleShape* GetDraw();

protected:
	sf::RectangleShape mButtonRect;
	ButtonState mButtonState;

private:
	sf::Texture mButtonIdleTex;
	sf::Texture mButtonHoverTex;
	sf::Texture mButtonActiveTex;
};

#endif

